# This code is generated using PyUIbuilder: https://pyuibuilder.com

import os
import PySide6.QtWidgets as qw
import PySide6.QtCore as qc
import PySide6.QtGui as qg

BASE_DIR = os.path.dirname(os.path.abspath(__file__))


app = qw.QApplication([])
app.setStyle("Fusion")
main = qw.QMainWindow()
main.setWindowTitle("Robot Control V1.0 Beta")
main.resize(700, 445)
main.setStyleSheet("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.00 rgb(54,77,72), stop:0.50 rgb(0,0,0), stop:1.00 rgb(56,81,77)); background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.00 rgb(54,77,72), stop:0.50 rgb(0,0,0), stop:1.00 rgb(56,81,77));")
main.move(0, 0)

main.menuBar().setVisible(False)


button = qw.QPushButton("Menu", main)
button.setStyleSheet("""
		QPushButton {
			background-color: rgb(0,0,0);
			color: rgb(0,252,147);
			border: 2px solid rgb(46,143,114);
			border-radius: 14px;
		}

		QPushButton:hover {
			color: rgb(0,0,0);
			background: rgb(89,230,157);
			background-color: rgb(89,230,157);
		}	""")
button.setGeometry(qc.QRect(300, 20, 110, 36))

button1 = qw.QPushButton("Editor", main)
button1.setStyleSheet("""
		QPushButton {
			background-color: rgb(0,0,0);
			color: rgb(0,252,147);
			border: 2px solid rgb(46,143,114);
			border-radius: 14px;
		}

		QPushButton:hover {
			color: rgb(0,0,0);
			background: rgb(89,230,157);
			background-color: rgb(89,230,157);
		}	""")
button1.setGeometry(qc.QRect(80, 20, 110, 36))

button2 = qw.QPushButton("Device", main)
button2.setStyleSheet("""
		QPushButton {
			background-color: rgb(0,0,0);
			color: rgb(0,252,147);
			border: 2px solid rgb(46,143,114);
			border-radius: 14px;
		}

		QPushButton:hover {
			color: rgb(0,0,0);
			background: rgb(89,230,157);
			background-color: rgb(89,230,157);
		}	""")
button2.setGeometry(qc.QRect(520, 20, 110, 36))


main.show()
app.exec()
