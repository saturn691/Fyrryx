def fetchUDPAddress(sock, most_likely_ip, port):
    if checkAddress(sock, most_likely_ip, port) == True:
        return most_likely_ip
    else:    
        for i in range(1, 255):
            ip_address = f"192.168.0.{i}"  # Customize the IP address range based on your network configuration
            if checkAddress(sock, ip_address, port) == True:
                return ip_address
    print(f"Nothing found at port {port} from IP = 192.168.0.XX . Please try again.")

# Returns True if we can connect to the IP address at port using socket
def checkAddress(sock, ip_address, port):
    try:
        server_address = (ip_address, port)
        sock.sendto("ping".encode(), server_address)
        data, addr = sock.recvfrom(1024)
        if data.decode() == "Pong!":
            return True
    except:
        pass
