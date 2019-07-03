import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5 import uic

class MyApp(QMainWindow):
	def __init__(self):
		super().__init__()
		self.timer = QTimer(self)
		self.timer.start(1000)
		self.timer.timeout.connect(self.timeout)

	def timeout(self):
		current_time = QTime.currentTime()
		text_time = current_time.toString("hh:mm:ss")
		time_msg = "현재시간: " + text_time

if __name__ == "__main__":
	app = QApplication(sys.argv)
	ex = MyApp()
	ex.show()
	sys.exit(app.exec_())
