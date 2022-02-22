#include "stdafx.h"
#include "CfgFile.h"

CCfgFile::CCfgFile(void)
{
}

CCfgFile::~CCfgFile(void)
{
	TToken* token;

	//*** delete all tokens
	for (int i = 0; i < (int)m_Tokens.size(); i++) {
		token = m_Tokens[i];
		delete token;
	}
	m_Tokens.clear();
}



int CCfgFile::LoadFile(char* name) {
	FILE* file;
	char line[10000], tmp[10000];
	TToken* token;
	int a, i, start, end;
	int section = 0;

	fopen_s(&file, name, "rt");
	if (file == NULL) return(-1);

	do {
		if (fgets(line, 10000, file) == NULL) break;
		//*** check for comments
		for (i = 0; i < 10000; i++) {
			if ((line[i] == '/') && (line[i + 1] == '/')) {
				line[i] = 0;
				break;
			}
			if ((line[i] == 0) || (line[i] == 10) || (line[i] == 13)) {
				line[i] = 0;
				break;
			}
		}
		//*** check for empy lines
		if ((strchr(line, '=') == NULL) && (strchr(line, '{') == NULL) && (strchr(line, '}') == NULL)) continue;

		//*** skip first spaces
		for (i = 0; i < (int)strlen(line); i++)
			if (line[i] >= 'A') break;
		start = i;

		//*** find the section start
		if (line[start] == '{') continue;


		//*** find the section end
		if (line[start] == '}') {
			section++;
			continue;
		}

		//*** find the =
		for (i = start; i < (int)strlen(line); i++)
			if (line[i] == '=') break;
		end = i;

		//*** extract the space between end of ID and =
		for (i = end - 1; i > start; i--)
			if (line[i] != ' ') break;
		end = i;

		//*** extract the ID string
		a = 0;
		for (i = start; i <= end; i++) {
			tmp[a] = line[i];
			a++;
		}
		tmp[a] = 0;

		token = new TToken;
		sprintf_s(token->id, "%s", tmp); //*** store it
		_strlwr_s(token->id, 255);


		//*** extract the value string

		//*** find the =
		for (i = start; i < (int)strlen(line); i++)
			if (line[i] == '=') break;
		end = i;

		a = 0;
		for (i = end + 1; i < (int)strlen(line); i++) {
			tmp[a] = line[i];
			a++;
		}
		tmp[a] = 0;
		sprintf_s(token->value, 255, "%s", tmp);

		//*** store the token
		token->section = section; //*** store the section number
		m_Tokens.push_back(token);


	} while (feof(file) == 0);

	m_NumSections = section;
	fclose(file);

	return(0);

}


int CCfgFile::GetIntValue(int section, char* id) {
	int i;
	TToken* token;


	for (i = 0; i < (int)m_Tokens.size(); i++) {
		token = m_Tokens[i];
		if (token->section != section) continue;
		if (strcmp(token->id, id) == 0) {
			return(atoi(token->value));
		}
	}
	return(0);
}


void CCfgFile::GetStrValue(int section, char* id, char* tmp) {
	int i;
	TToken* token;

	for (i = 0; i < (int)m_Tokens.size(); i++) {
		token = m_Tokens[i];
		if (token->section != section) continue;
		if (strcmp(token->id, id) == 0) {
			strcpy_s(tmp, 255, token->value);
			return;
		}
	}
	return;
}