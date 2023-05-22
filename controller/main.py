import socket
from udp_connect import fetchUDPAddress
from xbox_controller import XboxController
import time

# Define the target device and port
target_device = "Adafruit Metro M0"
TARGET_PORT = 6969
TARGET_IP = "192.169.0.8"

controller = XboxController()

while True:
    axis_inputs = controller.get_axis_inputs()
    button_inputs = controller.get_button_inputs()

    # Print the axis inputs
    print("Axis Inputs:")
    for axis_name, axis_value in axis_inputs.items():
        print(f"{axis_name}: {axis_value}")

    # Print the button inputs
    pressed_buttons = [button_name for button_name, button_state in button_inputs.items() if button_state]
    if pressed_buttons:
        print("Buttons pressed:", ", ".join(pressed_buttons))

    # Rest of your code here...
    time.sleep(1)
   

# # Create a UDP socket
# sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# sock.settimeout(0.01)  # Set a timeout value to limit the scan duration

# ip_address = None
# while ip_address == None:
#     ip_address = fetchUDPAddress(sock, TARGET_IP, TARGET_PORT)

# print(ip_address)

# sock.close()