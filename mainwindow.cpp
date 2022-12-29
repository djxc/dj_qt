#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"

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
#include <qgsmaptoolpan.h>
#include "gdal_priv.h"
#include "gdal.h"

#include "addlayercommon.h"
#include "exif.h"
#include "resource.h"

using namespace RESOURCE_CENTER;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{    
    resize(800, 600);
    setWindowTitle(tr("GaMi GIS测试平台"));
    initApp();    
}



/**
 * @brief MainWindow::addMenuAndToolbar
 * 添加菜单栏以及工具栏
 * 1、新建菜单栏对象QMenuBar，菜单栏对象可以包含多个按钮（QMenu）；
 * 2、个按钮又可以下拉为多个子按钮,通过addAction添加按钮的事件
 */
void MainWindow::addMenuAndToolbar()
{
    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = menuBar->addMenu("文件");
    fileMenu->addAction(open_ttl);
    fileMenu->addAction(new_ttl);
    fileMenu->addAction(vector_layer_ttl,this,SLOT(openVectorData()));
    fileMenu->addAction(raster_layer_ttl, this, SLOT(openRasterData()));
    fileMenu->addSeparator();
    fileMenu->addAction(close_all_layer_ttl, this, SLOT(closeAllLayers()));

    fileMenu->addAction(tr("quit"));

    // 数据
    QMenu *dataMenu = menuBar->addMenu("数据");
    dataMenu->addAction(tr("加载WMS图层"), this, SLOT(addWMSLayer()));
    dataMenu->addAction(tr("加载WFS图层"), this, SLOT(addWFSLayer()));
    dataMenu->addAction(tr("读取栅格数据"), this, SLOT(readIMAGE()));
    dataMenu->addAction(tr("读照片中gps信息"), this, SLOT(getGPSfromImage()));

    dataMenu->addAction(tr("test"), this, SLOT(test()));

    // 在线地图
    QMenu *onlineLayerMenu = menuBar->addMenu("在线地图");
    onlineLayerMenu->addAction(tr("Spinal Map"), this, SLOT(loadSpinalMap()));
    onlineLayerMenu->addAction(tr("forest Map"), this, SLOT(loadForestMap()));
    onlineLayerMenu->addAction(tr("terrain"), this, SLOT(loadTerrainMap()));
    onlineLayerMenu->addAction(tr("读照片中gps信息"), this, SLOT(getGPSfromImage()));

    this->setMenuBar(menuBar);

    // 创建工具栏
    QToolBar *fileToolBar = addToolBar(tr("&File"));
    fileToolBar-> addAction(tr("new"), this, SLOT(showArea()));
    fileToolBar->addAction(tr("打开属性表"), this, SLOT(showLayerTable()));
    fileToolBar->addAction(tr("Click"), this, SLOT(showDialog("djxc")));

    QStatusBar *statusBar = new QStatusBar(this);
    xyLabel = new QLabel(statusBar);
    xyLabel->setText("djkx");
    statusBar->addWidget(xyLabel);
    this->setStatusBar(statusBar);

    connect(canvas, SIGNAL(xyCoordinates(QgsPointXY)), this, SLOT(showMousePoint(QgsPointXY)));
    connect(canvas, SIGNAL(keyPressed(QKeyEvent)), this, SLOT(mouseClickEvent(QKeyEvent)));
}

/**
 * @brief MainWindow::splitteLayout
 * 分割窗口布局：
 * 1、右边为地图显示窗口；
 * 2、左边又分为上下，上边为图层管理，下边为属性表。
 */
void MainWindow::splitteLayout() {
    QSplitter *pLeftSpliter = new QSplitter(Qt::Vertical);

    // 图层管理器，创建treeView，需要绑定model，model提供数据。
    this->layerManager = new QTreeView(pLeftSpliter);
    this->layerManager->setStyleSheet("background-color:#AEEEEE;");

    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList()<<layer_manage_ttl);
    this->layerManager->setModel(model);
    // 双击图层管理器的图层触发事件
    connect(this->layerManager, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(treeViewClick(const QModelIndex)));

    // 属性表
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
    tableModel->setHeaderData(0, Qt::Vertical, "row 0");
    tableModel->setHeaderData(1, Qt::Vertical, "row 1");
    tableModel->setHeaderData(2, Qt::Vertical, "row 2");


    QSplitter *pSpliter = new QSplitter(Qt::Horizontal);

    pSpliter->addWidget(pLeftSpliter);
    pSpliter->addWidget(canvas);

    pSpliter->setStretchFactor(0, 1);
    pSpliter->setStretchFactor(1, 4);//左右宽度比为4：1

    pLeftSpliter->setStretchFactor(0, 4);//左面窗口上下窗口高度比为4：1
    pLeftSpliter->setStretchFactor(1, 1);

    this->setCentralWidget(pSpliter);

}


void MainWindow::addCommonLayer(int layerType)
{
    AddLayerCommon* addLayerCommon = new AddLayerCommon(layerType);
    connect(addLayerCommon,
            SIGNAL(sendLayerData(QString, QString, int)),
            this,
            SLOT(receiveLayerData(QString, QString, int)));
    int result = addLayerCommon->exec();
    qDebug() << result;
    delete addLayerCommon;
}

