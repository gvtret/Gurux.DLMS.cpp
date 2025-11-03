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

#ifndef GXASN1SEQUENCE_H
#define GXASN1SEQUENCE_H

#include <vector>
#include "GXAsn1Base.h"
#include "GXDLMSVariant.h"

/**
 * @brief Represents an ASN.1 SEQUENCE, which is an ordered collection of one or more ASN.1 types.
 *
 * This class acts as a container for a heterogeneous list of other ASN.1 objects.
 * It manages the memory of the contained objects, freeing them upon destruction.
 */
class CGXAsn1Sequence: public CGXAsn1Base {
private:
    /**
     * @brief A vector of pointers to the ASN.1 objects contained within the sequence.
     */
    std::vector<CGXAsn1Base *> m_Values;

public:
    /**
     * @brief Default constructor. Initializes an empty sequence.
     */
    CGXAsn1Sequence() {
    }

    /**
     * @brief Destructor.
     *
     * Iterates through the contained ASN.1 objects and deletes each one to prevent memory leaks.
     */
    ~CGXAsn1Sequence() {
        for (std::vector<CGXAsn1Base *>::iterator it = m_Values.begin(); it != m_Values.end(); ++it) {
            delete (*it);
        }
        m_Values.clear();
    }

    /**
     * @brief Gets the collection of ASN.1 objects in the sequence.
     * @return A pointer to the vector of contained ASN.1 base objects.
     */
    std::vector<CGXAsn1Base *> *GetValues() {
        return &m_Values;
    }
};

#endif  //GXASN1SEQUENCE_H
