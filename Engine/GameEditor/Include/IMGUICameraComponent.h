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

	class CCamera* m_Camera;
	class CIMGUIButton* m_CurrentCamera;

public:
	void InfoUpdate(CCamera* CCamera);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void CurrentCameraButtonClick();

	void InputZoom();

};
