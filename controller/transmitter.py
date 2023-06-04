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
import subprocess

class Transmitter:
    def __init__(self):
        # Create a UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(0.1)  # Set a timeout value to limit the scan duration
        
        self.port = 6969
        self.ping = 0
        self.packet_interval = 0.1 # Interval between packets in seconds
        self.send_time = 0

        # Shows what network we are connected to
        ssid = self.get_ssid()
        if ssid:
            print("Connected to Wi-Fi network:", ssid)
        else:
            print("Not connected to any Wi-Fi network.")
        
        # Gets the UDP address (asks user for IP)
        self.ip_address = self.findUDPAddress()

        self.screenshot_button_held = False

    # Returns the ssid of the network if connected
    def get_ssid(self):
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
        
    # Encodes data from a controller
    def encodeControllerData(self, axis_inputs, button_inputs):
        data = {
            "Movement X" : axis_inputs["Left Stick X"],
            "Movement Y" : axis_inputs["Left Stick Y"],
            "Turning" : axis_inputs["Right Stick X"],
            "Gas" : axis_inputs["Right Trigger"],
            "Reverse" : axis_inputs["Left Trigger"],
            "Boost" : button_inputs["A"],
            "Brake" : button_inputs["B"]
        }  
        
        return data
    
    # Encodes keyboard data
    def encodeKeyboardData(self, keyboardData):
        data = {}

        if keyboardData["pygame.K_a"]:
            data["Movement X"] = -1
        elif keyboardData["pygame.K_d"]:
            data["Movement X"] = 1
        else:
            data["Movement X"] = 0

        if keyboardData["pygame.K_w"]:
            data["Movement Y"] = -1
        elif keyboardData["pygame.K_s"]:
            data["Movement Y"] = 1
        else:
            data["Movement Y"] = 0
        
        if data["pygame.K_LEFT"]:
            data["Steering"] = -1
        elif data["pygame.K_RIGHT"]:
            data["Steering"] = 1
        
        if keyboardData["pygame.K_a"] or keyboardData["pygame.K_d"] or keyboardData["pygame.K_w"] or keyboardData["pygame.K_s"] or keyboardData["pygame.K_LEFT"] or keyboardData["pygame.K_RIGHT"]:
            data["Gas"] = 1
        else:
            data["Gas"] = 0
        
        data["Reverse"] = 0
        data["Boost"] = 0
        data["Brake"] = 0

        return data

    # Sends data to the server to be processed and handles resetting
    def sendData(self, data):
        if self.send_time + self.packet_interval > time.time():
            return
        self.send_time = time.time()

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
    
    def handleRequestedInputs(self, controller_type, button_inputs, keyboard_inputs, data):
        if controller_type == "Controller":
            if button_inputs["Back"] and button_inputs["Start"]:
                self.resetConnectionOnRequest()
            
            if button_inputs["LB"] and button_inputs["RB"]:
                self.screenshotDataOnRequest(data)
            else:
                self.screenshot_button_held = False
        
        elif controller_type == "Keyboard":
            if keyboard_inputs["pygame.K_r"]:
                self.resetConnectionOnRequest()
            
            if button_inputs["pygame.K_PRINTSCREEN"]:
                self.screenshotDataOnRequest(data)
            else:
                self.screenshot_button_held = False
    
    def resetConnectionOnRequest(self):
        # Reset the connection
        print("Connection reset")
        self.ip_address = self.findUDPAddress()

    def screenshotDataOnRequest(self, data):
        if not self.screenshot_button_held:
            self.screenshot_button_held = True
            print(data)
        else:
            return