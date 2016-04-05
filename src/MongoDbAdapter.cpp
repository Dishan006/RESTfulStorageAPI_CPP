/*
 * MongoDbAdapter.cpp

 *
 *  Created on: Apr 4, 2016
 *      Author: dishan
 */

#include "../Include/MongoDbAdapter.h"
#include <iostream>


bool MongoDbAdapter::IsSchemaDefined(string name)
{
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	bsoncxx::stdx::string_view dbName("StorageTestDB");

	mongocxx::database database = conn[dbName];

	auto cursor = database["schemas"].find( bsoncxx::builder::stream::document{} << "name" << name<<  bsoncxx::builder::stream::finalize);

	for (auto&& doc : cursor) {
		std::cout << bsoncxx::to_json(doc) << std::endl;
		return true;
	}

	return false;
}


mongocxx::database* MongoDbAdapter::GetDB()
{
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{}};
	bsoncxx::stdx::string_view dbName("StorageTestDB");
	return new mongocxx::database(conn[dbName]);
}
