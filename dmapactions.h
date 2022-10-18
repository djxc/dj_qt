#ifndef DMAPACTIONS_H
#define DMAPACTIONS_H

#include "qgsmaptool.h"
#include <QDebug>


class DMapActions: public QgsMapTool
{
public:
    DMapActions(QgsMapCanvas *canvas);
    virtual void canvasPressEvent( QgsMapMouseEvent *e );
};

#endif // DMAPACTIONS_H
