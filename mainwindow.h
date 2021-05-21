#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>

#include <qgsmapcanvas.h>
#include <qgssinglesymbolrenderer.h>

#include "utiltool.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QLabel *label1, *label2;
    QLineEdit *lineEdit;
    QPushButton *button;
    QgsMapCanvas *canvas;
    QgsVectorLayer *selectVectorLayer = NULL;
    void initLayout();
    void addMenuAndToolbar();
    void splitteLayout();
    void testLayout();
    void zoomToLayer();
    void addLayer(QgsMapLayer *layerToAdd, QString layer_type);
    QgsSingleSymbolRenderer* symbolPoint();
    QTreeView *layerManage;         // 树状图层管理
    int vectorLayerNum = 0;         // 矢量图层的个数
    int rasterLayerNum = 0;         // 栅格图层的个数
    QList<QgsMapLayer*> vectorLayerSet;     // 矢量图层集
    QList<QgsMapLayer*> rasterLayerSet;     // 栅格图层集

private slots:
    void showDialog();
    void showArea();
    void openVectorData();
    void openRasterData();
    void showLayerTable();
    void closeAllLayers();
    void treeViewClick(const QModelIndex & index);
    void readIMAGE();
    void getGPSfromImage();
    QString openFile(QString type, QString title);
};

#endif // MAINWINDOW_H
