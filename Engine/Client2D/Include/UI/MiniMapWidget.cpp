
#include "MiniMapWidget.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include <UI/Text.h>
#include "Scene/Viewport.h"
#include "Component/Camera.h"
#include <Scene/SceneManager.h>
#include "Resource/StructuredBuffer.h"
#include "../UI/UIManager.h"
#include "../UI/MiniMap.h"
#include "../Stage/StageManager.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Scene/CameraManager.h>
CMiniMapWidget::CMiniMapWidget() :
	m_TileCount(0),
	m_ObjectCount(0),
	m_EnemyCount(0)

{
}


CMiniMapWidget::~CMiniMapWidget()
{
	SAFE_DELETE(m_MapBuffer);
	SAFE_DELETE(m_CBuffer);
}

void CMiniMapWidget::Start()
{
	CWidget::Start();
}

bool CMiniMapWidget::Init()
{
	CWidget::Init();
	SetZOrder(UI_ZOrder::PlayerUI);
	m_vecMiniMapWidgetInfo.resize(3000);
	for (int i = 0; i < 3000; ++i)
	{
		m_vecMiniMapWidgetInfo[i].Opacity = 0.f;
	}
	m_CBuffer = new CMiniMapCBuffer;

	m_CBuffer->Init();
	m_CBuffer->SetSize(1.f, 1.f);
	m_MapBuffer = new CStructuredBuffer;

	if (!m_MapBuffer->Init("MiniMapBuffer", sizeof(MiniMapInfo),
		(unsigned int)3000, 31, true, CBT_VERTEX))
	{
		SAFE_DELETE(m_MapBuffer);
		return false;
	}
	m_Shader = CShaderManager::GetInst()->FindShader("MiniMapShader");
	return true;
}

void CMiniMapWidget::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);
	Vector2 MaxPos = Vector2(0.f, 0.f);
	if (!m_TileMapUpdate)
	{
		Clear();
		m_TileMapUpdate = true;
		CStage* Stage = CStageManager::GetInst()->GetCurStage();
		CTileMapComponent* Component=Stage->GetTileComonent();
		int CountX=Component->GetTileCountX();
		int CountY=Component->GetTileCountY();
		CountX *= 4;
		CountY *= 4;
		MaxPos = Vector2((float)CountX, (float)CountY);
		CCamera* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();
		Vector2 VRS = Camera->GetVRS();
		VRS -= MaxPos;
		VRS -= 50.f;
		SetPos(VRS);

		std::vector<CTile*> vecTile = Stage->GetvecTile();
		for (int i = 0; i < vecTile.size(); ++i)
		{
			int FrameX = vecTile[i]->GetFrameX()/16;
			int FrameY = vecTile[i]->GetFrameY()/16;
			if ((FrameX  <= 4 && FrameY  <= 2) || (FrameX==7 && FrameY==8) || (FrameX == 7 && FrameY == 8) || (FrameX == 7 && FrameY == 9)
				|| (FrameX == 8 && FrameY == 8) || (FrameX == 8 && FrameY == 9) || (FrameX == 9 && FrameY == 8) || (FrameX == 9 && FrameY == 9))
				continue;
			Vector2 Pos = vecTile[i]->GetPos();
			PushMiniMapInfoTile(Pos, Vector2(4.f, 4.f), Vector4(140.f / 255.f, 140.f / 255.f, 140.f / 255.f, 1.f),  Vector4(1.f, 1.f, 1.f, 1.f), 1.f);

		}
		vecTile = Stage->GetvecObjectTile();
		for (int i = 0; i < vecTile.size(); ++i)
		{
			int FrameX = vecTile[i]->GetFrameX() / 16;
			int FrameY = vecTile[i]->GetFrameY() / 16;
			if (FrameX >= 6 && FrameX <= 9 && FrameY <= 1)
			{
				Vector2 Pos = vecTile[i]->GetPos(); 
				PushMiniMapInfoTile(Pos, Vector2(4.f, 4.f), Vector4(140.f / 255.f, 140.f / 255.f, 140.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);
			}
		}


	}
}

void CMiniMapWidget::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);

}

void CMiniMapWidget::Render()
{

	CWidget::Render();
	m_MapBuffer->UpdateBuffer(&m_vecMiniMapWidgetInfo[0], sizeof(MiniMapInfo) * (m_TileCount + m_ObjectCount + m_EnemyCount));

	if (!IsEnable())
		return;
	m_MapBuffer->SetShader(31, CBT_VERTEX);
	m_CBuffer->UpdateCBuffer();

	m_Mesh->RenderInstancing((unsigned int)(m_TileCount + m_ObjectCount + m_EnemyCount));
	//m_MiniMapMesh->RenderInstancing((unsigned int)(m_TileCount + m_ObjectCount + m_EnemyCount));

	m_MapBuffer->ResetShader(31, CBT_VERTEX);

	ObjectClear();
}

CMiniMapWidget* CMiniMapWidget::Clone()
{
	return new CMiniMapWidget(*this);
}

