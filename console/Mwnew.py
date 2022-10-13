from PySide2.QtWidgets import QApplication, QMessageBox
from PySide2.QtUiTools import QUiLoader
salary_above_20k = '孙一峰你家被偷了\n 孙一峰你二矿也被偷了\n'
class Event:

    def __init__(self):
        # 从文件中加载UI定义

        # 从 UI 定义中动态 创建一个相应的窗口对象
        # 注意：里面的控件对象也成为窗口对象的属性了
        # 比如 self.ui.button , self.ui.textEdit
        self.ui = QUiLoader().load('ui/First.ui')

        self.ui.pushButton.clicked.connect(self.handleCalc)
#123123123
    def handleCalc(self):

        QMessageBox.about(self.ui,
                          '待处理事件',
                          f'''\n{salary_above_20k}
                            '''
                    )

app = QApplication([])
Event = Event()
Event.ui.show()
app.exec_()