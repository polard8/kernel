# Credits: https://wiki.python.org/moin/UdpCommunication

import socket

#Send to the server on localhost.
#UDP_IP = "127.0.0.1"

#Send to Gramado on virtualbox.
UDP_IP = "192.1.1.112"
UDP_PORT = 5005
MESSAGE = b"Hey Gramado!"

print("UDP target IP: %s" % UDP_IP)
print("UDP target port: %s" % UDP_PORT)
print("message: %s" % MESSAGE)

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
