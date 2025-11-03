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

#ifndef GXACCOUNT_H
#define GXACCOUNT_H

#include "GXIgnore.h"
#ifndef DLMS_IGNORE_ACCOUNT
#include "GXDLMSObject.h"
#include "GXCreditChargeConfiguration.h"
#include "GXTokenGatewayConfiguration.h"
#include "GXCurrency.h"

/**
 * @brief Represents a DLMS/COSEM Account object (class ID 19).
 *
 * This class models a prepayment account, managing credit, charges, and status
 * for services like electricity or gas.
 */
class CGXDLMSAccount: public CGXDLMSObject {
    /** @brief The payment mode (e.g., credit, prepayment). */
    DLMS_ACCOUNT_PAYMENT_MODE m_PaymentMode;
    /** @brief The current status of the account. */
    DLMS_ACCOUNT_STATUS m_AccountStatus;
    /** @brief An index to the credit object currently in use. */
    unsigned char m_CurrentCreditInUse;
    /** @brief The status of the credit currently in use. */
    DLMS_ACCOUNT_CREDIT_STATUS m_CurrentCreditStatus;
    /** @brief The sum of all positive current credit amounts. */
    int m_AvailableCredit;
    /** @brief The amount to be cleared from the account. */
    int m_AmountToClear;
    /** @brief A threshold related to the amount to clear. */
    int m_ClearanceThreshold;
    /** @brief The total aggregated debt on the account. */
    int m_AggregatedDebt;
    /** @brief References to credit objects associated with this account. */
    std::vector<std::string> m_CreditReferences;
    /** @brief References to charge objects associated with this account. */
    std::vector<std::string> m_ChargeReferences;
    /** @brief Configuration for credit and charge processing. */
    std::vector<CGXCreditChargeConfiguration> m_CreditChargeConfigurations;
    /** @brief Configuration for token gateway operations. */
    std::vector<CGXTokenGatewayConfiguration> m_TokenGatewayConfigurations;
    /** @brief The date and time when the account was activated. */
    CGXDateTime m_AccountActivationTime;
    /** @brief The date and time when the account was closed. */
    CGXDateTime m_AccountClosureTime;
    /** @brief The currency used for the account. */
    CGXCurrency m_Currency;
    /** @brief A threshold for triggering a low credit warning. */
    int m_LowCreditThreshold;
    /** @brief A threshold related to when the next credit becomes available. */
    int m_NextCreditAvailableThreshold;
    /** @brief The maximum emergency credit that can be provisioned. */
    unsigned short m_MaxProvision;
    /** @brief The time period for which the max provision is available. */
    int m_MaxProvisionPeriod;

