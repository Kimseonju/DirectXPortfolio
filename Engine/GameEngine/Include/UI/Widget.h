#pragma once

#include "../Ref.h"
#include "../Resource/SpriteMesh.h"
#include "../Resource/Shader.h"
#include "../Resource/UIColorTintCBuffer.h"

class CWidget :
	public CRef
{
	friend class CViewport;
	friend class CScene;

protected:
	CWidget();
	CWidget(const CWidget& widget);
	virtual ~CWidget() = 0;

protected:
	class CViewport* m_Viewport;
	class CScene* m_Scene;
	class CWidgetWindow* m_Owner;
	CSharedPtr<CSpriteMesh> m_Mesh;
	CSharedPtr<CShader> m_Shader;
	class CUITransformConstantBuffer* m_TransformCBuffer;
	class CUIColorTintCBuffer* m_TintCBuffer;
	Vector2		m_Pos;
	Vector2		m_RenderPos;
	Vector2		m_Pivot;
	Vector2		m_Size;
	float		m_Rotation;
	int			m_ZOrder;
	bool		m_Start;
	float		m_WorldZ;
	bool		m_Blind;
	bool		m_bCollision;
public:
	bool IsCollision() const;
	bool IsBlind() const
	{
		return m_Blind;
	}
	bool IsStart()	const
	{
		return m_Start;
	}

	int GetZOrder()	const
	{
		return m_ZOrder;
	}

	Vector2 GetPos()	const;

	Vector2 GetPivot()	const
	{
		return m_Pivot;
	}

	Vector2 GetSize()	const
	{
		return m_Size;
	}

	float GetRotation()	const
	{
		return m_Rotation;
	}

	virtual void Enable(bool bEnable)
	{
		m_Enable = bEnable;
	}
	virtual bool IsEnable();
public:
	virtual void SetZOrder(int ZOrder);
	void SetCollision(bool Collision)
	{
		m_bCollision = Collision;
	}
	void SetBlind(bool Blind)
	{
		m_Blind = Blind;
	}
	
	void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}

	void SetPos(float x, float y)
	{
		m_Pos = Vector2(x, y);
	}

	void SetPivot(const Vector2& Pivot)
	{
		m_Pivot = Pivot;
	}

	void SetPivot(float x, float y)
	{
		m_Pivot = Vector2(x, y);
	}

	void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}

	void SetSize(float x, float y)
	{
		m_Size = Vector2(x, y);
	}

	void SetRotation(float Rotation)
	{
		m_Rotation = Rotation;
	}

	void SetColorTint(float r, float g, float b, float a)
	{
		m_TintCBuffer->SetTint(r, g, b, a);
	}

	void SetColorTint(const Vector4& Color)
	{
		m_TintCBuffer->SetTint(Color);
	}
	void SetAnimation2DEnable(bool Enable);
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render();
	virtual CWidget* Clone();

public:
	//付快胶 面倒贸府
	virtual void CollisionMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime);
	//付快胶 面倒哈绢车阑锭 贸府
	virtual void CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime);
public:
	void UpdateWorldTransformZ();
public:
	virtual void CallAnimNotify(const std::string& Name);
};
