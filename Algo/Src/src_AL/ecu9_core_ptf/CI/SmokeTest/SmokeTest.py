###########################################################
#
# @author Dobato, Gabriel ALDE-RT/EES5
# @date   03.02.2020
# @version 0.0.1
#
###########################################################

import os
import signal
import subprocess
import sys
from   target import Target

#
#
# Smoke Test A230
#     1.- Flash generated HEX with J-Flash
#     2.- Run GDB Server
#     3.- Run GDB Client test script 
#         a.- Check init context is called
#         b.- Check cyclic runnables are called cyclically
#         c.- Check if any exception is executed
#     4.- Terminate GDB Server
#

ecu_high = Target( )
ecu_high.flash( '../../Build/Bin/F0Bw16_App_default/F0Bw16_App_default_ALL.hex',
                '../../Build/ToolsSpecific/Cust/Bw/Bw16/J-Flash/FLM3_HIGH_ECU.jflash')
ecu_high.GDB().run_server()
ecu_high.GDB().run_client_test('../../Build/Bin/F0Bw16_App_default/F0Bw16_App_default.elf',
                               'GDB_Script.py')
ecu_high.GDB().terminate_server()