    int Invoke(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

public:
    /** @brief Default constructor. */
    CGXDLMSAccount();
    /** @brief Short Name (SN) constructor. @param ln Logical Name. @param sn Short Name. */
    CGXDLMSAccount(std::string ln, unsigned short sn);
    /** @brief Logical Name (LN) constructor. @param ln Logical Name. */
    CGXDLMSAccount(std::string ln);

    /** @brief Gets the payment mode. @return The payment mode. */
    DLMS_ACCOUNT_PAYMENT_MODE GetPaymentMode() {
        return m_PaymentMode;
    }

    /** @brief Sets the payment mode. @param value The payment mode. */
    void SetPaymentMode(DLMS_ACCOUNT_PAYMENT_MODE value) {
        m_PaymentMode = value;
    }

    /** @brief Gets the account status. @return The account status. */
    DLMS_ACCOUNT_STATUS GetAccountStatus() {
        return m_AccountStatus;
    }

    /** @brief Sets the account status. @param value The account status. */
    void SetAccountStatus(DLMS_ACCOUNT_STATUS value) {
        m_AccountStatus = value;
    }

    /** @brief Gets the index of the credit currently in use. @return The credit index. */
    unsigned char GetCurrentCreditInUse() {
        return m_CurrentCreditInUse;
    }

    /** @brief Sets the index of the credit to be used. @param value The credit index. */
    void SetCurrentCreditInUse(unsigned char value) {
        m_CurrentCreditInUse = value;
    }

    /** @brief Gets the status of the current credit. @return The credit status. */
    DLMS_ACCOUNT_CREDIT_STATUS GetCurrentCreditStatus() {
        return m_CurrentCreditStatus;
    }

    /** @brief Sets the status of the current credit. @param value The credit status. */
    void SetCurrentCreditStatus(DLMS_ACCOUNT_CREDIT_STATUS value) {
        m_CurrentCreditStatus = value;
    }

    /** @brief Gets the total available credit. @return The available credit amount. */
    int GetAvailableCredit() {
        return m_AvailableCredit;
    }

    /** @brief Sets the total available credit. @param value The available credit amount. */
    void SetAvailableCredit(int value) {
        m_AvailableCredit = value;
    }

    /** @brief Gets the amount to be cleared. @return The amount to clear. */
    int GetAmountToClear() {
        return m_AmountToClear;
    }

    /** @brief Sets the amount to be cleared. @param value The amount to clear. */
    void SetAmountToClear(int value) {
        m_AmountToClear = value;
    }

    /** @brief Gets the clearance threshold. @return The clearance threshold. */
    int GetClearanceThreshold() {
        return m_ClearanceThreshold;
    }

    /** @brief Sets the clearance threshold. @param value The clearance threshold. */
    void SetClearanceThreshold(int value) {
        m_ClearanceThreshold = value;
    }

    /** @brief Gets the aggregated debt. @return The aggregated debt amount. */
    int GetAggregatedDebt() {
        return m_AggregatedDebt;
    }

    /** @brief Sets the aggregated debt. @param value The aggregated debt amount. */
    void SetAggregatedDebt(int value) {
        m_AggregatedDebt = value;
    }

    /** @brief Gets the list of credit references. @return A reference to the vector of credit references. */
    std::vector<std::string> &GetCreditReferences() {
        return m_CreditReferences;
    }

    /** @brief Sets the list of credit references. @param value A vector of credit references. */
    void SetCreditReferences(std::vector<std::string> &value) {
        m_CreditReferences = value;
    }

    /** @brief Gets the list of charge references. @return A reference to the vector of charge references. */
    std::vector<std::string> &GetChargeReferences() {
        return m_ChargeReferences;
    }

    /** @brief Sets the list of charge references. @param value A vector of charge references. */
    void SetChargeReferences(std::vector<std::string> &value) {
        m_ChargeReferences = value;
    }

    /** @brief Gets the credit/charge configurations. @return A reference to the vector of configurations. */
    std::vector<CGXCreditChargeConfiguration> &GetCreditChargeConfigurations() {
        return m_CreditChargeConfigurations;
    }

    /** @brief Sets the credit/charge configurations. @param value A vector of configurations. */
    void SetCreditChargeConfigurations(std::vector<CGXCreditChargeConfiguration> &value) {
        m_CreditChargeConfigurations = value;
    }

    /** @brief Gets the token gateway configurations. @return A reference to the vector of configurations. */
    std::vector<CGXTokenGatewayConfiguration> &GetTokenGatewayConfigurations() {
        return m_TokenGatewayConfigurations;
    }

    /** @brief Sets the token gateway configurations. @param value A vector of configurations. */
    void SetTokenGatewayConfigurations(std::vector<CGXTokenGatewayConfiguration> &value) {
        m_TokenGatewayConfigurations = value;
    }

    /** @brief Gets the account activation time. @return A reference to the activation time object. */
    CGXDateTime &GetAccountActivationTime() {
        return m_AccountActivationTime;
    }

    /** @brief Sets the account activation time. @param value The activation time. */
    void SetAccountActivationTime(CGXDateTime &value) {
        m_AccountActivationTime = value;
    }

    /** @brief Gets the account closure time. @return A reference to the closure time object. */
    CGXDateTime &GetAccountClosureTime() {
        return m_AccountClosureTime;
    }

    /** @brief Sets the account closure time. @param value The closure time. */
    void SetAccountClosureTime(CGXDateTime &value) {
        m_AccountClosureTime = value;
    }

    /** @brief Gets the currency for the account. @return A reference to the currency object. */
    CGXCurrency &GetCurrency() {
        return m_Currency;
    }

    /** @brief Gets the low credit threshold. @return The threshold value. */
    int GetLowCreditThreshold() {
        return m_LowCreditThreshold;
    }

    /** @brief Sets the low credit threshold. @param value The threshold value. */
    void SetLowCreditThreshold(int value) {
        m_LowCreditThreshold = value;
    }

    /** @brief Gets the next credit available threshold. @return The threshold value. */
    int GetNextCreditAvailableThreshold() {
        return m_NextCreditAvailableThreshold;
    }

    /** @brief Sets the next credit available threshold. @param value The threshold value. */
    void SetNextCreditAvailableThreshold(int value) {
        m_NextCreditAvailableThreshold = value;
    }

    /** @brief Gets the maximum provision for emergency credit. @return The max provision amount. */
    int GetMaxProvision() {
        return m_MaxProvision;
    }

    /** @brief Sets the maximum provision for emergency credit. @param value The max provision amount. */
    void SetMaxProvision(int value) {
        m_MaxProvision = value;
    }

    /** @brief Gets the maximum provision period. @return The max provision period. */
    int GetMaxProvisionPeriod() {
        return m_MaxProvisionPeriod;
    }

    /** @brief Sets the maximum provision period. @param value The max provision period. */
    void SetMaxProvisionPeriod(int value) {
        m_MaxProvisionPeriod = value;
    }

    // Returns amount of attributes.
    int GetAttributeCount();
    // Returns amount of methods.
    int GetMethodCount();
    //Get attribute values of object.
    void GetValues(std::vector<std::string> &values);
    // Returns collection of attributes to read.
    void GetAttributeIndexToRead(bool all, std::vector<int> &attributes);
    // Returns data type of given attribute.
    int GetDataType(int index, DLMS_DATA_TYPE &type);
    // Returns value of given attribute.
    int GetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);
    // Set value of given attribute.
    int SetValue(CGXDLMSSettings &settings, CGXDLMSValueEventArg &e);

    /**
     * @brief Invokes the 'activate' method on the account object.
     * @param client The client instance to use for sending the request.
     * @param[out] reply A vector where the response PDU(s) will be stored.
     * @return 0 on success, or an error code.
     */
    int Activate(CGXDLMSClient *client, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Invokes the 'close' method on the account object.
     * @param client The client instance.
     * @param[out] reply A vector for the response PDU(s).
     * @return 0 on success, or an error code.
     */
    int Close(CGXDLMSClient *client, std::vector<CGXByteBuffer> &reply);

    /**
     * @brief Invokes the 'reset' method on the account object.
     * @param client The client instance.
     * @param[out] reply A vector for the response PDU(s).
     * @return 0 on success, or an error code.
     */
    int Reset(CGXDLMSClient *client, std::vector<CGXByteBuffer> &reply);
};
#endif  //DLMS_IGNORE_ACCOUNT
#endif  //GXACCOUNT_H
