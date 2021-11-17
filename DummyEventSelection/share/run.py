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
        pass

    def add_output_vec(self, output_vec, args):
        output_vec.append("/Event/OEC")

    def init(self, toptask, args):

        import DummyEventSelection

        selectionalg = toptask.createAlg("SelectionAlg")


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
