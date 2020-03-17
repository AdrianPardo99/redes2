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
            msg=desc.recv(1024)
            print("Mensaje del cliente: "+ msg.decode("utf-8"))
            print(self.checkTypeMsg(msg))
            print("Escribe un mensaje: ", end = '')
            message=input()
            message+="\n"
            desc.send(bytes(message,"utf-8"))
            if message=='cerrar\n':
                break
            elif msg=='cerrar\n':
                break

        desc.close()


    def checkTypeMsg(self,msg):
        if(msg[0]=="\x00"):
            return "nickname"
        elif msg[0]=="\x01":
            return "file"
        else:
            return "message"

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

servidor=Server('127.0.0.1',8080)
servidor.initServer()
servidor.initServer2()
