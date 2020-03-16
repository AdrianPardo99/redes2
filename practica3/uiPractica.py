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
        super(Ui, self).__init__()
        interfaces = netifaces.interfaces()
        print("Interfaces de red:"+str(interfaces))
        uic.loadUi('inicial.ui', self)
        self.error1=ErrorDialog()
        self.button = self.findChild(QtWidgets.QPushButton, 'btnAbrir') # Find the button
        self.button.clicked.connect(self.btnAbrirClick) # Remember to pass the definition/method, not the return value!
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
        self.lista=self.findChild(QtWidgets.QListView,'listaIP')
        self.model = QtGui.QStandardItemModel()
        self.lista.setModel(self.model)
        for i in interfaces:
            self.comboBox.addItem(str(i))
        self.button.setEnabled(False)
        self.button2.setEnabled(False)
        self.button3.setEnabled(False)
        self.button4.setEnabled(False)
        self.show()

    ### Aqui va la logica del evento de enviar archivos ###
    def btnFileClick(self):
        print("Abriendo file manager")

    ### Aqui va la logica del evento de los datos de la interfaz de red ###
    def btnScanClick(self):
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
        for i in arrayIP:
            item=QtGui.QStandardItem(i)
            self.model.appendRow(item)
        self.button2.setEnabled(True)
        self.button.setEnabled(True)
        self.button4.setEnabled(True)


    ### Aqui va la logica de enviar mensajes ###
    def btnSentClick(self):
        print("Enviando: ")

    ### Aqui va la logica de contactar con un miembro de la red ###
    def btnAbrirClick(self):
        # This is executed when the button is pressed
        print('Abriendo chat: ')


    ### Aqui esta la logica del las interfaces de red ###
    def btnInterfacesClick(self):
        self.model.removeRows( 0, self.model.rowCount() )
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
            self.button.setEnabled(False)
            self.button2.setEnabled(False)
            self.button4.setEnabled(False)
            self.button3.setEnabled(False)
        else:
            print(str(self.addrs[netifaces.AF_INET]))
            self.button.setEnabled(False)
            self.button2.setEnabled(False)
            self.button4.setEnabled(False)
            self.button3.setEnabled(True)

app = QtWidgets.QApplication([])
win= Ui()
app.exec_()
