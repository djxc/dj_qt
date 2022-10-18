#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>

#include <qgsmapcanvas.h>
#include <qgssinglesymbolrenderer.h>

#include "layermanager.h"
#include "parsephotolatlon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void mouseMoveEvent(QMouseEvent *e);

private:
    Ui::MainWindow *ui;
    QLabel *label1, *label2, *xyLabel;
    QLineEdit *lineEdit;
    QPushButton *button;
    QgsMapCanvas *canvas;
    void initLayout();
    void addMenuAndToolbar();
    void splitteLayout();
    void testLayout();
    void zoomToLayer();
    void addLayerItem(QString layer_name);
    QgsSingleSymbolRenderer* symbolPoint();
    QTreeView *layerManager;
    int vectorLayerNum = 0;
    int rasterLayerNum = 0;
    QList<QgsMapLayer*> vectorLayerSet;
    QList<QgsMapLayer*> rasterLayerSet;
    LayerManager *layerManage;
    void initApp();
    void addCommonLayer(int layerType);

private slots:
    void showDialog();
    void addWMSLayer();
    void addWFSLayer();
    void showArea();
    void openVectorData();
    void openRasterData();
    void showLayerTable();
    void closeAllLayers();
    void treeViewClick(const QModelIndex & index);
    void readIMAGE();
    void getGPSfromImage();
    void receiveLayerData(QString layerName, QString layerUrl, int layerType);
    void test();
    void loadSpinalMap();
    void loadForestMap();
    void loadTerrainMap();
    QString openFile(QString type, QString title);

public slots:
    void showMousePoint(const QgsPointXY &p);
    void mouseClickEvent(const QKeyEvent &e);
};
#endif // MAINWINDOW_H
