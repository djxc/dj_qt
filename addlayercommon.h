#ifndef ADDLAYERCOMMON_H
#define ADDLAYERCOMMON_H

#include <QDialog>
#include <qlineedit.h>

namespace Ui {
    class AddLayerCommon;
}

/**
 * @brief The AddLayerCommon class
 * 通用图层加载对象
 */
class AddLayerCommon : public QDialog
{
    Q_OBJECT

public:
    explicit AddLayerCommon(int layerType, QWidget *parent = nullptr);
    ~AddLayerCommon();
    QString getDataURL();
    QString getLayerName();

private:
    Ui::AddLayerCommon *ui;
    QLineEdit *urlLineEdit;
    QLineEdit *layerNameEdit;
    void init();
    int layerType;

signals:
    void sendLayerData(QString layerName, QString layerUrl, int layerType);


private slots:
    void addLayerClose();
    void closeWithNoLayer();

};

#endif // ADDLAYERCOMMON_H
