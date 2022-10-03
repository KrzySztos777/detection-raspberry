import sys
import threading
import os,signal
import subprocess
import fcntl
#from tendo import singleton

from time import time
from math import floor

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5 import uic

from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import QTimer
#raspivid -n -fps 40 -w 640 -h 480 -t 0 --raw - -rf rgb -o /dev/null  | ./raspitune 640 480 | python3 ./app.py 640 480
#raspivid -n -fps 40 -w 1024 -h 768 -t 0 --raw - -rf rgb -o /dev/null  | ./raspitune 1024 768 | python3 ./app.py 1024 768


class MainWindow(QtWidgets.QMainWindow):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        uic.loadUi("mainwindow.ui", self)
        
        #Setting window size
        if(len(sys.argv)==3):
            self.width=int(sys.argv[1])
            self.height=int(sys.argv[2])
            
            self.imageLabel.resize(self.width,self.height);
            self.imageLabel.setMinimumSize(self.width,self.height);
            self.resize(self.width,self.height+self.statusbar.frameGeometry().height());
            self.header="P6\n"+str(self.width)+" "+str(self.height)+"\n255\n"
            self.imageSize=self.width*self.height*3
            self.image=bytes(self.header,'ASCII')+bytes('\0'*self.imageSize,'ASCII')+bytes('\n','ASCII')
            
        
        #Setting imageLabel
        self.pixmap = QPixmap()
        self.imageLabel.setPixmap(self.pixmap)
        self.data=bytes()
        self.prevData=bytes()
        self.image=bytes()
        
        #Setting deamon
        x = threading.Thread(target=self.deamon, args=(sys.stdin.buffer.raw,))
        x.start()
        
        #Setting timer
        self.timer=QTimer()
        self.timer.timeout.connect(self.updateLabel)
        self.timer.start(1000/40)
        self.ts=floor(time())
        self.frameCounter=0
        
        #setting for motor driver
        self.motorDriverProgram="./Subsystem/motor.o"
        self.MotorInputFileName="./err"
        self.motorInput=open(self.MotorInputFileName,"r")
        self.resoultion=3200#resoultion of stepper motor
        self.motorSubprocess=False
        
        #Setting widgets
        self.running=False
        self.angleLabelFormat="Visibility angle: %3.d "
        self.freqLabelFormat="Maximal frequency: %4.d "
        self.mainButton.clicked.connect(self.mainClick)
        
        if(self.instanceAlreadyRunning()):
            error_dialog = QtWidgets.QErrorMessage()
            error_dialog.showMessage("Already running. Close program instance to start new one.")
            error_dialog.exec_()
            self.close()
        
    def instanceAlreadyRunning(self,label="default"):#https://stackoverflow.com/questions/380870/make-sure-only-a-single-instance-of-a-program-is-running
        
        lockFilePointer = os.open(f"./instance_{label}.lock", os.O_WRONLY | os.O_CREAT)

        try:
            fcntl.lockf(lockFilePointer, fcntl.LOCK_EX | fcntl.LOCK_NB)
            alreadyRunning = False
        except IOError:
            alreadyRunning = True

        return alreadyRunning
    
    
    
    def mainClick(self):
        if(self.running==False):
            #self.motorInput=open(self.MotorInputFileName,"r")
            #self.motorInput.read()
            #self.motorSubprocess=subprocess.Popen(["./motorSimpleDetection", "3200", "100", "135"], stdin=self.motorInput)
            self.motorSubprocess=subprocess.Popen([self.motorDriverProgram, ], stdin=self.motorInput)
            self.mainButton.setText("Stop and Close")
            self.running=True
        else:
            self.running=False
            self.close()
    
    def deamon(self,inputStream):
        while 1:
            readed=inputStream.read(self.imageSize-len(self.data))
            self.data+=readed
            
            if len(self.data)==self.imageSize:# and self.data!=self.prevData:
                self.image=bytes(self.header,'ASCII')+self.data+bytes('\n','ASCII')
                self.prevData=self.data
                self.data=bytes()
                
                if self.ts==floor(time()):
                    self.frameCounter+=1
                else:
                    self.statusbar.showMessage("FPS: "+str(self.frameCounter));
                    self.frameCounter=1
                    self.ts=floor(time())
    
    def updateLabel(self):
        self.pixmap.loadFromData(self.image,"PPM")
        self.imageLabel.setPixmap(self.pixmap)
        sys.stdout.buffer.raw.write(self.image)
            
    def closeEvent(self,event):
        self.motorInput.close()
        if(self.motorSubprocess!=False):
            self.motorSubprocess.send_signal(signal.SIGUSR1)
            self.motorSubprocess.wait()
        #self.closeDueErrorLol()
        os.killpg(os.getppid(),signal.SIGKILL)
        #event.ignore()
        
#me=singleton.SingleInstance()
app = QtWidgets.QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()
