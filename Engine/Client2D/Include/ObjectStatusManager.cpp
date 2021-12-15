#include "ObjectStatusManager.h"
#include "BasicStatus.h"
#include <PathManager.h>

CObjectStatusManager::CObjectStatusManager()
{
}

CObjectStatusManager::~CObjectStatusManager()
{
	auto iter = m_MapStatus.begin();
	auto iterEnd = m_MapStatus.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter).second);
	}
	m_MapStatus.clear();
}

bool CObjectStatusManager::LoadStatus(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	CBasicStatus* Status = FindStatus(Name);

	if (Status)
		return true;

	Status = new CBasicStatus;
	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	TCHAR	FullPath[MAX_PATH] = {};
	TCHAR	Name1[MAX_PATH] = {};

	if (Info)
		lstrcpy(FullPath, Info->pPath);

	lstrcat(FullPath, FileName);
	lstrcat(Name1, FileName);

	char	FullPathMultibyte[MAX_PATH] = {};
	char	NameMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

	ConvertLength = WideCharToMultiByte(CP_ACP, 0, Name1, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, Name1, -1, NameMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "rb");

	if (!pFile)
		return false;

	char line[1024];
	while (fgets(line, 1024, pFile))
	{
		remove_spaces(line);

		struct data d;

		char* tmp = _strdup(line);
		getfield(tmp, &d, 16);
		std::string s_0 = d.s[0];
		std::string s_1 = d.s[1];
		size_t num = s_1.find('\r');
		
		if (num != std::string::npos)
		{
			s_1.erase(s_1.find('\r'));
		}
		num = s_1.find('\n');
		if (num != std::string::npos)
		{
			s_1.erase(s_1.find('\n'));
		}
		if (s_0 == "Object")
		{

		}
		else if (s_0 == "HP")
		{
			int HP = std::stoi(s_1);
			Status->SetHP(HP);
		}
		else if (s_0 == "HPMAX")
		{
			int HPMAX = std::stoi(s_1);
			Status->SetHPMax(HPMAX);

		}
		else if (s_0 == "Dash")
		{
			int Dash = std::stoi(s_1);
			Status->SetDash(Dash);

		}
		else if (s_0 == "DashMax")
		{
			int DashMax = std::stoi(s_1);
			Status->SetDashMax(DashMax);

		}
		else if (s_0 == "AttackSpeed")
		{
			float AttackSpeed = std::stof(s_1);
			Status->SetAttackSpeed(AttackSpeed);

		}
		else if (s_0 == "ReloadSpeed")
		{
			float ReloadSpeed = std::stof(s_1);
			Status->SetReloadSpeed(ReloadSpeed);

		}
		else if (s_0 == "MoveSpeed")
		{
			float MoveSpeed = std::stof(s_1);
			Status->SetMoveSpeed(MoveSpeed);

		}
		else if (s_0 == "Damage")
		{
			int Damage = std::stoi(s_1);
			Status->SetDamage(Damage);

		}
		else if (s_0 == "DamageMax")
		{
			int DamageMax = std::stoi(s_1);
			Status->SetDamageMax(DamageMax);

		}
		else if (s_0 == "Armor")
		{
			int Armor = std::stoi(s_1);
			Status->SetArmor(Armor);

		}
		else if (s_0 == "Critical")
		{
			int Critical = std::stoi(s_1);
			Status->SetCritical(Critical);

		}
		else if (s_0 == "Evasion")
		{
			int Evasion = std::stoi(s_1);
			Status->SetEvasion(Evasion);

		}
		else if (s_0 == "Magazine")
		{
			int Magazine = std::stoi(s_1);
			Status->SetMagazine(Magazine);

		}
		else if (s_0 == "MagazineMax")
		{
			int MagazineMax = std::stoi(s_1);
			Status->SetMagazineMax(MagazineMax);

		}

		else if (s_0 == "Price")
		{
			int MagazineMax = std::stoi(s_1);
			Status->SetPrice(MagazineMax);

		}
		free(tmp);
	}

	m_MapStatus.insert(std::make_pair(Name, Status));


	fclose(pFile);
	return true;
}

CBasicStatus* CObjectStatusManager::FindStatus(const std::string& Name)
{
	auto    iter = m_MapStatus.find(Name);

	if (iter == m_MapStatus.end())
		return nullptr;

	return iter->second;
}

void CObjectStatusManager::remove_spaces(char* s)
{
	const char* d = s;
	do
	{
		while (*d == ' ')
		{
			++d;
		}
	}
	while (*s++ = *d++);
}

void CObjectStatusManager::getfield(char* line, data* d, int end_idx)
{
	int idx = 0;
	char* Context = nullptr;
	char* token = strtok_s(line, ",", &Context);

	do
	{
		//printf("token: %s\n", token);
		strcpy_s(d->s[idx++], token);
	}
	while (idx != end_idx && (token = strtok_s(NULL, ",", &Context)));

}

DEFINITION_SINGLE(CObjectStatusManager)