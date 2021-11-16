#!/usr/bin/env python
#-*- coding: utf-8 -*-
#-*- author: Tao Lin -*-

##############################################################################
# Import
##############################################################################
from Tutorial import JUNOApplication
from Tutorial import JUNOModule
from Tutorial import JUNODataBufferModule
from Tutorial import JUNORootInputModule
from Tutorial import JUNORootOutputModule

##############################################################################
# Module definition
##############################################################################

class MixingModule(JUNOModule):
    def __init__(self):
        pass

    def register_options(self, parser):
        pass

    def add_output_vec(self, output_vec, args):
        output_vec.append("/Event/OEC")

    def init(self, toptask, args):

        import DummyEventMixing

        mixingalg = toptask.createAlg("MixingAlg")

        rates = {"U238": 3.224, 
                 "Th232": 0.792,
                 "K40": 0.518}

        inputs = {}

        if args.input is None:
            inputs = {"U238": "@U238.list.txt",
                      "Th232": "@Th232.list.txt",
                      "K40": "@K40.list.txt"}
        else:
            # the format: --input U238:@filelist.txt
            # while in filelist.txt, it contains all the branches
            for f in args.input:
                k, v = f.split(":", 1)
                inputs[k] = v

        # expand the file list
        inputs_expanded = {}
        print(inputs)
        for k, v in inputs.items():
            filelist = []
            if not v.startswith("@"):
                filelist.append(v)
                inputs_expanded[k] = filelist
                continue
            # if it startswith @
            with open(v[1:]) as finput:
                for line in finput:
                    fn = line.strip()
                    filelist.append(fn)

            inputs_expanded[k] = filelist

        mixingalg.property("Rates").set(rates)
        mixingalg.property("Inputs").set(inputs_expanded)

##############################################################################
# Application
##############################################################################

import Sniper
# Sniper.setLogLevel(0)

juno_application = JUNOApplication(description="Event mixing")
juno_application.set_default_input_action("append")
juno_application.set_default_output("sample_oec.root")

databuffer_module = JUNODataBufferModule()
rootoutput_module = JUNORootOutputModule()
evtmixing_module = MixingModule()

juno_application.register(databuffer_module)
juno_application.register(rootoutput_module)

juno_application.register(evtmixing_module)


juno_application.run()
