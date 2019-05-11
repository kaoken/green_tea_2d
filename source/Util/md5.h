#pragma once
/*
* @file  md5.h
* SHA-256 hash in C
*
* Copyright (c) 2014 Project Nayuki
* http://www.nayuki.io/page/fast-sha2-hashes-in-x86-assembly
*
* (MIT License)
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
* - The above copyright notice and this permission notice shall be included in
*   all copies or substantial portions of the Software.
* - The Software is provided "as is", without warranty of any kind, express or
*   implied, including but not limited to the warranties of merchantability,
*   fitness for a particular purpose and noninfringement. In no event shall the
*   authors or copyright holders be liable for any claim, damages or other
*   liability, whether in an action of contract, tort or otherwise, arising from,
*   out of or in connection with the Software or the use or other dealings in the
*   Software.
*/

#include <Core/greenTea2D.h>
#include "guid.h"


//! @name SHA256
//@{
gt2GUID MD5_GUID_A(const std::string &str);
gt2GUID MD5_GUID_W(const std::wstring &str);
void MD5(const std::string str, uint8_t aOut[16]);
void MD5(const std::wstring str, uint8_t aOut[16]);
std::string MD5_Str(const std::string &str);
std::wstring MD5_WStr(const std::wstring &str);
//@}

#ifdef _UNICODE
#  define MD5_TStr(str) MD5_WStr(str)
#  define MD5_GUID(str) MD5_GUID_W(str)
#else
#  define MD5_TStr(str) MD5_Str(str)
#  define MD5_GUID(str) MD5_GUID_A(str)
#endif