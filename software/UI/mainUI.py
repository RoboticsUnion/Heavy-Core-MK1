from PySide6.QtWidgets import (
    QApplication, QWidget, QPushButton, QLabel,
    QVBoxLayout, QHBoxLayout, QStackedWidget
)
from PySide6.QtCore import Qt
from PySide6.QtGui import QShortcut, QKeySequence
import sys

app = QApplication(sys.argv)

# ----------------------------------------------------
# Hauptfenster
# ----------------------------------------------------
main_window = QWidget()
main_window.setWindowTitle("Web-Style Menü")

main_layout = QVBoxLayout()      # Gesamtlayout
navbar = QHBoxLayout()           # Obere Button-Leiste
pages = QStackedWidget()         # Seitencontainer


# ----------------------------------------------------
# Seite 1 – Beispiel mit sauberem Layout
# ----------------------------------------------------
seite1 = QWidget()
seite1_layout = QVBoxLayout()

title1 = QLabel("SEITE 1 – Titel")
title1.setAlignment(Qt.AlignCenter)

text1 = QLabel("Hier steht mehr Text, perfekt zentriert.")
text1.setAlignment(Qt.AlignCenter)

# Buttons in einer Reihe
row1 = QHBoxLayout()
row1.addStretch()
row1.addWidget(QPushButton("Knopf A"))
row1.addWidget(QPushButton("Knopf B"))
row1.addStretch()

seite1_layout.addWidget(title1)
seite1_layout.addWidget(text1)
seite1_layout.addLayout(row1)
seite1_layout.addStretch()

seite1.setLayout(seite1_layout)


# ----------------------------------------------------
# Seite 2
# ----------------------------------------------------
seite2 = QWidget()
seite2_layout = QVBoxLayout()

title2 = QLabel("SEITE 2 – Info")
title2.setAlignment(Qt.AlignCenter)

text2 = QLabel("Dies ist eine andere Seite.")
text2.setAlignment(Qt.AlignCenter)

seite2_layout.addWidget(title2)
seite2_layout.addWidget(text2)
seite2_layout.addStretch()

seite2.setLayout(seite2_layout)


# ----------------------------------------------------
# Seite 3
# ----------------------------------------------------
seite3 = QWidget()
seite3_layout = QVBoxLayout()

title3 = QLabel("SEITE 3 – Einstellungen")
title3.setAlignment(Qt.AlignCenter)

seite3_layout.addWidget(title3)
seite3_layout.addStretch()

seite3.setLayout(seite3_layout)


# ----------------------------------------------------
# Seite 4
# ----------------------------------------------------
seite4 = QWidget()
seite4_layout = QVBoxLayout()

title4 = QLabel("SEITE 4 – Daten")
title4.setAlignment(Qt.AlignCenter)

seite4_layout.addWidget(title4)
seite4_layout.addStretch()

seite4.setLayout(seite4_layout)


# ----------------------------------------------------
# Seite 5
# ----------------------------------------------------
seite5 = QWidget()
seite5_layout = QVBoxLayout()

title5 = QLabel("SEITE 5 – Tools")
title5.setAlignment(Qt.AlignCenter)

seite5_layout.addWidget(title5)
seite5_layout.addStretch()

seite5.setLayout(seite5_layout)


# ----------------------------------------------------
# Seiten ins StackedWidget
# ----------------------------------------------------
pages.addWidget(seite1)
pages.addWidget(seite2)
pages.addWidget(seite3)
pages.addWidget(seite4)
pages.addWidget(seite5)


# ----------------------------------------------------
# Navbar Buttons
# ----------------------------------------------------
btn1 = QPushButton("Seite 1")
btn2 = QPushButton("Seite 2")
btn3 = QPushButton("Seite 3")
btn4 = QPushButton("Seite 4")
btn5 = QPushButton("Seite 5")

btn1.clicked.connect(lambda: pages.setCurrentIndex(0))
btn2.clicked.connect(lambda: pages.setCurrentIndex(1))
btn3.clicked.connect(lambda: pages.setCurrentIndex(2))
btn4.clicked.connect(lambda: pages.setCurrentIndex(3))
btn5.clicked.connect(lambda: pages.setCurrentIndex(4))

navbar.addWidget(btn1)
navbar.addWidget(btn2)
navbar.addWidget(btn3)
navbar.addWidget(btn4)
navbar.addWidget(btn5)

btn_exit = QPushButton("Beenden")
btn_exit.clicked.connect(app.quit)
navbar.addWidget(btn_exit)

# ----------------------------------------------------
# Alles zusammenbauen
# ----------------------------------------------------
main_layout.addLayout(navbar)
main_layout.addWidget(pages)

main_window.setLayout(main_layout)
main_window.showFullScreen()

shortcut = QShortcut(QKeySequence("Escape"), main_window)
shortcut.setContext(Qt.ApplicationShortcut)
shortcut.activated.connect(app.quit)

sys.exit(app.exec())