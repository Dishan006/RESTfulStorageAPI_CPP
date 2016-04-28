/*
 * RequestHandler.cpp

 *
 *  Created on: Feb 29, 2016
 *      Author: dishan
 */
#include <iostream>
#include "RequestHandler.h"

#include "../Include/Commands/SchemaManager.h"
#include "Base64.h"
#include "HashUtil.h"

using namespace std;

RequestHandler::RequestHandler(MySqlDbAdapter dbAdapter)
{
	this->dbAdapter =dbAdapter;
}

int RequestHandler::ProcessRequest(Request request, string *response)
{
	if(!this->AuthenticateUser(request))
	{
		*response = "Unauthorized";
		return 403;
	}

	RequestContext context(request);

	if(IsValidEndPoint(request.RequestString))
	{
		if(request.RequestString.find("Schemas") == 0 || request.RequestString.find("schemas") ==0)
		{
			SchemaManager manager(context);

			if(request.Method == "POST")
			{
				return manager.Create(response);
			}

			if(request.Method == "GET")
			{
				if(request.RequestString.length()==7) // Schemas only, without schema name as id.
				{
					return manager.GetAll(response);
				}

			}
		}

	}

	*response = "Not Found";
	return 404;
}

bool RequestHandler::AuthenticateUser(Request request)
{
	if(request.Headers.size()>0)
	{
		map<string,string>::iterator it = request.Headers.find("Authorization");

		if(it!= request.Headers.end())
		{
			string autheHedareValue = it->second;
			if(!autheHedareValue.empty())
			{
				if (autheHedareValue.find("Basic") == 0)
				{
					string encodedSection = autheHedareValue.substr(6,autheHedareValue.length()-1); // 6 to skip the "Basic " string
					//cout << "CPP: encodedSection :"<< encodedSection<<"\n";

					string decodedData = base64_decode(encodedSection);
					//cout << "CPP: Decoded :"<< decodedData<<"\n";

					int splitter = decodedData.find_first_of(":",0);

					string userName = decodedData.substr(0,splitter);

					string* hashed = HashUtil::GenaretSHA256(decodedData);
					//cout << "CPP: Hashed :"<< *hashed<<"\n";

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
			}
		}
	}

	return false;
}

bool RequestHandler::IsValidEndPoint(string resource)
{
	int splitter = resource.find_first_of("/",0);
	string firstSegment = resource.substr(0,splitter);

	if(firstSegment=="schemas")
	{
		return true;
	}

	return false;
}


