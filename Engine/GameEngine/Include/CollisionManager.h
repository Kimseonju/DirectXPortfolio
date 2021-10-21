#pragma once

#include "GameEngine.h"

//�浹ä���� �����Ѵ�.
//�浹ä���� ����ϴ� ������ �� �浹ü�� ��� ä���� ������������ �ٸ�ä�ο� �Ҽӵ��ִ� �浹ü�� �浹�� �Ұ����� ���Ұ����� �������ֱ� �����̴�.
class CCollisionManager
{
private:
	std::vector<CollisionChannel*>	m_vecChannel;
	std::unordered_map<std::string, CollisionProfile*>	m_mapProfile;

public:
	bool Init();
	bool CreateChannel(const std::string& Name, Collision_Interaction Interaction);
	bool CreateProfile(const std::string& Name, Collision_Channel Channel);
	//���������� ä�λ��¸� �����Ѵ� (Dest ä���� �浹���� ���� ����)
	bool SetProfileChannelState(const std::string& Name, Collision_Channel DestChannel,
		Collision_Interaction Interaction);
	CollisionProfile* FindProfile(const std::string& Name);

	DECLARE_SINGLE(CCollisionManager)
};
