"""*********************************************
Fyrryx UDP Protocol

Data is encoded into JSON format before sending/recieving, except for pings ("ping" is answered by "pong").
JSON will look something like this: {"key1":"value1","key2":"value2"}.
To encode/decode in python, "json" is used
To encode/decode in CPP, "ArduinoJson.h" is used (located in /headers/ArduinoJson.h)
*********************************************"""
import socket
import pygame
import json
import time
import subprocess

class Transmitter:
    # This sets up the UDP socket and other member data
    def __init__(self):
        # Create a UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(0.1)  # Set a timeout value to limit the scan duration
        
        self.port = 6969
        self.ping = 0
        self.packet_interval = 0.1 # Interval between packets in seconds
        self.send_time = time.time()

        # Shows what network we are connected to
        ssid = self.__get_ssid()
        if ssid:
            print("Connected to Wi-Fi network:", ssid)
        else:
            print("Not connected to any Wi-Fi network.")
        
        # Gets the UDP address (asks user for IP)
        self.ip_address = self.__findUDPAddress()

        self.screenshot_button_held = False

    # Returns the ssid of the network if connected
    def __get_ssid(self):
        try:
            output = subprocess.check_output(["netsh", "wlan", "show", "interfaces"], universal_newlines=True)
            lines = output.splitlines()
            for line in lines:
                if "SSID" in line:
                    ssid = line.split(":")[1].strip()
                    return ssid
        except subprocess.CalledProcessError:
            pass
        return None

    # Blocking function that will continiously search for the server
    def __findUDPAddress(self):
        target_ip_address = input("Enter server address (192.168.0.XX): ")
        if target_ip_address.isnumeric():
            target_ip_address = f"192.168.0.{target_ip_address}"
        
        for i in range(10):
            if self.__checkAddress((target_ip_address, self.port)):
                break
        else:
            print("Couldn't connect to server. Please try again.\n")
            return self.__findUDPAddress()

        print("Connection established at IP: " + target_ip_address)

        return target_ip_address

    # Returns True if we can connect to the IP address at port using socket
    def __checkAddress(self, server_address):
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
        
    # Encodes data from a controller
    def encodeControllerData(self, axis_inputs, button_inputs):
        data = {
            "Movement X" : axis_inputs["Left Stick X"],
            "Movement Y" : axis_inputs["Left Stick Y"],
            "Turning" : axis_inputs["Right Stick X"],
            "Horn" : button_inputs["B"],
            "Intro" : button_inputs["D-pad Up"],
            "Chorus" : button_inputs["D-pad Down"]
        }  
        
        return data
    
    # Encodes keyboard data
    def encodeKeyboardData(self, keyboardData):
        data = {}
        movement = False

        if pygame.K_a in keyboardData:
            data["Movement X"] = -1
        elif pygame.K_d in keyboardData:
            data["Movement X"] = 1
        else:
            data["Movement X"] = 0

        if pygame.K_w in keyboardData:
            data["Movement Y"] = -1
        elif pygame.K_s in keyboardData:
            data["Movement Y"] = 1
        else:
            data["Movement Y"] = 0
        
        if pygame.K_LEFT in keyboardData:
            data["Turning"] = -1
        elif pygame.K_RIGHT in keyboardData:
            data["Turning"] = 1
        else: 
            data["Turning"] = 0
    
        data["Horn"] = 1 if pygame.K_f in keyboardData else 0
        data["Intro"] = 1 if pygame.K_1 in keyboardData else 0
        data["Chorus"] = 1 if pygame.K_2 in keyboardData else 0

        return data

    # Sends data to the server to be processed and handles resetting
    def sendData(self, data):
        if self.send_time + self.packet_interval > time.time():
            return

        json_data = json.dumps(data) # Packages the data into a JSON file
        print(json_data)

        server_address = (self.ip_address, self.port)
        self.sock.sendto(json_data.encode(), server_address) # Sends the data to the server
        try:
            data, addr = self.sock.recvfrom(1024) # Waits until a "pong" is received from the server
        except:
            self.ping = 9999 # There is a timeout of 100ms, so this activates when it timeouts
            return
        
        end_time = time.time() # Ends the timer
        ping = (end_time - self.send_time) * 1000 # Works out the difference in ms
        self.ping = ping  # Allows the user to fetch the ping
        
        self.send_time = time.time() # Starts the timer 

    # Receives data from server and returns it
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
    
    # Handles any requested inuputs (e.g. screenshot data)
    def handleRequestedInputs(self, controller_type, button_inputs, keyboard_inputs, data):
        if controller_type == "Controller":
            if button_inputs["Back"] and button_inputs["Start"]:
                self.__resetConnectionOnRequest()
            
            if button_inputs["LB"] and button_inputs["RB"]:
                self.__screenshotDataOnRequest(data)
            else:
                self.screenshot_button_held = False
        
        elif controller_type == "Keyboard":
            if "pygame.K_r" in keyboard_inputs:
                self.__resetConnectionOnRequest()
            
            if "pygame.K_PRINTSCREEN" in keyboard_inputs:
                self.__screenshotDataOnRequest(data)
            else:
                self.screenshot_button_held = False
    
    # Resets the connection
    def __resetConnectionOnRequest(self):
        # Reset the connection
        print("Connection reset")
        self.ip_address = self.__findUDPAddress()

    # Screenshots the data on RISING EDGE
    def __screenshotDataOnRequest(self, data):
        if not self.screenshot_button_held:
            self.screenshot_button_held = True
            print(data)
        else:
            return