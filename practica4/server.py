#!/usr/bin/env python3

#/*Developed by:
# * Valdez Bernal Maria Fernanda
# * Valdez Esquivel Melani Betsabee
# * Gonzalez Pardo Adrian
# * 3CV6 20-02
# * Last file update: 8-04-2020 */

import sys
import socket
import os

enumFormato=list()
listaFormato=list()
listaBuffer=list()
tamBufferTotal=list()
numSegmentos=list()
##### Ya casi esta todo checar la separación de información vía stackoverflow y
##### hacer la lista de esos datos para enviarlos vía broadcast y multicast

def fileOpen(arg,index):
    op=open(arg,"rb")
    dataRead=op.read()
    listaBuffer.append(dataRead)
    print("Tamanio en segmentos de 20 : "+str(1+int(len(dataRead)/20)))
    if int(len(dataRead)/20) > 1495:
        print("Mayor tamanio")
        numSegmentos.append(1+int(len(dataRead)/1495))
    else:
        numSegmentos.append(1+int(len(dataRead)/20))
    tamBufferTotal.append(len(dataRead))
    op.close()

def validaType():
    c=0
    for i in listaFormato:
        if i=="JPG" or i=="PNG" or i=="JPEG" or i=="GIF":
            c+=1
    if c==5:
        print("Formatos correctos procediendo a abrir socket")
    else:
        print("Error formatos no aceptados")
        sys.exit(1)

def typeFile(arg):
    listacmd="file "+arg
    files=os.popen(listacmd,'r').readlines()
    type=files[0].split(" ")
    listaFormato.append(type[1])

if len(sys.argv)<6:
    print("Error\nUsage: ",sys.argv[0]," <File-0> <File-1> <File-2> <File-3> <File-4>")
    sys.exit(1)
else:
    for i in range(1,len(sys.argv)):
        typeFile(sys.argv[i])
        enumFormato.append(str(i-1))
    validaType()
    for i in range(1,len(sys.argv)):
        fileOpen(sys.argv[i],i-1)
