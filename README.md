﻿# 利用osgeo4w安装qgis开发环境
- 1、首先安装osgeo4w，选择qgis，勾选libs下的所有。
- 2、不采用osgeo4w自带的qt，自己重新安装qt与qtceator（利用vs没有搞定）
- 3、在项目环境中配置osgeo4w的依赖，并将一些dll库放在release文件夹下，不然会包找不到xxx.dll库错误。

# 学习使用qt
- 1、安装qt集成开发环境，qtcreator
- 2、创建简单的窗口，显示界面元素
- 3、注册元素响应事件，实现交互

# my qgis开发：
- 1、使用splitter分割界面，将界面划分为左右两部分。右边为地图显示窗口；左边又分为上下两部分，上部为图层列表；下部为属性表。
- 2、添加菜单栏以及工具栏。
- 3、加载栅格数据以及矢量数据。
- 4、显示矢量数据的属性表。
- 5、给矢量点图层渲染svg图标。
- 6、点击图层列表，缩放至选中的图层

# 项目proj.db出现问题
- 1、修改项目构建环境，PROJ_LIB修改为osgeo4w文件下的OSGeo4W64\share\proj
- 2、gdal在osgeo4w安装时已经安装了，可以直接使用，需要在项目中添加LIBS += -L"D:\Program Files (x86)\OSGeo4W64\lib" -lgdal_i

# QGIS中添加WFS图层
- 1、WFS图层添加与矢量图层添加逻辑类似，仅需要修改类型为WFS
```C++
    QgsVectorLayer *testLayer = new QgsVectorLayer(
        "http://localhost:8090/geoserver/wfs?service=wfs&version=1.1.0&request=GetFeature&typeName=topp:states",
        "test", "WFS");
```

- 2、WMS图层添加，
```c++
    QgsRasterLayer* rasterLayer = new QgsRasterLayer("url=http://localhost:8090/geoserver/nurc/wms&layers=Img_Sample&styles=&format=image/png&crs=EPSG:4326",
                         "name", "WMS");
```
- 3、XYZ图层加载
```
    type=xyz&url=http://c.tile.openstreetmap.org/{z}/{x}/{y}.png
```
https://webrd02.is.autonavi.com/appmaptile?lang=zh_cn&size=1&scale=1&style=8&x={x}&y={y}&z={z}


# 加载图层时报错 proj_identify: Cannot find proj.db
在项目中添加运行环境变量PROJ_LIB=D:\Program Files (x86)\OSGeo4W64\share\proj即可解决问题

# 编译时报错，常量中有换行符
1、首先需要在工具-》选项-》文件编辑器 文件编码修改为”如果编码是UTF-8则添加“
2、菜单栏->编辑->Slect Encoding...->UTF-8->按编码保存、
3、在需要的头文件中加入#pragma execution_character_set("utf-8")即可
