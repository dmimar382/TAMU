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
ExecStep $xv_path/bin/xsim mux_4bit_4to1_tb_behav -key {Behavioral:sim_1:Functional:mux_4bit_4to1_tb} -tclbatch mux_4bit_4to1_tb.tcl -log simulate.log
