/*
 * CreateSchemaCommand.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: dishan
 */

#include "../../Include/Commands/CreateSchemaCommand.h"
#include "../../Include/MongoDbAdapter.h"
#include <algorithm>


CreateSchemaCommand::CreateSchemaCommand(Request request)
{
	MongoDbAdapter mongoAdapter;

	string schemaName = request.RequestString.substr(8,request.RequestString.length()-1); // remove "schemas/"

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
