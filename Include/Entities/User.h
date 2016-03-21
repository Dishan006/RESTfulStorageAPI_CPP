/*
 * User.h
 *
 *  Created on: Mar 16, 2016
 *      Author: dishan
 */

#include <string>

using namespace std;

#ifndef ENTITIES_USER_H_
#define ENTITIES_USER_H_

class User
{
public:
	int UserID;
	string UserName;
	User(int userId, string userName);
	User();
};



#endif /* ENTITIES_USER_H_ */
