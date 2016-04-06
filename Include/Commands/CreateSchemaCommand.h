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
public:
	CreateSchemaCommand(RequestContext requestContext);
    void Execute();
};



#endif /* COMMANDS_CREATESCHEMACOMMAND_H_ */
