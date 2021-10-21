#pragma once
#include "GameEngine.h"

//디바이스를 초기화하기위한 핸들, 해상도, 창모드풀스크린, 
class CDevice
{
private:
	//ID3D11Device를 타고들어가서 IUnknown이 있는데 이것이 컴 객체이다.
	ID3D11Device*			m_pDevice;
	//디바이스 콘텍스트는 디바이스를 대신해서 작업을 받아오고 처리명령을 내릴 수 있는
	//대리자같은 녀석
	//텍스쳐를 로딩한다던지 비디오에다가 리소스 로딩하는것은 일반 디바이스를 주로 활용
	ID3D11DeviceContext*	m_pContext;

	//API는 더블버퍼링 DirectX는 페이지플리핑
	//페이지플리핑용
	IDXGISwapChain*			m_pSwapChain;

	//백버퍼역할을 한다
	//SwapChain이 가지고있는 백버퍼를 RenderTargetView에 묶어주고 출력을
	//RenderTargetView에 해주게되면 묶여있는 BackBuffer에 출력이 되게 된다. 대신출력용?
	ID3D11RenderTargetView* m_pTargetView;

	//동일한 해상도의 깊이 버퍼를 갖게되는데 깊이 버퍼란 말그대로 깊이값을 저장하는것
	//이 라이브러리를 이용해서 2D 제작하고 이후 3D까지 제작을 한다
	//3D같은경우에은 가까이있는 물체가 멀리있는 물체를 가린다
	//그것이 가능한 이유가 깊이버퍼가 있기 때문이다.
	//깊이버퍼는 0~1로 수치가 정해짐
	//출력하기전에 1로 초기화하고 싹 출력함.
	//1이 가장 멀리있는 녀석이라고 보면 됨.
	//깊이는 픽셀단위로 계산이된다.
	//겹치는부분은 깊이에따라 갱신하거나 갱신하지 않는다.
	//API에서 y솔트했던것이라고 생각하면 될듯
	
	//Stencil 이것도 동일한 해상도의 버퍼가 하나 더 있다.
	//Stencil은 하나당 1byte를 차지해서 0~255사이의 정수를 저장할 수 있게 한다.
	//특수효과같은것을 만들어낼때 stencil을 사용하게 된다. 
	//2D에서는 사용안한다.
	ID3D11DepthStencilView* m_pDepthView;
	Resolution				m_RS;
	HWND					m_hWnd;
	float					m_ClearColor[4];
	// RGB 0~255를 다이렉트에서는 0~1사이의 실수값으로 사용한다.
	Vector2                 m_ResolutionRatio;

private:
	//2D
	ID2D1RenderTarget* m_2DTarget;	
	//2D World용
	ID2D1RenderTarget* m_2DTargetWorld; 
	ID2D1Factory* m_2DFactory;

public:
	ID2D1RenderTarget* Get2DTarget()   const
	{
		return m_2DTarget;
	}

	ID2D1RenderTarget* Get2DTargetWorld()   const
	{
		return m_2DTargetWorld;
	}

	ID2D1Factory* Get2DFactory()   const
	{
		return m_2DFactory;
	}

public:
	ID3D11Device* GetDevice() const
	{
		return m_pDevice;
	}
	ID3D11DeviceContext* GetContext() const
	{
		return m_pContext;
	}
	IDXGISwapChain* GetSwapChain() const
	{
		return m_pSwapChain;
	}
	Resolution GetResolution() const
	{
		return m_RS;
	}

	Vector2 GetResolutionRatio()    const;

public:
	bool CreateWorld2DTarget(IDXGISurface* Surface);
public:

	bool Init(HWND hWnd, int Width, int Height, bool ScreenMode);
	void Update();
	void ClearTarget();
	void Render();

	DECLARE_SINGLE(CDevice)
};

