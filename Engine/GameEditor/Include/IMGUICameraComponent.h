#pragma once
#include "IMGUIWidgetComponent.h"



class CIMGUICameraComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUICameraComponent();
	virtual ~CIMGUICameraComponent();

private:
	class CIMGUIText* m_CameraType;
	class CIMGUIDrag* m_CameraZoom;
	class CIMGUIText* m_CameraLeft;
	class CIMGUIText* m_CameraBottom;
	class CIMGUIDrag* m_CameraMinX;
	class CIMGUIDrag* m_CameraMinY;
	class CIMGUIDrag* m_CameraMaxX;
	class CIMGUIDrag* m_CameraMaxY;

	class CCamera* m_Camera;
	class CIMGUIButton* m_CurrentCamera;
public:
	void UpdateInfo(CCamera* CCamera);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void CurrentCameraButtonClick();

	void InputZoom();
	void InputMinX();
	void InputMinY();
	void InputMaxX();
	void InputMaxY();
};
