/*
 * RequestBroker.h
 *
 *  Created on: Feb 29, 2016
 *      Author: dishan
 */
#include <string>
using namespace std;
#include "Request.h"
#include "MySqlDbAdapter.h"

#ifndef REQUESTHANDLER_H_
#define REQUESTHANDLER_H_
class RequestHandler
{

private:
	MySqlDbAdapter dbAdapter;
	bool AuthenticateUser(Request request);
	bool IsValidEndPoint(string resource);

public:
	RequestHandler(MySqlDbAdapter dbAdapter);
	int ProcessRequest(Request request, string *response);


};
#endif /* REQUESTHANDLER_H_ */
