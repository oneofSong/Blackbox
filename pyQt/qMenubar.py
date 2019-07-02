import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QAction, qApp
from PyQt5.QtGui import QIcon

class MyApp(QMainWindow):
	def __init__(self):
		super().__init__()
		self.initUI()

	def initUI(self):
		# action
		exitAction = QAction(QIcon('./image/exit.png'), 'Exit', self)
		exitAction.setShortcut('Ctrl+Q')
		exitAction.setStatusTip('Exit application')
		exitAction.triggered.connect(qApp.quit)
		
		# statucbar 생성
		self.statusBar()
		
		# menubar 생성
		menubar = self.menuBar()
		menubar.setNativeMenuBar(False)
		fileMenu = menubar.addMenu('&File')
		fileMenu.addAction(exitAction)
		helpMenu = menubar.addMenu('&Help')

		self.setWindowIcon(QIcon('./image/icon.png'))

		self.setWindowTitle('Menubar')
		self.setGeometry(300,300,300,200)
		self.show()

if __name__ == '__main__':
	app = QApplication(sys.argv)
	ex = MyApp()
	sys.exit(app.exec_())
