#include "cmainscene.h"
#include "config.h"
#include <QIcon>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include <QSoundEffect>

CMainScene::CMainScene(QWidget *parent)
    : QWidget(parent)
{
    // 初始化场景
    this->initScene();

    // 启动游戏
    this->playGame();
}

CMainScene::~CMainScene()
{
}

void CMainScene::initScene()
{
   // 初始化窗口大小
   this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);

   // 设置窗口标题
   this->setWindowTitle(GAME_TITLE);

    // 设置图标资源
   this->setWindowIcon(QIcon( GAME_ICON));  // 加头文件 #include <QIcon>

    // 定时器设置
    this->m_Timer.setInterval(GAME_RATE);

    this->m_recorder = 0;

    // 随机数种子
    srand((unsigned int)time(NULL));  // 头文件  #include <ctime>
}

void CMainScene::playGame()
{
    // 背景音乐
    QSoundEffect *background_sound = new QSoundEffect(this);
    background_sound->setSource(QUrl::fromLocalFile(SOUND_BACKGROUND));
    background_sound->setLoopCount(QSoundEffect::Infinite);
    background_sound->play();

    // 启动定时器
    this->m_Timer.start();

    // 监听定时器
    connect(&(this->m_Timer),&QTimer::timeout,[=](){
        //敌机出场
        enemyToScene();
        // 更新游戏中元素的坐标
        updatePosition();
        // 重新绘制图片
        update();
        // 碰撞检测
        collisionDetection();
    });
}

void CMainScene::updatePosition()
{
    // 更新地图坐标
    this->m_map.mapPosition();
    // 测试子弹代码
    // this->temp_bullet.m_Free = false;
    // this->temp_bullet.updatePosition();
    // 发射子弹
    this->m_hero.shoot();
    // 计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        // 如果子弹状态为非空闲，计算发射位置
        if(!this->m_hero.m_bullets[i].m_Free)
        {
            this->m_hero.m_bullets[i].updatePosition();
        }
    }
    // 敌机坐标计算
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        // 非空闲敌机 更新坐标
       if(this->m_enemys[i].m_Free == false)
       {
          this->m_enemys[i].updatePosition();
       }
    }
    //计算爆炸播放的图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
           m_bombs[i].updateInfo();
        }
    }
}

void CMainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制地图
    painter.drawPixmap(0,this->m_map.m_map1_posY , this->m_map.m_map1);
    painter.drawPixmap(0,this->m_map.m_map2_posY , this->m_map.m_map2);

    // 绘制英雄
    painter.drawPixmap(this->m_hero.m_X,this->m_hero.m_Y,this->m_hero.m_Plane);

    // 测试子弹代码
    // painter.drawPixmap(this->temp_bullet.m_X,this->temp_bullet.m_Y,this->temp_bullet.m_Bullet);
    // 绘制子弹
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        // 如果子弹状态为非空闲，计算发射位置
        if(!this->m_hero.m_bullets[i].m_Free)
        {
            painter.drawPixmap(this->m_hero.m_bullets[i].m_X,this->m_hero.m_bullets[i].m_Y,this->m_hero.m_bullets[i].m_Bullet);
        }
    }
    // 绘制敌机
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(this->m_enemys[i].m_Free == false)
        {
            painter.drawPixmap(this->m_enemys[i].m_X,this->m_enemys[i].m_Y,this->m_enemys[i].m_enemy);
        }
    }
    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
           painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }
}

void CMainScene::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x() - this->m_hero.m_Rect.width()*0.5; //鼠标位置 - 飞机矩形的一半
    int y = event->y() - this->m_hero.m_Rect.height()*0.5;

    // 边界检测
    if(x <= 0 )
    {
        x = 0;
    }
    if(x >= GAME_WIDTH - this->m_hero.m_Rect.width())
    {
        x = GAME_WIDTH - this->m_hero.m_Rect.width();
    }
    if(y <= 0)
    {
        y = 0;
    }
    if(y >= GAME_HEIGHT - this->m_hero.m_Rect.height())
    {
        y = GAME_HEIGHT - this->m_hero.m_Rect.height();
    }
    this->m_hero.setPosition(x,y);
}

void CMainScene::enemyToScene()
{
    this->m_recorder++;
    if(this->m_recorder < ENEMY_INTERVAL)
    {
        return;
    }

    this->m_recorder = 0;

    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(this->m_enemys[i].m_Free)
        {
            // 敌机空闲状态改为false
            this->m_enemys[i].m_Free = false;
            // 设置坐标
            this->m_enemys[i].m_X = rand() % (GAME_WIDTH - this->m_enemys[i].m_Rect.width());
            this->m_enemys[i].m_Y = -this->m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void CMainScene::collisionDetection()
{
    // 遍历所有非空闲的敌机
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        if(this->m_enemys[i].m_Free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        // 遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(this->m_hero.m_bullets[j].m_Free)
            {
                // 空闲子弹 跳转下一次循环
                continue;
            }

            // 如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
            if(this->m_enemys[i].m_Rect.intersects(this->m_hero.m_bullets[j].m_Rect))
            {
                this->m_enemys[i].m_Free = true;
                this->m_hero.m_bullets[j].m_Free = true;
                // 播放爆炸音效
                QSoundEffect *bomb_sound = new QSoundEffect(this);
                bomb_sound->setSource(QUrl::fromLocalFile(SOUND_BOMB));
                bomb_sound->setLoopCount(QSoundEffect::Infinite);
                bomb_sound->play();
                // 播放爆炸效果
                for(int k = 0 ; k < BOMB_NUM;k++)
                {
                    if(this->m_bombs[k].m_Free)
                    {
                        QSoundEffect bomb_sound;
                        bomb_sound.setSource(QUrl::fromLocalFile(SOUND_BACKGROUND));
                        bomb_sound.setLoopCount(QSoundEffect::Infinite);
                        bomb_sound.play();
                        // 爆炸状态设置为非空闲
                        this->m_bombs[k].m_Free = false;
                        // 更新坐标

                        this->m_bombs[k].m_X = m_enemys[i].m_X;
                        this->m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }
}

