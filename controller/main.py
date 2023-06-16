from controls import Controller
from transmitter import Transmitter
from window import Window

# Creates the objects that are needed
controller = Controller()
# transmitter = Transmitter()
window = Window()

# Main game loop
while True:
    # axis_inputs = controller.get_axis_inputs()
    # button_inputs = controller.get_button_inputs()
    # keyboard_inputs = controller.get_keyboard_inputs() # Handles pygame.quit()

    # if controller.type == "Controller":    
        # data = transmitter.encodeControllerData(axis_inputs, button_inputs)
    # else:
        # data = transmitter.encodeKeyboardData(keyboard_inputs)
    
    # transmitter.sendData(data)
    # received_data = transmitter.receiveData()
    received_data = {"Name" : "Kay", "Age": 224, "MagneticField": 1}

    # transmitter.handleRequestedInputs(controller.type, button_inputs, keyboard_inputs, window.get_info())

    window.update_info(received_data, 5)
    window.update_display()