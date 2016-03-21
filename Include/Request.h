/*
 * Request.h
 *
 *  Created on: Feb 27, 2016
 *      Author: dishan
 */
#include <string>
#include <vector>
#include <map>
using namespace std;

#ifndef REQUEST_H_
#define REQUEST_H_


class Request
{
public:
  string RequestString;
  string Method;
  string Body;
  int HeaderCount;
  map<string,string> Headers;
  Request(char* request, char* method, char* body, char**headers, int hederCount);

};




#endif /* REQUEST_H_ */
