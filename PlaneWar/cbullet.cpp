#include "cbullet.h"

CBullet::CBullet()
{
    // 加载子弹资源
    this->m_Bullet.load(BULLET_PATH);

    // 子弹坐标 初始坐标可随意设置，后期会重置
    this->m_X = GAME_WIDTH*0.5 - this->m_Bullet.width()*0.5;
    this->m_Y = GAME_HEIGHT;

    // 子弹状态
    this->m_Free = true;

    // 子弹速度
    this->m_Speed = BULLET_SPEED;

    // 子弹矩形框
    this->m_Rect.setWidth(this->m_Bullet.width());
    this->m_Rect.setHeight(this->m_Bullet.height());
    this->m_Rect.moveTo(this->m_X,this->m_Y);
}

void CBullet::updatePosition()
{
    // 如果子弹是空闲状态，不需要坐标计算
    // 玩家飞机可以控制子弹的空闲状态为false
    if(this->m_Free)
    {
        return;
    }

    // 子弹向上移动
    this->m_Y  -= this->m_Speed;
    this->m_Rect.moveTo(this->m_X,this->m_Y);

    if(this->m_Y <= -this->m_Rect.height())
    {
        this->m_Free = true;
    }
}
