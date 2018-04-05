#include "stdafx.h"
#include "sqlQuery.h"
#include <iostream>
using namespace std;

sqlQuery::sqlQuery()
{
	sql::Statement *stmt = NULL;
	sql::ResultSet *res=NULL;

	try
	{
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://localhost:3306", "root", "root");
		con->setSchema("chinese");
		std::cout << "连接成功" << std::endl;
		stmt = con->createStatement();
		stmt->execute("SET CHARSET GB2312");
		res=stmt->executeQuery("SELECT * FROM chinese.`character`");
		while (res->next()){
			//string tmp = res->getString(2).c_str();
			//cout << tmp << endl;
		}
	}
	catch (sql::SQLException e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	delete stmt;
	delete res;

}


sqlQuery::~sqlQuery()
{
}

bool sqlQuery::find(string target,int level)
{
	sql::Statement *stmt = NULL;
	sql::ResultSet *res = NULL;
	bool bFind = false;
	try
	{
		string query = "";
		if (COMPLETE == level){
			query = "SELECT * FROM chinese.`character` where chinese_char = '";
			query.append(target);
			query.append("'");
		}
		else
		{

			query = "SELECT * FROM chinese.`character` where chinese_char like '";
			query.append(target);
			query.append("%'");
		}
		stmt = con->createStatement();
		res = stmt->executeQuery(query.c_str());
		while (res->next()){
			string tmp = res->getString(2).c_str();
			//cout << tmp << endl;
			bFind=true;
		}
	}
	catch (sql::SQLException e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	delete stmt;
	delete res;
	return bFind;
}