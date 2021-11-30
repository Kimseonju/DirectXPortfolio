#include "BossDieEffectStart.h"
#include <Scene/Scene.h>
#include "BossDieParticle.h"
#include <Engine.h>
#include <Component/Camera.h>
#include <Scene/CameraManager.h>
#include <Scene/SceneResource.h>
CBossDieEffectStart::CBossDieEffectStart():
	m_Belial(nullptr)
{
}

CBossDieEffectStart::CBossDieEffectStart(const CBossDieEffectStart& obj) :
	CEffectObject(obj)
{
	m_Belial = obj.m_Belial;
}

CBossDieEffectStart::~CBossDieEffectStart()
{
}

void CBossDieEffectStart::Start()
{
}

bool CBossDieEffectStart::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(31.f, 31.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("ObjectDieEffect", false);
	m_Animation2D->SetFrameEndFunction<CBossDieEffectStart>(this, &CBossDieEffectStart::AnimationFrameEnd);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);
	//*/
	//	m_pScene->GetResource()->CreateAnimationSequence2D("ObjectDieEffect");
	//m_pScene->GetResource()->SetAnimationSequence2DTexture("ObjectDieEffect",
	//	"ObjectDieEffect", TEXT("Effect/Die/Die.png"));
	//
	//for (int i = 0; i < 11; ++i)
	//{
	//	m_pScene->GetResource()->AddAnimationSequence2DFrame("ObjectDieEffect",
	//		Vector2(i * 50.f, 0), Vector2((i + 1) * 50.f, 50.f));
	//}

	m_pScene->GetResource()->FindSound("EnemyDie")->Play();
	return true;
}

void CBossDieEffectStart::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);

}

void CBossDieEffectStart::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CBossDieEffectStart::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CBossDieEffectStart::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CBossDieEffectStart* CBossDieEffectStart::Clone()
{
	return new CBossDieEffectStart(*this);
}

void CBossDieEffectStart::Animation2DNotify(const std::string& Name)
{
}

void CBossDieEffectStart::AnimationFrameEnd(const std::string& Name)
{

	CEngine::GetInst()->SetTimeScale(1.f);
	Active(false);

	CBossDieParticle* obj = m_pScene->SpawnObject<CBossDieParticle>("BossDieParticle");
	obj->SetWorldPos(GetWorldPos());
	obj->SetBelial(m_Belial);
	CCamera* Camera=m_pScene->GetCameraManager()->GetCurrentCamera();
	Camera->AddCameraMove2D(Vector2(GetWorldPos().x, GetWorldPos().y), 99999.f);
	Camera->AddCameraShake(Vector2(1.f, 1.f), 99999.f);
}
