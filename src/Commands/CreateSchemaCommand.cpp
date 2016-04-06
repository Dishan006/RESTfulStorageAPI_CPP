/*
 * CreateSchemaCommand.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: dishan
 */

#include "CreateSchemaCommand.h"
#include "MongoDbAdapter.h"
#include <algorithm>


CreateSchemaCommand::CreateSchemaCommand(RequestContext requestContext)
{
	MongoDbAdapter mongoAdapter;

	string schemaName = requestContext.request.RequestString.substr(8,requestContext.request.RequestString.length()-1); // remove "schemas/"

	std::transform(schemaName.begin(), schemaName.end(), schemaName.begin(), ::tolower);

	if(!mongoAdapter.IsSchemaDefined(schemaName))
	{
		cout<< schemaName<<" Schema is not defined"<<endl;
	}else
	{
		cout << schemaName <<" Schema is defined"<<endl;
	}
}

void CreateSchemaCommand::Execute()
{

}
