from controller import Controller
from transmitter import Transmitter
from window import Window

controller = Controller()
transmitter = Transmitter()
window = Window()

while True:
    if controller.type == "Controller":
        axis_inputs = controller.get_axis_inputs()
        button_inputs = controller.get_button_inputs()
        data = transmitter.encodeControllerData(axis_inputs, button_inputs)
    else:
        keyboard_inputs = controller.get_keyboard_inputs()
        data = transmitter.encodeKeyboardData(keyboard_inputs)
    
    transmitter.sendData(data)
    received_data = transmitter.receiveData()
    # received_data = {"Name" : "name", "Age": 0, "MagneticField": 0}

    transmitter.handleRequestedInputs(controller.type, button_inputs, keyboard_inputs, window.get_info())

    window.update_info(received_data, transmitter.ping)
    if window.update_display():
        break