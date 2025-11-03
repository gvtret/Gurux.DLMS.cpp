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
 * @brief Represents a DLMS/COSEM activity calendar, which defines tariff and
 *        price information for different seasons, weeks, and days.
 */
class CGXDLMSActivityCalendar : public CGXDLMSObject
{
    /**
     * The name of the active calendar.
     */
    std::string m_CalendarNameActive;
    /**
     * The name of the passive calendar, which is scheduled to become active
     * at a later time.
     */
    std::string m_CalendarNamePassive;
    /**
     * A list of season profiles for the active calendar.
     */
    std::vector<CGXDLMSSeasonProfile*> m_SeasonProfileActive;
    /**
     * A list of week profiles for the active calendar.
     */
    std::vector<CGXDLMSWeekProfile*> m_WeekProfileTableActive;
    /**
     * A list of day profiles for the active calendar.
     */
    std::vector<CGXDLMSDayProfile*> m_DayProfileTableActive;
    /**
     * A list of season profiles for the passive calendar.
     */
    std::vector<CGXDLMSSeasonProfile*> m_SeasonProfilePassive;
    /**
     * A list of day profiles for the passive calendar.
     */
    std::vector<CGXDLMSDayProfile*> m_DayProfileTablePassive;
    /**
     * A list of week profiles for the passive calendar.
     */
    std::vector<CGXDLMSWeekProfile*> m_WeekProfileTablePassive;
    /**
     * The activation time for the passive calendar.
     */
    CGXDateTime m_Time;

public:
    /**
     * @brief Initializes a new instance of the CGXDLMSActivityCalendar class.
     */
    CGXDLMSActivityCalendar();

    /**
     * @brief Initializes a new instance of the CGXDLMSActivityCalendar class.
     * @param ln The logical name of the object.
     * @param sn The short name of the object.
     */
    CGXDLMSActivityCalendar(std::string ln, unsigned short sn);

    /**
     * @brief Initializes a new instance of the CGXDLMSActivityCalendar class.
     * @param ln The logical name of the object.
     */
    CGXDLMSActivityCalendar(std::string ln);

    /**
     * @brief Destroys the CGXDLMSActivityCalendar object, freeing all allocated
     *        profiles.
     */
    ~CGXDLMSActivityCalendar();

    /**
     * @brief Gets the name of the active calendar.
     * @return The active calendar name.
     */
    std::string GetCalendarNameActive();

    /**
     * @brief Sets the name of the active calendar.
     * @param value The active calendar name.
     */
    void SetCalendarNameActive(std::string value);

    /**
     * @brief Gets the list of season profiles for the active calendar.
     * @return A reference to the vector of active season profiles.
     */
    std::vector<CGXDLMSSeasonProfile*>& GetSeasonProfileActive();

    /**
     * @brief Sets the list of season profiles for the active calendar.
     * @param value The vector of active season profiles.
     */
    void SetSeasonProfileActive(std::vector<CGXDLMSSeasonProfile*>& value);

    /**
     * @brief Gets the list of week profiles for the active calendar.
     * @return A reference to the vector of active week profiles.
     */
    std::vector<CGXDLMSWeekProfile*>& GetWeekProfileTableActive();

    /**
     * @brief Sets the list of week profiles for the active calendar.
     * @param value The vector of active week profiles.
     */
    void SetWeekProfileTableActive(std::vector<CGXDLMSWeekProfile*>& value);

    /**
     * @brief Gets the list of day profiles for the active calendar.
     * @return A reference to the vector of active day profiles.
     */
    std::vector<CGXDLMSDayProfile*>& GetDayProfileTableActive();

    /**
     * @brief Sets the list of day profiles for the active calendar.
     * @param value The vector of active day profiles.
     */
    void SetDayProfileTableActive(std::vector<CGXDLMSDayProfile*>& value);

    /**
     * @brief Gets the name of the passive calendar.
     * @return The passive calendar name.
     */
    std::string GetCalendarNamePassive();

    /**
     * @brief Sets the name of the passive calendar.
     * @param value The passive calendar name.
     */
    void SetCalendarNamePassive(std::string value);

    /**
     * @brief Gets the list of season profiles for the passive calendar.
     * @return A reference to the vector of passive season profiles.
     */
    std::vector<CGXDLMSSeasonProfile*>& GetSeasonProfilePassive();

    /**
     * @brief Sets the list of season profiles for the passive calendar.
     * @param value The vector of passive season profiles.
     */
    void SetSeasonProfilePassive(std::vector<CGXDLMSSeasonProfile*>& value);

    /**
     * @brief Gets the list of week profiles for the passive calendar.
     * @return A reference to the vector of passive week profiles.
     */
    std::vector<CGXDLMSWeekProfile*>& GetWeekProfileTablePassive();

    /**
     * @brief Sets the list of week profiles for the passive calendar.
     * @param value The vector of passive week profiles.
     */
    void SetWeekProfileTablePassive(std::vector<CGXDLMSWeekProfile*>& value);

    /**
     * @brief Gets the list of day profiles for the passive calendar.
     * @return A reference to the vector of passive day profiles.
     */
    std::vector<CGXDLMSDayProfile*>& GetDayProfileTablePassive();

    /**
     * @brief Sets the list of day profiles for the passive calendar.
     * @param value The vector of passive day profiles.
     */
    void SetDayProfileTablePassive(std::vector<CGXDLMSDayProfile*>& value);

    /**
     * @brief Gets the activation time for the passive calendar.
     * @return The activation time.
     */
    CGXDateTime& GetTime();

    /**
     * @brief Sets the activation time for the passive calendar.
     * @param value The activation time.
     */
    void SetTime(CGXDateTime& value);

    //LCOV_EXCL_START
    /**
     * @brief Returns the total number of attributes in the object.
     * @return The attribute count.
     */
    int GetAttributeCount();

    /**
     * @brief Returns the total number of methods in the object.
     * @return The method count.
     */
    int GetMethodCount();
    //LCOV_EXCL_STOP

    /**
     * @brief Retrieves all attribute values from the object.
     * @param values A vector to store the attribute values as strings.
     */
    void GetValues(std::vector<std::string>& values);

    /**
     * @brief Fills a list with the attribute indices that should be read from
     *        the device.
     * @param all        If true, all attributes are included; otherwise, only
     *                   unread attributes are included.
     * @param attributes A list to store the indices of attributes to read.
     */
    void GetAttributeIndexToRead(bool all, std::vector<int>& attributes);

    /**
     * @brief Gets the data type of a specific attribute.
     * @param index The index of the attribute.
     * @param type  An output parameter to store the attribute's data type.
     * @return An error code indicating the success of the operation.
     */
    int GetDataType(int index, DLMS_DATA_TYPE& type);

    /**
     * @brief Gets the value of a specific attribute.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing attribute details.
     * @return An error code indicating the success of the operation.
     */
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    /**
     * @brief Sets the value of a specific attribute.
     * @param settings The DLMS settings for the connection.
     * @param e        An event argument object containing attribute details.
     * @return An error code indicating the success of the operation.
     */
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};
#endif  //DLMS_IGNORE_ACTIVITY_CALENDAR

#endif  //GXDLMSACTIVITYCALENDAR_H
