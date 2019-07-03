import sys
from PyQt5.QtWidgets import QApplication, QWidget,QVBoxLayout,QLineEdit,QCheckBox
from PyQt5.QtCore import Qt


class MyApp(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        display = QLineEdit('')
        self.display = display
        self.display.setReadOnly(True)
        self.display.setAlignment(Qt.AlignCenter)
        self.display.setMaxLength(15)
	

        self.cb1 = QCheckBox('짜장', self)
        self.cb1.move(20, 20)
        self.cb1.stateChanged.connect(self.checkedBox)

        self.cb2 = QCheckBox('짬뽕', self)
        self.cb2.move(20, 20)
        self.cb2.stateChanged.connect(self.checkedBox)

        self.cb3 = QCheckBox('탕수육', self)
        self.cb3.move(20, 20)
        self.cb3.stateChanged.connect(self.checkedBox)

        vbox = QVBoxLayout()
        vbox.addWidget(self.display)
        vbox.addWidget(self.cb1)
        vbox.addWidget(self.cb2)
        vbox.addWidget(self.cb3)

        self.setLayout(vbox)

        self.setWindowTitle('Stylesheet')
        self.setGeometry(300, 300, 300, 200)
        self.show()

    def checkedBox(self, state):
        clickedButton = self.sender()

        if self.display.text() == '':
            if state == Qt.Checked:
                self.display.setText(clickedButton.text())
        else:
            if state == Qt.Checked:
                self.display.setText(self.display.text() + "," +clickedButton.text())
            else:
                index = self.display.text().find(clickedButton.text())
                if index == 0: 
                    self.display.setText(self.display.text().replace(clickedButton.text(),"",1))
                else: 
                    self.display.setText(self.display.text().replace(","+clickedButton.text(),"",1))

        if self.display.text() != "" and self.display.text()[0] == ',':
             self.display.setText(self.display.text().replace(",","",1))



if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())
