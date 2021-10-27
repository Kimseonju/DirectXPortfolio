#pragma once
#include "IMGUIWindow.h"
class CInspectorWindow :
	public CIMGUIWindow
{
public:
	CInspectorWindow();
	virtual ~CInspectorWindow();

private:
	class CIMGUITransformComponent* m_Transform;
	class CIMGUISpriteComponent* m_Sprite;
	class CIMGUICollider2DComponent* m_Collider2D;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void TransformUpdate(class CSceneComponent* Obj);
	void SpriteUpdate(class CSpriteComponent* Sprite);
	void CreateTransform();
	void CreateSprite();
	void CreateCollider2D();

	
};
