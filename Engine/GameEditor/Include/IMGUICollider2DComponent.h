#pragma once
#include "IMGUIWidgetComponent.h"
class CIMGUICollider2DComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUICollider2DComponent();
	virtual ~CIMGUICollider2DComponent();

private:
	class CIMGUITextInput* m_OffsetInputPosX;
	class CIMGUITextInput* m_OffsetInputPosY;

	class CIMGUITextInput* m_OffsetInputScaleX;
	class CIMGUITextInput* m_OffsetInputScaleY;

	class CIMGUIComboBox* m_Collider2DType;


public:
	void SetPosition(const Vector2& Pos);
	void SetScale(const Vector2& Pos);
	void TypeComboCallback(int SelectIndex, const char* Item);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void InputPosX();
	void InputPosY();

	void InputScaleX();
	void InputScaleY();
};
