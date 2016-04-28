/*
 * RequestContext.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: dishan
 */

#include "RequestContext.h"

RequestContext::RequestContext()
{
}

RequestContext::RequestContext(Request request)
{
	this->request = request;

	if(!request.Body.empty())
	{
		Json::Value root;
		Json::CharReaderBuilder rbuilder;
		// Configure the Builder, then ...
		std::string errs;

		istringstream requestString(request.Body);
		bool parsingSuccessful = Json::parseFromStream(rbuilder, requestString, &root, &errs);
		if (!parsingSuccessful)
		{
			// report to the user the failure and their locations in the document.
			std::cout  << "Failed to parse configuration\n"
					<< errs;
			return;
		}

		this->requestRoot = root;
	}
}

