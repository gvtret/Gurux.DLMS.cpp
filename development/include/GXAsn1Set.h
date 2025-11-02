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

#ifndef GXASNSET_H
#define GXASNSET_H

#include <string>
#include "GXAsn1Base.h"

/**
 * @brief Represents an ASN.1 SET, an unordered collection of one or more types.
 *
 * In this implementation, the SET is represented as a key-value pair of ASN.1 objects.
 * It manages the memory of the key and value objects, freeing them upon destruction.
 */
class CGXAsn1Set: public CGXAsn1Base {
private:
    /**
     * @brief A pointer to the key ASN.1 object.
     */
    CGXAsn1Base *m_Key;
    /**
     * @brief A pointer to the value ASN.1 object.
     */
    CGXAsn1Base *m_Value;

public:
    /**
     * @brief Default constructor. Initializes an empty SET with null key and value.
     */
    CGXAsn1Set() {
        m_Value = m_Key = NULL;
    }

    /**
     * @brief Constructor that initializes the SET with a key and a value.
     * @param key A pointer to the ASN.1 object to be used as the key.
     * @param value A pointer to the ASN.1 object to be used as the value.
     */
    CGXAsn1Set(CGXAsn1Base *key, CGXAsn1Base *value) {
        m_Key = key;
        m_Value = value;
    }

    /**
     * @brief Destructor.
     *
     * Deletes the key and value ASN.1 objects to prevent memory leaks.
     */
    ~CGXAsn1Set() {
        if (m_Value != NULL) {
            delete m_Value;
            m_Value = NULL;
        }
        if (m_Key != NULL) {
            delete m_Key;
            m_Key = NULL;
        }
    }

    /**
     * @brief Gets the key part of the SET.
     * @return A pointer to the key ASN.1 base object.
     */
    CGXAsn1Base *GetKey() {
        return m_Key;
    }

    /**
     * @brief Gets the value part of the SET.
     * @return A pointer to the value ASN.1 base object.
     */
    CGXAsn1Base *GetValue() {
        return m_Value;
    }

    /**
     * @brief Converts the SET to its string representation.
     * @return A string that concatenates the string representations of the key and value.
     */
    std::string ToString() {
        std::string value;
        if (m_Key != NULL) {
            value += m_Key->ToString();
        }
        if (m_Value != NULL) {
            value += m_Value->ToString();
        }
        return value;
    }
};

#endif  //GXASNSET_H
