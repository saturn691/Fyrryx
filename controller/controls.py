import pygame
import sys
from time import sleep

class Controller:
    def __init__(self):
        # Initialize Pygame
        pygame.init()
        pygame.joystick.init()
        self.type = "Controller"

        try:
            self.controller = pygame.joystick.Joystick(0)
            self.controller.init()
            self.dpad_state = (0, 0)

        except pygame.error:
            print("WARNING: No controller found. Proceeding with keyboard controller (WASD to move, arrow keys to steer)")
            self.type = "Keyboard"

    def get_axis_inputs(self):
        if self.type != "Controller":
            return None
        
        # Get the current state of the controller
        pygame.event.pump()

        # Initialize the dictionary to store axis inputs
        axis_inputs = {}

        # Mapping of axis indices to Xbox names
        axis_mapping = {
            0: "Left Stick X",
            1: "Left Stick Y",
            2: "Right Stick X",
            3: "Right Stick Y",
            4: "Left Trigger",
            5: "Right Trigger"
        }

        # Get the values of each axis
        for axis_index, axis_name in axis_mapping.items():
            axis_value = self.controller.get_axis(axis_index)
            axis_inputs[axis_name] = axis_value

        return axis_inputs

    def get_button_inputs(self):
        if self.type != "Controller":
            return None
        
        # Get the current state of the controller
        pygame.event.pump()

        # Initialize the dictionary to store button inputs
        button_inputs = {}

        # Mapping of button indices to Xbox names
        button_mapping = {
            0: "A",
            1: "B",
            2: "X",
            3: "Y",
            4: "LB",
            5: "RB",
            6: "Back",
            7: "Start",
            8: "Left Stick",
            9: "Right Stick"
        }

        # Get the state of each button
        for button_index, button_name in button_mapping.items():
            button_state = self.controller.get_button(button_index)
            button_inputs[button_name] = button_state

        # Handle D-pad inputs
        hat = self.controller.get_hat(0)
        dpad_changed = hat != self.dpad_state
        self.dpad_state = hat

        dpad_inputs = {
            (1, 0): "D-pad Right",
            (-1, 0): "D-pad Left",
            (0, 1): "D-pad Up",
            (0, -1): "D-pad Down",
            (0, 0): None  # No D-pad input
        }

        if dpad_changed:
            for dpad_state, dpad_name in dpad_inputs.items():
                if self.dpad_state == dpad_state:
                    if dpad_name is not None:
                        button_inputs[dpad_name] = 1
                else:
                    if dpad_name is not None:
                        button_inputs[dpad_name] = 0

        # Handle combined D-pad inputs
        if self.dpad_state == (1, 1):
            button_inputs["D-pad Up"] = 1
            button_inputs["D-pad Right"] = 1
        elif self.dpad_state == (-1, 1):
            button_inputs["D-pad Up"] = 1
            button_inputs["D-pad Left"] = 1
        elif self.dpad_state == (1, -1):
            button_inputs["D-pad Down"] = 1
            button_inputs["D-pad Right"] = 1
        elif self.dpad_state == (-1, -1):
            button_inputs["D-pad Down"] = 1
            button_inputs["D-pad Left"] = 1
        
        return button_inputs
    
    def get_keyboard_inputs(self):
        keyboard_inputs = []

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                keyboard_inputs.append(event.key)
                print(event.key)

        return keyboard_inputs