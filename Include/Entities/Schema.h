/*
 * Schema.h
 *
 *  Created on: Apr 14, 2016
 *      Author: dishan
 */

#include <string>
#include <map>
using namespace std;

#ifndef ENTITIES_SCHEMA_H_
#define ENTITIES_SCHEMA_H_

class Schema
{
public:
	int SchemaId;
	string SchemaName;
	string EntityName;
	string EntitySetName;
	map<string,string> Fileds;
	Schema();
};





#endif /* ENTITIES_SCHEMA_H_ */
