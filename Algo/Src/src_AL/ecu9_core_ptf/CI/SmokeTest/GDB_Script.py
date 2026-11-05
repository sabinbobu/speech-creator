###########################################################
#
# @author Dobato, Gabriel ALDE-RT/EES5
# @date   03.02.2020
# @version 0.0.1
#
###########################################################

import os
import sys
import platform
import gdb
import time
import logging


class GDB_Handler:
    def __init__(self):
        try:
            """Workauround. Get Object Data Base from SmokeTest
               through temporal file"""
            self.temp_file = open("st_temp.txt",'r')
            self.odb = self.temp_file.readlines()[0].strip()
            self.temp_file.close()
        except:
            print("Something went wrong while reading elf path")
            sys.exit(1)

        """Remove temporary file"""
        if os.path.exists(self.temp_file.name):
            os.remove(self.temp_file.name)
        else:
            print('{} does not exit'.format(self.temp_file.name))

        self.execute('file {}'.format(self.odb))
        self.execute('set pagination off')

    def connect_to_server(self):
        """ TCP Port hardcoded, need rework"""
        self.execute('target remote localhost:2331')
        self.execute('monitor reset')
        self.execute('set confirm off')

    def load_odb(self):
        self.execute('load')

    @staticmethod
    def execute(command, from_tty = False, to_string = False):
        gdb.execute('{}'.format(command), from_tty, to_string )

    def terminate(self):
        gdb.execute('quit')

    def __del__(self):
        pass
        #try:
        #    os.remove(self.temp_file.name)
        #except:
        #    print("Something went wrong while deleting temp file")

    class Variable:
        def __init__(self,var):
            self.var = var

        def write(self, value):
            GDB_Handler.execute('set {} = {}'.format(self.var,value))

        def read(self):
            return gdb.parse_and_eval(self.var)

    class Flow:
        """ Go to next instruction(source line), diving into function"""

        @staticmethod
        def step():
            GDB_Handler.execute('step')

        """ Go to next instruction(source line) but don't dive into functions"""
        @staticmethod
        def over():
            GDB_Handler.execute('next')

        @staticmethod
        def run_until_return():
            GDB_Handler.execute('finish')

        @staticmethod
        def run():
            GDB_Handler.execute('continue')

        @staticmethod
        def run_until(function):
            GDB_Handler.execute('until {}'.format(function))

        @staticmethod
        def stop():
            GDB_Handler.execute('interrupt')

        @staticmethod
        def reset():
            GDB_Handler.execute('monitor reset')

        @staticmethod
        def wait(sec):
            time.sleep(sec)

    class Breakpoint:
        def __init__(self, gdb_breakpoint):
            self.gdb_breakpoint      = gdb.Breakpoint(gdb_breakpoint);
            self.gdb_breakpoint_name = gdb_breakpoint;

        """Return True if this Breakpoint object is valid, False otherwise.
           A Breakpoint object can become invalid if the user deletes the breakpoint.
           In this case, the object still exists, but the underlying breakpoint does not. 
           In the cases of watchpoint scope, the watchpoint remains valid even if 
           execution of the inferior leaves the scope of that watchpoint."""
        def is_valid(self):
            return self.gdb_breakpoint.is_valid()

        """Permanently deletes the gdb breakpoint. This also invalidates the Python Breakpoint object. 
           Any further access to this object's attributes or methods will raise an error."""
        def delete(self):
            self.gdb_breakpoint.delete()
            #GDB_Handler.execute('clear {}'.format(self.gdb_breakpoint_name))

        @staticmethod
        def remove_all():
            GDB_Handler.execute('clear')

        """This attribute is True if the breakpoint is enabled, and False otherwise.
           This attribute is writable. """
        def enabled(self):
            return self.gdb_breakpoint.enabled()

        def hit_count(self):
            return self.gdb_breakpoint.hit_count

        def location(self):
            return self.gdb_breakpoint.location

        """This attribute holds a breakpoint expression, as specified by the user. 
           It is a string. If the breakpoint does not have an expression 
           (the breakpoint is not a watchpoint) the attribute's value is None.
           This attribute is not writable."""
        def expression(self):
            return self.gdb_breakpoint.expression

