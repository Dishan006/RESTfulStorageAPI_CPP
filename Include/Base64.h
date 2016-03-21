/*
 * Base64Encoder.h
 *
 *  Created on: Mar 9, 2016
 *      Author: dishan
 */
#include <string>

using namespace std;

#ifndef BASE64ENCODER_H_
#define BASE64ENCODER_H_

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif /* BASE64ENCODER_H_ */
