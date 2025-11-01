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

#ifndef GXASN1CONTEXT_H
#define GXASN1CONTEXT_H

#include <vector>
#include "GXAsn1Base.h"
#include "GXDLMSVariant.h"

/**
 * @brief Represents an ASN.1 context-specific tagged value.
 *
 * In ASN.1, context-specific tags are used to distinguish between different
 * data elements within a defined context, such as within a SET or SEQUENCE.
 * A context-specific value can be either primitive or constructed (containing
 * other ASN.1 values).
 */
class CGXAsn1Context: public CGXAsn1Base {
private:
    /**
     * @brief The context-specific tag number (index).
     */
    int m_Index;
    /**
     * @brief A flag indicating whether the tag is constructed (true) or primitive (false).
     */
    bool m_Constructed;
    /**
     * @brief A collection of nested ASN.1 objects if the tag is constructed.
     */
    std::vector<CGXAsn1Base *> m_Values;

public:
    /**
     * @brief Constructor.
     */
    CGXAsn1Context();

    /**
     * @brief Destructor.
     *
     * Cleans up and frees the memory of all ASN.1 objects contained within the `m_Values` vector.
     */
    ~CGXAsn1Context();

    /**
     * @brief Gets the context-specific tag number.
     * @return The tag number (index).
     */
    int GetIndex();

    /**
     * @brief Sets the context-specific tag number.
     * @param value The tag number (index).
     */
    void SetIndex(int value);

    /**
     * @brief Checks if the tag is marked as constructed.
     * @return True if the tag is constructed, false otherwise.
     */
    bool GetConstructed();

    /**
     * @brief Sets the constructed flag for the tag.
     * @param value True to mark the tag as constructed, false for primitive.
     */
    void SetConstructed(bool value);

    /**
     * @brief Gets the collection of nested ASN.1 objects.
     * @return A pointer to the vector of contained ASN.1 base objects. This is
     *         primarily used when the tag is constructed.
     */
    std::vector<CGXAsn1Base *> *GetValues() {
        return &m_Values;
    }
};

#endif  //GXASN1CONTEXT_H
