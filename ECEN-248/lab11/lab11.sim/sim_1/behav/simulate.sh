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
ExecStep $xv_path/bin/xsim combination_lock_fsm_tb_behav -key {Behavioral:sim_1:Functional:combination_lock_fsm_tb} -tclbatch combination_lock_fsm_tb.tcl -log simulate.log
