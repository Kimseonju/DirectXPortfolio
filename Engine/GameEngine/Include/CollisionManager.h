#pragma once

#include "GameEngine.h"

//충돌채널을 관리한다.
//충돌채널을 사용하는 이유는 이 충돌체가 어떠한 채널을 가지고있을때 다른채널에 소속되있는 충돌체가 충돌을 할것인지 안할것인지 결정해주기 때문이다.
class CCollisionManager
{
private:
	std::vector<CollisionChannel*>	m_vecChannel;
	std::unordered_map<std::string, CollisionProfile*>	m_mapProfile;

public:
	bool Init();
	bool CreateChannel(const std::string& Name, Collision_Interaction Interaction);
	bool CreateProfile(const std::string& Name, Collision_Channel Channel);
	//프로파일의 채널상태를 수정한다 (Dest 채널을 충돌할지 말지 수정)
	bool SetProfileChannelState(const std::string& Name, Collision_Channel DestChannel,
		Collision_Interaction Interaction);
	CollisionProfile* FindProfile(const std::string& Name);

	DECLARE_SINGLE(CCollisionManager)
};
