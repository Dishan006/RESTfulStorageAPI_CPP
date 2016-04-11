/*
 * CreateSchemaCommand.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: dishan
 */

#include "CreateSchemaCommand.h"
#include "MongoDbAdapter.h"
#include <algorithm>
#include "json.h"


CreateSchemaCommand::CreateSchemaCommand(RequestContext requestContext)
{
	this->context =requestContext;
}

int CreateSchemaCommand::Execute(string* response)
{
	MongoDbAdapter mongoAdapter;

	string schemaName = this->context.request.RequestString.substr(8,this->context.request.RequestString.length()-1); // remove "schemas/"

	std::transform(schemaName.begin(), schemaName.end(), schemaName.begin(), ::tolower);

	if(mongoAdapter.IsSchemaDefined(schemaName))
	{
		cout << schemaName <<" Schema is defined"<<endl;
		*response = "{ \"error\": \"A Schema with that name has been already defined\"}";
		return 400;
	}

	std::cout  << this->context.requestRoot.get("Test", "").asString() <<endl;
	std::cout  << this->context.requestRoot.get("tests", "").asString() <<endl;

	*response = "OK";
	return 200;
}
