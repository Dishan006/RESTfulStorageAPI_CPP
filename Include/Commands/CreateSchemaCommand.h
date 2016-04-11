/*
 * CreateSchemaCommand.h
 *
 *  Created on: Mar 30, 2016
 *      Author: dishan
 */

#include "RequestContext.h"
#include <iostream>
#include <stdlib.h>

#ifndef COMMANDS_CREATESCHEMACOMMAND_H_
#define COMMANDS_CREATESCHEMACOMMAND_H_

class CreateSchemaCommand
{
private:
	RequestContext context;

public:
	CreateSchemaCommand(RequestContext requestContext);
    int Execute(string* response);
};



#endif /* COMMANDS_CREATESCHEMACOMMAND_H_ */
