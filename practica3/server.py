#/*Developed by:
# * Valdez Bernal Maria Fernanda
# * Valdez Esquivel Melani Betsabee
# * Gonzalez Pardo Adrian
# * 3CV6 20-02
# * Last file update: 16-03-2020 */

#!/usr/bin/env python3
import sys
import socket
import threading


class Server:
    def __init__(self,ip,port):
        self.ip=ip
        self.port=port

    def initChat(self,descriptor):
        desc=descriptor
        while True:
            self.msg=desc.recv(1024)
            print("Mensaje del cliente: "+ self.msg.decode("utf-8"))
            print("Escribe un mensaje: ", end = '')
            self.message=input()
            self.message+="\n"
            desc.send(bytes(self.message,"utf-8"))
            if self.message=='cerrar\n':
                break
            elif self.msg=='cerrar\n':
                break

        desc.close()

    def initServer(self):
        self.s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.s.bind((self.ip,self.port))
        self.s.listen(1)

    def initServer2(self):
        while True:
            clientSocket, address = self.s.accept()
            print(f"Conexion de {address} ha sido establecida")
            hilo1 = threading.Thread(target=self.initChat,args=(clientSocket,))
            hilo1.start()




        self.s.close()

servidor=Server('127.0.0.1',8082)
servidor.initServer()
servidor.initServer2()
