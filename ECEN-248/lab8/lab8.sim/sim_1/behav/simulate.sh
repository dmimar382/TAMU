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
ExecStep $xv_path/bin/xsim add_2bit_tb_behav -key {Behavioral:sim_1:Functional:add_2bit_tb} -tclbatch add_2bit_tb.tcl -view /home/ugrads/d/dmimar382/lab8/sr_latch_tb_behav.wcfg -log simulate.log
