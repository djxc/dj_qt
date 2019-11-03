#include "mainwindow.h"
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QSplitter>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QTreeView>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QTableView>

#include <qgsmaplayer.h>
#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <qgsproject.h>
#include <qgsrasterlayer.h>
#include <qgsvectorlayercache.h>
#include <qgsattributetableview.h>
#include <qgsattributetablemodel.h>
#include <qgsattributetablefiltermodel.h>
#include <qgseditorwidgetregistry.h>

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
    resize(800, 600);
    setWindowTitle(tr("study"));
    this->addMenuAndToolbar();
//    this->initLayout();
    this->splitteLayout();
}

/**
 * @brief MainWindow::splitteLayout
 * 分割窗口布局：
 * 1、右边为地图显示窗口；
 * 2、左边又分为上下，上边为图层管理，下边为属性表。
 */
void MainWindow::splitteLayout()
{
    QSplitter *pLeftSpliter = new QSplitter(Qt::Vertical);

    QTreeView *treeView = new QTreeView(pLeftSpliter);
    treeView->setStyleSheet("background-color:#CCFF99;");
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList()<<
                                     QStringLiteral("项目名")<<QStringLiteral("信息"));
    QStandardItem * item = new QStandardItem(tr("item one"));//创建一个条目对象
    model->appendRow(item);//通过模型对象添加这个条目
    model->item(0)->appendRow(new QStandardItem(tr("item four")));
    treeView->setModel(model);


     QTableView *table = new QTableView(pLeftSpliter);
//     table->setStyleSheet("background-color:#FFB7DD;");

     QStandardItemModel *tableModel = new QStandardItemModel;   //创建一个标准的条目模型
     table->setModel(tableModel);   //将tableview设置成model这个标准条目模型的模板, model设置的内容都将显示在tableview上

     tableModel->setHorizontalHeaderItem(0, new QStandardItem("姓名") );
     tableModel->setHorizontalHeaderItem(1, new QStandardItem("学号"));
     tableModel->setHorizontalHeaderItem(2, new QStandardItem("性别"));
     tableModel->setHorizontalHeaderItem(3, new QStandardItem("年龄"));
     tableModel->setHorizontalHeaderItem(4, new QStandardItem("院系"));
     tableModel->setHorizontalHeaderItem(5, new QStandardItem("兴趣"));

     table->setColumnWidth(0, 100);    //设置列的宽度
     table->setColumnWidth(1, 150);
     table->setColumnWidth(2, 50);
     table->setColumnWidth(3, 50);
     table->setColumnWidth(4, 100);
     table->setColumnWidth(5, 150);

     /*setItem设置条目栏中的一个格子的信息*/
     tableModel->setItem(1, 5, new QStandardItem("hello world" ) );

     /*设置行字段名*/
     tableModel->setRowCount(3);
     tableModel->setHeaderData(0,Qt::Vertical, "行0");
     tableModel->setHeaderData(1,Qt::Vertical, "行1");
     tableModel->setHeaderData(2,Qt::Vertical, "行2");


    QSplitter *pSpliter = new QSplitter(Qt::Horizontal);
    canvas = new QgsMapCanvas();

    pSpliter->addWidget(pLeftSpliter);
    pSpliter->addWidget(canvas);

    pSpliter->setStretchFactor(0, 1);
    pSpliter->setStretchFactor(1, 4);//左右宽度比为4：1

    pLeftSpliter->setStretchFactor(0, 4);//左面窗口上下窗口高度比为4：1
    pLeftSpliter->setStretchFactor(1, 1);

    this->setCentralWidget(pSpliter);
}


/**
 * @brief MainWindow::addMenuAndToolbar
 * 添加菜单栏以及工具栏
 */
void MainWindow::addMenuAndToolbar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("文件");
    fileMenu->addAction(tr("open"));
    fileMenu->addAction(tr("new"));
    fileMenu->addAction(tr("矢量文件"),this,SLOT(openVectorData()));
    fileMenu->addAction(tr("柵格文件"),this,SLOT(openRasterData()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("exit"));
    this->setMenuBar(menuBar);

    QToolBar *fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(tr("new"));
    fileToolBar->addAction(tr("打开属性表"), this, SLOT(showLayerTable()));
    fileToolBar->addAction(tr("Click"), this, SLOT(showDialog()));
}


