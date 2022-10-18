#include "dmapactions.h"

DMapActions::DMapActions(QgsMapCanvas* canvas)
    :QgsMapTool(canvas)
{

}

void DMapActions::canvasPressEvent(QgsMapMouseEvent *e)
{
      qDebug() << "图层加载成功";
}
