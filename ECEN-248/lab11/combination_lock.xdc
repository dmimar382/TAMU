#LEDs
#IO_L23P_T3_35
set_property PACKAGE_PIN M14 [get_ports {LEDs[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs[0]}]

##IO_L23N_T3_35
set_property PACKAGE_PIN M15 [get_ports {LEDs[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs[1]}]

##IO_0_35
set_property PACKAGE_PIN G14 [get_ports {LEDs[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs[2]}]

##IO_L3N_T0_DQS_AD1N_35
set_property PACKAGE_PIN D18 [get_ports {LEDs[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDs[3]}]

##Pmod Header JB
##IO_L15N_T2_DQS_34
set_property PACKAGE_PIN U20 [get_ports {JB[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {JB[0]}]

##IO_L15P_T2_DQS_34
set_property PACKAGE_PIN T20 [get_ports {JB[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {JB[1]}]

##IO_L16N_T2_34
set_property PACKAGE_PIN W20 [get_ports {JB[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {JB[2]}]



##BUTTONS
##IO_L20N_T3_34
set_property PACKAGE_PIN V16 [get_ports {Reset}]
set_property IOSTANDARD LVCMOS33 [get_ports {Reset}]
##IO_L20N_T3_34
set_property PACKAGE_PIN R18 [get_ports {Key1}]
set_property IOSTANDARD LVCMOS33 [get_ports {Key1}]

##IO_L20N_T3_34
set_property PACKAGE_PIN P16 [get_ports {Key2}]
set_property IOSTANDARD LVCMOS33 [get_ports {Key2}]

##Switches
#IO_L19N_T3_VREF_35
set_property PACKAGE_PIN G15 [get_ports {Password[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Password[0]}]

#IO_L24P_T3_34
set_property PACKAGE_PIN P15 [get_ports {Password[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Password[1]}]

#IO_L4N_T0_34
set_property PACKAGE_PIN W13 [get_ports {Password[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Password[2]}]

#IO_L9P_T1_DQS_34
set_property PACKAGE_PIN T16 [get_ports {Password[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Password[3]}]


##Clock signal
##IO_L11P_T1_SRCC_35	
set_property PACKAGE_PIN L16 [get_ports Clk]
set_property IOSTANDARD LVCMOS33 [get_ports Clk]
create_clock -add -name sys_clk_pin -period 20.00 -waveform {0 8} [get_ports Clk]