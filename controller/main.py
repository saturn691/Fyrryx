from xbox_controller import XboxController
from transmitter import Transmitter
from window import Window

# Define the target port and IP
TARGET_PORT = 6969
TARGET_IP = "192.169.0.8"

controller = XboxController()
transmitter = Transmitter(TARGET_IP, TARGET_PORT)
window = Window()

while True:
    axis_inputs = controller.get_axis_inputs()
    button_inputs = controller.get_button_inputs()

    transmitter.sendData(axis_inputs, button_inputs)
    received_data = transmitter.receiveData()

    # received_data = {"Name" : "name", "Age": 0, "MagneticField": "up"}
    if button_inputs["LB"] and button_inputs["RB"]:
        print(received_data)

    if received_data != None:
        current_data = received_data 

    window.update_info(current_data, transmitter.ping)
    if window.update_display():
        break   