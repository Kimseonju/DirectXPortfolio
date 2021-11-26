#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include <Component/TileMapComponent.h>
class CEndingTerrain :
	public CGameObject
{
	friend class CScene;

protected:
	CEndingTerrain();
	CEndingTerrain(const CEndingTerrain& obj);
	virtual ~CEndingTerrain();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CTileMapComponent> m_TileMap;

protected:
public:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEndingTerrain* Clone();
};
