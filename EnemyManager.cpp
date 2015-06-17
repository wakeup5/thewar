#include "stdafx.h"
#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::initialize()
{
	_vEnemy = new VEnemy;
	OBJECTMANAGER->addObject(GUID_ENEMYS, _vEnemy);

	_bullet = new Bullet;
	_bullet->initialize(800);
	OBJECTMANAGER->addObject(GUID_ENEMY_BULLET, _bullet);

	return S_OK;
}
void EnemyManager::release()
{
	for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end(); _viEnemy = _vEnemy->erase(_viEnemy));
	_vEnemy->clear();
	SAFE_DELETE(_vEnemy);
}
void EnemyManager::update()
{
	Bullet::LBullet* playerBullet = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_BULLET)->getBullet();
	UI* ui = OBJECTMANAGER->findObject<UI>(GUID_UI);
	RECT r;
	for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end();)
	{
		(*_viEnemy)->update();

		//플레이어 총알과 충돌처리
		for (Bullet::LIBullet liBullet = playerBullet->begin(); liBullet != playerBullet->end();)
		{
			if (IntersectRect(&r, &(*liBullet)->getRect(), &(*_viEnemy)->getRect()))
			{
				(*_viEnemy)->setHp((*_viEnemy)->getHp() - (*liBullet)->getDamage());
				(*_viEnemy)->hit();
				EFFECTMANAGER->addEffect(IMAGEMANAGER->findImage("water ball pop")->getSpriteImage((*liBullet)->getX(), (*liBullet)->getY(), 4, 1));

				liBullet = playerBullet->erase(liBullet);
			}
			else
			{
				liBullet++;
			}
		}

		if ((*_viEnemy)->getHp() <= 0)
		{
			ui->setKillNum(ui->getKillNum() - 1);
			_viEnemy = _vEnemy->erase(_viEnemy);
		}
		else
		{
			_viEnemy++;
		}
	}

	_bullet->update();
	//printf("enemy size : %d\n", _vEnemy->size());
}
void EnemyManager::render()
{
	for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end(); _viEnemy++)
	{
		(*_viEnemy)->render();
	}

	_bullet->render();
}
void EnemyManager::addEnemy(float x, float y)
{
	Enemy* enemy = new Enemy;
	enemy->initialize();
	enemy->setPosition(x, y);

	_vEnemy->push_back(enemy);
}

void EnemyManager::addBoss(float x, float y, float hp)
{
	Enemy* enemy = new EnemyBoss;
	enemy->initialize();
	enemy->setPosition(x, y);
	enemy->setHp(hp);

	_vEnemy->push_back(enemy);
}

void EnemyManager::clear()
{
	for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end(); _viEnemy = _vEnemy->erase(_viEnemy));
	_vEnemy->clear();
}