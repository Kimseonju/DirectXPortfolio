#pragma once
#include <GameEngine.h>
#include <GameObject.h>
#include "Object/Enemy.h"

class CRoomInfo
{
	Vector2 m_MapCount;
	
	std::list<CSharedPtr<CEnemy>>	m_AllEnemy;
	std::list<CSharedPtr<CGameObject>>m_AllObejct;
	std::list<CSharedPtr<CGameObject>>m_AllTear;

	//���� �� �׾���� �״� ������Ʈ
	std::list<CSharedPtr<CGameObject>>m_AllEnemyInvincibility;


};

