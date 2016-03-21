#include <iostream>
#include <string>
#include <sstream>
#include "../Include/Request.h"
#include "../Include/RequestHandler.h"
using namespace std;

extern "C" int ProcessRequest(char* requestString, char* method, char* body, char**headers, int hederCount, char** out_response) {

	Request request(requestString,method,body,headers,hederCount);

	DbAdapter adapter;
	RequestHandler handler(adapter);

	string* responseString = new string();
	int status = handler.ProcessRequest(request, responseString);

	*out_response = (char*)responseString->c_str();

	return status;
}
