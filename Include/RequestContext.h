/*
 * RequestContext.h
 *
 *  Created on: Apr 6, 2016
 *      Author: dishan
 */

#include "Request.h"
#include "json.h"
#include <iostream>

#ifndef REQUESTCONTEXT_H_
#define REQUESTCONTEXT_H_

class RequestContext
{

public:
	Request request;
	Json::Value requestRoot;
	RequestContext(Request request);

};



#endif /* REQUESTCONTEXT_H_ */