/**
 * @brief MainWindow::addWMSLayer
 * 加载wms图层
 */
void MainWindow::addWMSLayer()
{
    addCommonLayer(1);
}

/**
 * @brief MainWindow::addWFSLayer
 * 加载wfs图层
 */
void MainWindow::addWFSLayer()
{
    addCommonLayer(2);
}



/**
 * @brief MainWindow::openVectorData
 * 打开矢量数据
 */
void MainWindow::openVectorData() {
    QString path = openFile("ESRI Shapefile(*.shp)", "打开矢量数据");
    if (path == NULL) {
        return;
    }
    bool isOk = this->layerManage->addVectorLayer(path, canvas);
    if (!isOk) {
        QMessageBox::critical(this,tr("Error"),tr("Open file failed!\nReason:%1"));
    }
    addLayerItem(QFileInfo(path).completeBaseName());
}

/**
 * @brief MainWindow::openRaster
 * 打开栅格数据
 */
void MainWindow::openRasterData() {
    QString path = openFile("*.tif", "打开栅格数据");
    if (path == NULL) {
        return;
    }

    bool isOk = this->layerManage->addRasterLayer(path, canvas);
    if (!isOk) {
        QMessageBox::critical(this,tr("Error"),tr("Open file failed!\nReason:%1"));
    }
    addLayerItem(QFileInfo(path).completeBaseName());
}


/**
 * @brief MainWindow::addLayer
 * 将图层添加到mapCanvas中
 * 1、首先将rasterLayerNum加一
 * 2、将图层添加到map中缩放至添加的图层
 * 3、图层管理中添加该图层名称
 * @param layerToAdd
 */
