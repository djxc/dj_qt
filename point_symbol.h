#ifndef POINTSYMBOL_H
#define POINTSYMBOL_H

#include <QString>
#include <qgssinglesymbolrenderer.h>

/**
 * @brief The PointSymbol class
 * 点状样式
 */
class PointSymbol
{
public:
    PointSymbol();
    QgsSingleSymbolRenderer* createPictureSymbol(QString picture_path);
};

#endif // POINTSYMBOL_H
