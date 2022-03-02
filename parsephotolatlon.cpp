#include "parsephotolatlon.h"
#include<qdebug.h>

#include "exif.h"

ParsePhotoLatLon::ParsePhotoLatLon()
{

}

void ParsePhotoLatLon::getGPSfromImage(QString photoPath)
{
    // 读取jpg文件到缓冲区
    FILE *fp = fopen(photoPath.toStdString().c_str(), "rb");
    if (!fp) {
        qDebug() << "Can't open file.\n";
        return;
    }
    // 文件偏移，此处将文件流移动到文件末尾，为了接下来计算文件大小。
    fseek(fp, 0, SEEK_END);
    // 文件流在文件中的当前位置
    unsigned long fsize = ftell(fp);
    // 将文件流位置设为文件的开头
    rewind(fp);
    // 将文件读取到缓冲区字节数组buf中，fread读取成功会返回读取的元素的个数
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
        qDebug() << "Can't read file.\n";
        delete[] buf;
        return;
    }
    fclose(fp);

    // Parse EXIF
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    QString str;
    if (code) {
        str.sprintf("Error parsing EXIF: code %d\n", code);
        qDebug()<<str;
        return;
    }
    // Dump EXIF information
    str.sprintf("Camera make          : %s\n"
                "Camera model         : %s\n"
                "Software             : %s\n",
                result.Make.c_str(), result.Model.c_str(), result.Software.c_str());
    qDebug()<<str;
    str.sprintf("GPS Latitude         : %f deg (%f deg, %f min, %f sec %c)\n",
                result.GeoLocation.Latitude, result.GeoLocation.LatComponents.degrees,
                result.GeoLocation.LatComponents.minutes,
                result.GeoLocation.LatComponents.seconds,
                result.GeoLocation.LatComponents.direction);
    qDebug()<<str;
    str.sprintf("GPS Longitude        : %f deg (%f deg, %f min, %f sec %c)\n",
                result.GeoLocation.Longitude, result.GeoLocation.LonComponents.degrees,
                result.GeoLocation.LonComponents.minutes,
                result.GeoLocation.LonComponents.seconds,
                result.GeoLocation.LonComponents.direction);
    qDebug()<<str;
    str.sprintf("GPS Altitude         : %f m\n", result.GeoLocation.Altitude);
    qDebug()<<str;
    str.sprintf("GPS Precision (DOP)  : %f\n", result.GeoLocation.DOP);
    qDebug()<<str;
}
