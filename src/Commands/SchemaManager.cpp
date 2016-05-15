/*
 * SchemaManager.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: dishan
 */

#include "MongoDbAdapter.h"
#include <algorithm>

#include "SchemaManager.h"
#include "json.h"


SchemaManager::SchemaManager(RequestContext requestContext)
{
	this->context =requestContext;
}

int SchemaManager::Create(string* response)
{
	MongoDbAdapter mongoAdapter;


	cout  <<"Schema:"<<  this->context.requestRoot["SchemaName"]<<endl;
	string schemaName = this->context.requestRoot["SchemaName"].asString();
	string entitySetName = this->context.requestRoot["EntitySetName"].asString();

	if(mongoAdapter.IsSchemaDefined(entitySetName))
	{
		cout << schemaName <<" Schema is defined"<<endl;
		*response = "{ \"error\": \"A Schema with that entity set name has been already defined.\"}";
		return 400;
	}

	if(schemaName!="Empty")
	{
		mongoAdapter.CreateSchema(schemaName,this->context.requestRoot);
		*response = this->context.requestRoot.toStyledString();
		return 201;
	}


	*response = "{ \"error\": \"Error during the creation of the schema.\"}";
	return 400;
}

int SchemaManager::GetAll(string* response)
{
	MongoDbAdapter mongoAdapter;
	*response = mongoAdapter.GetSchemaCollection().toStyledString();
	return 200;
}

int SchemaManager::GetSingleEntity(string* response, string key)
{
	MongoDbAdapter mongoAdapter;
	Json::Value value = mongoAdapter.GetSchema(key);

	if(value == Json::nullValue)
	{
		*response = "{ \"error\": \"A Schema with that name was not found.\"}";
		return 404;
	}

	*response = value.toStyledString();
	return 200;
}

int SchemaManager::DeleteSingleEntity(string* response, string key)
{
	MongoDbAdapter mongoAdapter;
	if(!mongoAdapter.IsSchemaDefined(key))
	{
		*response = "{ \"error\": \"A Schema with that name was not found.\"}";
		return 404;
	}

	mongoAdapter.DeleteSchema(key);
	*response = "{ \"message\": \"The schema was successfully deleted.\"}";
	return 200;
}

