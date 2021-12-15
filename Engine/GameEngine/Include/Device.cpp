#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice():
	m_pDevice(nullptr),
	m_pContext(nullptr),
	m_pSwapChain(nullptr),
	m_pTargetView(nullptr),
	m_pDepthView(nullptr),
	m_RS{},
	m_hWnd(nullptr),
	m_ClearColor{},
	m_2DTarget(nullptr),
	m_2DTargetWorld(nullptr),
	m_2DFactory(nullptr),
	m_DefaultState(nullptr),
	m_OriginState(nullptr)
{
}
CDevice::~CDevice()
{
	SAFE_RELEASE(m_2DTargetWorld);
	SAFE_RELEASE(m_2DTarget);
	SAFE_RELEASE(m_2DFactory);

	SAFE_RELEASE(m_pDepthView);
	SAFE_RELEASE(m_pTargetView);
	SAFE_RELEASE(m_pSwapChain);
	if (m_pContext)
		m_pContext->ClearState();
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);
}

Vector2 CDevice::GetResolutionRatio() const
{
	return m_ResolutionRatio;
}

bool CDevice::CreateWorld2DTarget(IDXGISurface* Surface)
{
	D2D1_RENDER_TARGET_PROPERTIES	props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE::D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));

	if (FAILED(m_2DFactory->CreateDxgiSurfaceRenderTarget(Surface, props, &m_2DTargetWorld)))
		return false;

	return true;
}

