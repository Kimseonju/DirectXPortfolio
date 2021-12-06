#pragma once
#include <Scene\SceneMode.h>
class CLoadingScene :
	public CSceneMode
{
	friend class CScene;

protected:
	CLoadingScene();
	virtual ~CLoadingScene();

private:
	class CLoadingUI* m_Widget;
	class CLoadingThread* m_Thread;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Start();
};

