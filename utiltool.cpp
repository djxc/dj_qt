#include "utiltool.h"

utilTool::utilTool()
{
}

/**
 * @brief utilTool::openFile
 * 打开文件对话框
 * @param parent
 * @param type
 * @return
 */
QString utilTool::openFile(QWidget *parent, QString type) {
    QString path = QFileDialog::getOpenFileName(parent, QString("Open File"),
                                                QString(),type);
    if (path.isEmpty())
    {
        return "";
    }
    return path;
}
