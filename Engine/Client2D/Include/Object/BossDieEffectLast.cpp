#include "BossDieEffectLast.h"
#include <Scene/Scene.h>
#include "BossDieParticle.h"
#include "Belial.h"
#include <Scene/SceneResource.h>
#include "BossDieEffect.h"
CBossDieEffectLast::CBossDieEffectLast() :
	m_SpawnCountMax(6.f),
	m_SpawnCount(0.f),
	m_SpawnTimerMax(0.2f),
	m_SpawnTimer(0.f)

{
}

CBossDieEffectLast::CBossDieEffectLast(const CBossDieEffectLast& obj) :
	CEffectObject(obj)
{

}

CBossDieEffectLast::~CBossDieEffectLast()
{
}

void CBossDieEffectLast::Start()
{
}

bool CBossDieEffectLast::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(31.f, 31.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("ObjectDieEffect", false);
	m_Animation2D->SetFrameEndFunction<CBossDieEffectLast>(this, &CEffectObject::AnimationFrameEnd);
	m_Animation2D->SetSequencePlayRate("ObjectDieEffect", 2.f);
	//m_pScene->GetResource()->FindSound("EnemyDie")->Play();

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);

	return true;
}

void CBossDieEffectLast::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
	m_SpawnTimer += DeltaTime;
	if (m_SpawnCount == m_SpawnCountMax)
	{
		m_Belial->EffectEnd();
		return;
	}
	if (m_SpawnTimer >= m_SpawnTimerMax)
	{
		m_SpawnCount++;
		m_SpawnTimer -= m_SpawnTimerMax;
		for (int i = 0; i < 8; ++i)
		{
			CBossDieEffect* Effect = m_pScene->SpawnObject<CBossDieEffect>("BossDieEffect");
			Effect->SetWorldPos(GetWorldPos());
			Effect->SetWorldRotationZ(45.f * i);
			Effect->AddRelativePos(Effect->GetAxis(AXIS_Y) * 10.f * m_SpawnCount);

		}
		m_pScene->GetResource()->FindSound("EnemyDie")->Play();
	}
}

void CBossDieEffectLast::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CBossDieEffectLast::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CBossDieEffectLast::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CBossDieEffectLast* CBossDieEffectLast::Clone()
{
	return new CBossDieEffectLast(*this);
}

void CBossDieEffectLast::Animation2DNotify(const std::string& Name)
{
}

void CBossDieEffectLast::AnimationFrameEnd(const std::string& Name)
{
}
