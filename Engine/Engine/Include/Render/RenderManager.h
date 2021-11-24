#pragma once

#include "../GameEngine.h"
#include "../Resource/RenderTarget.h"
#include "../Resource/Material.h"
#include "../UI/MouseWidget.h"


class CRenderManager
{
private:
	class CPostProcessCBuffer* m_PostProcessCBuffer;
	class CPaperBurnCBuffer* m_PaperBurnCBuffer;

	Render_Space    m_RenderSpace;
	class CPrimitiveComponent** m_pRenderList2D[RT2D_End];
	int m_RenderList2DCount[RT2D_End];
	int m_RenderList2DCapacity[RT2D_End];

	class CPrimitiveComponent** m_pRenderList3D[RT3D_End];
	int m_RenderList3DCount[RT3D_End];
	int m_RenderList3DCapacity[RT3D_End];

	class CPrimitiveComponent** m_pRenderListDistortion;
	int m_RenderListDistortionCount;
	int m_RenderListDistortionCapacity;

	class CRenderState* m_WorldState[RST_End];
	class CRenderState* m_DepthDisable;
	class CRenderState* m_AlphaBlend;
	class CRenderState* m_UIAlphaBlend;

	CSharedPtr<CRenderTarget> m_DiffuseTarget;
	CSharedPtr<CMaterial>   m_DiffuseTargetMaterial;

	CSharedPtr<CRenderTarget> m_DistortionTarget;
	CSharedPtr<CMaterial>   m_DistortionTargetMaterial;

	class CDistortionCBuffer* m_DistortionCBuffer;

	CSharedPtr<CMouseWidget>    m_MouseWidget;
	bool		m_PaperBurnEnable;
	bool		m_PaperBurnInverse;
	float		m_PaperBurnTimeMax;
	float		m_PaperBurnTime;

	std::vector<TorchInfo>	m_vecTorchInfo;
	int m_TouchCount;
	class CStructuredBuffer* m_TorchCBuffer;
public:

	void SetMouseWidget(CMouseWidget* Widget)
	{
		m_MouseWidget = Widget;
	}

	Render_Space GetRenderSpace()   const
	{
		return m_RenderSpace;
	}

	CRenderTarget* GetDiffuseTarget()   const
	{
		return m_DiffuseTarget;
	}
	void SetWorldRenderState(const std::string& Name);
	void SetBlur(bool Enable);
	void SetDistortion(bool Enable);
	void SetDistortionWeight(float Weight);
	void SetDistortionSpeed(float Speed);
	void SetPaperBurn(bool Enable);

public:
	bool Init();
	void SetDefaultTarget();
	void Render(float DeltaTime);

private:
	void Render2D(float DeltaTime);
	void Render3D(float DeltaTime);

public:
	void AddPrimitiveComponent(class CPrimitiveComponent* pPrimitive);
	void AddTouchLight(Vector3 Pos, Matrix matWVP,Vector4 Color, bool bEnable = true);
	void TouchLightClear();
private:
	static bool Sort2DObject(class CPrimitiveComponent* Src, class CPrimitiveComponent* Dest);

	DECLARE_SINGLE(CRenderManager)
};

