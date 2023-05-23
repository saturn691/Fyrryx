"""*********************************************
Fyrryx UDP Protocol

This transmitter will send UDP packets in the form of JSON. Data can be encoded and decoded in a very flexible manner.
This transmitter will also recieve UDP packets in the form of JSON. This will recieve the name, age and magnetic field.
*********************************************"""
import socket
import json

class Transmitter:
    def __init__(self, TARGET_IP, TARGET_PORT):
        self.TARGET_IP = TARGET_IP
        self.port = TARGET_PORT

        # Create a UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(0.25)  # Set a timeout value to limit the scan duration

        self.ip_address = self.findUDPAddress()

    # Blocking function that will continiously search for the server
    def findUDPAddress(self):
        ip_address = None
        while ip_address == None:
            ip_address = self.fetchUDPAddress()

        print("Connection established at IP: " + ip_address)

        return ip_address

    # Searches target IP, then searches IP from 1 to 255
    def fetchUDPAddress(self):
        if self.checkAddress(self.TARGET_IP) == True:
            return self.TARGET_IP
        else:    
            for i in range(1, 255):
                ip_address = f"192.168.0.{i}"  # Customize the IP address range based on your network configuration
                if self.checkAddress(ip_address) == True:
                    return ip_address

        print(f"Nothing found at port {self.port} from IP = 192.168.0.XX . Please try again.")

    # Returns True if we can connect to the IP address at port using socket
    def checkAddress(self, ip_address):
        try:
            server_address = (ip_address, self.port)
            self.sock.sendto("ping".encode(), server_address)
            data, addr = self.sock.recvfrom(1024)
            if data.decode() == "Pong!":
                return True
        except:
            return False

    # Sends data to the server to be processed and handles resetting
    def handleInputs(self, axis_inputs, button_inputs):
        if button_inputs["Back"] and button_inputs["Start"]:
            # Reset the connection
            print("Connection reset")
            self.ip_address = self.findUDPAddress()

        data = {
            "Movement" : axis_inputs["Left Stick X"],
            "Turning" : axis_inputs["Right Stick X"],
            "Gas" : axis_inputs["Right Trigger"],
            "Reverse" : axis_inputs["Left Trigger"],
            "Boost" : button_inputs["A"],
            "Brake" : button_inputs["B"]
        }    

        json_data = json.dumps(data)    
        
        server_address = (self.ip_address, self.port)
        self.sock.sendto(json_data.encode(), server_address)

    def receiveData(self):
        data, addr = self.sock.recvfrom(1024)
        
        json_data = data.decode()
        received_data = json.loads(json_data)
        
        for key, value in received_data.items():
            if value is not None:
                print(key, ":", value)
