/*
 * EntityManager.h
 *
 *  Created on: May 12, 2016
 *      Author: dishan
 */

#include "RequestContext.h"
#include <iostream>
#include <stdlib.h>
#ifndef COMMANDS_ENTITYMANAGER_H_
#define COMMANDS_ENTITYMANAGER_H_

class EntityManager
{

private:
	RequestContext context;

public:
	EntityManager(RequestContext requestContext);
    int GetAll(string* response, string entitySetName);
};




#endif /* COMMANDS_ENTITYMANAGER_H_ */
