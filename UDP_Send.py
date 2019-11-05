import socket

UDP_IP = "192.168.1.1"
UDP_PORT = 57222

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
#sock.bind((UDP_IP, UDP_PORT))
Off = 'Stop!'
On = 'Start!'

# Example Commands
#sock.sendto(Off, (UDP_IP, UDP_PORT))
#sock.sendto(On, (UDP_IP, UDP_PORT))