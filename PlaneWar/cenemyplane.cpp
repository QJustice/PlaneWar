#include "cenemyplane.h"
#include "config.h"

CEnemyPlane::CEnemyPlane()
{
    // 敌机资源加载
    this->m_enemy.load(ENEMY_PATH);

    // 敌机位置
    this->m_X = 0;
    this->m_Y = 0;

    // 敌机状态
    this->m_Free = true;

    // 敌机速度
    this->m_Speed = ENEMY_SPEED;

    // 敌机矩形
    this->m_Rect.setWidth(this->m_enemy.width());
    this->m_Rect.setHeight(this->m_enemy.height());
    this->m_Rect.moveTo(this->m_X,this->m_Y);
}

void CEnemyPlane::updatePosition()
{
    // 空闲状态，不计算坐标
    if(this->m_Free)
    {
        return;
    }

    this->m_Y += this->m_Speed;
    this->m_Rect.moveTo(this->m_X,this->m_Y);

    if(this->m_Y >= GAME_HEIGHT)
    {
        this->m_Free = true;
    }
}
