/*
 * EntityConverter.cpp

 *
 *  Created on: May 3, 2016
 *      Author: dishan
 */

#include "EntityConverter.h"

std::vector<Schema> EntityConverter::ConvertJsonSchemaCollectionToEntities(Json::Value collection)
{
	std::vector<Schema> result;

	Json::Value schemaArray = collection["Schemas"];

	if(schemaArray.isArray())
	{
		for (uint i=0;i<schemaArray.size();i++)
		{
			Schema schema;
			Json::Value schemaElement = schemaArray[i];
			schema.SchemaName = schemaElement["SchemaName"].asString();
			schema.EntitySetName = schemaElement["EntitySetName"].asString();
			schema.EntityName = schemaElement["EntityName"].asString();
			Json::Value fields = schemaElement["Fields"];

			map<string,string> fieldsMap;

			if(fields.isArray())
			{
				for (uint j=0;j<fields.size();j++)
				{
					Json::Value field = fields[j];

					for (auto const& id : field.getMemberNames()) {
					    fieldsMap[id]= field[id].asString();
					}
				}
			}

			schema.JsonValue = schemaElement;
			result.push_back(schema);
		}
	}

	return result;
}



