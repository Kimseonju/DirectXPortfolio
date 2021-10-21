#pragma once
#include "GameEngine.h"

//����̽��� �ʱ�ȭ�ϱ����� �ڵ�, �ػ�, â���Ǯ��ũ��, 
class CDevice
{
private:
	//ID3D11Device�� Ÿ����� IUnknown�� �ִµ� �̰��� �� ��ü�̴�.
	ID3D11Device*			m_pDevice;
	//����̽� ���ؽ�Ʈ�� ����̽��� ����ؼ� �۾��� �޾ƿ��� ó������� ���� �� �ִ�
	//�븮�ڰ��� �༮
	//�ؽ��ĸ� �ε��Ѵٴ��� �������ٰ� ���ҽ� �ε��ϴ°��� �Ϲ� ����̽��� �ַ� Ȱ��
	ID3D11DeviceContext*	m_pContext;

	//API�� ������۸� DirectX�� �������ø���
	//�������ø��ο�
	IDXGISwapChain*			m_pSwapChain;

	//����ۿ����� �Ѵ�
	//SwapChain�� �������ִ� ����۸� RenderTargetView�� �����ְ� �����
	//RenderTargetView�� ���ְԵǸ� �����ִ� BackBuffer�� ����� �ǰ� �ȴ�. �����¿�?
	ID3D11RenderTargetView* m_pTargetView;

	//������ �ػ��� ���� ���۸� ���ԵǴµ� ���� ���۶� ���״�� ���̰��� �����ϴ°�
	//�� ���̺귯���� �̿��ؼ� 2D �����ϰ� ���� 3D���� ������ �Ѵ�
	//3D������쿡�� �������ִ� ��ü�� �ָ��ִ� ��ü�� ������
	//�װ��� ������ ������ ���̹��۰� �ֱ� �����̴�.
	//���̹��۴� 0~1�� ��ġ�� ������
	//����ϱ����� 1�� �ʱ�ȭ�ϰ� �� �����.
	//1�� ���� �ָ��ִ� �༮�̶�� ���� ��.
	//���̴� �ȼ������� ����̵ȴ�.
	//��ġ�ºκ��� ���̿����� �����ϰų� �������� �ʴ´�.
	//API���� y��Ʈ�ߴ����̶�� �����ϸ� �ɵ�
	
	//Stencil �̰͵� ������ �ػ��� ���۰� �ϳ� �� �ִ�.
	//Stencil�� �ϳ��� 1byte�� �����ؼ� 0~255������ ������ ������ �� �ְ� �Ѵ�.
	//Ư��ȿ���������� ������ stencil�� ����ϰ� �ȴ�. 
	//2D������ �����Ѵ�.
	ID3D11DepthStencilView* m_pDepthView;
	Resolution				m_RS;
	HWND					m_hWnd;
	float					m_ClearColor[4];
	// RGB 0~255�� ���̷�Ʈ������ 0~1������ �Ǽ������� ����Ѵ�.
	Vector2                 m_ResolutionRatio;

private:
	//2D
	ID2D1RenderTarget* m_2DTarget;	
	//2D World��
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

