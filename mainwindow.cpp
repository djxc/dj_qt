#include "mainwindow.h"
#include <QGridLayout>
/**
 * @brief MainWindow::MainWindow
 * @param parent
 * 构造函数，设置页面元素
 * 1、配置窗口样式，大小以及标题等
 * 2、创建挂件，并设置大小位置
 * 3、创建布局，将布局应用于挂件
 * 4、创建具体页面元素，将其加载到布局上
 * 5、注册交互事件函数
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 600);
    QWidget *djwidget = new QWidget(this);
    djwidget->setGeometry(10, 10, 400, 400);
    QGridLayout *djlayout = new QGridLayout();
    djwidget->setLayout(djlayout);

    label1 = new QLabel(this);
    label1->setText(tr("请输入半径"));
    lineEdit = new QLineEdit(this);
    label2 = new QLabel(this);
    button = new QPushButton(this);
    button->setText(tr("显示面积"));
    djlayout->addWidget(label1, 0, 0);
    djlayout->addWidget(lineEdit, 1, 0);
    djlayout->addWidget(label2, 0, 1);
    djlayout->addWidget(button, 1, 1);
    connect(button, SIGNAL(clicked()), this, SLOT(showArea()));
}

void MainWindow::showArea()
{
    bool ok;
    QString tempStr;
    QString valueStr = lineEdit->text();
    int valueInt = valueStr.toInt(&ok);
    double area = valueInt * valueInt * 3.1416;
    label2->setText(tempStr.setNum(area));
}

MainWindow::~MainWindow()
{

}
