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

#ifndef GXDLMSVARIANT_H
#define GXDLMSVARIANT_H

#include <vector>
#include "GXDate.h"
#include "GXTime.h"
#include "GXDateTime.h"
#include "GXBytebuffer.h"
#include "GXByteArray.h"


#define __tagVARIANT
#define __VARIANT_NAME_1
#define __VARIANT_NAME_2
#define __VARIANT_NAME_3

class CGXDLMSVariant;

/**
 * @brief Represents a DLMS/COSEM variant data type.
 */
struct dlmsVARIANT {
    /**
     * @brief The data type.
     */
	DLMS_DATA_TYPE vt;

	union {
		unsigned char bVal;
		char cVal;
		short iVal;
		long lVal;
		long long llVal;
		float fltVal;
		double dblVal;
		bool boolVal;
		unsigned short uiVal;
		unsigned long ulVal;
		unsigned long long ullVal;
		unsigned char *byteArr;
	} __VARIANT_NAME_3;

    CGXDateTime dateTime;
    /**
     * @brief The size of the byte array.
     */
    unsigned short size;
    std::string strVal;
    std::vector<CGXDLMSVariant> Arr;
};

/**
 * @brief Represents a DLMS/COSEM variant data type.
 */
class CGXDLMSVariant: public dlmsVARIANT {
    static int Convert(CGXDLMSVariant *item, DLMS_DATA_TYPE type);

public:
    /**
     * @brief Clears the variant.
     */
    void Clear();

    /**
     * @brief Default constructor.
     */
    CGXDLMSVariant();

    /**
     * @brief Copy constructor.
     * @param value The object to copy.
     */
    CGXDLMSVariant(const CGXDLMSVariant &value);

    /**
     * @brief Constructor.
     * @param value A float value.
     */
    CGXDLMSVariant(float value);

    /**
     * @brief Constructor.
     * @param value A double value.
     */
    CGXDLMSVariant(double value);

    /**
     * @brief Constructor.
     * @param value An unsigned long long value.
     */
    CGXDLMSVariant(unsigned long long value);

    /**
     * @brief Constructor.
     * @param value A long long value.
     */
    CGXDLMSVariant(long long value);

    /**
     * @brief Constructor.
     * @param value A boolean value.
     */
    CGXDLMSVariant(bool value);

    /**
     * @brief Constructor.
     * @param value A char value.
     */
    CGXDLMSVariant(char value);

    /**
     * @brief Constructor.
     * @param value A short value.
     */
    CGXDLMSVariant(short value);

    /**
     * @brief Constructor.
     * @param value An int value.
     */
    CGXDLMSVariant(int value);

    /**
     * @brief Constructor.
     * @param value A long value.
     */
    CGXDLMSVariant(long value);

    /**
     * @brief Constructor.
     * @param value A tm struct.
     */
    CGXDLMSVariant(struct tm value);

    /**
     * @brief Constructor.
     * @param value A byte array.
     * @param count The number of bytes.
     */
    CGXDLMSVariant(unsigned char *value, int count);

    /**
     * @brief Constructor.
     * @param value A CGXDate object.
     */
    CGXDLMSVariant(CGXDate &value);

    /**
     * @brief Constructor.
     * @param value A CGXTime object.
     */
    CGXDLMSVariant(CGXTime &value);

    /**
     * @brief Constructor.
     * @param value A CGXDateTime object.
     */
    CGXDLMSVariant(CGXDateTime &value);

    /**
     * @brief Constructor.
     * @param value A CGXDLMSVariant object.
     */
    CGXDLMSVariant(CGXDLMSVariant *value);

    /**
     * @brief Constructor.
     * @param pValue A byte array.
     * @param count The number of bytes.
     * @param type The data type.
     */
    CGXDLMSVariant(unsigned char *pValue, int count, DLMS_DATA_TYPE type);

    /**
     * @brief Constructor.
     * @param value An unsigned char value.
     */
    CGXDLMSVariant(unsigned char value);

    /**
     * @brief Constructor.
     * @param value An unsigned short value.
     */
    CGXDLMSVariant(unsigned short value);

    /**
     * @brief Constructor.
     * @param value An unsigned long value.
     */
    CGXDLMSVariant(unsigned long value);

    /**
     * @brief Constructor.
     * @param value A string value.
     */
    CGXDLMSVariant(std::string value);

    /**
     * @brief Constructor.
     * @param value A wide string value.
     */
    CGXDLMSVariant(std::wstring value);

