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
ExecStep $xv_path/bin/xelab -wto ea420be2a0cc4df2a262c0a9fa7a3b48 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot four_bit_alu_tb_behav xil_defaultlib.four_bit_alu_tb xil_defaultlib.glbl -log elaborate.log
