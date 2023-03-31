#include "cmap.h"
#include "config.h"

CMap::CMap()
{
    // 初始化加载地图对象
    this->m_map1.load(MAP_PATH);
    this->m_map2.load(MAP_PATH);

    // 设置地图其实y轴坐标
    this->m_map1_posY = -GAME_HEIGHT;
    this->m_map2_posY = 0;

    // 设置地图滚动速度
    this->m_scroll_speed = MAP_SCROLL_SPEED;
}

void CMap::mapPosition()
{
    // 处理第一张图片滚动
    this->m_map1_posY += MAP_SCROLL_SPEED;
    if(this->m_map1_posY >= 0)
    {
        this->m_map1_posY =-GAME_HEIGHT;
    }

    // 处理第二张图片滚动
    this->m_map2_posY += MAP_SCROLL_SPEED;
    if(this->m_map2_posY >= GAME_HEIGHT )
    {
        this->m_map2_posY =0;
    }
}
