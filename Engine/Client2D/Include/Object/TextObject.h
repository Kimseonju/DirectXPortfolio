#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include <Component/RigidBodyComponent.h>
#include "../UI/TextWidget.h"
#include "../BasicStatus.h"

class CTextObject :
	public CGameObject
{
	friend class CScene;

protected:
	CTextObject();
	CTextObject(const CTextObject& obj);
	virtual ~CTextObject();

protected:
	CSharedPtr<CWidgetComponent> m_WidgetComponent;
	class CTextWidget* m_Widget;
	CSharedPtr<CRigidBodyComponent> m_RigidBodyComponent;

	float			m_LifeTime;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTextObject* Clone();

public:
	void SetText(std::string Text);
	void Gold();
	void Damage();
};
