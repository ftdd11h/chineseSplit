#pragma once
#include <string>
#include "sqlQuery.h"
using namespace std;
class Split
{
public:
	Split( string str_target=NULL);
	~Split();
	string getSplitString(string str_strget);
	string matching(string origion);
	string getResult();
	string talieSplit(string str);
private:
	string m_strTarget;
	string m_strResult; 
	sqlQuery *m_database;
};