    /**
     * @brief Constructor.
     * @param value A CGXByteBuffer object.
     */
    CGXDLMSVariant(CGXByteBuffer &value);

    /**
     * @brief Constructor.
     * @param value A C-style string.
     */
    CGXDLMSVariant(const char *value);

    /**
     * @brief Constructor.
     * @param value An unsigned int value.
     */
    CGXDLMSVariant(unsigned int value);

    /**
     * @brief Destructor.
     */
    ~CGXDLMSVariant();

    /**
     * @brief Copy assignment operator.
     * @param value The object to copy.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(const CGXDLMSVariant &value);

    /**
     * @brief Assignment operator.
     * @param value A string value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(std::string value);

    /**
     * @brief Assignment operator.
     * @param value A C-style string.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(const char *value);

    /**
     * @brief Assignment operator.
     * @param value A CGXByteBuffer object.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(CGXByteBuffer &value);

    /**
     * @brief Assignment operator.
     * @param value A CGXByteArray object.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(CGXByteArray &value);

    /**
     * @brief Assignment operator.
     * @param value A float value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(float value);

    /**
     * @brief Assignment operator.
     * @param value A double value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(double value);

    /**
     * @brief Assignment operator.
     * @param value An unsigned long long value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(unsigned long long value);

    /**
     * @brief Assignment operator.
     * @param value A long long value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(long long value);

    /**
     * @brief Assignment operator.
     * @param value A boolean value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(const bool value);

    /**
     * @brief Assignment operator.
     * @param value A char value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(char value);

    /**
     * @brief Assignment operator.
     * @param value A short value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(short value);

    /**
     * @brief Assignment operator.
     * @param value An int value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(int value);

    /**
     * @brief Assignment operator.
     * @param value A long value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(long value);

    /**
     * @brief Assignment operator.
     * @param value An unsigned char value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(unsigned char value);

    /**
     * @brief Assignment operator.
     * @param value An unsigned short value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(unsigned short value);

    /**
     * @brief Assignment operator.
     * @param value An unsigned int value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(unsigned int value);

    /**
     * @brief Assignment operator.
     * @param value An unsigned long value.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(unsigned long value);

    /**
     * @brief Assignment operator.
     * @param value A tm struct.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(struct tm value);

    /**
     * @brief Assignment operator.
     * @param value A CGXDate object.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(CGXDate &value);

    /**
     * @brief Assignment operator.
     * @param value A CGXTime object.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(CGXTime &value);

    /**
     * @brief Assignment operator.
     * @param value A CGXDateTime object.
     * @return A reference to this object.
     */
    CGXDLMSVariant &operator=(CGXDateTime &value);

    /**
     * @brief Adds a byte array to the variant.
     * @param pValue The byte array.
     * @param count The number of bytes.
     */
    void Add(const unsigned char *pValue, int count);

    /**
     * @brief Adds a C-style string to the variant.
     * @param pValue The C-style string.
     * @param count The number of characters.
     */
    void Add(const char *pValue, int count);

    /**
     * @brief Adds a string to the variant.
     * @param value The string to add.
     */
    void Add(std::string value);

    /**
     * @brief Checks if this variant is equal to another.
     * @param item The other variant.
     * @return True if equal, false otherwise.
     */
    bool Equals(CGXDLMSVariant &item);

    /**
     * @brief Changes the type of the variant.
     * @param newType The new type.
     * @return An error code.
     */
    int ChangeType(DLMS_DATA_TYPE newType);

    /**
     * @brief Gets the size of the variant in bytes.
     * @return The size in bytes.
     */
    int GetSize() const;

    /**
     * @brief Gets the size of a data type in bytes.
     * @param vt The data type.
     * @return The size in bytes.
     */
    static int GetSize(DLMS_DATA_TYPE vt);

    /**
     * @brief Converts the variant to a string.
     * @return The string representation of the variant.
     */
    std::string ToString() const;

    /**
     * @brief Converts the variant to an integer.
     * @return The integer value.
     */
    int ToInteger();

    /**
     * @brief Converts the variant to a double.
     * @return The double value.
     */
    double ToDouble();

    /**
     * @brief Gets the byte representation of the variant.
     * @param value A buffer to store the bytes.
     * @return An error code.
     */
    int GetBytes(CGXByteBuffer &value);

    /**
     * @brief Checks if the variant is a number.
     * @return True if the variant is a number, false otherwise.
     */
    bool IsNumber();
};
#endif  //GXDLMSVARIANT_H
