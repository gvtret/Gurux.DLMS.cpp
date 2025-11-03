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

#ifndef GXASN1VARIANT_H
#define GXASN1VARIANT_H

#include "GXDLMSVariant.h"
#include "GXAsn1Base.h"

/**
 * @brief Represents an ASN.1 ANY type, which can hold any ASN.1 value.
 *
 * This class uses a CGXDLMSVariant to store the actual data, allowing it to
 * hold a value of any supported DLMS/COSEM data type. It provides numerous
 * constructors and assignment operators for easy conversion from standard
 * C++ types.
 */
class CGXAsn1Variant: public CGXAsn1Base {
private:
    /**
     * @brief The underlying variant object that holds the data.
     */
    CGXDLMSVariant m_Value;

public:
    /**
     * @brief Default constructor. Initializes an empty variant object.
     */
    CGXAsn1Variant() {
    }

    /**
     * @brief Gets the underlying CGXDLMSVariant object.
     * @return A reference to the internal variant object.
     */
    CGXDLMSVariant &GetValue() {
        return m_Value;
    }

    /**
     * @brief Sets the value of the variant from another CGXDLMSVariant object.
     * @param value The new value.
     */
    void SetValue(CGXDLMSVariant &value) {
        m_Value = value;
    }

    /** @brief Constructor for float. @param value The initial value. */
    CGXAsn1Variant(float value);
    /** @brief Constructor for double. @param value The initial value. */
    CGXAsn1Variant(double value);
    /** @brief Constructor for unsigned long long. @param value The initial value. */
    CGXAsn1Variant(unsigned long long value);
    /** @brief Constructor for long long. @param value The initial value. */
    CGXAsn1Variant(long long value);
    /** @brief Constructor for bool. @param value The initial value. */
    CGXAsn1Variant(bool value);
    /** @brief Constructor for char. @param value The initial value. */
    CGXAsn1Variant(char value);
    /** @brief Constructor for short. @param value The initial value. */
    CGXAsn1Variant(short value);
    /** @brief Constructor for int. @param value The initial value. */
    CGXAsn1Variant(int value);
    /** @brief Constructor for long. @param value The initial value. */
    CGXAsn1Variant(long value);
    /** @brief Constructor for struct tm. @param value The initial value. */
    CGXAsn1Variant(struct tm value);
    /** @brief Constructor for byte array. @param value A pointer to the byte array. @param count The number of bytes. */
    CGXAsn1Variant(unsigned char *value, int count);
    /** @brief Constructor for CGXDate. @param value The initial value. */
    CGXAsn1Variant(CGXDate &value);
    /** @brief Constructor for CGXTime. @param value The initial value. */
    CGXAsn1Variant(CGXTime &value);
    /** @brief Constructor for CGXDateTime. @param value The initial value. */
    CGXAsn1Variant(CGXDateTime &value);
    /** @brief Copy constructor. @param value The object to copy. */
    CGXAsn1Variant(CGXAsn1Variant *value);
    /** @brief Constructor for unsigned char. @param value The initial value. */
    CGXAsn1Variant(unsigned char value);
    /** @brief Constructor for unsigned short. @param value The initial value. */
    CGXAsn1Variant(unsigned short value);
    /** @brief Constructor for unsigned long. @param value The initial value. */
    CGXAsn1Variant(unsigned long value);
    /** @brief Constructor for std::string. @param value The initial value. */
    CGXAsn1Variant(std::string value);
    /** @brief Constructor for std::wstring. @param value The initial value. */
    CGXAsn1Variant(std::wstring value);
    /** @brief Constructor for CGXByteBuffer. @param value The initial value. */
    CGXAsn1Variant(CGXByteBuffer &value);
    /** @brief Constructor for CGXByteArray. @param value The initial value. */
    CGXAsn1Variant(CGXByteArray &value);
    /** @brief Constructor for C-style string. @param value The initial value. */
    CGXAsn1Variant(const char *value);
    /** @brief Constructor for unsigned int. @param value The initial value. */
    CGXAsn1Variant(unsigned int value);
    /**
     * @brief Destructor.
     */
    ~CGXAsn1Variant();

    /** @brief Assignment operator. @param value The object to assign from. @return A reference to this object. */
    CGXAsn1Variant &operator=(const CGXAsn1Variant &value);
    /** @brief Assignment operator for std::string. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(std::string value);
    /** @brief Assignment operator for C-style string. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(const char *value);
    /** @brief Assignment operator for CGXByteBuffer. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(CGXByteBuffer &value);
    /** @brief Assignment operator for CGXByteArray. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(CGXByteArray &value);
    /** @brief Assignment operator for float. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(float value);
    /** @brief Assignment operator for double. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(double value);
    /** @brief Assignment operator for unsigned long long. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(unsigned long long value);
    /** @brief Assignment operator for long long. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(long long value);
    /** @brief Assignment operator for bool. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(const bool value);
    /** @brief Assignment operator for char. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(char value);
    /** @brief Assignment operator for short. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(short value);
    /** @brief Assignment operator for int. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(int value);
    /** @brief Assignment operator for long. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(long value);
    /** @brief Assignment operator for unsigned char. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(unsigned char value);
    /** @brief Assignment operator for unsigned short. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(unsigned short value);
    /** @brief Assignment operator for unsigned int. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(unsigned int value);
    /** @brief Assignment operator for unsigned long. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(unsigned long value);
    /** @brief Assignment operator for struct tm. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(struct tm value);
    /** @brief Assignment operator for CGXDate. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(CGXDate &value);
    /** @brief Assignment operator for CGXTime. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(CGXTime &value);
    /** @brief Assignment operator for CGXDateTime. @param value The value to assign. @return A reference to this object. */
    CGXAsn1Variant &operator=(CGXDateTime &value);

    /**
     * @brief Compares this variant with another for equality.
     * @param item The variant to compare against.
     * @return True if the variants are equal, false otherwise.
     */
    bool Equals(CGXAsn1Variant &item);

    /**
     * @brief Converts the variant's value to its string representation.
     * @return A string representation of the contained value.
     */
    std::string ToString();
};

#endif  //GXASN1VARIANT_H
