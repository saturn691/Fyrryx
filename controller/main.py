from xbox_controller import XboxController
from transmitter import Transmitter
from window import Window

controller = XboxController()
transmitter = Transmitter()
window = Window()

while True:
    axis_inputs = controller.get_axis_inputs()
    button_inputs = controller.get_button_inputs()

    transmitter.sendData(axis_inputs, button_inputs)
    received_data = transmitter.receiveData()

    # received_data = {"Name" : "name", "Age": 0, "MagneticField": "up"}

    if button_inputs["LB"] and button_inputs["RB"]:
        print(window.get_info())

    window.update_info(received_data, transmitter.ping)
    if window.update_display():
        break   