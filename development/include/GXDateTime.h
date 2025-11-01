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

#ifndef GXDATETIME_H
#define GXDATETIME_H

#include <cctype>
#include <locale>
#include <stdio.h>
#include <string>
#include <sstream>
#include <time.h>
#include "enums.h"

/**
 * @brief Enumerates skipped fields from a date-time.
 */
enum DATETIME_SKIPS {
    /**
     * @brief Nothing is skipped from the date-time.
     */
    DATETIME_SKIPS_NONE = 0x0,
    /**
     * @brief Year part of the date-time is skipped.
     */
    DATETIME_SKIPS_YEAR = 0x1,
    /**
     * @brief Month part of the date-time is skipped.
     */
    DATETIME_SKIPS_MONTH = 0x2,
    /**
     * @brief Day part is skipped.
     */
    DATETIME_SKIPS_DAY = 0x4,
    /**
     * @brief Day of week part of the date-time is skipped.
     */
    DATETIME_SKIPS_DAYOFWEEK = 0x8,
    /**
     * @brief Hours part of the date-time is skipped.
     */
    DATETIME_SKIPS_HOUR = 0x10,
    /**
     * @brief Minute part of the date-time is skipped.
     */
    DATETIME_SKIPS_MINUTE = 0x20,
    /**
     * @brief Seconds part of the date-time is skipped.
     */
    DATETIME_SKIPS_SECOND = 0x40,
    /**
     * @brief Hundreds of seconds part of the date-time is skipped.
     */
    DATETIME_SKIPS_MS = 0x80,
    /**
     * @brief Deviation is skipped.
     */
    DATETIME_SKIPS_DEVITATION = 0x100,
    /**
     * @brief Status is skipped.
     */
    DATETIME_SKIPS_STATUS = 0x200
};

/**
 * @brief Represents extra information for a date-time.
 */
enum DATE_TIME_EXTRA_INFO {
    /**
     * @brief No extra info.
     */
    DATE_TIME_EXTRA_INFO_NONE = 0x0,
    /**
     * @brief Daylight savings begin.
     */
    DATE_TIME_EXTRA_INFO_DST_BEGIN = 0x1,
    /**
     * @brief Daylight savings end.
     */
    DATE_TIME_EXTRA_INFO_DST_END = 0x2,
    /**
     * @brief Last day of the month.
     */
    DATE_TIME_EXTRA_INFO_LAST_DAY = 0x4,
    /**
     * @brief 2nd last day of the month.
     */
    DATE_TIME_EXTRA_INFO_LAST_DAY2 = 0x8,
};

/**
 * @brief Constants for different orders of date components.
 */
typedef enum {
    GXDLMS_DATE_FORMAT_INVALID = -1,
    GXDLMS_DATE_FORMAT_DMY = 0,
    GXDLMS_DATE_FORMAT_MDY = 1,
    GXDLMS_DATE_FORMAT_YMD = 2,
    GXDLMS_DATE_FORMAT_YDM = 3
} GXDLMS_DATE_FORMAT;

/**
 * @brief Represents a date and time value, allowing for some fields to be ignored.
 */
class CGXDateTime {
    friend class CGXTime;
    friend class CGXDate;
    short m_Deviation;
    DATETIME_SKIPS m_Skip;
    struct tm m_Value;
    DATE_TIME_EXTRA_INFO m_Extra;
    DLMS_CLOCK_STATUS m_Status;

    /////////////////////////////////////////////////////////////////////////
    // DLMS Standard says that Time zone is from normal time to UTC in minutes.
    // If meter is configured to use UTC time (UTC to normal time) set this to true.
    bool m_UseUtc2NormalTime;

    void Init(int year, int month, int day, int hour, int minute, int second, int millisecond, int devitation);
    //Get date format.
    int GetDateFormat2(GXDLMS_DATE_FORMAT &format, char &separator) const;

    //Get time format.
    int GetTimeFormat2(char &separator, char &use24HourClock);

    int GetDateTimeFormat(
        std::string &value, GXDLMS_DATE_FORMAT &format, char &dateSeparator, char &timeSeparator, char &use24HourClock
    );

public:
    /**
     * @brief Default constructor.
     */
    CGXDateTime();

    /**
     * @brief Constructor for Unix time.
     * @param value The Unix time value.
     */
    CGXDateTime(const unsigned long value);

    /**
     * @brief Constructor for Unix time.
     * @param unixTime The Unix time value.
     */
    CGXDateTime(const unsigned long long unixTime);

    /**
     * @brief Constructor.
     * @param value A tm struct.
     */
    CGXDateTime(struct tm &value);

    /**
     * @brief Constructor.
     * @param value A pointer to a tm struct.
     */
    CGXDateTime(struct tm *value);

