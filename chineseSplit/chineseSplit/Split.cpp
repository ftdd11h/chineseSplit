#include "stdafx.h"
#include "Split.h"


Split::Split(string strtarge)
{
	m_strTarget = strtarge;
	m_database = new sqlQuery();
}


Split::~Split()
{
}

string Split::getSplitString(string str_target)
{
	string str_result = "";
	if (str_target == "")
		str_result = "";
	cout << str_target.length() << endl;
	string tmp = "";
	for (int i = 0; i < str_target.length();i+=2){
		char ch[3];
		ch[0] = str_target[i];
		ch[1] = str_target[i+1];
		ch[2] = 0;
		cout << ch << endl;
		tmp.append(ch);
		if (tmp.length()>2){
			if (m_database->find(tmp,FUZZY)){
			}
			else{
				//¼õ×ÖÆ¥Åä
				string res=matching(tmp);
				i -= tmp.length() - res.length();
				res.append("/");
				str_result.append(res);
				tmp = "";
			}
		}
	}
	m_strResult = str_result;
	if (tmp.length() == 2 || m_database->find(tmp, COMPLETE)){
		m_strResult.append(tmp);
	}
	else{
		//Î²²¿Î´µÇÂ½´Ê
		//tmp=talieSplit(tmp);
		//m_strResult.append(tmp);
	}
	return str_result;
}

string Split::matching(string tmp)
{
	string res = "";
	if (tmp.length() == 2){
		res = tmp;
		return res;
	}
	tmp = tmp.substr(0, tmp.length()-2);
	if (m_database->find(tmp,COMPLETE)){
		res = tmp;
	}
	else{
		//¼õ×ÖÆ¥Åä
		res=matching(tmp);
	}
	return res;
}
string Split::getResult()
{
	getSplitString(m_strTarget);
	return m_strResult;
}
string Split::talieSplit(string str)
{
	if (str.length() <= 2)
		return str;
	string res = matching(str);
	res.append("/");
	m_strResult.append(res);
	str = str.substr(res.length(), str.length());
	res=talieSplit(str);
	return res;
}