#pragma once
#include "IMGUIWindow.h"
#include "GameEngine.h"
class CInspectorWindow :
	public CIMGUIWindow
{
public:
	CInspectorWindow();
	virtual ~CInspectorWindow();

private:
	class CIMGUIObjectInfoComponent* m_Object;
	class CIMGUITransformComponent* m_Transform;
	class CIMGUISpriteComponent* m_Sprite;
	class CIMGUICollider2DComponent* m_Collider;
	class CIMGUICameraComponent* m_Camera;

	
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void ObjectUpdateInfo(class CGameObject* Obj);
	void TransformUpdate(class CSceneComponent* Obj);
	void SpriteUpdate(class CSpriteComponent* Sprite);
	void ColliderUpdate(class CCollider* Collider);
	void CameraUpdate(class CCamera* Camera);
	void CreateObjectInfo();
	void CreateTransform();
	void CreateSprite();
	void CreateCollider();
	void CreateCamera();
	void AllComponentClose();
	
};
