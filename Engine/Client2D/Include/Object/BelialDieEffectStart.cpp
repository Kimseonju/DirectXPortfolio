#include "BelialDieEffectStart.h"
CBelialDieEffectStart::CBelialDieEffectStart()
{
}

CBelialDieEffectStart::CBelialDieEffectStart(const CBelialDieEffectStart& obj) :
	CEffectObject(obj)
{
}

CBelialDieEffectStart::~CBelialDieEffectStart()
{
}

void CBelialDieEffectStart::Start()
{
}

bool CBelialDieEffectStart::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(31.f, 31.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("ObjectDieEffect", false);
	m_Animation2D->SetFrameEndFunction<CBelialDieEffectStart>(this, &CEffectObject::AnimationFrameEnd);

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

	return true;
}

void CBelialDieEffectStart::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CBelialDieEffectStart::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CBelialDieEffectStart::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CBelialDieEffectStart::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CBelialDieEffectStart* CBelialDieEffectStart::Clone()
{
	return new CBelialDieEffectStart(*this);
}

void CBelialDieEffectStart::Animation2DNotify(const std::string& Name)
{
}

void CBelialDieEffectStart::AnimationFrameEnd(const std::string& Name)
{
}