bool CDevice::Init(HWND hWnd, int Width, int Height, bool ScreenMode)
{

	m_hWnd = hWnd;
	m_RS.Width = Width;
	m_RS.Height = Height;

	unsigned int		Flag = 0;

#ifdef _DEBUG
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	//나중을위해 폰트(TEXT) 넣기
	Flag |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	//스왑체인 만들기위한 구조체
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};

	SwapDesc.BufferDesc.Width= Width;
	SwapDesc.BufferDesc.Height = Height;
	//픽셀포맷                            Unsigned Normal 0~1사이값을 갖는 픽셀포맷이다
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//화면갱신주기
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;
	//확대축소시 처리하는방법      //배율지정X
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//라인을 위부터 아래까지 스캔하는것
	//순서 안정하기로
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//백버퍼 몇개?
	SwapDesc.BufferCount = 1;
	//버퍼용도 랜더타겟 출력용으로 사용할것이다
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	SwapDesc.OutputWindow = hWnd;

	//멀티샘플링을 지원을하는데 픽셀을 출력할때 좀 더 퀄리티있게 출력해주는 용도 안티앨리어싱
	//실제 게임개발할때는 다이렉트 멀티샘플링 사용X 성능이 좋지 않다.
	SwapDesc.SampleDesc.Count = 1;		// 1은 멀티샘플링 안한다. 만약 사용한다면 4~8로 카운트
	SwapDesc.SampleDesc.Quality = 0;	// 
	SwapDesc.Windowed = ScreenMode;
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; 

	D3D_FEATURE_LEVEL	Flevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL	Flevel1 = D3D_FEATURE_LEVEL_11_0;



	//D3D_DRIVER_TYPE_HARDWARE 그래픽카드
	//Device, Context, SwapChain 생성
	if(FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag, 
		&Flevel, 1, D3D11_SDK_VERSION, &SwapDesc, &m_pSwapChain, &m_pDevice, &Flevel1, &m_pContext)))
		return false;

	//SwapChain이 가지고있는 백버퍼를 가져오기
	//SwapChain이 Textuire로 BackBuffer정보를 가지고있기 떄문에 이 타입의 변수를 선언하여
	//버퍼를 가지고온다
	//ID3D11Texture2D : DirectX11에서 지원되는 Texture 객체
	
	ID3D11Texture2D*  pBackBuffer = nullptr;

	//2번 인자에 들어가는 타입의 ID를 이용하여 SwapChain이 가지고 있는 해당 타입의 버퍼를 얻어온다.
	//이렇게 얻어온 버퍼는 RefCount가 증가하게된다.
	//그러므로 사용후 반드시 Release를 해주어야된다.
	//__uuidof(ID3D11Texture2D)  ID3D11Texture2D의 아이디 클래스마다 아이디같은것
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	
	//위에서 얻어온 BackBuffer를 이용해서 RenderTargetView를 생성하고
	//BackBuffer를 RenderTargetView에 묶어준다.
	m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pTargetView);

	SAFE_RELEASE(pBackBuffer);

	//깊이버퍼를 만들어준다.
	D3D11_TEXTURE2D_DESC	DepthDesc = {};

	DepthDesc.Width = Width;
	DepthDesc.Height = Height;

	//하나의 텍스처 객체에다가 여러개를 저장할 수 있는것
	//minmap때 다시 이야기한다고함
	//2D는 깊이가 한장만 있으면 충분하기 때문에 1로 해서 쓰겠다라고 알림
	DepthDesc.ArraySize = 1;

	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//어떤용도에 따라 BindFlag가 달라짐
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	//비디오메모리에다가 저장을 할때 저장되있는 값을 수정하게 가능하도록 해주는데 다만 이 작업 자체가 느리다.
	//용도를 D3D11_USAGE_DEFAULT로 만들어놓고 메모리에 접근해서 값을 수정하려고하면 작업이 매우 느려진다.
	//하지만 출력용으로 사용할때는 매우 빠르다.

	//D3D11_USAGE_IMMUTABLE
	//메모리 접근 불가 출력 최적화 버퍼, 출력이 가장 빠르다.
	//D3D11_USAGE_DYNAMIC
	//동적으로 처리할때 만듬, (CPU가 이용하는 메모리에 복제본을 만들어서 실시간으로 접근해서 데이터 변경할때)
	//출력속도는 느리다
	//D3D11_USAGE_STAGING
	//데이터보관용버퍼 필요할때 꺼내다쓰는용(없다고치면댐)
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthDesc.SampleDesc.Count = 1;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1;

	ID3D11Texture2D* pDepthStencilTex = nullptr;
							//1.으로 셋팅한것으로 만들겠다.
							//2. 데이터가 있는지 없는지
							//3. 그렇게 생성을 한다.
	m_pDevice->CreateTexture2D(&DepthDesc, nullptr, &pDepthStencilTex);

	m_pDevice->CreateDepthStencilView(pDepthStencilTex, nullptr, &m_pDepthView);

	SAFE_RELEASE(pDepthStencilTex);

	//RenderTargetView와 DepthStencilView
	//
	// Device에 생성한 RenderTargetView와 DepthStencilView를 묶어준다.
	//m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthView);

	// 실제 추력되는 2D 뷰포트 영역
	//
	D3D11_VIEWPORT VP = {};
	
	VP.Width = (float)Width;
	VP.Height = (float)Height;
	VP.MaxDepth = 1.f;

	m_pContext->RSSetViewports(1, &VP);

	//2D Factory를 만들기

	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_2DFactory)))
		return false;

	//원래있는 BackBuffer의 Surface를 얻어오기
	//Surface= 주로 2D이미지 데이터를 보관하는데 이용하는 픽셀의 행렬이다.

	//표면
	IDXGISurface* BackSurface = nullptr;

	m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&BackSurface));

	// 2D용 렌더타겟을 만들어준다.
	// 단, 출력할 Surface는 위에서 얻어온 BackBuffer의 Surface로 지정하여 2D도
	// 출력이 가능하도록 만들어 주어야 한다.
	//알파곱한것으로 처리
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));

	if (FAILED(m_2DFactory->CreateDxgiSurfaceRenderTarget(BackSurface, props, &m_2DTarget)))
		return false;

	SAFE_RELEASE(BackSurface);

	return true;
}

void CDevice::Update()
{
	RECT	rcClient = {};
	GetClientRect(m_hWnd, &rcClient);

	float	Width = (float)(rcClient.right - rcClient.left);
	float	Height = (float)(rcClient.bottom - rcClient.top);

	m_ResolutionRatio.x = m_RS.Width / Width;
	m_ResolutionRatio.y = m_RS.Height / Height;
}

void CDevice::ClearTarget()
{
	//IMGUI 도킹쪽 버그 이유는 계속 묶어줘야대서? IMGUI윈도우잡고 바깥으로나가면  오브젝트들이 뒤로가버림
	m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthView);
	m_pContext->ClearRenderTargetView(m_pTargetView, m_ClearColor);
	m_pContext->ClearDepthStencilView(m_pDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
		1.f, 0);

}

void CDevice::Render()
{
	m_pSwapChain->Present(0, 0);
}
