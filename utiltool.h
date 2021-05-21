#ifndef UTILTOOL_H
#define UTILTOOL_H
#include <string>
#include <qstring.h>
#include <QFileDialog>

class utilTool
{
public:
    utilTool();
    void sayHello();
    QString openFile(QWidget *parent, QString fileType);
};

#endif // UTILTOOL_H
