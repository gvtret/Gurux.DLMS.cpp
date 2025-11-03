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

#ifndef GXADJACENTCELL_H
#define GXADJACENTCELL_H

#include <string>

/**
 * @brief Represents information about a neighboring (adjacent) GSM cell.
 *
 * This class is used to store data for a single adjacent cell, which typically
 * includes its unique identifier and the measured signal quality. This information
 * is often used in cellular network diagnostics and monitoring.
 */
class GXAdjacentCell {
private:
    /**
    * @brief The unique four-byte identifier for the cell (Cell ID).
    */
    unsigned long m_CellId;

    /**
    * @brief The measured signal quality of the cell.
    *
    * This value typically represents the received signal strength or a similar
    * quality metric. The exact meaning can depend on the underlying cellular module.
    */
    unsigned char m_SignalQuality;

public:
    /**
    * @brief Retrieves the cell ID.
    * @return The four-byte cell ID.
    */
    unsigned long GetCellId();

    /**
    * @brief Sets the cell ID.
    * @param value The four-byte cell ID.
    */
    void SetCellId(unsigned long value);

    /**
    * @brief Retrieves the signal quality.
    * @return The signal quality value.
    */
    unsigned char GetSignalQuality();

    /**
    * @brief Sets the signal quality.
    * @param value The signal quality value.
    */
    void SetSignalQuality(unsigned char value);
};
#endif  //GXADJACENTCELL_H