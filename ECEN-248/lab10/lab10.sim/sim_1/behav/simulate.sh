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
ExecStep $xv_path/bin/xsim cla_16bit_tb_behav -key {Behavioral:sim_1:Functional:cla_16bit_tb} -tclbatch cla_16bit_tb.tcl -log simulate.log
