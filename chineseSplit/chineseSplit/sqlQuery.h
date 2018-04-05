#pragma once

#include <iostream>
#include <cstring>

#include "mysql_driver.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/metadata.h"
#include "cppconn/exception.h"
#include <string>
using namespace std;
enum macthLevel
{
	FUZZY,				//Ä£ºýÆ¥Åä
	COMPLETE			//ÍêÈ«Æ¥Åä
};

class sqlQuery
{
public:
	sqlQuery();
	~sqlQuery();
	bool sqlQuery::find(string target, int level);
private:
	sql::Driver* driver;
	sql::Connection* con;
};

