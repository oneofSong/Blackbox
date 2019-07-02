import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QToolTip, QMainWindow

from PyQt5.QtCore import QCoreApplication
from PyQt5.QtGui import QIcon, QFont

class MyApp(QMainWindow):
	def __init__(self):
		super().__init__()
		self.initUI()

	def initUI(self):
		#status bar 생성
		self.statusBar().showMessage('Ready')
		
		# icon set
		self.setWindowIcon(QIcon('./image/icon.png'))
		
		self.setWindowTitle('Statusbar')
		self.setGeometry(300,300,300,200)
		self.show()

if __name__ == '__main__':
	app = QApplication(sys.argv)
	ex = MyApp()
	sys.exit(app.exec_())
