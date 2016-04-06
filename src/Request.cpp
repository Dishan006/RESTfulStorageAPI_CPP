/*
 * Request.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: dishan
 */
#include "Request.h"
#include <string>
#include <vector>
#include<stdlib.h>
#include <algorithm>


Request::Request(char* request, char* method, char* body, char**headers, int headerCount)
{
	this->HeaderCount =headerCount;
	this->RequestString = string(request);
	this->Body = string(body);
	this->Method= string(method);

	map<string,string> headersMap;
	for(int i=0;i<headerCount;i++)
	{
		string headerString = string(headers[i]);
		int splitter = headerString.find_first_of(":",0);

		string key = headerString.substr(0,splitter-1);
		key.erase(std::remove(key.begin(), key.end(), ' '), key.end());

		string value = headerString.substr(splitter+1,headerString.length()-1-splitter);
		value.erase(std::remove(value.begin(), value.begin()+3, ' '), value.begin()+3);

		headersMap.insert(pair<string,string>(key,value));
	}

	this->Headers = headersMap;
}

Request::Request()
{}



