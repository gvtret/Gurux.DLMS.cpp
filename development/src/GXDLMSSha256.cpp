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

#include <openssl/sha.h>
#include "../include/GXDLMSSha256.h"

int CGXDLMSSha256::Hash(
    CGXByteBuffer& data,
    CGXByteBuffer& digest)
{
    digest.Capacity(SHA256_DIGEST_LENGTH);
    SHA256((unsigned char*)data.GetData(), data.GetSize(), (unsigned char*)digest.GetData());
    digest.SetSize(SHA256_DIGEST_LENGTH);
    return 0;
}