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

#ifndef GXDLMSEMERGENCYPROFILE_H
#define GXDLMSEMERGENCYPROFILE_H

#include "GXDateTime.h"

/**
 * @brief This class represents an emergency profile for the DLMS/COSEM protocol.
 */
class CGXDLMSEmergencyProfile {
    /**
     * @brief The ID of the emergency profile.
     */
    int m_ID;
    /**
     * @brief The activation time of the emergency profile.
     */
    CGXDateTime m_ActivationTime;
    /**
     * @brief The duration of the emergency profile.
     */
    int m_Duration;

public:
    /**
     * @brief Gets the ID of the emergency profile.
     * @return The ID of the emergency profile.
     */
    int GetID();
    /**
     * @brief Sets the ID of the emergency profile.
     * @param value The new ID.
     */
    void SetID(int value);

    /**
     * @brief Gets the activation time of the emergency profile.
     * @return The activation time.
     */
    CGXDateTime &GetActivationTime();
    /**
     * @brief Sets the activation time of the emergency profile.
     * @param value The new activation time.
     */
    void SetActivationTime(CGXDateTime value);

    /**
     * @brief Gets the duration of the emergency profile.
     * @return The duration.
     */
    int GetDuration();
    /**
     * @brief Sets the duration of the emergency profile.
     * @param value The new duration.
     */
    void SetDuration(int value);

    /**
     * @brief Returns a string representation of the emergency profile.
     * @return A string representation.
     */
    std::string ToString();
};

#endif  //GXDLMSEMERGENCYPROFILE_H
