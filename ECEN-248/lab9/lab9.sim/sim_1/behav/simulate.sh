#!/bin/sh -f
xv_path="/softwares/Linux/xilinx/Vivado/2015.2"
ExecStep()
{
"$@"
RETVAL=$?
if [ $RETVAL -ne 0 ]
then
exit $RETVAL
fi
}
ExecStep $xv_path/bin/xsim bounce_tb_behav -key {Behavioral:sim_1:Functional:bounce_tb} -tclbatch bounce_tb.tcl -view /home/ugrads/d/dmimar382/ecen248/lab9/up_counter_tb_behav.wcfg -log simulate.log
