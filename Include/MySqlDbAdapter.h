/*
 * DbAdapter.h
 *
 *  Created on: Mar 16, 2016
 *      Author: dishan
 */

#ifndef MYSQLDBADAPTER_H_
#define MYSQLDBADAPTER_H_

#include "Entities/User.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MySqlDbAdapter
{

private:
	sql::Connection* GetConnection();

public:
	User* GetUser(string userName, string basicAuthHash);

};

#endif /* MYSQLDBADAPTER_H_ */
