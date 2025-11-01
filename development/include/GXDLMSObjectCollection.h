//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXDLMSOBJECTCOLLECTION_H
#define GXDLMSOBJECTCOLLECTION_H

#include <vector>
#include "GXDLMSObject.h"
#include "GXXmlWriterSettings.h"

/**
 * @brief Represents a collection of DLMS/COSEM objects.
 */
class CGXDLMSObjectCollection: public std::vector<CGXDLMSObject *> {
public:
    /**
     * @brief Destructor.
     */
    ~CGXDLMSObjectCollection();

    /**
     * @brief Finds an object by its logical name.
     * @param type The object type.
     * @param ln The logical name.
     * @return A pointer to the found object, or NULL if not found.
     */
    CGXDLMSObject *FindByLN(DLMS_OBJECT_TYPE type, std::string &ln);

    /**
     * @brief Finds an object by its logical name.
     * @param type The object type.
     * @param ln The logical name.
     * @return A pointer to the found object, or NULL if not found.
     */
    CGXDLMSObject *FindByLN(DLMS_OBJECT_TYPE type, unsigned char ln[6]);

    /**
     * @brief Finds an object by its short name.
     * @param sn The short name.
     * @return A pointer to the found object, or NULL if not found.
     */
    CGXDLMSObject *FindBySN(unsigned short sn);

    /**
     * @brief Gets all objects of a specific type.
     * @param type The object type.
     * @param items A reference to a collection to store the found objects.
     */
    void GetObjects(DLMS_OBJECT_TYPE type, CGXDLMSObjectCollection &items);

    /**
     * @brief Adds an object to the collection.
     * @param item A pointer to the object to add.
     */
    void push_back(CGXDLMSObject *item);

    /**
     * @brief Frees the memory allocated by the objects in the collection.
     */
    void Free();

    /**
     * @brief Converts the collection to a string.
     * @return The string representation of the collection.
     */
    std::string ToString();

    /**
     * @brief Saves the COSEM objects to a file.
     * @param fileName The name of the file.
     * @return An error code.
     */
    int Save(const char *fileName);

    /**
     * @brief Saves the COSEM objects to a file.
     * @param fileName The name of the file.
     * @param settings The XML writer settings.
     * @return An error code.
     */
    int Save(const char *fileName, CGXXmlWriterSettings &settings);

    /**
     * @brief Loads COSEM objects from a file.
     * @param fileName The name of the XML file.
     * @return An error code.
     */
    int Load(const char *fileName);
};

#endif  //GXDLMSOBJECTCOLLECTION_H
