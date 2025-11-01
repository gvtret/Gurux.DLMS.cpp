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

#ifndef CGXASNBASE_H
#define CGXASNBASE_H

#include <string>
#include <assert.h>

/**
 * @brief This is the base class for all ASN.1 data types.
 *
 * It provides a common interface for ASN.1 objects, primarily for converting
 * their values to a string representation. This class is intended to be inherited
 * by specific ASN.1 type implementations.
 */
class CGXAsn1Base {
public:
    /**
     * @brief Converts the ASN.1 object's value to its string representation.
     *
     * This is a virtual method that should be overridden by all derived classes.
     * The base implementation asserts if called, as it has no value to convert.
     *
     * @return A string representation of the object's value.
     */
    virtual std::string ToString() {
        assert(0);
        return "";
    }

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~CGXAsn1Base() {
    }
};

#endif  //CGXASNBASE_H
