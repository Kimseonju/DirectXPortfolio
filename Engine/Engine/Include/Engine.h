#pragma once
#include "GameEngine.h"
#include "UI/MouseWidget.h"

class CEngine
{

private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_RS;
	class CTimer* m_pTimer;
	float       m_TimeScale;

	static bool m_Loop;
	class CDebugLogWindow* m_DebugLogWindow;
	bool		m_OnLogFPS;
	class CGlobalCBuffer* m_GlobalCBuffer;
	float		m_AccTime;
	CSharedPtr<CMouseWidget>	m_MouseWidget;
	bool		m_Start;
	bool		m_CollisionRender;
	bool m_ObjectPause;
public:
	bool GetCollisionRender() const
	{
		return m_CollisionRender;
	}
	void SetCollisionRender(bool CollisionRender)
	{
		m_CollisionRender = CollisionRender;
	}
	void SetResolution(int Width, int Height)
	{
		m_RS.Width = Width;
		m_RS.Height = Height;
	}

	void SetTimeScale(float TimeScale)
	{
		m_TimeScale = TimeScale;
	}

	void SetObjectPause(bool bPause)
	{
		m_ObjectPause = bPause;
	}
	bool IsObjectPause()
	{
		return m_ObjectPause;
	}
	static bool IsLoop()
	{
		return m_Loop;
	}

	void OnDebugLog();
	void AddDebugLog(const char* Text);
	void OnLogFPS(bool Log)
	{
		m_OnLogFPS = Log;
	}

	void Exit();
public:
	float GetFPS();
public:


	bool Init(const TCHAR* pClass, const TCHAR* pTitle, HINSTANCE hInst,
		int IconID, int iSmallIconID, int Width, int Height, bool ScreenMode = true);
	bool Init(HINSTANCE hInst, HWND hWnd, int Width, int Height, bool ScreenMode = true);
	int Run();
	void RunNoLoop();

private:
	void Logic();
	//씬이 업데이트가 되니 안되니
	bool Update(float DeltaTime);
	//업데이트가 끝난 후 처리 (NextUpdate)
	bool PostUpdate(float DeltaTime);
	bool Collision(float DeltaTime);
	bool Render(float DeltaTime);
private:

	void Register(const TCHAR* pClass, int IconID, int SmallIconID);
	bool Create(const TCHAR* pClass, const TCHAR* pTitle);

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	void SetMouseWidget();

	template <typename T>
	T* CreateMouseWidget(const std::string& Name)
	{
		T* Mouse = new T;

		if (!Mouse->Init())
		{
			SAFE_DELETE(Mouse);
			return nullptr;
		}

		m_MouseWidget = Mouse;
		Mouse->Release();

		SetMouseWidget();

		return Mouse;
	}

	DECLARE_SINGLE(CEngine)
};

