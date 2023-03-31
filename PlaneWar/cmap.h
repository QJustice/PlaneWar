#ifndef CMAP_H
#define CMAP_H

#include <QPixmap>

class CMap
{
public:
    // 构造函数
    CMap();

    // 地图滚动坐标计算
    void mapPosition();

    // 地图图片对象
    QPixmap m_map1;
    QPixmap m_map2;

    // 地图Y轴坐标
    int m_map1_posY;
    int m_map2_posY;

    // 地图滚动幅度
    int m_scroll_speed;
};

#endif // CMAP_H
