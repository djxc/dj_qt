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
#include <qgsmarkersymbollayer.h>
#include <qgsattributetableview.h>
#include <qgsattributetablemodel.h>
#include <qgseditorwidgetregistry.h>
#include <qgsattributetablefiltermodel.h>
#include <qgssinglesymbolrenderer.h>
#include <qgswkbtypes.h>
#include <gdal/gdal_priv.h>

#include "exif.h"

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
    setWindowTitle(tr("dj地理信息系统"));
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

    // 创建treeView，需要绑定model，model提供数据。
    this->layerManage = new QTreeView(pLeftSpliter);
    this->layerManage->setStyleSheet("background-color:#CCFF99;");
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("图层管理"));
//    QStandardItem * item = new QStandardItem(tr("图层管理"));//创建一个条目对象
//    QStandardItem * edit = new QStandardItem(tr("数据编辑"));//创建一个条目对象
//    model->appendRow(item);//通过模型对象添加这个条目
//    model->appendRow(edit);
    //    model->item(0)->appendRow(new QStandardItem(tr("item four")));
    this->layerManage->setModel(model);


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
    connect(this->layerManage, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(treeViewClick(const QModelIndex)));
}

void MainWindow::treeViewClick(const QModelIndex & index) {
    QStandardItemModel *m = (QStandardItemModel *)index.model();
    for(int columnIndex = 0; columnIndex < m->columnCount(); columnIndex++)
    {
        QModelIndex x=m->index(index.row(),columnIndex);
        QString s= x.data().toString();
        qDebug()<< s;
    }
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
    fileMenu->addAction(tr("关闭所有图层"),this,SLOT(closeAllLayers()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("exit1"));

    QMenu *dataMenu = menuBar->addMenu("数据");
    dataMenu->addAction(tr("读取栅格数据"), this, SLOT(readIMAGE()));
    dataMenu->addAction(tr("读照片中gps信息"), this, SLOT(getGPSfromImage()));

    this->setMenuBar(menuBar);

    QToolBar *fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(tr("new"), this, SLOT(showArea()));
    fileToolBar->addAction(tr("打开属性表"), this, SLOT(showLayerTable()));
    //    fileToolBar->addAction(tr("Click"), this, SLOT(showDialog("djxc")));
}

/**
 * @brief MainWindow::readIMAGE
 * 采用gdal读取栅格数据，首先需要编译gdal文件找到gdal的动态连接库文件即gdal.so文件，以及gdal.h头文件
 */
void MainWindow::readIMAGE(){
    GDALAllRegister();
    const char *strImg = ("/home/djxc/2019/data/world.tif");
    GDALDataset *ImgBef = (GDALDataset *) GDALOpen(strImg, GA_ReadOnly);
    if (ImgBef == NULL)
    {
        qDebug()<<strImg;
    }else {
        qDebug()<< ImgBef;
    }
    int nCols = ImgBef->GetRasterXSize();         //获取影像信息
    int nRows = ImgBef->GetRasterYSize();
    int nBands = ImgBef->GetRasterCount();
    GDALDataType gBand = ImgBef->GetRasterBand(1)->GetRasterDataType();
    int nBits = GDALGetDataTypeSize(gBand);
    qDebug()<< nCols;
    qDebug()<< nRows;
    qDebug()<< nBands;
    qDebug()<< nBits;
    delete ImgBef;
}

/**
 * @brief MainWindow::getGPSfromImage
 * 采用别人的exif文件，获取图片中的gps数据
 */
void MainWindow :: getGPSfromImage(){
    qDebug()<<tr("获取gps数据");
    // 读取jpg文件到缓冲区
    FILE *fp = fopen("/home/djxc/test3.jpg", "rb");
    if (!fp) {
        qDebug()<<tr("Can't open file.\n");
        return;
    }
    // 文件偏移，此处将文件流移动到文件末尾，为了接下来计算文件大小。
    fseek(fp, 0, SEEK_END);
    // 文件流在文件中的当前位置
    unsigned long fsize = ftell(fp);
    // 将文件流位置设为文件的开头
    rewind(fp);
    // 将文件读取到缓冲区字节数组buf中，fread读取成功会返回读取的元素的个数
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
        qDebug()<<tr("Can't read file.\n");
        delete[] buf;
        return;
    }
    fclose(fp);

    // Parse EXIF
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    QString str;
    if (code) {
        str.sprintf("Error parsing EXIF: code %d\n", code);
        qDebug()<<str;
        return;
    }
    // Dump EXIF information
    str.sprintf("Camera make          : %s\n"
                "Camera model         : %s\n"
                "Software             : %s\n",
                result.Make.c_str(), result.Model.c_str(), result.Software.c_str());
    printf("GPS Latitude         : %f deg (%f deg, %f min, %f sec %c)\n",
           result.GeoLocation.Latitude, result.GeoLocation.LatComponents.degrees,
           result.GeoLocation.LatComponents.minutes,
           result.GeoLocation.LatComponents.seconds,
           result.GeoLocation.LatComponents.direction);
    printf("GPS Longitude        : %f deg (%f deg, %f min, %f sec %c)\n",
           result.GeoLocation.Longitude, result.GeoLocation.LonComponents.degrees,
           result.GeoLocation.LonComponents.minutes,
           result.GeoLocation.LonComponents.seconds,
           result.GeoLocation.LonComponents.direction);
    printf("GPS Altitude         : %f m\n", result.GeoLocation.Altitude);
    printf("GPS Precision (DOP)  : %f\n", result.GeoLocation.DOP);
    qDebug()<<str;

}


