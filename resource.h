﻿#pragma execution_character_set("utf-8")
#ifndef RESOURCE_H
#define RESOURCE_H
#include<QString>

namespace RESOURCE_CENTER {

    const QString static open_ttl = "打开";
    const QString static new_ttl = "新建";
    const QString static vector_layer_ttl = "矢量";
    const QString static raster_layer_ttl = "栅格";
    const QString static layer_manage_ttl = "图层管理";
    const QString static close_all_layer_ttl = "关闭所有";
}

class Resource
{
public:
    Resource();

};

#endif // RESOURCE_H
