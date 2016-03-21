/*
 * RequestHandler.cpp

 *
 *  Created on: Feb 29, 2016
 *      Author: dishan
 */
#include <iostream>
#include "../Include/RequestHandler.h"

#include "../Include/Base64.h"
#include "../Include/HashUtil.h"
using namespace std;

RequestHandler::RequestHandler(DbAdapter dbAdapter)
{
	this->dbAdapter =dbAdapter;
}

int RequestHandler::ProcessRequest(Request request, string *response)
{
	if(request.Headers.size()>0)
	{
		map<string,string>::iterator it = request.Headers.find("Authorization");

		if(it!= request.Headers.end())
		{
			string autheHedareValue = it->second;
			if(!autheHedareValue.empty() && this->AuthenticateUser(autheHedareValue))
			{
				*response = "Authenticated";
				return 200;
			}
		}
	}

	*response = "Unauthorized";
	return 403;
}

bool RequestHandler::AuthenticateUser(string authHeader)
{
	if (authHeader.find("Basic") == 0)
	{
		string encodedSection = authHeader.substr(6,authHeader.length()-1); // 6 to skip the "Basic " string
		cout << "CPP: encodedSection :"<< encodedSection<<"\n";

		string decodedData = base64_decode(encodedSection);
		cout << "CPP: Decoded :"<< decodedData<<"\n";

		int splitter = decodedData.find_first_of(":",0);

		string userName = decodedData.substr(0,splitter);

		string* hashed = HashUtil::GenaretSHA256(decodedData);
		cout << "CPP: Hashed :"<< *hashed<<"\n";

		User* user=	dbAdapter.GetUser(userName,*hashed);

		delete(hashed);

		if(user!=NULL)
		{
			delete(user);
			return true;
		}

		delete(user);
		return false;
	}

	return false;
}


