# 利用osgeo4w安装qgis开发环境
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
