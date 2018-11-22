// MyATLCOM.cpp: WinMain 的實作


#include "stdafx.h"
#include "resource.h"
#include "MyATLCOM_i.h"


using namespace ATL;


class CMyATLCOMModule : public ATL::CAtlExeModuleT< CMyATLCOMModule >
{
public :
	DECLARE_LIBID(LIBID_MyATLCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYATLCOM, "{e98a0478-bdf7-45cb-9f87-0dee4867809b}")
};

CMyATLCOMModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

