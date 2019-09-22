#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

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
private slots:
    void showArea();
};

#endif // MAINWINDOW_H
