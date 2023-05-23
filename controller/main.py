import socket
from xbox_controller import XboxController
from transmitter import Transmitter

# Define the target port and IP
TARGET_PORT = 6969
TARGET_IP = "192.169.0.8"

controller = XboxController()
transmitter = Transmitter(TARGET_IP, TARGET_PORT)

while True:
    axis_inputs = controller.get_axis_inputs()
    button_inputs = controller.get_button_inputs()
    transmitter.handleInputs(axis_inputs, button_inputs)
    transmitter.receiveData()
   
sock.close()