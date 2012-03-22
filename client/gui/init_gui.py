
import sys
from PyQt4 import QCore, QtGui
from gui import Ui_MainWindow as mainWindow


class MainWindow(QtGui.QMainWindow):
        def __init__(self, parent=None):
                QtGui.QWidget.__init__(self, parent)
        self.ui = mainWindow()
        self.ui.setupUi(self)


if __name__ == "__main__":
        app = QtGui.QApplication(sys.argv)
        mainWindow = MainWindow()
        mainWindow.show()
        sys.exit(app.exec_())
