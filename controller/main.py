import socket
from udp_connect import fetchUDPAddress
import controls

# Define the target device and port
target_device = "Adafruit Metro M0"
TARGET_PORT = 6969
TARGET_IP = "192.169.0.8"

while True:
    output = controls.get_button_events()
    if output != None:
        print(output)
        

# # Create a UDP socket
# sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# sock.settimeout(0.01)  # Set a timeout value to limit the scan duration

# ip_address = None
# while ip_address == None:
#     ip_address = fetchUDPAddress(sock, TARGET_IP, TARGET_PORT)

# print(ip_address)

# sock.close()