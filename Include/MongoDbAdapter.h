/*
 * MongoDbAdapter.h
 *
 *  Created on: Mar 30, 2016
 *      Author: dishan
 */

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <string>
using namespace std;

#ifndef MONGODBADAPTER_H_
#define MONGODBADAPTER_H_

class MongoDbAdapter
{
public:
	bool IsSchemaDefined(string name);

private:
	mongocxx::database* GetDB();

};


#endif /* MONGODBADAPTER_H_ */
