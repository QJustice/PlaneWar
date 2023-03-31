#include "cheroplane.h"
#include "config.h"

CHeroPlane::CHeroPlane()
{
    // 初始化加载飞机图片资源
    this->m_Plane.load(HERO_PATH);

    // 初始化坐标
    this->m_X = GAME_WIDTH * 0.5 - this->m_Plane.width()*0.5;
    this->m_Y = GAME_HEIGHT - this->m_Plane.height();

    // 初始化矩形框
    this->m_Rect.setWidth(this->m_Plane.width());
    this->m_Rect.setHeight(this->m_Plane.height());
    this->m_Rect.moveTo(this->m_X,this->m_Y);

    // 初始化发射间隔记录
    this->m_recorder = 0;
}

void CHeroPlane::shoot()
{
    // 累加时间间隔记录变量
    this->m_recorder++;
    // 判断如果记录数字 未达到发射间隔，直接return
    if(this->m_recorder < BULLET_INTERVAL)
    {
        return;
    }
    // 到达发射时间处理
    // 重置发射时间间隔记录
    this->m_recorder = 0;

    // 发射子弹
    for(int i = 0 ; i < BULLET_NUM;i++)
    {
        // 如果是空闲的子弹进行发射
        if(this->m_bullets[i].m_Free)
        {
            // 将改子弹空闲状态改为假
            this->m_bullets[i].m_Free = false;
            // 设置发射的子弹坐标
            this->m_bullets[i].m_X = this->m_X + this->m_Rect.width()*0.5 - 10;
            this->m_bullets[i].m_Y = this->m_Y - 25 ;
            break;
        }
    }
}

void CHeroPlane::setPosition(int x, int y)
{
    this->m_X = x;
    this->m_Y = y;
    this->m_Rect.moveTo(this->m_X,this->m_Y);
}
