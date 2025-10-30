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
// and/or modify it under the terms of the GNU General License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXADJACENTCELL_H
#define GXADJACENTCELL_H

/**
 * Represents a GSM adjacent cell, providing information about neighboring cells.
*/
class GXAdjacentCell {
private:
    /**
     * Four byte cell ID.
     */
    unsigned long m_CellId = 0;

    /**
     * Signal quality.
     */
    unsigned char m_SignalQuality = 0;

public:
    /**
     * Constructor.
     */
    GXAdjacentCell();

    /**
     * Constructor.
     *
     * @param cellId Four byte cell ID.
     * @param signalQuality Signal quality.
     */
    GXAdjacentCell(unsigned long cellId, unsigned char signalQuality);

    /**
     * @return Four byte cell ID.
     */
    unsigned long GetCellId() const;

    /**
     * @param value
     *            Four byte cell ID.
     */
    void SetCellId(unsigned long value);

    /**
     * @return Signal quality.
     */
    unsigned char GetSignalQuality() const;

    /**
     * @param value
     *            Signal quality.
     */
    void SetSignalQuality(unsigned char value);
};
#endif  //GXADJACENTCELL_H