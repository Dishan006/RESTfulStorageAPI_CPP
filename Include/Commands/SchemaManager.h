/*
 * SchemaManager.h
 *
 *  Created on: Mar 30, 2016
 *      Author: dishan
 */

#include "RequestContext.h"
#include <iostream>
#include <stdlib.h>

#ifndef COMMANDS_SCHEMAMANAGER_H_
#define COMMANDS_SCHEMAMANAGER_H_

class SchemaManager
{
private:
	RequestContext context;

public:
	SchemaManager(RequestContext requestContext);
    int Create(string* response);
    int GetAll(string* response);
    int GetSingleEntity(string* response, string key);
    int DeleteSingleEntity(string* response, string key);
};



#endif /* COMMANDS_CREATESCHEMACOMMAND_H_ */