/**
 * @brief MainWindow::closeAllLayers 关闭所有图层
 * 1、将矢量与栅格图层集清空，然后将清空的数据集放在canvas中
 */
void MainWindow::closeAllLayers()
{
    qDebug()<< this->rasterLayerSet;
    qDebug()<< this->vectorLayerSet;
    this->rasterLayerSet.clear();
    this->vectorLayerSet.clear();
    this->canvas->setLayers(this->rasterLayerSet);
}
/**
 * @brief MainWindow::showLayerTable
 * 显示图层的属性表
 */
void MainWindow::showLayerTable()
{
    qDebug()<< this->selectVectorLayer;
    if(this->selectVectorLayer == NULL){
        QMessageBox::warning(NULL, "消息", "您未选择图层", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    }else {
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
    QMessageBox::warning(NULL, "消息", "content", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
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


    QgsVectorLayer  *layer = new QgsVectorLayer(path, QFileInfo(path).completeBaseName(),"ogr");
    if (!layer->isValid())
    {
        QMessageBox::critical(this,tr("Error"),tr("Open file failed!\nReason:%1"));
        return;
    }
    QgsWkbTypes::GeometryType type = layer->geometryType();
    /**判断图层的几何类型，根据几何类型进行渲染*/
    if(type == QgsWkbTypes::PointGeometry){
        layer->setRenderer(symbolPoint());
    }

    QgsMapLayer * add_layers;

    add_layers = QgsProject::instance()->addMapLayer(layer,true);

    this->vectorLayerSet.push_back(layer);
    canvas->setExtent(layer->extent());

    canvas->setLayers(this->vectorLayerSet);
    canvas->enableAntiAliasing(true);
    canvas->setCanvasColor(QColor(100,100,100));
    canvas->freeze(false);
    canvas->setDragMode(QGraphicsView::RubberBandDrag);
    canvas->setVisible(true);
    canvas->zoomToFullExtent();
    canvas->refresh();
    //    this->showLayerTable(layer);
    selectVectorLayer = layer;
    this->vectorLayerNum++;
    QStandardItemModel *model = (QStandardItemModel*)this->layerManage->model();
    QStandardItem * item = new QStandardItem(layer->name());//创建一个条目对象
    model->appendRow(item);
    this->layerManage->setModel(model);
}



/**
 * @brief MainWindow::symbolPoint
 * 给点Point设置样式返回一个singleRender指针
 */
QgsSingleSymbolRenderer* MainWindow::symbolPoint(){
    QgsSvgMarkerSymbolLayer *svgMarkSymbol = new QgsSvgMarkerSymbolLayer(tr("/home/djxc/2019/MyGIS/data/car.svg"));
    svgMarkSymbol->setSize(8.0);
    QgsSymbolLayerList symbolList;
    symbolList.append(svgMarkSymbol);

    QgsMarkerSymbol *markSymbol = new QgsMarkerSymbol(symbolList);
    QgsSingleSymbolRenderer *singleRender = new QgsSingleSymbolRenderer(markSymbol);
    return singleRender;
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

    QgsMapLayer * add_layers;

    add_layers = QgsProject::instance()->addMapLayer(rasterLayer, true);
    this->rasterLayerSet.append( rasterLayer );
    canvas->setExtent( rasterLayer->extent() );
    canvas->setLayers(this->rasterLayerSet);
    canvas->setVisible( true );
    canvas->freeze( false );
    canvas->refresh();
    QStandardItemModel *model = (QStandardItemModel*)this->layerManage->model();
    QStandardItem * item = new QStandardItem(rasterLayer->name());//创建一个条目对象
    model->appendRow(item);
    this->layerManage->setModel(model);
}


MainWindow::~MainWindow()
{
    delete canvas;
}
