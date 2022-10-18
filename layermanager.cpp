#include "layermanager.h"

#include <qfiledialog.h>
#include <qgsproject.h>
#include <qgsrasterlayer.h>
#include <qgsvectorlayer.h>
#include <qmessagebox.h>

LayerManager::LayerManager()
{


}

/**
 * @brief LayerManager::addWFSLayer 打开矢量数据文件
 * @param layerURL wfs图层url
 * @param canvas mapcanvas
 * @return 成功返回true否则返回false
 */
bool LayerManager::addWFSLayer(QString layerURL, QString layerName, QgsMapCanvas *canvas)
{
    QgsVectorLayer  *layer = new QgsVectorLayer(layerURL, layerName, "WFS");
    return addCommonVectorLayer(layer, canvas);
}

QList<QgsRasterLayer *> LayerManager::getRasterLayers()
{
    return rasterLayerSet;
}

QList<QgsVectorLayer *> LayerManager::getVecotrLayers()
{
    return vectorLayerSet;
}


/**
 * @brief LayerManager::addOnlineMap 加载在线地图
 * @param layerUrl
 * @param layerName
 * @param canvas
 * @return
 */
bool LayerManager::addOnlineMap(QString layerUrl, QString layerName, QgsMapCanvas *canvas)
{
    bool addResult = addWMSLayer(layerUrl, canvas, layerName);
    if (addResult) {
        qDebug() << "图层加载成功";
    } else {
        qDebug() << "图层加载失败";
    }
    return addResult;
}

/**
 * @brief LayerManager::addVectorLayer 打开矢量数据文件
 * @param layerPath 文件路径
 * @param canvas mapcanvas
 * @return 成功返回true否则返回false
 */
bool LayerManager::addVectorLayer(QString layerPath, QgsMapCanvas *canvas)
{
    QgsVectorLayer  *layer = new QgsVectorLayer(layerPath, QFileInfo(layerPath).completeBaseName(),"ogr");
    return addCommonVectorLayer(layer, canvas);
}

/**
 * @brief LayerManager::addCommonVectorLayer
 * @param layer
 * @param canvas
 * @return
 */
bool LayerManager::addCommonVectorLayer(QgsVectorLayer *layer, QgsMapCanvas *canvas)
{
    if (!layer->isValid())
    {
        return false;
    }
    QgsWkbTypes::GeometryType type = layer->geometryType();
    /**判断图层的几何类型，根据几何类型进行渲染*/
    if(type == QgsWkbTypes::PointGeometry){
//        layer->setRenderer(symbolPoint());
    }
    this->vectorLayerNum++;
    this->vectorLayerSet.append(layer);
    this->addLayer(layer, canvas);
    return true;
}

/**
 * @brief LayerManager::addWMSLayer 打开WMS栅格数据文件
 * @param layerURL 图层的url
 * @param canvas mapcanvas
 * @param layerName 图层名称
 * @return 成功返回true否则返回false
 */
bool LayerManager::addWMSLayer(QString layerURL, QgsMapCanvas *canvas, QString layerName) {
    QgsRasterLayer* rasterLayer = new QgsRasterLayer(layerURL, layerName, "wms");
    return addCommonRasterLayer(rasterLayer, canvas);
}

/**
 * @brief LayerManager::addRasterLayer 打开栅格数据文件
 * @param layerPath 文件路径
 * @param canvas mapcanvas
 * @return 成功返回true否则返回false
 */
bool LayerManager::addRasterLayer(QString layerPath, QgsMapCanvas *canvas)
{
    QgsRasterLayer* rasterLayer = new QgsRasterLayer(layerPath, QFileInfo(layerPath).completeBaseName(), "gdal");
    return addCommonRasterLayer(rasterLayer, canvas);
}

/**
 * @brief LayerManager::addCommonRasterLayer 通用的加载栅格图层方法
 * @param rasterLayer 栅格图层
 * @param canvas mapcanvas
 * @return 成功返回true否则返回false
 */
bool LayerManager::addCommonRasterLayer(QgsRasterLayer* rasterLayer, QgsMapCanvas* canvas)
{
    qDebug()<< rasterLayer->extent();
    if ( !rasterLayer->isValid() )
    {
        return false;
    }
    this->rasterLayerNum++;
    this->rasterLayerSet.append(rasterLayer);
    this->addLayer(rasterLayer, canvas);
     qDebug()<<"获取数据";
    return true;
}

/**
 * @brief LayerManager::getSelectLayer
 * 获取当前选择的图层
 * @return
 */
QgsMapLayer* LayerManager::getSelectLayer()
{
    return this->selectLayer;
}


/**
 * @brief LayerManager::setSelectLayer
 * 修改当前选择的图层
 * @param layer
 */
void LayerManager::setSelectLayer(QgsMapLayer *layer)
{
    this->selectLayer = layer;
}

/**
 * @brief LayerManager::getSelectedLayerCache
 * 首先判断当前选择的涂层是否为矢量图层
 * @return
 */
QgsVectorLayerCache *LayerManager::getSelectedLayerCache()
{
    return NULL;
}




/**
 * @brief MainWindow::addLayer
 * 将图层添加到mapCanvas中
 * 1、首先将rasterLayerNum加一
 * 2、将图层添加到map中缩放至添加的图层
 * 3、图层管理中添加该图层名称
 * 4、修改当前选择的图层为该图层
 * @param layerToAdd
 */
void LayerManager::addLayer(QgsMapLayer *layerToAdd, QgsMapCanvas *canvas) {
    QgsMapLayer * add_layers = QgsProject::instance()->addMapLayer(layerToAdd, true);
    canvas->setExtent( layerToAdd->extent() );
    // 将栅格与矢量图层放在一个list中进行显示
    QList<QgsMapLayer*> allLayers;
    allLayers.append(add_layers);
    foreach(QgsMapLayer *vectorLayer, this->vectorLayerSet) {
        allLayers.append(vectorLayer);
    }
    foreach(QgsMapLayer *rasterLayer, this->rasterLayerSet) {
        allLayers.append(rasterLayer);
    }
    canvas->setLayers(allLayers);
    canvas->setVisible( true );
    canvas->freeze( false );
    canvas->refresh();
    selectLayer = layerToAdd;
}
