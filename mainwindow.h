#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <qgsmapcanvas.h>

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
    void initLayout();
    void addMenuAndToolbar();
    void splitteLayout();
    void testLayout();

private slots:
    void showDialog();
    void showArea();
    void openVectorData();
    void openRasterData();
};

#endif // MAINWINDOW_H
