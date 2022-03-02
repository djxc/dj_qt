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
 * @brief LayerManager::addVectorLayer
 * 打开矢量数据
 */
bool LayerManager::addVectorLayer(QString layerPath, QgsMapCanvas *canvas)
{

    QgsVectorLayer  *layer = new QgsVectorLayer(layerPath, QFileInfo(layerPath).completeBaseName(),"ogr");
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
 * @brief LayerManager::addRasterLayer
 * 打开栅格数据
 */
bool LayerManager::addRasterLayer(QString layerPath, QgsMapCanvas *canvas)
{
    QgsRasterLayer* rasterLayer = new QgsRasterLayer(layerPath, QFileInfo(layerPath).completeBaseName(), "gdal");
     qDebug()<< rasterLayer->extent();
    if ( !rasterLayer->isValid() )
    {
        return false;
    }
    this->rasterLayerNum++;
    this->rasterLayerSet.append(rasterLayer);
    this->addLayer(rasterLayer, canvas);
     qDebug()<<"获取tif数据";
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
    foreach(QgsMapLayer *rasterLayer, this->rasterLayerSet) {
        allLayers.append(rasterLayer);
    }
    foreach(QgsMapLayer *vectorLayer, this->vectorLayerSet) {
        allLayers.append(vectorLayer);
    }
    canvas->setLayers(allLayers);
    canvas->setVisible( true );
    canvas->freeze( false );
    canvas->refresh();
    selectLayer = layerToAdd;
}
