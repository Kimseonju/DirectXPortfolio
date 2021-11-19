#pragma once
#include <Ref.h>


struct data{
char s[2][1024];
};
class CObjectStatusManager :
	public CRef
{
private:
	std::unordered_map<std::string, class CBasicStatus*> m_MapStatus;
public:

	bool LoadStatus(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = CSV_PATH);


	class CBasicStatus* FindStatus(const std::string& Name);

	void remove_spaces(char* s);
	void getfield(char* line, struct data* d, int end_idx);

	DECLARE_SINGLE(CObjectStatusManager)

};
