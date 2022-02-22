#pragma once
#include <vector>

class CCfgFile
{
public:
	struct TToken {
		int section;
		char id[255];
		char value[255];
	};
	std::vector <TToken*> m_Tokens;
	int m_NumSections;

public:
	int GetNumSections() { return(m_NumSections); }
	int LoadFile(char* name);
	int GetIntValue(int section, char* id);
	void GetStrValue(int section, char* id, char* tmp);
	CCfgFile(void);
	~CCfgFile(void);
};
