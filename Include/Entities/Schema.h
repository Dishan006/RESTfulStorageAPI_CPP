/*
 * Schema.h
 *
 *  Created on: Apr 14, 2016
 *      Author: dishan
 */

#include <string>
#include <map>
#include "Entity.h"

using namespace std;

#ifndef ENTITIES_SCHEMA_H_
#define ENTITIES_SCHEMA_H_

class Schema:public Entity
{
public:
	string SchemaName;
	string EntityName;
	string EntitySetName;
	map<string,string> Fields;
	Schema();
};

#endif /* ENTITIES_SCHEMA_H_ */
