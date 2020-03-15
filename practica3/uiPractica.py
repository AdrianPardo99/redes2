#!/usr/bin/env python3
from PyQt5 import QtWidgets, uic
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QMainWindow, QDialog
from PyQt5.QtCore import pyqtSlot
import netifaces
import sys
class Ui(QtWidgets.QMainWindow):
    ban = 0
    banIp=0
    def __init__(self):
        super(Ui, self).__init__()
        interfaces = netifaces.interfaces()
        print("Interfaces de red:"+str(interfaces))
        uic.loadUi('inicial.ui', self)

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
        for i in interfaces:
            self.comboBox.addItem(str(i))
        self.button.setEnabled(False)
        self.button2.setEnabled(False)
        self.button3.setEnabled(False)
        self.button4.setEnabled(False)
        self.show()

    def btnFileClick(self):
        print("Abriendo file manager")

    def btnScanClick(self):
        print("Escaneando y obteniendo datos de la interfaz de red: ")
        self.button2.setEnabled(True)
        self.button.setEnabled(True)
        self.button4.setEnabled(True)
        banIp=1

    def btnSentClick(self):
        print("Enviando: ")

    def btnAbrirClick(self):
        # This is executed when the button is pressed
        print('Abriendo chat: ')

    def btnInterfacesClick(self):
        banner=False
        print("Se selecciono: "+self.comboBox.currentText())
        self.label.setText("Chat usando la interfaz: "+self.comboBox.currentText())
        addrs= netifaces.ifaddresses(self.comboBox.currentText())
        try:
            print("Lenght "+str(len(str(addrs[netifaces.AF_INET]))))
            banner=False
        except:
            banner=True
        if banner:
            print("No se pueden reconocer los datos")
            self.button.setEnabled(False)
            self.button2.setEnabled(False)
            self.button4.setEnabled(False)
            self.button3.setEnabled(False)
        else:
            print(str(addrs[netifaces.AF_INET]))
            self.button.setEnabled(False)
            self.button2.setEnabled(False)
            self.button4.setEnabled(False)
            self.button3.setEnabled(True)
        ban=1



app = QtWidgets.QApplication([])
win= Ui()
app.exec_()
