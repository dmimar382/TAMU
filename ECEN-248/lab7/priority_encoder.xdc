## This file is a general .xdc for the ZYBO Rev B board

##Buttons
##IO_L20N_T3_34 #Button0
set_property PACKAGE_PIN R18 [get_ports {W[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {W[0]}]

##IO_L24N_T3_34 #Button1
set_property PACKAGE_PIN P16 [get_ports {W[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {W[1]}]

##IO_L18P_T2_34 #Button2
set_property PACKAGE_PIN V16 [get_ports {W[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {W[2]}]

##IO_L7P_T1_34 #Button3
set_property PACKAGE_PIN Y16 [get_ports {W[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {W[3]}]

##LEDs
##IO_L23P_T3_35  #LED0
set_property PACKAGE_PIN M14 [get_ports {Y[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Y[0]}]

##IO_L23N_T3_35  #LED1
set_property PACKAGE_PIN M15 [get_ports {Y[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Y[1]}]

##IO_0_35  #LED2
set_property PACKAGE_PIN G14 [get_ports {zero}]
set_property IOSTANDARD LVCMOS33 [get_ports {zero}]

