#include "point_symbol.h"

#include <qgsmarkersymbollayer.h>
PointSymbol::PointSymbol()
{

}

/**
 * 根据输入的图片位置，生成该图片的样式
 * @brief PointSymbol::createPictureSymbol
 * @param layer_name
 * @return QgsSingleSymbolRenderer
 */
QgsSingleSymbolRenderer* PointSymbol::createPictureSymbol(QString picture_path) {
    QgsSvgMarkerSymbolLayer *svgMarkSymbol = new QgsSvgMarkerSymbolLayer(picture_path);
    svgMarkSymbol->setSize(8.0);
    QgsSymbolLayerList symbolList;
    symbolList.append(svgMarkSymbol);

    QgsMarkerSymbol *markSymbol = new QgsMarkerSymbol(symbolList);
    QgsSingleSymbolRenderer *singleRender = new QgsSingleSymbolRenderer(markSymbol);
    return singleRender;
}
