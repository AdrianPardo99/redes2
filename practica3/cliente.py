#/*Developed by:
# * Valdez Bernal Maria Fernanda
# * Valdez Esquivel Melani Betsabee
# * Gonzalez Pardo Adrian
# * 3CV6 20-02
# * Last file update: 16-03-2020 */

#!/usr/bin/env python3
import sys
import socket


class Cliente(object):

    def __init__(self, ip,port):
        self.s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.s.connect((ip,port))

    def initCliente(self):
        while True:
            print("Escribe un mensaje para el servidor: ", end = '')
            message=input()
            message+="\n"
            self.s.send(bytes(message,"utf-8"))
            msg=self.s.recv(1024)
            print("Mensaje del servidor: "+msg.decode("utf-8"))
            if msg=="cerrar\n":
                break
            elif message=="cerrar\n":
                break
        self.s.close()
cliente=Cliente('127.0.0.1',8082)
cliente.initCliente()
