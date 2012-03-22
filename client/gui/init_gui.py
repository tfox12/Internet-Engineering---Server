
import sys
from PyQt4 import QtCore, QtGui
from gui import Ui_MainWindow as mainWindow
from HttpLib import client as client


class MainWindow(QtGui.QMainWindow):
    
    
        def __init__(self, parent=None):
                QtGui.QWidget.__init__(self, parent)
                self.ui = mainWindow()
                self.ui.setupUi(self)
                QtCore.QObject.connect(self.ui.loadUrlButton, QtCore.SIGNAL("clicked()"), self.display_page)
              

        def display_page(self):
            target_url = self.ui.textEdit.toPlainText()
            response = client.fetchPage(str(target_url))
            self.ui.webView.setHtml(response.contents)

if __name__ == "__main__":
        app = QtGui.QApplication(sys.argv)
        mainWindow = MainWindow()
        mainWindow.show()
        sys.exit(app.exec_())