void MainWindow::addLayerItem(QString layer_name) {

    // 添加成功之后需要将栅格图层名称添加到图层管理器中
    QStandardItemModel *model = (QStandardItemModel*)this->layerManager->model();
    QStandardItem * item = new QStandardItem(layer_name);//创建一个条目对象
    model->insertRow(0, item);
    this->layerManager->setModel(model);
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
 * @brief MainWindow::readIMAGE
 * 采用gdal读取栅格数据，首先需要编译gdal文件找到gdal的动态连接库文件即gdal.so文件，以及gdal.h头文件
 */
void MainWindow::readIMAGE(){
    GDALAllRegister();
    const char *strImg = ("D:\\Data\\LE07_L1TP_120035_20211012_20211107_01_T1_B1.TIF");
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
    QString imagePath = QFileDialog::getOpenFileName( this, tr("选择图片"), "", "*.jpg" );
    qDebug()<<imagePath.toStdString().c_str();
    ParsePhotoLatLon *parsePhoto = new ParsePhotoLatLon();
    parsePhoto->getGPSfromImage(imagePath);
}

/**
 * @brief MainWindow::receiveLayerData 加载wms或wfs图层
 * @param layerName
 * @param layerUrl
 * @param layerType
 */
void MainWindow::receiveLayerData(QString layerName, QString layerUrl, int layerType)
{
    qDebug("layerName: %s", qPrintable(layerName));
    bool addResult = false;
    switch (layerType) {
    case 1:
        addResult = layerManage->addWMSLayer(layerUrl, canvas, layerName);
        break;
    case 2:
        addResult = layerManage->addWFSLayer(layerUrl, layerName, canvas);
        break;
    }
    if (addResult) {
        addLayerItem(layerName);
    }
}

void MainWindow::test()
{
    QList<QgsVectorLayer*>layers = layerManage->getVecotrLayers();
    QgsVectorLayer* layer = layers[0];
    QgsFeature f;
    QgsFeatureIterator features = layer->getFeatures();
    while (features.nextFeature(f)) {
        qDebug() << f.id();
    }
    layer->setLabelsEnabled(true);
    QgsFeatureIds ids = layer->selectedFeatureIds();
    //  选择要素，qgis会将要素高亮
    layer->select(40);
    layer->startEditing();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    //鼠标移动追踪事件   显示按下坐标
    qDebug()<<"("+QString::number(e->x())+","+QString::number(e->y())+")";

}

void MainWindow::loadSpinalMap()
{
    QString layerMapName = "spinal map";
    bool addResult = layerManage->addOnlineMap(
                "type=xyz&url=https://a.tile.thunderforest.com/spinal-map/{z}/{x}/{y}.png?apikey=41f4f936f1d148f69cbd100812875c88",
                layerMapName, canvas);
    if (addResult) {
        addLayerItem(layerMapName);
    }
}

void MainWindow::loadForestMap() {

    QString layerMapName = "forest map";
    bool addResult = layerManage->addOnlineMap(
                "type=xyz&url=https://b.tile.thunderforest.com/transport-dark/{z}/{x}/{y}.png?apikey=41f4f936f1d148f69cbd100812875c88",
                layerMapName, canvas);
    if (addResult) {
        addLayerItem(layerMapName);
    }
}

void MainWindow::loadTerrainMap() {
    QString layerName = "terrain Map";

    bool addResult = layerManage->addOnlineMap(
                "type=xyz&url=https://stamen-tiles-a.a.ssl.fastly.net/terrain/{z}/{x}/{y}.jpg",
                layerName, canvas);
    if (addResult) {
        addLayerItem(layerName);
    }
}


/**
 * 双击图层管理器中的图层名称触发该事件
 * 1、双击图层将其zoom to layer，需要首先获取双击图层的名称，
 * 遍历栅格图层获取与该名称一致的图层，然后将其缩放
 * @brief MainWindow::treeViewClick
 * @param index
 */
void MainWindow::treeViewClick(const QModelIndex & index) {
    QStandardItemModel *m = (QStandardItemModel *)index.model();
    for(int columnIndex = 0; columnIndex < m->columnCount(); columnIndex++)
    {
        QModelIndex x = m->index(index.row(),columnIndex);
        QString s = x.data().toString();
        QgsMapLayer *selectedLayer = NULL;
        foreach(QgsMapLayer *mapLayer, this->layerManage->getRasterLayers()) {
            if(s == mapLayer->name()) {
                selectedLayer = mapLayer;
                break;
            }
        }

        foreach(QgsMapLayer *mapLayer, this->layerManage->getVecotrLayers()) {
            if(s == mapLayer->name()) {
                selectedLayer = mapLayer;
                break;
            }
        }
        if(selectedLayer) {
            // 缩放至图层
            this->canvas->setExtent(selectedLayer->extent());
            this->canvas->refresh();
        }
    }
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
 * @brief MainWindow::closeAllLayers 关闭所有图层
 * 1、将矢量与栅格图层集清空，然后将清空的数据集放在canvas中
 */
void MainWindow::closeAllLayers()
{
    this->layerManage->getRasterLayers().clear();
    this->layerManage->getVecotrLayers().clear();
    QList<QgsMapLayer*> allLayers;
    canvas->setLayers(allLayers);
    canvas->setVisible( true );
    canvas->freeze( false );
    canvas->refresh();
    // 清空图层管理的内容
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList()<<layer_manage_ttl);
    this->layerManager->setModel(model);
}
/**
 * @brief MainWindow::showLayerTable
 * 显示图层的属性表
 */
void MainWindow::showLayerTable()
{
    QgsMapLayer *selectedLayer = this->layerManage->getSelectLayer();
    qDebug()<< selectedLayer;
    if (typeid (QgsVectorLayer) != typeid (selectedLayer)) {
        QMessageBox::warning(NULL, "消息", "仅可打开矢量数据属性表", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    } else if(selectedLayer == NULL){
        QMessageBox::warning(NULL, "消息", "您未选择图层", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    }else {
        //        QgsVectorLayer *vectorLayer = (QgsVectorLayer) selectedLayer->;
        //        QgsVectorLayerCache* lc = new QgsVectorLayerCache(
        //                    selectVectorLayer, selectVectorLayer->featureCount());
        //        QgsAttributeTableView* tv = new QgsAttributeTableView();
        //        QgsAttributeTableModel* tm = new QgsAttributeTableModel( lc );
        //        QgsAttributeTableFilterModel* tfm = new QgsAttributeTableFilterModel(
        //                    canvas, tm, tm );
        //        tm->loadLayer();
        //        tv->setModel( tfm );
        //        tv->show();
    }
}

/**
 * @brief MainWindow::showDialog
 * 显示消息对话框
 */
void MainWindow::showDialog()
{
    QMessageBox::warning(NULL, "消息", "content", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
}

void MainWindow::zoomToLayer() {

}



/**
 * @brief utilTool::openFile
 * 打开文件对话框
 * @param parent
 * @param type
 * @return
 */
QString MainWindow::openFile(QString type, QString title) {
    QString path = QFileDialog::getOpenFileName(this, title,
                                                QString(),type);
    if (path.isEmpty())
    {
        return "";
    }
    return path;
}

void MainWindow::showMousePoint(const QgsPointXY &p)
{
    double xLat = p.x();
    if (xLat <= -180) {
        xLat = xLat + 360;
    }
    if (xLat >= 180) {
        xLat = xLat - 360;
    }
    QString label = "纬度 : " + QString::number(p.y(),'f',3) + " 经度 : " + QString::number(xLat,'f',3);
    xyLabel->setText(label);
}

void MainWindow::mouseClickEvent(const QKeyEvent &e)
{
    qDebug() << e.text();
}

/**
 * @brief MainWindow::initApp
 * 初始化程序
 */
void MainWindow::initApp()
{
    canvas = new QgsMapCanvas();

    QColor color;
    color.setRgb(120, 50, 200, 10);
    canvas->setCanvasColor(color);
    this->addMenuAndToolbar();
    this->splitteLayout();

    // 添加pan控件，使图层可以用鼠标左键拖动
    QgsMapToolPan* tool = new QgsMapToolPan(canvas);
    canvas->setMapTool(tool);

    this->layerManage = new LayerManager();
    this->setMouseTracking(true);//设置窗体追踪鼠标
}


MainWindow::~MainWindow()
{
    delete ui;
}

