import socket

# Define the target device and port
target_device = "Adafruit Metro M0"
target_port = 6969

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.settimeout(0.05)  # Set a timeout value to limit the scan duration

# Iterate through IP addresses in the local network
for i in range(1, 255):
    print(i)
    ip_address = f"192.168.0.{i}"  # Customize the IP address range based on your network configuration
    server_address = (ip_address, target_port)

    try:
        # Send a test message to the target device
        sock.sendto("ping".encode(), server_address)
        
        # Wait for a response
        data, addr = sock.recvfrom(1024)
        
        # Check the response to see if it matches the device return message
        if data.decode() == "Pong!":
            print(f"Found {target_device} at IP address: {ip_address}")
            break
            
    except:
        pass

# Close the socket
sock.close()