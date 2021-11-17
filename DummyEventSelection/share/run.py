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

class SelectionModule(JUNOModule):
    def __init__(self):
        pass

    def register_options(self, parser):
        parser.add_argument("--delay-energy-min", type=float, default=1.9, help='Delay Energy min (MeV)')
        parser.add_argument("--delay-energy-max", type=float, default=2.5, help='Delay Energy max (MeV)')
        parser.add_argument("--prompt-energy-min", type=float, default=0.7, help='Prompt Energy min (MeV)')
        parser.add_argument("--prompt-energy-max", type=float, default=12., help='Prompt Energy max (MeV)')
        parser.add_argument("--time-cut", type=float, default=0.001, help='time cut (s)')
        parser.add_argument("--dist-cut", type=float, default=1.5, help='distance cut (m)')
        pass

    def add_output_vec(self, output_vec, args):
        output_vec.append("/Event/OEC")

    def init(self, toptask, args):

        buffermgr = toptask.findSvc("BufferMemMgr")
        buffermgr.property("TimeWindow").set([-1,1])

        import DummyEventSelection

        selectionalg = toptask.createAlg("SelectionAlg")
        selectionalg.property("DelayEnergyRange").set([args.delay_energy_min, args.delay_energy_max])
        selectionalg.property("PromptEnergyRange").set([args.prompt_energy_min, args.prompt_energy_max])
        selectionalg.property("TimeCut").set(args.time_cut) # 1ms = 0.001s
        selectionalg.property("DistanceCut").set(args.dist_cut) # 1.5m

##############################################################################
# Application
##############################################################################

import Sniper
# Sniper.setLogLevel(0)

juno_application = JUNOApplication(description="Event Selection")
juno_application.set_default_input("sample_oec.root")

databuffer_module = JUNODataBufferModule()
rootinput_module = JUNORootInputModule()
selection_module = SelectionModule()

juno_application.register(databuffer_module)
juno_application.register(rootinput_module)

juno_application.register(selection_module)


juno_application.run()
