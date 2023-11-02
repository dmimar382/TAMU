#This Xilinx Design Constraints (XDC) creates a mapping of
#the input and output ports from your top level
#module to the actual pins on the FPGA



##Switches
#SW0
set_property PACKAGE_PIN G15 [get_ports {W[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {W[0]}]

#SW1
set_property PACKAGE_PIN P15 [get_ports {W[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {W[1]}]

#SW2
set_property PACKAGE_PIN W13 [get_ports {En}]
set_property IOSTANDARD LVCMOS33 [get_ports {En}]

##LEDs
#LD0
set_property PACKAGE_PIN M14 [get_ports {Y[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Y[0]}]

#LD1
set_property PACKAGE_PIN M15 [get_ports {Y[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Y[1]}]

#LD2
set_property PACKAGE_PIN G14 [get_ports {Y[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Y[2]}]

#LD3
set_property PACKAGE_PIN D18 [get_ports {Y[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {Y[3]}]

