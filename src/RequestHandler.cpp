/*
 * RequestHandler.cpp

 *
 *  Created on: Feb 29, 2016
 *      Author: dishan
 */
#include <iostream>
#include "RequestHandler.h"

#include "SchemaManager.h"
#include "Base64.h"
#include "HashUtil.h"
#include "EntityConverter.h"
#include "MongoDbAdapter.h"

using namespace std;

const string GetRequestKey(const string resourceUrl);

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

	Schema* requestSchema = NULL;

	if(IsValidEndPoint(request.RequestString,requestSchema))
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
				string key = GetRequestKey(request.RequestString);
				return manager.GetSingleEntity(response,key);

			}

			if(request.Method == "DELETE")
			{
				string key = GetRequestKey(request.RequestString);
				return manager.DeleteSingleEntity(response,key);
			}

			if(request.Method == "PATCH")
			{
				string key = GetRequestKey(request.RequestString);
				return manager.DeleteSingleEntity(response,key);
			}
		}else
			if(requestSchema!=NULL)
			{
				if(request.Method == "GET")
				{
					if(request.RequestString.length()==requestSchema->EntitySetName.length()) // Get All
					{

					}

					string key = GetRequestKey(request.RequestString);

				}
			}

		*response = "{ \"error\": \"Feature Not Implemented\"}";
		return 501;

	}

	*response = "{ \"error\": \"Item Not found\"}";
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

bool RequestHandler::IsValidEndPoint(const string resource,Schema *schema)
{
	int splitter = resource.find_first_of("/",0);
	if(splitter == -1)
	{
		splitter = resource.find_first_of("(",0);
	}
	string firstSegment = resource.substr(0,splitter);

	if(firstSegment=="schemas")
	{
		return true;
	}

	MongoDbAdapter mongoAdapter;

	Json::Value schemaCollectionJson = mongoAdapter.GetSchemaCollection();
	EntityConverter entityConverter;

	std::vector<Schema> schemaCollection = entityConverter.ConvertJsonSchemaCollectionToEntities(schemaCollectionJson);

	if(int(schemaCollection.size())>0)
	{
		for(std::size_t i=0;i<schemaCollection.size();i++)
		{
			if(schemaCollection[i].EntitySetName== firstSegment)
			{
				schema = new Schema(schemaCollection[i]);
				return true;
			}
		}
	}

	return false;
}

const string GetRequestKey(const string resourceUrl)
{
	int keyStart =resourceUrl.find("(");
	int keyEnd =resourceUrl.find(")");
	if(keyStart>0 && keyEnd>0 && (keyEnd>keyStart))
	{
		keyStart++;
		string key  = resourceUrl.substr(keyStart,(keyEnd-keyStart));
		cout << "Key:"<< key<<"\n";
		return key;
	}

	return "";
}

