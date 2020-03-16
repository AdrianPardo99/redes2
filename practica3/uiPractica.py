#/*Developed by:
# * Valdez Bernal Maria Fernanda
# * Valdez Esquivel Melani Betsabee
# * Gonzalez Pardo Adrian
# * 3CV6 20-02
# * Last file update: 15-03-2020 */

#!/usr/bin/env python3
from PyQt5 import QtWidgets, uic, QtGui
from PyQt5.QtGui import QIcon, QPixmap, QFont, QStandardItemModel, QStandardItem
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QMainWindow, QDialog,QLabel
from PyQt5.QtCore import pyqtSlot
import netifaces
import sys
import subprocess


### Elemento de dialogo para manejo de mensajes de error ###
class ErrorDialog(QDialog):
    def __init__(self):
        QDialog.__init__(self)
        self.resize(200,90)
        self.setWindowTitle("Error")
        self.message=QLabel(self)
        self.message.setFont(QtGui.QFont("Times", 12, QtGui.QFont.Bold))
        self.message.setStyleSheet('color: red')

        #pixmap = QPixmap('error.png')
        #self.message.setPixmap(pixmap)
        #pixmap.resize(10,10)

        self.message.move(10,10)

### Main principal para la aplicacion del chat con sockets grafico ###
class Ui(QtWidgets.QMainWindow):
    ### Init de la clase ###
    def __init__(self):
        self.nickname="d3vcr4ck:"
        self.listaUsr=list()
        self.diccionarioUsr=dict()
        super(Ui, self).__init__()
        interfaces = netifaces.interfaces()
        print("Interfaces de red:"+str(interfaces))
        uic.loadUi('inicial.ui', self)
        self.error1=ErrorDialog()
        self.button1 =self.findChild(QtWidgets.QPushButton, 'btnInterfaces') # Find the button
        self.button1.clicked.connect(self.btnInterfacesClick)
        self.button2 =self.findChild(QtWidgets.QPushButton, 'btnSent') # Find the button
        self.button2.clicked.connect(self.btnSentClick)
        self.button3 =self.findChild(QtWidgets.QPushButton, 'btnScan') # Find the button
        self.button3.clicked.connect(self.btnScanClick)
        self.button4 =self.findChild(QtWidgets.QPushButton, 'btnArchivo') # Find the button
        self.button4.clicked.connect(self.btnFileClick)
        self.comboBox = self.findChild(QtWidgets.QComboBox, 'cmbInterfaces')
        self.label=self.findChild(QtWidgets.QLabel, 'lblChat')
        self.lista=self.findChild(QtWidgets.QListWidget,'listaIP')
        self.label1=self.findChild(QtWidgets.QLabel,'lblChatWith')
        self.lista.itemClicked.connect(self.btnAbrirClick)
        self.texto=self.findChild(QtWidgets.QTextEdit,'textEdit')
        self.chat=self.findChild(QtWidgets.QTextEdit,'txtMessage')
        for i in interfaces:
            self.comboBox.addItem(str(i))
        self.button2.setEnabled(False)
        self.button3.setEnabled(False)
        self.button4.setEnabled(False)
        self.texto.setEnabled(False)
        self.show()

    ### Aqui va la logica del evento de enviar archivos ###
    def btnFileClick(self):
        print("Abriendo file manager")

    ### Aqui va la logica del evento de los datos de la interfaz de red ###
    def btnScanClick(self):
        self.listaUsr.clear()
        self.lista.clear()
        addrShow=self.addrs[netifaces.AF_INET]
        datos=addrShow[0]
        valData=self.comboBox.currentText()
        if valData!="lo":
            print(str(datos))
            ip=datos['addr']
            netmask=datos['netmask']
            strCMD="./calculadora "+ip+" "+netmask
            subprocess.call(strCMD.split(" "))
            fileIP=open("ips.txt","rt")
            datoIPs=fileIP.read()
            fileIP.close()
            arrayIP=datoIPs.split("\n")
        else:
            arrayIP=list()
            arrayIP.append("127.0.0.1")
        self.lista.addItems(arrayIP)
        for i in arrayIP:
            diccionario={"ip":i,"chat":list()}
            self.listaUsr.append(diccionario)
        print(str(self.listaUsr))


    def actualizaChat(self):
        self.texto.setText("")
        for i in self.listaChatUsuario:
            self.texto.setText(self.texto.toPlainText()+i)

    ### Aqui va la logica de enviar mensajes ###
    def btnSentClick(self):
        tam=self.chat.toPlainText()
        if len(tam)==0:
            self.error1.message.setText("No dejar vacio la \ncaja de texto de chat")
            self.error1.exec_()
        else:
            self.chat.setPlainText("")
            self.listaChatUsuario.append(self.nickname+" "+tam+"\n")
            print("Enviando: "+tam)
            self.actualizaChat()

    ### Aqui va la logica de contactar con un miembro de la red ###
    def btnAbrirClick(self,item):
        # This is executed when the button is pressed
        self.label1.setText("Conversando con: "+item.text())
        con=0
        for i in self.listaUsr:
            diccionario=i
            val=diccionario['ip']
            if item.text()==val:
                self.listaChatUsuario=diccionario['chat']
                break
        if len(self.listaChatUsuario)==0:
            self.texto.setText("Inicia conversacion: ")
        self.actualizaChat()
        self.button2.setEnabled(True)
        self.button4.setEnabled(True)


    ### Aqui esta la logica del las interfaces de red ###
    def btnInterfacesClick(self):
        self.lista.clear()
        banner=False
        print("Se selecciono: "+self.comboBox.currentText())
        self.label.setText("Chat usando la interfaz: "+self.comboBox.currentText())
        self.addrs= netifaces.ifaddresses(self.comboBox.currentText())
        try:
            print("Lenght "+str(len(str(self.addrs[netifaces.AF_INET]))))
            banner=False
        except:
            banner=True
        if banner:
            print("No se pueden reconocer los datos")
            self.error1.message.setText("No se pueden obtener \ndatos de esta interfaz")
            self.error1.exec_()
            self.button2.setEnabled(False)
            self.button4.setEnabled(False)
            self.button3.setEnabled(False)
        else:
            print(str(self.addrs[netifaces.AF_INET]))
            self.button2.setEnabled(False)
            self.button4.setEnabled(False)
            self.button3.setEnabled(True)

app = QtWidgets.QApplication([])
win= Ui()
app.exec_()
