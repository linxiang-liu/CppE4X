#pragma once

#include <malloc.h>
#include <windows.h>

#define USE_LIN_CHAR_SET_VARIANT char* _lin_dst = 0; wchar_t* _lin_wdst = 0; int _lin_dst_size = 0;

#define LIN_CHAR_SET_NO_WARNING  _lin_dst; _lin_wdst;_lin_dst_size;

#define USE_LIN_CHAR_SET USE_LIN_CHAR_SET_VARIANT;LIN_CHAR_SET_NO_WARNING


#ifdef LIN_CHAR_SET_USE_STL

#include <string>
std::string _w2a( const std::wstring& pwcsSrc, int codepage)
{
	USE_LIN_CHAR_SET;
	_lin_dst_size = pwcsSrc.size()*3;
	_lin_dst = new (std::nothrow) char[ _lin_dst_size];
	if( _lin_dst == 0) return std::string();

	_lin_dst_size = WideCharToMultiByte( codepage, 0, pwcsSrc.c_str(), pwcsSrc.length(), _lin_dst, _lin_dst_size, 0, 0);

	if( _lin_dst_size == 0) 
	{
		delete[] _lin_dst;
		return std::string();
	}

	_lin_dst[_lin_dst_size] = 0;
	std::string result = _lin_dst;
	delete[] _lin_dst;
	return result;
}

std::wstring _a2w( const std::string& pszSrc, int codepage)
{
	USE_LIN_CHAR_SET;
	_lin_dst_size = pszSrc.size()*2;
	_lin_wdst = new (std::nothrow) wchar_t [ _lin_dst_size];
	if( _lin_wdst == 0) return std::wstring();

	_lin_dst_size = MultiByteToWideChar( codepage, 0, pszSrc.c_str(), pszSrc.length(), _lin_wdst,_lin_dst_size);

	if( _lin_dst_size == 0)
	{
		delete[] _lin_wdst;
		return std::wstring();
	}

	_lin_wdst[_lin_dst_size] = 0;
	std::wstring result = _lin_wdst;
	delete[] _lin_wdst;
	return result;}

#else
#define _w2a( pwcsSrc, codepage) ( pwcsSrc == 0? 0:( \
	(_lin_dst = (char*)_alloca( ((_lin_dst_size = (int)wcslen( pwcsSrc))+ 1)*3))== 0? 0 : (\
	(_lin_dst_size = WideCharToMultiByte( codepage, 0, pwcsSrc, _lin_dst_size, _lin_dst, _lin_dst_size*3, 0, 0))==0? \
	((_lin_dst[0]=0)==0 ? _lin_dst:0): (\
	(_lin_dst[_lin_dst_size] = 0) == 0? _lin_dst : 0))))

#define _a2w( pszSrc, codepage) (pszSrc == 0? 0 : (\
	(_lin_wdst = (wchar_t*)_alloca( ((_lin_dst_size = (int)strlen( pszSrc)) + 1)*2)) == 0? 0 : (\
	(_lin_dst_size = MultiByteToWideChar( codepage, 0, pszSrc, _lin_dst_size, _lin_wdst,_lin_dst_size + sizeof(wchar_t))) == 0? \
	((_lin_wdst[0]=0)==0? _lin_wdst:0) : (\
	(_lin_wdst[ _lin_dst_size] = 0) == 0? _lin_wdst: 0))))

#endif


#define _utf82w( pszSrc) _a2w( pszSrc, CP_UTF8)
#define _w2utf8( pszSrc) _w2a( pszSrc, CP_UTF8)

#define _utf72w( pszSrc) _a2w( pszSrc, CP_UTF7)
#define _w2utf7( pszSrc) _w2a( pszSrc, CP_UTF7)


// µ¼³öµÄºê
#define a2w(pszSrc) _a2w(pszSrc, CP_ACP)
#define w2a(tcsSrc) _w2a(tcsSrc, CP_ACP)

#ifdef UNICODE
#define a2t(pszSrc) a2w(pszSrc)
#define t2a(tcsSrc) w2a(tcsSrc)
#define w2t(wcsSrc) wcsSrc;
#define t2w(tcsSrc) tcsSrc;
#else
#define a2t(pszSrc) pszSrc
#define t2a(tcsSrc) tcsSrc
#define w2t(wcsSrc) wta(wcsSrc)
#define t2w(tcsSrc) a2w(tcsSrc)
#endif

#define w2utf8(wcsSrc) _w2utf8(wcsSrc)
#define utf82w(pszSrc) _utf82w(pszSrc)
#define w2utf7(wcsSrc) _w2utf7(wcsSrc)
#define utf72w(pszSrc) _utf72w(pszSrc)

#define a2utf8(pszSrc) w2utf8(a2w(pszSrc))
#define a2utf7(pszSrc) w2utf7(a2w(pszSrc))
#define utf82a(pszSrc) w2a(utf82w(pszSrc))
#define utf72a(pszSrc) w2a(utf72w(pszSrc))
#define t2utf8(tcsSrc) w2utf8(tcsSrc)
#define t2utf7(tcsSrc) w2utf7(tcsSrc)
#define utf82t(pszSrc) w2t(utf82w(pszSrc))
#define utf72t(pszSrc) w2t(utf72w(pszSrc))
