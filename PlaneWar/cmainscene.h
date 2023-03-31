#ifndef CMAINSCENE_H
#define CMAINSCENE_H

#include <QWidget>
#include "cmap.h"
#include <QTimer>
#include "cheroplane.h"
#include "cbullet.h"
#include "cenemyplane.h"
#include "cbomb.h"

class CMainScene : public QWidget
{
    Q_OBJECT

public:
    CMainScene(QWidget *parent = nullptr);
    ~CMainScene();

    void  initScene();
    // 启动游戏  用于启动定时器对象
    void playGame();
    // 更新坐标
    void updatePosition();
    // 绘图事件
    void paintEvent(QPaintEvent *event);
    // 重写鼠标移动事件 函数名不可改
    void mouseMoveEvent(QMouseEvent *event) override;
    // 地图对象
    CMap m_map;
    // 飞机对象
    CHeroPlane m_hero;
    // 定时器
    QTimer m_Timer;
    // 测试子弹代码
    // CBullet temp_bullet;
    // 敌机出场
    void enemyToScene();

    // 敌机数组
    CEnemyPlane m_enemys[ENEMY_NUM];

    // 敌机出场间隔记录
    int m_recorder;

    void collisionDetection();

    // 爆炸数组
    CBomb m_bombs[BOMB_NUM];
};
#endif // CMAINSCENE_H
