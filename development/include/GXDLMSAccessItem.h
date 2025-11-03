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

#ifndef CGXDLMSACCESSITEM_H
#define CGXDLMSACCESSITEM_H

#include "GXDLMSObject.h"

/**
 * @brief Represents a single operation within an Access service request.
 *
 * The Access service allows a client to read or write a list of attributes from
 * multiple objects in a single transaction. This class defines one item in that list,
 * specifying the target object, the command (read/write), and the attribute index.
 */
class CGXDLMSAccessItem {
    /**
     * @brief A pointer to the target COSEM object for the access operation.
     */
    CGXDLMSObject *m_Target;
    /**
     * @brief The type of access command to be executed (e.g., read, write).
     */
    DLMS_ACCESS_SERVICE_COMMAND_TYPE m_Command;
    /**
     * @brief The index of the attribute to be accessed within the target object.
     */
    unsigned char m_Index;
    /**
     * @brief The error code returned by the server for this specific access item.
     */
    DLMS_ERROR_CODE m_Error;
    /**
     * @brief The value read from or written to the attribute.
     */
    CGXDLMSVariant m_Value;

public:
    /** @brief Gets the COSEM target object. @return A pointer to the target object. */
    CGXDLMSObject *GetTarget();
    /** @brief Sets the COSEM target object. @param value A pointer to the target object. */
    void SetTarget(CGXDLMSObject *value);

    /** @brief Gets the executed command type. @return The access command type. */
    DLMS_ACCESS_SERVICE_COMMAND_TYPE GetCommand();
    /** @brief Sets the executed command type. @param value The access command type. */
    void SetCommand(DLMS_ACCESS_SERVICE_COMMAND_TYPE value);

    /** @brief Gets the attribute index. @return The attribute index. */
    unsigned char GetIndex();
    /** @brief Sets the attribute index. @param value The attribute index. */
    void SetIndex(unsigned char value);

    /** @brief Sets the reply error code. @param value The error code. */
    void SetError(DLMS_ERROR_CODE value);
    /** @brief Gets the reply error code. @return The error code. */
    DLMS_ERROR_CODE GetError();

    /** @brief Sets the reply value. @param value The value. */
    void SetValue(CGXDLMSVariant &value);
    /** @brief Gets the reply value. @return A reference to the value. */
    CGXDLMSVariant &GetValue();

    /**
     * @brief Default constructor.
     */
    CGXDLMSAccessItem();

    /**
     * @brief Constructor to initialize an access item.
     * @param command The command to execute (read/write).
     * @param target A pointer to the COSEM target object.
     * @param attributeIndex The index of the attribute to access.
     */
    CGXDLMSAccessItem(DLMS_ACCESS_SERVICE_COMMAND_TYPE command, CGXDLMSObject *target, unsigned char attributeIndex);
};
#endif  //CGXDLMSACCESSITEM_H
