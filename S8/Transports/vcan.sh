sudo modprobe vcan # Load virtual CAN Kernel module
sudo ip link add dev vcan0 type vcan # Add virtual CAN socket called vcan0
sudo ip link set up vcan0 # Set vcan0 up

sudo modprobe can_raw
