#pragma once

#include "Item.h"
#include "Component/SpriteComponent.h"


class CTaana :
	public CItem
{
	friend class CScene;

protected:
	CTaana();
	CTaana(const CTaana& obj);
	virtual ~CTaana();


protected:
	CAnimation2D* m_Animation2D;
public:
	virtual void Enable(bool bEnable);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTaana* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};
