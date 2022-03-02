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

private:
    Ui::MainWindow *ui;
    QLabel *label1, *label2;
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