/**
 * @brief MainWindow::showLayerTable
 * 显示图层的属性表
 */
void MainWindow::showLayerTable()
{
    QgsVectorLayerCache* lc = new QgsVectorLayerCache(
                selectVectorLayer, selectVectorLayer->featureCount());
    QgsAttributeTableView* tv = new QgsAttributeTableView();
    QgsAttributeTableModel* tm = new QgsAttributeTableModel( lc );
    QgsAttributeTableFilterModel* tfm = new QgsAttributeTableFilterModel(
                canvas, tm, tm );
    tm->loadLayer();
    tv->setModel( tfm );
    tv->show();
}


/**
 * @brief MainWindow::initLayout
 *  增加显示内容
 */
void MainWindow::initLayout()
{
    QWidget *djwidget = new QWidget(this);
    djwidget->setGeometry(10, 10, 200, 200);
    djwidget->setStyleSheet("background-color:blue;");

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

/**
 * @brief MainWindow::showArea
 * 计算面积
 */
void MainWindow::showArea()
{
    bool ok;
    QString tempStr;
    QString valueStr = lineEdit->text();
    int valueInt = valueStr.toInt(&ok);
    double area = valueInt * valueInt * 3.1416;
    label2->setText(tempStr.setNum(area));
}

/**
 * @brief MainWindow::showDialog
 * 显示消息对话框
 */
void MainWindow::showDialog()
{
    QMessageBox::warning(NULL, "消息", "你好，我是小杜！", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
}

/**
 * @brief MainWindow::openVectorData
 * 打开矢量数据
 */
void MainWindow::openVectorData()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                QString(),"ESRI Shapefile(*.shp)");
    if (path.isEmpty())
    {
        return;
    }

    QgsVectorLayer  *layer = new QgsVectorLayer(path,QFileInfo(path).completeBaseName(),"ogr");
    if (!layer->isValid())
    {
        QMessageBox::critical(this,tr("Error"),tr("Open file failed!\nReason:%1"));
        return;
    }

    QgsMapLayer * add_layers;

    QList<QgsMapLayer*> myLayerSet;

    add_layers = QgsProject::instance()->addMapLayer(layer,true);

    myLayerSet.push_back(layer);
    canvas->setExtent(layer->extent());
    canvas->setLayers(myLayerSet);
    canvas->enableAntiAliasing(true);
    canvas->setCanvasColor(QColor(100,100,100));
    canvas->freeze(false);
    canvas->setDragMode(QGraphicsView::RubberBandDrag);
    canvas->setVisible(true);
    canvas->zoomToFullExtent();
    canvas->refresh();
//    this->showLayerTable(layer);
    selectVectorLayer = layer;
}

/**
 * @brief MainWindow::openRaster
 * 打开栅格数据
 */
void MainWindow::openRasterData() {
    QString filename = QFileDialog::getOpenFileName( this, tr( "open raster" ), "", "*.tif" );
    QStringList temp = filename.split( QDir::separator() );
    QString basename = temp.at( temp.size() - 1 );
    QgsRasterLayer* rasterLayer = new QgsRasterLayer( filename, basename, "gdal");
    if ( !rasterLayer->isValid() )
    {
        QMessageBox::critical( this, "error", "layer is invalid" );
        return;
    }

    QList<QgsMapLayer*> myLayerSet;
    QgsMapLayer * add_layers;

    add_layers = QgsProject::instance()->addMapLayer(rasterLayer, true);
    myLayerSet.append( rasterLayer );
    canvas->setExtent( rasterLayer->extent() );
    canvas->setLayers(myLayerSet);
    canvas->setVisible( true );
    canvas->freeze( false );
    canvas->refresh();
}


MainWindow::~MainWindow()
{
    delete canvas;
}