void CMiniMapWidget::PushMiniMapInfoTile(Vector2 Pos, Vector2 Size, Vector4 Color, Vector4 EmvColor, float Opacity)
{
	MiniMapInfo Info;
	Matrix	matScale, matRot, matTranslation, matWorld;

	Vector2 RenderPos = Pos;
	Pos.x += GetPos().x;
	Pos.y += GetPos().y;
	RenderPos /= 4.f;
	RenderPos += GetPos();
	
	if (m_Owner)
		RenderPos += m_Owner->GetPos();
	
	matScale.Scaling(Size.x, Size.y, 1.f);
	matRot.Rotation(0.f, 0.f, m_Rotation);

	matTranslation.Translation(RenderPos.x, RenderPos.y, 0.f);

	matWorld = matScale * matRot * matTranslation;

	Matrix	matProj;

	if (m_Viewport)
		matProj = m_Viewport->GetCamera()->GetProjMatrix();

	else
		matProj = CSceneManager::GetInst()->GetScene()->GetViewport()->GetCamera()->GetProjMatrix();

	Info.matWVP = matWorld * matProj;
	Info.Color = Color;
	Info.EmvColor = EmvColor;
	Info.Opacity = Opacity;
	Info.Enable = 1;
	Info.Pos = Pos;
	m_vecMiniMapWidgetInfo[m_TileCount + m_ObjectCount + m_EnemyCount] = Info;
	m_TileCount++;
}

void CMiniMapWidget::PushMiniMapInfoObject(Vector2 Pos, Vector2 Size, Vector4 Color, Vector4 EmvColor, float Opacity)
{
	MiniMapInfo Info;
	Matrix	matScale, matRot, matTranslation, matWorld;

	Vector2 RenderPos = Pos;
	Pos.x += GetPos().x;
	Pos.y += GetPos().y;
	RenderPos /= 4.f;
	RenderPos += GetPos();
	RenderPos -= Vector2(0.5f, 0.5f) * Size;
	if (m_Owner)
		RenderPos += m_Owner->GetPos();

	matScale.Scaling(Size.x, Size.y, 1.f);
	matRot.Rotation(0.f, 0.f, m_Rotation);

	matTranslation.Translation(RenderPos.x, RenderPos.y, m_WorldZ);

	matWorld = matScale * matRot * matTranslation;

	Matrix	matProj;

	if (m_Viewport)
		matProj = m_Viewport->GetCamera()->GetProjMatrix();

	else
		matProj = CSceneManager::GetInst()->GetScene()->GetViewport()->GetCamera()->GetProjMatrix();

	Info.matWVP = matWorld * matProj;
	Info.Color = Color;
	Info.EmvColor = EmvColor;
	Info.Opacity = Opacity;
	Info.Enable = 1;
	Info.Pos = Pos;
	m_vecMiniMapWidgetInfo[m_TileCount + m_ObjectCount + m_EnemyCount] = Info;
	m_ObjectCount++;

}
void CMiniMapWidget::PushMiniMapInfoEnemy(Vector2 Pos, Vector2 Size, Vector4 Color, Vector4 EmvColor, float Opacity)
{
	MiniMapInfo Info;

	Matrix	matScale, matRot, matTranslation, matWorld;

	Vector2 RenderPos = Pos;
	Pos.x += GetPos().x;
	Pos.y += GetPos().y;
	RenderPos /= 4.f;
	RenderPos += GetPos();
	RenderPos -= Vector2(0.5f, 0.5f) * Size;
	if (m_Owner)
		RenderPos += m_Owner->GetPos();

	matScale.Scaling(Size.x, Size.y, 1.f);
	matRot.Rotation(0.f, 0.f, m_Rotation);

	matTranslation.Translation(RenderPos.x, RenderPos.y, m_WorldZ);

	matWorld = matScale * matRot * matTranslation;

	Matrix	matProj;

	if (m_Viewport)
		matProj = m_Viewport->GetCamera()->GetProjMatrix();

	else
		matProj = CSceneManager::GetInst()->GetScene()->GetViewport()->GetCamera()->GetProjMatrix();

	Info.matWVP = matWorld * matProj;
	Info.Color = Color;
	Info.EmvColor = EmvColor;
	Info.Opacity = Opacity;
	Info.Pos = Pos;
	m_vecMiniMapWidgetInfo[m_TileCount + m_ObjectCount + m_EnemyCount] = Info;
	m_EnemyCount++;
}

void CMiniMapWidget::ObjectClear()
{
	for (int i = 0; i < m_EnemyCount + m_ObjectCount; ++i)
	{
		m_vecMiniMapWidgetInfo[i + m_TileCount].Opacity = 0.f;;
	}
	m_EnemyCount = 0;
	m_ObjectCount = 0;
}

void CMiniMapWidget::Clear()
{

	for (int i = 0; i < m_TileCount + m_EnemyCount + m_ObjectCount; ++i)
	{
		m_vecMiniMapWidgetInfo[i + m_TileCount].Opacity = 0.f;
	}
	m_TileCount = 0;
	m_EnemyCount = 0;
	m_ObjectCount = 0;
}
