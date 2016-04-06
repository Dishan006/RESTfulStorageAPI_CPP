/*
 * DbAdapter.cpp
 *
 *  Created on: Mar 16, 2016
 *      Author: dishan
 */

#include "User.h"
#include <iostream>
#include <stdlib.h>
#include "MySqlDbAdapter.h"

User* MySqlDbAdapter::GetUser(string userName, string basicAuthHash)
{
	cout <<userName <<" : "<<basicAuthHash<<endl;

	sql::Connection* connection = GetConnection();
	sql::ResultSet *res;

	sql::PreparedStatement *pstmt;
	//pstmt = connection->prepareStatement("SELECT * FROM Users");
	//ToDO: check for injection
	pstmt = connection->prepareStatement("SELECT * FROM Users WHERE UserName = ? AND BasicAuthHash = ?");
	pstmt->setString(1, userName);
	pstmt->setString(2, basicAuthHash);
	res = pstmt->executeQuery();

	User* accessingUser = NULL;

	while (res->next()) {
		accessingUser = new User();
		accessingUser->UserID = res->getInt(1);
		accessingUser->UserName = res->getString(2);
		break;
		//cout << res->getString(2) <<" : "<<res->getString(3)<<endl;
	}

	delete res;
	delete connection;
	delete pstmt;
	return accessingUser;
}


sql::Connection* MySqlDbAdapter::GetConnection()
{
	try {
		sql::Driver *driver;
		sql::Connection *con;

		/* Create a connection */
		driver = get_driver_instance();

		cout <<"Connecting to DB"<<endl;
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root@006");
		/* Connect to the MySQL test database */
		con->setSchema("SandBox");

		cout <<"Connected"<<endl;
		driver->threadEnd();
		return con;

	} catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return NULL;
}