def EmulateRxCanReceived(value):
    if value is True:
        GDB_Handler.execute('set CddCanNm_GblNmMessageReceived = {}'.format(1))
        pass
    else:
        GDB_Handler.execute('set CddCanNm_GblNmMessageReceived = {}'.format(0))
        pass



########################################################################################
#
# Basic Test based on GDB
#
########################################################################################

#
#Init gdb handler
#
gdb_handler = GDB_Handler()
gdb_handler.connect_to_server()
gdb_handler.load_odb()
gdb_handler.Flow.reset()

#
#Init log File
#
logging.basicConfig(filename='SmokeTest.log',level=logging.DEBUG, filemode='w')
logging.info('------- Running basic smoke test -----')

#
#Init test env
#

#Assign breakpoint-tick
breakpoint_tick = 'TASK_OsConf_OsTask_OsTask_Timing_2_100ms'

#Emulate that target gets CAN frames to avoid sleep Mode
EmulateRxCanReceived(True)

#run until main
main_BP = gdb_handler.Breakpoint('main')
gdb_handler.Flow.run()
main_BP.delete()

#
#Check Init Context
#

#DriverInitList Zero/One/Two

DriverInitList_BP = gdb_handler.Breakpoint('Cdd_Init')
EmulateRxCanReceived(True)
gdb_handler.Flow.run_until(breakpoint_tick)

if DriverInitList_BP.hit_count() is not 1 :
    logging.error('DriverInitList not executed')
else:
    logging.info('DriverInitList executed')
DriverInitList_BP.delete()

#Application Init
AppInit_BP = gdb_handler.Breakpoint('CddSpi_Start')
EmulateRxCanReceived(True)
gdb_handler.Flow.run_until(breakpoint_tick)

if AppInit_BP.hit_count() is not 1 :
    logging.error('AppInit not executed')
else:
    logging.info('AppInit executed')
AppInit_BP.delete()

#
#Check Cyclic Context
#

#1ms cyclic runnable
cyclic_1ms_BP = gdb_handler.Breakpoint('CddSpi_Cycle1ms')

for x in range(0,10):
    gdb_handler.Flow.run_until(breakpoint_tick)
    EmulateRxCanReceived(True)

if cyclic_1ms_BP.hit_count() is not 9 :
    logging.error('Cyclic runnable not executed the expected cycles')
else:
    logging.info('Cyclic runnable executed the expected cycles')

cyclic_1ms_BP.delete()


#
#Check no exception is excuted
#
NMI_Fault_BP   = gdb_handler.Breakpoint('Os_NMI_Fault_Handler')
Hard_Fault_BP  = gdb_handler.Breakpoint('Os_Hard_Fault_Exception_Handler')
MPU_Fault_BP   = gdb_handler.Breakpoint('Os_MPU_Fault_Handler')
BUS_Fault_BP   = gdb_handler.Breakpoint('Os_BUS_Fault_Handler')
USAGE_Fault_BP = gdb_handler.Breakpoint('Os_USAGE_Fault_Handler')

for x in range(0,50):
    gdb_handler.Flow.run_until(breakpoint_tick)
    EmulateRxCanReceived(True)

if NMI_Fault_BP.hit_count() is not 0 :
    logging.error('NMI Fault exception executed')
else:
    logging.info('NMI Fault exception not executed')

if Hard_Fault_BP.hit_count() is not 0 :
    logging.error('Hard Fault exception executed')
else:
    logging.info('Hard Fault exception not executed')

if MPU_Fault_BP.hit_count() is not 0 :
    logging.error('MPU Fault exception executed')
else:
    logging.info('MPU Fault exception not executed')

if BUS_Fault_BP.hit_count() is not 0 :
    logging.error('BUS Fault exception executed')
else:
    logging.info('BUS Fault exception not executed')

if USAGE_Fault_BP.hit_count() is not 0 :
    logging.error('USAGE Fault exception executed')
else:
    logging.info('USAGE Fault exception not executed')


#Stop session
gdb_handler.terminate()
