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

#ifndef GXDLMSACTIVITYCALENDAR_H
#define GXDLMSACTIVITYCALENDAR_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_ACTIVITY_CALENDAR

#include "GXDLMSObject.h"
#include "GXDLMSSeasonProfile.h"
#include "GXDLMSWeekProfile.h"
#include "GXDLMSDayProfile.h"

/**
 * @brief Represents a DLMS/COSEM activity calendar.
 */
class CGXDLMSActivityCalendar: public CGXDLMSObject {
    std::string m_CalendarNameActive;
    std::string m_CalendarNamePassive;
    std::vector<CGXDLMSSeasonProfile *> m_SeasonProfileActive;
    std::vector<CGXDLMSWeekProfile *> m_WeekProfileTableActive;
    std::vector<CGXDLMSDayProfile *> m_DayProfileTableActive;
    std::vector<CGXDLMSSeasonProfile *> m_SeasonProfilePassive;
    std::vector<CGXDLMSDayProfile *> m_DayProfileTablePassive;
    std::vector<CGXDLMSWeekProfile *> m_WeekProfileTablePassive;
    CGXDateTime m_Time;

public:
    /**
     * @brief Constructor.
     */
    CGXDLMSActivityCalendar();

    /**
     * @brief Constructor.
     * @param ln The logical name of the object.
     * @param sn The short name of the object.
     */
    CGXDLMSActivityCalendar(std::string ln, unsigned short sn);

    /**
     * @brief Constructor.
     * @param ln The logical name of the object.
     */
    CGXDLMSActivityCalendar(std::string ln);

    /**
     * @brief Destructor.
     */
    ~CGXDLMSActivityCalendar();

    /**
     * @brief Gets the active calendar name.
     * @return The active calendar name.
     */
    std::string GetCalendarNameActive();

    /**
     * @brief Sets the active calendar name.
     * @param value The active calendar name to set.
     */
    void SetCalendarNameActive(std::string value);

    /**
     * @brief Gets the active season profile.
     * @return A reference to the vector of active season profiles.
     */
    std::vector<CGXDLMSSeasonProfile *> &GetSeasonProfileActive();

    /**
     * @brief Sets the active season profile.
     * @param value The vector of active season profiles to set.
     */
    void SetSeasonProfileActive(std::vector<CGXDLMSSeasonProfile *> &value);

    /**
     * @brief Gets the active week profile table.
     * @return A reference to the vector of active week profiles.
     */
    std::vector<CGXDLMSWeekProfile *> &GetWeekProfileTableActive();

    /**
     * @brief Sets the active week profile table.
     * @param value The vector of active week profiles to set.
     */
    void SetWeekProfileTableActive(std::vector<CGXDLMSWeekProfile *> &value);

    /**
     * @brief Gets the active day profile table.
     * @return A reference to the vector of active day profiles.
     */
    std::vector<CGXDLMSDayProfile *> &GetDayProfileTableActive();

    /**
     * @brief Sets the active day profile table.
     * @param value The vector of active day profiles to set.
     */
    void SetDayProfileTableActive(std::vector<CGXDLMSDayProfile *> &value);

    /**
     * @brief Gets the passive calendar name.
     * @return The passive calendar name.
     */
    std::string GetCalendarNamePassive();

    /**
     * @brief Sets the passive calendar name.
     * @param value The passive calendar name to set.
     */
    void SetCalendarNamePassive(std::string value);

    /**
     * @brief Gets the passive season profile.
     * @return A reference to the vector of passive season profiles.
     */
    std::vector<CGXDLMSSeasonProfile *> &GetSeasonProfilePassive();

    /**
     * @brief Sets the passive season profile.
     * @param value The vector of passive season profiles to set.
     */
    void SetSeasonProfilePassive(std::vector<CGXDLMSSeasonProfile *> &value);

    /**
     * @brief Gets the passive week profile table.
     * @return A reference to the vector of passive week profiles.
     */
    std::vector<CGXDLMSWeekProfile *> &GetWeekProfileTablePassive();

    /**
     * @brief Sets the passive week profile table.
     * @param value The vector of passive week profiles to set.
     */
    void SetWeekProfileTablePassive(std::vector<CGXDLMSWeekProfile *> &value);

    /**
     * @brief Gets the passive day profile table.
     * @return A reference to the vector of passive day profiles.
     */
    std::vector<CGXDLMSDayProfile *> &GetDayProfileTablePassive();

    /**
     * @brief Sets the passive day profile table.
     * @param value The vector of passive day profiles to set.
     */
    void SetDayProfileTablePassive(std::vector<CGXDLMSDayProfile *> &value);

    /**
     * @brief Gets the activation time.
     * @return A reference to the activation time.
     */
    CGXDateTime &GetTime();

    /**
     * @brief Sets the activation time.
     * @param value The activation time to set.
     */
    void SetTime(CGXDateTime &value);

    /**
     * @brief Gets the number of attributes.
     * @return The number of attributes.
     */
    int GetAttributeCount();

    /**
     * @brief Gets the number of methods.
     * @return The number of methods.
     */
    int GetMethodCount();

    /**
     * @brief Gets the attribute values as strings.
     * @param values A reference to a vector to store the values.
     */
    void GetValues(std::vector<std::string> &values);

    /**
     * @brief Gets the attribute indices to read.
     * @param all True to get all attributes, false to get only unread ones.
     * @param attributes A reference to a vector to store the attribute indices.
     */
    void GetAttributeIndexToRead(bool all, std::vector<int> &attributes);

    /**
     * @brief Gets the data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return An error code.
     */
    int GetDataType(int index, DLMS_DATA_TYPE &type);

    /**
     * @brief Gets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int GetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

    /**
     * @brief Sets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int SetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);
};
#endif  //DLMS_IGNORE_ACTIVITY_CALENDAR

#endif  //GXDLMSACTIVITYCALENDAR_H
