#pragma once
#include "IMGUIWidgetComponent.h"
//Transform
class CIMGUITransformComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUITransformComponent();
	virtual ~CIMGUITransformComponent();

private:
	class CIMGUITextInput* m_InputPosX;
	class CIMGUITextInput* m_InputPosY;
	class CIMGUITextInput* m_InputPosZ;

	class CIMGUITextInput* m_InputRotX;
	class CIMGUITextInput* m_InputRotY;
	class CIMGUITextInput* m_InputRotZ;

	class CIMGUITextInput* m_InputScaleX;
	class CIMGUITextInput* m_InputScaleY;
	class CIMGUITextInput* m_InputScaleZ;


	class CIMGUITextInput* m_InputPivotX;
	class CIMGUITextInput* m_InputPivotY;
	class CIMGUITextInput* m_InputPivotZ;
	class CSceneComponent* m_Component;
public:
	void SetPosition(const Vector3& Pos);
	void SetRotation(const Vector3& Pos);
	void SetScale(const Vector3& Pos);
	void SetPivot(const Vector3& Pos);
	void SetComponent(class CSceneComponent* Component);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void InputPosX();
	void InputPosY();
	void InputPosZ();

	void InputRotX();
	void InputRotY();
	void InputRotZ();

	void InputScaleX();
	void InputScaleY();
	void InputScaleZ();


	void InputPivotX();
	void InputPivotY();
	void InputPivotZ();
};
