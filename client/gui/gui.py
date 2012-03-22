# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'web_client.ui'
#
# Created: Thu Mar 22 18:01:26 2012
#      by: PyQt4 UI code generator 4.9.1
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(800, 600)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.textEdit = QtGui.QTextEdit(self.centralwidget)
        self.textEdit.setGeometry(QtCore.QRect(40, 10, 701, 21))
        self.textEdit.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.textEdit.setObjectName(_fromUtf8("textEdit"))
        self.loadUrlButton = QtGui.QPushButton(self.centralwidget)
        self.loadUrlButton.setGeometry(QtCore.QRect(740, 10, 21, 21))
        self.loadUrlButton.setObjectName(_fromUtf8("loadUrlButton"))
        self.cancelLoadButton = QtGui.QPushButton(self.centralwidget)
        self.cancelLoadButton.setGeometry(QtCore.QRect(770, 10, 16, 21))
        self.cancelLoadButton.setObjectName(_fromUtf8("cancelLoadButton"))
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 18))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName(_fromUtf8("menuFile"))
        self.menuWorthwhile = QtGui.QMenu(self.menubar)
        self.menuWorthwhile.setObjectName(_fromUtf8("menuWorthwhile"))
        self.menuMenus = QtGui.QMenu(self.menubar)
        self.menuMenus.setObjectName(_fromUtf8("menuMenus"))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        MainWindow.setStatusBar(self.statusbar)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuWorthwhile.menuAction())
        self.menubar.addAction(self.menuMenus.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QtGui.QApplication.translate("MainWindow", "MainWindow", None, QtGui.QApplication.UnicodeUTF8))
        self.loadUrlButton.setText(QtGui.QApplication.translate("MainWindow", "PushButton", None, QtGui.QApplication.UnicodeUTF8))
        self.cancelLoadButton.setText(QtGui.QApplication.translate("MainWindow", "PushButton", None, QtGui.QApplication.UnicodeUTF8))
        self.menuFile.setTitle(QtGui.QApplication.translate("MainWindow", "File", None, QtGui.QApplication.UnicodeUTF8))
        self.menuWorthwhile.setTitle(QtGui.QApplication.translate("MainWindow", "Worthwhile", None, QtGui.QApplication.UnicodeUTF8))
        self.menuMenus.setTitle(QtGui.QApplication.translate("MainWindow", "Menus", None, QtGui.QApplication.UnicodeUTF8))

