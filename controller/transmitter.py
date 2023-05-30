"""*********************************************
Fyrryx UDP Protocol

Data is encoded into JSON format before sending/recieving, except for pings ("ping" is answered by "pong").
JSON will look something like this: {"key1":"value1","key2":"value2"}.
To encode/decode in python, "json" is used
To encode/decode in CPP, "ArduinoJson.h" is used (located in /headers/ArduinoJson.h)
*********************************************"""
import socket
import json
import time

class Transmitter:
    def __init__(self):
        # Create a UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(1)  # Set a timeout value to limit the scan duration
        
        self.port = 6969
        self.ping = 0
        self.packet_interval = 0.1 # Interval between packets in seconds
        self.send_time = 0

        self.ip_address = self.findUDPAddress()
        self.screenshot_button_held = False

    # Blocking function that will continiously search for the server
    def findUDPAddress(self):
        target_ip_address = input("Enter server address (192.168.0.XX): ")
        if target_ip_address.isnumeric():
            target_ip_address = f"192.168.0.{target_ip_address}"
        
        for i in range(10):
            if self.checkAddress((target_ip_address, self.port)):
                break
        else:
            print("Couldn't connect to server. Please try again.\n")
            return self.findUDPAddress()

        print("Connection established at IP: " + target_ip_address)

        return target_ip_address

    # Returns True if we can connect to the IP address at port using socket
    def checkAddress(self, server_address):
        try:
            start_time = time.time()

            self.sock.sendto("ping".encode(), server_address)
            print("Sent ping to server: " + server_address[0])
            data, addr = self.sock.recvfrom(1024)

            end_time = time.time()
            
            ping = (end_time - start_time) * 1000
            self.ping = ping
            
            return True
        
        except:
            return False
        

    # Sends data to the server to be processed and handles resetting
    def sendData(self, axis_inputs, button_inputs):
        if self.send_time + self.packet_interval > time.time():
            return
        self.send_time = time.time()
        
        if button_inputs["Back"] and button_inputs["Start"]:
            # Reset the connection
            print("Connection reset")
            self.ip_address = self.findUDPAddress()

        data = {
            "Movement X" : axis_inputs["Left Stick X"],
            "Movement Y" : axis_inputs["Left Stick Y"],
            "Turning" : axis_inputs["Right Stick X"],
            "Gas" : axis_inputs["Right Trigger"],
            "Reverse" : axis_inputs["Left Trigger"],
            "Boost" : button_inputs["A"],
            "Brake" : button_inputs["B"]
        }    

        json_data = json.dumps(data)  
        print(json_data)

        server_address = (self.ip_address, self.port)
        start_time = time.time()
        self.sock.sendto(json_data.encode(), server_address)
        try:
            data, addr = self.sock.recvfrom(1024)
        except:
            self.ping = 9999
            return
        end_time = time.time()
        ping = (end_time - start_time) * 1000
        self.ping = ping

    def receiveData(self):
        try:
            data, addr = self.sock.recvfrom(1024)
        except TimeoutError:
            return

        json_data = data.decode()
        received_data = None

        try:
            received_data = json.loads(json_data)
        except json.JSONDecodeError as e:
            pass
        
        if received_data:
            return received_data
        else:
            pass
    
    def screenshotDataOnRequest(self, button_inputs, data):
        if button_inputs["LB"] and button_inputs["RB"] and not self.screenshot_button_held:
            self.screenshot_button_held = True
            print(data)
        elif button_inputs["LB"] and button_inputs["RB"]:
            self.screenshot_button_held = True
        else:
            self.screenshot_button_held = False