/*
 * RequestBroker.h
 *
 *  Created on: Feb 29, 2016
 *      Author: dishan
 */
#include <string>
using namespace std;
#include "Request.h"
#include "DbAdapter.h"

#ifndef REQUESTHANDLER_H_
#define REQUESTHANDLER_H_
class RequestHandler
{

private:
    DbAdapter dbAdapter;
	bool AuthenticateUser(string authHeader);

public:
	RequestHandler(DbAdapter dbAdapter);
	int ProcessRequest(Request request, string *response);


};
#endif /* REQUESTHANDLER_H_ */
