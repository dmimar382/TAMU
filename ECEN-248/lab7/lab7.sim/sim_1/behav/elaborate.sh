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
ExecStep $xv_path/bin/xelab -wto 6fa55d95a4344d95bae3fb1d2001d963 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot mux_4bit_4to1_tb_behav xil_defaultlib.mux_4bit_4to1_tb xil_defaultlib.glbl -log elaborate.log
