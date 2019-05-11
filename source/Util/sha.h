/*
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
#pragma once

#include <Core/greenTea2D.h>
#include <Util/guid.h>


//! @name SHA256
//@{
gt2GUID Sha256_GUID(std::string str);
gt2GUID Sha256_GUID(std::wstring str);
void Sha256(std::string str, uint8_t aOut[32]);
void Sha256(std::wstring str, uint8_t aOut[32]);
std::string Sha256_Str(std::string str);
std::wstring Sha256_WStr(std::wstring str);
//@}

//! @name SHA512
//@{
std::string Sha512_Str(std::string str);
std::wstring Sha512_WStr(std::wstring str);
void Sha512(std::string str, uint8_t aOut[64]);
void Sha512(std::wstring str, uint8_t aOut[64]);
//@}



#ifdef _UNICODE
#  define Sha256_TStr(str) Sha256_WStr(str)
#  define Sha512_TStr(str) Sha512_WStr(str)
#else
#  define Sha256_TStr(str) Sha256_Str(str)
#  define Sha512_TStr(str) Sha512_Str(str)
#endif
