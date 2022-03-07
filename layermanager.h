#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <qgsmapcanvas.h>
#include <qgsmaplayer.h>
#include <qgsvectorlayercache.h>

class LayerManager
{
public:
    LayerManager();
    QgsMapLayer *selectLayer = NULL;
    bool addVectorLayer(QString layerPath, QgsMapCanvas *canvas);
    bool addRasterLayer(QString layerPath, QgsMapCanvas *canvas);
//    removeLayer();
//    closeAllLayer();
    int vectorLayerNum = 0;
    int rasterLayerNum = 0;
    QgsMapLayer* getSelectLayer();

    void setSelectLayer(QgsMapLayer *Layer);
    QgsVectorLayerCache* getSelectedLayerCache();

    bool addWMSLayer(QString layerPath, QgsMapCanvas *canvas, QString layerName);
    bool addCommonRasterLayer(QgsRasterLayer *rasterLayer, QgsMapCanvas *canvas);
    bool addCommonVectorLayer(QgsVectorLayer *layer, QgsMapCanvas *canvas);
    bool addWFSLayer(QString layerURL, QString layerName, QgsMapCanvas *canvas);
private:
    QList<QgsMapLayer*> vectorLayerSet;
    QList<QgsMapLayer*> rasterLayerSet;
    void addLayer(QgsMapLayer *layerToAdd, QgsMapCanvas *canvas);
};

#endif // LAYERMANAGER_H
