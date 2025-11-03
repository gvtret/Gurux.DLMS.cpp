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

#ifndef GXCREDIT_CHARGE_CONFIGURATION_H
#define GXCREDIT_CHARGE_CONFIGURATION_H

#include "enums.h"
#include <string>

/**
 * @brief Represents the configuration for credit and charge operations in a DLMS/COSEM account.
 *
 * This class defines the references and settings for managing credit and charges
 * within a DLMS Account object.
 */
class CGXCreditChargeConfiguration {
    /**
     * @brief A reference to an object that provides credit to the account.
     */
    std::string m_CreditReference;

    /**
     * @brief A reference to an object that applies charges to the account.
     */
    std::string m_ChargeReference;

    /**
     * @brief Defines the behavior of the credit collection process.
     */
    DLMS_CREDIT_COLLECTION_CONFIGURATION m_CollectionConfiguration;

public:
    /**
     * @brief Default constructor.
     */
    CGXCreditChargeConfiguration();

    /**
     * @brief Gets the credit reference.
     * @return A reference to the credit reference string.
     */
    std::string &GetCreditReference();

    /**
     * @brief Sets the credit reference.
     * @param value The new credit reference string.
     */
    void SetCreditReference(std::string &value);

    /**
     * @brief Gets the charge reference.
     * @return A reference to the charge reference string.
     */
    std::string &GetChargeReference();

    /**
     * @brief Sets the charge reference.
     * @param value The new charge reference string.
     */
    void SetChargeReference(std::string &value);

    /**
     * @brief Gets the collection configuration.
     * @return The DLMS_CREDIT_COLLECTION_CONFIGURATION enumeration.
     */
    DLMS_CREDIT_COLLECTION_CONFIGURATION GetCollectionConfiguration();

    /**
     * @brief Sets the collection configuration.
     * @param value The DLMS_CREDIT_COLLECTION_CONFIGURATION enumeration.
     */
    void SetCollectionConfiguration(DLMS_CREDIT_COLLECTION_CONFIGURATION value);

    /**
     * @brief Converts the configuration to a string representation.
     * @return A string describing the credit/charge configuration.
     */
    std::string ToString();
};
#endif  //GXCREDIT_CHARGE_CONFIGURATION_H
