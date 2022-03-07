#include "addlayercommon.h"
#include "ui_addlayercommon.h"

#include <QCheckBox>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <qtextedit.h>

AddLayerCommon::AddLayerCommon(int layerType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLayerCommon)
{
    ui->setupUi(this);
    setWindowTitle("添加图层");
    this->layerType = layerType;
    init();
}

AddLayerCommon::~AddLayerCommon()
{
    delete ui;
}

QString AddLayerCommon::getDataURL()
{
    return this->urlLineEdit->text();
}

QString AddLayerCommon::getLayerName()
{
    return this->layerNameEdit->text();
}

void AddLayerCommon::init()
{

    // 图层路径输入以及名称
    urlLineEdit = new QLineEdit(this);
    QLabel *urlLabel = new QLabel(this);
    urlLabel->setText("图层 url:");
    urlLineEdit->setPlaceholderText("输入图层url");

    layerNameEdit = new QLineEdit(this);
    QLabel *layerNameLabel = new QLabel(this);
    layerNameLabel->setText("图层名称:");
    layerNameEdit->setPlaceholderText("输入图层名称");

    layerNameEdit->setFixedWidth(150);
    urlLineEdit->setFixedWidth(200);

    // 添加按钮
    QPushButton *addButton = new QPushButton(this);
    addButton->setText("添加图层");
    // 设置头像
//    QPixmap pixmap(":/Images/logo");
//    pImageLabel->setFixedSize(90, 90);
//    pImageLabel->setPixmap(pixmap);
//    pImageLabel->setScaledContents(true);

    QGridLayout *pLayout = new QGridLayout();
    // 头像 第0行，第0列开始，占3行1列
//    pLayout->addWidget(pImageLabel, 0, 0, 3, 1);

    pLayout->addWidget(layerNameLabel, 0, 0, 1, 2);
    pLayout->addWidget(layerNameEdit, 0, 2);

    pLayout->addWidget(urlLabel, 1, 0, 1, 2);
    pLayout->addWidget(urlLineEdit, 1, 2);
    pLayout->addWidget(addButton, 2, 1, 1, 2);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addLayerClose()));


    // 记住密码 第2行，第1列开始，占1行1列 水平居左 垂直居中
//    pLayout->addWidget(pRememberCheckBox, 2, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
//    // 自动登录 第2行，第2列开始，占1行1列 水平居右 垂直居中
//    pLayout->addWidget(pAutoLoginCheckBox, 2, 2, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
    // 登录按钮 第3行，第1列开始，占1行2列
//    pLayout->addWidget(urlLable, 3, 1, 1, 2);
    // 设置水平间距
    pLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    pLayout->setVerticalSpacing(10);
    // 设置外间距
    pLayout->setContentsMargins(10, 10, 10, 10);

    this->setLayout(pLayout);
}


void AddLayerCommon::addLayerClose()
{
    QString layerUrl = urlLineEdit->text();
    QString layerName = layerNameEdit->text();
    emit sendLayerData(layerName, layerUrl, this->layerType);
    accept();
}

void AddLayerCommon::closeWithNoLayer()
{
    reject();
}
