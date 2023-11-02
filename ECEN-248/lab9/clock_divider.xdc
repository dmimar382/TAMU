##Clock signal
##IO_L11P_T1_SRCC_35	
set_property PACKAGE_PIN L16 [get_ports ClkIn]
set_property IOSTANDARD LVCMOS33 [get_ports ClkIn]
create_clock -add -name sys_clk_pin -period 8.00 -waveform {0 4} [get_ports ClkIn]

##Pmod Header JB
##IO_L15N_T2_DQS_34
set_property PACKAGE_PIN U20 [get_ports {ClkOut[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {ClkOut[0]}]

##IO_L15P_T2_DQS_34
set_property PACKAGE_PIN T20 [get_ports {ClkOut[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {ClkOut[1]}]

##IO_L16N_T2_34
set_property PACKAGE_PIN W20 [get_ports {ClkOut[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {ClkOut[2]}]

##IO_L16P_T2_34
set_property PACKAGE_PIN V20 [get_ports {ClkOut[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {ClkOut[3]}]
