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

	//string schemaName = this->context.request.RequestString.substr(8,this->context.request.RequestString.length()-1); // remove "schemas/"

	//std::transform(schemaName.begin(), schemaName.end(), schemaName.begin(), ::tolower);

	cout  <<"Schema:"<<  this->context.requestRoot["SchemaName"]<<endl;
	string schemaName = this->context.requestRoot["SchemaName"].asString();
	if(mongoAdapter.IsSchemaDefined(schemaName))
	{
		cout << schemaName <<" Schema is defined"<<endl;
		*response = "{ \"error\": \"A Schema with that name has been already defined\"}";
		return 400;
	}

	if(schemaName!="Empty")
	{
		mongoAdapter.CreateSchema(schemaName,this->context.requestRoot);
		*response = this->context.requestRoot.toStyledString();
		return 201;
	}


	*response = "{ \"error\": \"Error during the creation of the schema\"}";
	return 400;
}