    /**
     * @brief Constructor.
     * @param year The year.
     * @param month The month.
     * @param day The day.
     * @param hour The hour.
     * @param minute The minute.
     * @param second The second.
     * @param millisecond The millisecond.
     */
    CGXDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);

    /**
     * @brief Constructor.
     * @param year The year.
     * @param month The month.
     * @param day The day.
     * @param hour The hour.
     * @param minute The minute.
     * @param second The second.
     * @param millisecond The millisecond.
     * @param devitation The deviation.
     */
    CGXDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int devitation);

    /**
     * @brief Gets the system date-time format.
     * @param value A reference to a string to store the format.
     */
    static void GetSystemDateTimeFormat(std::string &value);

    /**
     * @brief Destructor.
     */
    virtual ~CGXDateTime();

    /**
     * @brief Sets the date-time from a string.
     * @param value The string.
     * @return An error code.
     */
    int FromString(const char *value);

    /**
     * @brief Converts the date-time to a formatted string.
     * @param pattern The format pattern.
     * @param value A reference to a string to store the result.
     * @return An error code.
     */
    int ToFormatString(const char *pattern, std::string &value);

    /**
     * @brief Converts the date-time to a formatted string using the system format.
     * @param value A reference to a string to store the result.
     * @return An error code.
     */
    int ToFormatString(std::string &value);

    /**
     * @brief Gets the tm struct value.
     * @return A reference to the tm struct.
     */
    struct tm &GetValue();

    /**
     * @brief Sets the tm struct value.
     * @param value The tm struct to set.
     */
    void SetValue(const struct tm &value);

    /**
     * @brief Gets the skipped fields.
     * @return The skipped fields.
     */
    DATETIME_SKIPS GetSkip();

    /**
     * @brief Sets the skipped fields.
     * @param value The fields to skip.
     */
    void SetSkip(DATETIME_SKIPS value);

    /**
     * @brief Converts the date-time to a string.
     * @return The string representation of the date-time.
     */
    std::string ToString() const;

    /**
     * @brief Gets the current date-time.
     * @return The current date-time.
     */
    static CGXDateTime Now();

    /**
     * @brief Gets the extra info.
     * @return The extra info.
     */
    DATE_TIME_EXTRA_INFO GetExtra();

    /**
     * @brief Sets the extra info.
     * @param value The extra info to set.
     */
    void SetExtra(DATE_TIME_EXTRA_INFO value);

    /**
     * @brief Gets the deviation.
     * @return The deviation.
     */
    int GetDeviation();

    /**
     * @brief Sets the deviation.
     * @param value The deviation to set.
     */
    void SetDeviation(int value);

    /**
     * @brief Gets the clock status.
     * @return The clock status.
     */
    DLMS_CLOCK_STATUS GetStatus();

    /**
     * @brief Sets the clock status.
     * @param value The clock status to set.
     */
    void SetStatus(DLMS_CLOCK_STATUS value);

    /**
     * @brief Resets the date and time fields.
     */
    void Reset();

    /**
     * @brief Resets the date fields.
     */
    void ResetDate();

    /**
     * @brief Sets the time to midnight.
     */
    void ResetTime();

    /**
     * @brief Adds hours to the current time.
     * @param hours The number of hours to add.
     * @return An error code.
     */
    int AddHours(int hours);

    /**
     * @brief Adds minutes to the current time.
     * @param minutes The number of minutes to add.
     * @return An error code.
     */
    int AddMinutes(int minutes);

    /**
     * @brief Adds seconds to the current time.
     * @param seconds The number of seconds to add.
     * @return An error code.
     */
    int AddSeconds(int seconds);

    /**
     * @brief Adds days to the current time.
     * @param hours The number of days to add.
     * @return An error code.
     */
    int AddDays(int hours);

    /**
     * @brief Compares the current time to another time.
     * @param antherDate The other date-time to compare to.
     * @return A value indicating the comparison result.
     */
    int CompareTo(CGXDateTime &antherDate);

    /**
     * @brief Gets the number of days in a given month.
     * @param year The year.
     * @param month The month.
     * @return The number of days in the month.
     */
    static unsigned char DaysInMonth(int year, short month);

    /**
     * @brief Gets the difference between two times in milliseconds.
     * @param start The start time.
     * @param to The end time.
     * @return The difference in milliseconds.
     */
    static long GetDifference(struct tm &start, CGXDateTime &to);

    /**
     * @brief Converts the value to local time.
     * @param localTime A reference to a tm struct to store the local time.
     * @return An error code.
     */
    int ToLocalTime(struct tm &localTime);

    /**
     * @brief Gets the current timezone.
     * @return The current timezone.
     */
    static short GetCurrentTimeZone();

    /**
     * @brief Gets the current deviation.
     * @return The current deviation.
     */
    static char GetCurrentDeviation();

    /**
     * @brief Returns the date-time as Unix time.
     * @return The Unix time.
     */
    unsigned long ToUnixTime();

    /**
     * @brief Gets whether to use UTC to normal time conversion.
     * @return True to use UTC to normal time, false otherwise.
     */
    bool GetUseUtc2NormalTime();

    /**
     * @brief Sets whether to use UTC to normal time conversion.
     * @param value True to use UTC to normal time, false otherwise.
     */
    void SetUseUtc2NormalTime(bool value);
};
#endif  //GXDATETIME_H
