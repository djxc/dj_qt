#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

/**
  程序主入口
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    printf("%s", "home\n");
    printf("djxc\n");
    MainWindow w;
    w.show();

    return a.exec();
}
