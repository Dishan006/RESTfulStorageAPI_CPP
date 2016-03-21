/*
 * HashUtil.cpp

 *
 *  Created on: Mar 13, 2016
 *      Author: dishan
 */

#include "../Include/HashUtil.h"
#include <string>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

#include <openssl/sha.h>


string* HashUtil::GenaretSHA256(string input)
{
	char* charArray = (char*)input.c_str();
	char outputBuffer[65];
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, charArray, strlen(charArray));
	SHA256_Final(hash, &sha256);
	int i = 0;
	for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}
	outputBuffer[64] = 0;

	return new string(outputBuffer);
}
