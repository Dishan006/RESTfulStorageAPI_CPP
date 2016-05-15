/*
 * EntityConverter.h
 *
 *  Created on: May 3, 2016
 *      Author: dishan
 */

#include "json.h"
#include "Schema.h"
#include <vector>

#ifndef ENTITIES_ENTITYCONVERTER_H_
#define ENTITIES_ENTITYCONVERTER_H_

class EntityConverter
{
public:
	std::vector<Schema> ConvertJsonSchemaCollectionToEntities(Json::Value collection);
};

#endif /* ENTITIES_ENTITYCONVERTER_H_ */
