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
class CGXDLMSActivityCalendar: public CGXDLMSObject
{
    /**
     * Active calendar name.
     */
    std::string m_CalendarNameActive;
    /**
     * Passive calendar name.
     */
    std::string m_CalendarNamePassive;
    /**
     * Active season profile.
     */
    std::vector<CGXDLMSSeasonProfile*> m_SeasonProfileActive;
    /**
     * Active week profile table.
     */
    std::vector<CGXDLMSWeekProfile*> m_WeekProfileTableActive;
    /**
     * Active day profile table.
     */
    std::vector<CGXDLMSDayProfile*> m_DayProfileTableActive;
    /**
     * Passive season profile.
     */
    std::vector<CGXDLMSSeasonProfile*> m_SeasonProfilePassive;
    /**
     * Passive day profile table.
     */
    std::vector<CGXDLMSDayProfile*> m_DayProfileTablePassive;
    /**
     * Passive week profile table.
     */
    std::vector<CGXDLMSWeekProfile*> m_WeekProfileTablePassive;
    /**
     * Activation time.
     */
    CGXDateTime m_Time;
public:
    /**
     * Constructor.
     */
    CGXDLMSActivityCalendar();

    /**
     * Constructor.
     *
     * @param ln
     *            Logical Name of the object.
     * @param sn
     *            Short Name of the object.
     */
    CGXDLMSActivityCalendar(std::string ln, unsigned short sn);

    /**
     * Constructor.
     *
     * @param ln
     *            Logical Name of the object.
     */
    CGXDLMSActivityCalendar(std::string ln);

    /**
     * Destructor.
     */
    ~CGXDLMSActivityCalendar();

    /**
     * @return Active calendar name.
     */
    std::string GetCalendarNameActive();

    /**
     * @param value
     *            Active calendar name.
     */
    void SetCalendarNameActive(std::string value);

    /**
     * @return Active season profile.
     */
    std::vector<CGXDLMSSeasonProfile*>& GetSeasonProfileActive();

    /**
     * @param value
     *            Active season profile.
     */
    void SetSeasonProfileActive(std::vector<CGXDLMSSeasonProfile*>& value);

    /**
     * @return Active week profile table.
     */
    std::vector<CGXDLMSWeekProfile*>& GetWeekProfileTableActive();

    /**
     * @param value
     *            Active week profile table.
     */
    void SetWeekProfileTableActive(std::vector<CGXDLMSWeekProfile*>& value);

    /**
     * @return Active day profile table.
     */
    std::vector<CGXDLMSDayProfile*>& GetDayProfileTableActive();

    /**
     * @param value
     *            Active day profile table.
     */
    void SetDayProfileTableActive(std::vector<CGXDLMSDayProfile*>& value);

    /**
     * @return Passive calendar name.
     */
    std::string GetCalendarNamePassive();

    /**
     * @param value
     *            Passive calendar name.
     */
    void SetCalendarNamePassive(std::string value);

    /**
     * @return Passive season profile.
     */
    std::vector<CGXDLMSSeasonProfile*>& GetSeasonProfilePassive();

    /**
     * @param value
     *            Passive season profile.
     */
    void SetSeasonProfilePassive(std::vector<CGXDLMSSeasonProfile*>& value);

    /**
     * @return Passive week profile table.
     */
    std::vector<CGXDLMSWeekProfile*>& GetWeekProfileTablePassive();

    /**
     * @param value
     *            Passive week profile table.
     */
    void SetWeekProfileTablePassive(std::vector<CGXDLMSWeekProfile*>& value);

    /**
     * @return Passive day profile table.
     */
    std::vector<CGXDLMSDayProfile*>& GetDayProfileTablePassive();

    /**
     * @param value
     *            Passive day profile table.
     */
    void SetDayProfileTablePassive(std::vector<CGXDLMSDayProfile*>& value);

    /**
     * @return Activation time.
     */
    CGXDateTime& GetTime();

    /**
     * @param value
     *            Activation time.
     */
    void SetTime(CGXDateTime& value);

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
    void GetValues(std::vector<std::string>& values);

    /**
     * @brief Gets the attribute indices to read.
     * @param all True to get all attributes, false to get only unread ones.
     * @param attributes A reference to a vector to store the attribute indices.
     */
    void GetAttributeIndexToRead(bool all, std::vector<int>& attributes);

    /**
     * @brief Gets the data type of an attribute.
     * @param index The attribute index.
     * @param type A reference to store the data type.
     * @return An error code.
     */
    int GetDataType(int index, DLMS_DATA_TYPE& type);

    /**
     * @brief Gets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    /**
     * @brief Sets the value of a given attribute.
     * @param settings The DLMS settings.
     * @param e The value event argument.
     * @return An error code.
     */
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};
#endif  //DLMS_IGNORE_ACTIVITY_CALENDAR

#endif  //GXDLMSACTIVITYCALENDAR_H
