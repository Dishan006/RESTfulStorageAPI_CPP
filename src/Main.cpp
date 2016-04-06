#include <iostream>
#include <string>
#include <sstream>
#include "Request.h"
#include "RequestHandler.h"
using namespace std;

extern "C" int ProcessRequest(char* requestString, char* method, char* body, char**headers, int hederCount, char** out_response) {

	Request request(requestString,method,body,headers,hederCount);

	MySqlDbAdapter adapter;
	RequestHandler handler(adapter);

	string* responseString = new string();
	int status = handler.ProcessRequest(request, responseString);

	*out_response = (char*)responseString->c_str();

	//delete responseString;
	return status;
}
