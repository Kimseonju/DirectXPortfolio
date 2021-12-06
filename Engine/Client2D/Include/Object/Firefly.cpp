#include "Firefly.h"
#include <Input.h>
#include "../UI/UIManager.h"
#include "../UI/MiniMap.h"
#include "Player.h"
#include "../GlobalValue.h"
CFirefly::CFirefly():
	m_NextPos(Vector2(0.f, 0.f)),
	m_OldPos(Vector2(0.f,0.f)),
	m_MoveTimer(0.f)
{
}

CFirefly::CFirefly(const CFirefly& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CFirefly::~CFirefly()
{
}

void CFirefly::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Sprite->Enable(bEnable);
	m_Collider2D->Enable(bEnable);
}

void CFirefly::Start()
{
	CGameObject::Start();

}

bool CFirefly::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_SpriteBlend = CreateSceneComponent<CSpriteComponent>("SpriteBlend");


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_SpriteBlend);
	m_Sprite->AddChild(m_Collider2D);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(10.f, 10.f, 0.f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	{
		CMaterial* Material = m_Sprite->GetMaterial(0);
		Material->AddTexture("FireFly2", TEXT("object/Firefly2.png"));
		Material->SetBaseColor(231.f / 255.f, 102.f / 255.f, 229.f / 255.f, 0.8f);
	}

	m_SpriteBlend->SetPivot(0.5f, 0.5f, 0.f);
	m_SpriteBlend->SetWorldScale(50.f, 50.f, 0.f);
	m_SpriteBlend->SetRender2DType(Render_Type_2D::RT2D_Particle);

	{
		CMaterial* Material = m_SpriteBlend->GetMaterial(0);
		Material->AddTexture("FireFlyBlend", TEXT("object/FireFlyBlend.png"));
		Material->SetBaseColor(231.f / 255.f, 102.f / 255.f, 229.f / 255.f, 0.4f);
	}


	m_Collider2D->SetCollisionProfile("Object");
	m_Collider2D->AddCollisionCallbackFunction<CFirefly>(Collision_State::Begin, this,
		&CFirefly::CollisionBegin);


	m_Collider2D->SetExtent(0.2f, 0.2f);
	m_Collider2D->Enable(false);
	return true;
}

void CFirefly::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_MoveTimer += DeltaTime/2.f;
	if (m_MoveTimer < 1.f)
	{
		Vector3 Pos = GetWorldPos();
		Vector2 Pos2 = Vector2(Pos.x, Pos.y);
		if (Pos2 != m_NextPos)
		{
			Vector2 LerpPos = m_OldPos.Lerp2DMax(m_OldPos, m_NextPos, m_MoveTimer);
			SetWorldPos(LerpPos.x, LerpPos.y, 0.f);

		}
	}
	else
	{
		m_Collider2D->Enable(true);
		CPlayer* player = CGlobalValue::MainPlayer;
		Vector3 Pos = player->GetWorldPos() - GetWorldPos();
		Pos.z = 0.f;
		Pos.Normalize();
		Pos *= 300.f*DeltaTime;
		AddWorldPos(Pos);
	}
}

void CFirefly::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CFirefly::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CFirefly::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);
	CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(4.f, 4.f), Vector4(0.f / 255.f, 0.f / 255.f, 255.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);

}

void CFirefly::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CFirefly* CFirefly::Clone()
{
	return new CFirefly(*this);
}

void CFirefly::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		Active(false);
	}
}
