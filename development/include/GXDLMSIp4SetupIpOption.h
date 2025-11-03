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

#ifndef GXDLMSIP4SETUPIPOPTION_H
#define GXDLMSIP4SETUPIPOPTION_H

#include "GXIgnore.h"
#include "GXDLMSObject.h"

/**
 * @brief This class represents an IP option for the IP4 setup in the DLMS/COSEM protocol.
 */
class CGXDLMSIp4SetupIpOption {
    /**
     * @brief The type of the IP option.
     */
    IP_OPTION_TYPE m_Type;
    /**
     * @brief The length of the IP option.
     */
    short m_Length;
    /**
     * @brief The data of the IP option.
     */
    CGXByteBuffer m_Data;

public:
    /**
     * @brief Gets the type of the IP option.
     * @return The type of the IP option.
     */
    IP_OPTION_TYPE GetType();
    /**
     * @brief Sets the type of the IP option.
     * @param value The new type.
     */
    void SetType(IP_OPTION_TYPE value);

    /**
     * @brief Gets the length of the IP option.
     * @return The length of the IP option.
     */
    short GetLength();
    /**
     * @brief Sets the length of the IP option.
     * @param value The new length.
     */
    void SetLength(short value);
    /**
     * @brief Gets the data of the IP option.
     * @return The data of the IP option.
     */
    CGXByteBuffer &GetData();
    /**
     * @brief Sets the data of the IP option.
     * @param value The new data.
     */
    void SetData(CGXByteBuffer &value);

    /**
     * @brief Returns a string representation of the IP option.
     * @return A string representation.
     */
    std::string ToString();
};
#endif  //GXDLMSIP4SETUPIPOPTION_H
