import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QToolTip
from PyQt5.QtCore import QCoreApplication
from PyQt5.QtGui import QIcon, QFont

class MyApp(QWidget):
	def __init__(self):
		super().__init__()
		self.initUI()

	def initUI(self):
		# tooltip 표시
		QToolTip.setFont(QFont('SansSerif', 10))
		self.setToolTip('This is a <b>QWidget</b> widget')

		# button 생성		
		btn = QPushButton('Quit',self)
		btn.move(50,50)
		btn.resize(btn.sizeHint())
		btn.clicked.connect(QCoreApplication.instance().quit)
		
		# icon set
		self.setWindowIcon(QIcon('./image/icon.png'))
		
		self.setWindowTitle('Quit Button')
		self.setGeometry(300,300,300,200)
		self.show()

if __name__ == '__main__':
	app = QApplication(sys.argv)
	ex = MyApp()
	sys.exit(app.exec_())
