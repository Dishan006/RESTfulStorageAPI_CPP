/*
 * MongoDbAdapter.cpp

 *
 *  Created on: Apr 4, 2016
 *      Author: dishan
 */

#include "MongoDbAdapter.h"
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
#include <iostream>


bool MongoDbAdapter::IsSchemaDefined(string entitySetName)
{
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	bsoncxx::stdx::string_view dbName("StorageTestDB");

	mongocxx::database database = conn[dbName];

	auto cursor = database["schemas"].find( bsoncxx::builder::stream::document{} << "EntitySetName" << entitySetName<<  bsoncxx::builder::stream::finalize);

	for (auto&& doc : cursor) {
		std::cout << bsoncxx::to_json(doc) << std::endl;
		return true;
	}

	return false;
}

void MongoDbAdapter::CreateSchema(string name, Json::Value schemaObject)
{
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	bsoncxx::stdx::string_view dbName("StorageTestDB");

	mongocxx::database database = conn[dbName];
	bsoncxx::builder::stream::document document{};

	auto fileds = schemaObject["Fields"].getMemberNames();

	auto collection = database["schemas"];
	document << "SchemaName" << schemaObject.get("SchemaName", "").asString()
											<< "EntityName" << schemaObject.get("EntityName", "").asString()
											<< "EntitySetName" << schemaObject.get("EntitySetName", "").asString()
											<< "Fields" << open_document;

	for (auto const& id : fileds) {
		std::cout << id << std::endl;
		document<< id<< schemaObject["Fields"][id].asString();
	}

	document <<close_document;

	auto result =collection.insert_one(document.view());
}


Json::Value MongoDbAdapter::GetSchemaCollection()
{
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	bsoncxx::stdx::string_view dbName("StorageTestDB");

	mongocxx::database database = conn[dbName];

	auto cursor = database["schemas"].find({});

	Json::Value schemas;
	Json::Value array;

	for (auto&& doc : cursor) {

		string json  =bsoncxx::to_json(doc);
		std::cout << json << std::endl;
		Json::Value parsedFromString;
		Json::Reader reader;
		bool parsingSuccessful = reader.parse(json, parsedFromString);
		if (parsingSuccessful)
		{
			parsedFromString.removeMember("_id"); // Hide the BSON id.
			array.append(parsedFromString);
		}
	}

	schemas["Schemas"] = array;
	return schemas;
}

Json::Value MongoDbAdapter::GetSchema(string name)
{
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	bsoncxx::stdx::string_view dbName("StorageTestDB");

	mongocxx::database database = conn[dbName];

	auto cursor = database["schemas"].find( bsoncxx::builder::stream::document{} << "SchemaName" << name<<  bsoncxx::builder::stream::finalize);

	for (auto&& doc : cursor) {
		string json  =bsoncxx::to_json(doc);
		std::cout << json << std::endl;
		Json::Value parsedFromString;
		Json::Reader reader;
		bool parsingSuccessful = reader.parse(json, parsedFromString);
		if (parsingSuccessful)
		{
			parsedFromString.removeMember("_id"); // Hide the BSON id.
			return parsedFromString;
		}
	}

	return Json::nullValue;
}

void MongoDbAdapter::DeleteSchema(string name)
{
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	bsoncxx::stdx::string_view dbName("StorageTestDB");

	mongocxx::database database = conn[dbName];

    bsoncxx::builder::stream::document filter_builder;
    filter_builder << "SchemaName" << name;
    database["schemas"].delete_one(filter_builder.view());
}

void MongoDbAdapter::UpdateSchema(string name, Json::Value schemaObject)
{
	// TODO:Implement this!!! :D
}
