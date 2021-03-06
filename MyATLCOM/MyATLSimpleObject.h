// MyATLSimpleObject.h: CMyATLSimpleObject 的宣告

#pragma once
#include "resource.h"       // 主要符號



#include "MyATLCOM_i.h"
#include "_IMyATLSimpleObjectEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台上未正確支援單一執行緒 COM 物件，例如 Windows Mobile 平台沒有包含完整的 DCOM 支援。請定義 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 來強制 ATL 支援建立單一執行緒 COM 物件的實作，以及允許使用其單一執行緒 COM 物件實作。您的 rgs 檔中的執行緒模型已設定為 'Free'，因為這是非 DCOM Windows CE 平台中唯一支援的執行緒模型。"
#endif

using namespace ATL;

class CMyClassFactory : public CComClassFactory
{

public:
	STDMETHOD(CreateInstance)(LPUNKNOWN pUnkOuter, REFIID riid, void** ppvObj)
	{
		_ASSERTE(m_pfnCreateInstance != NULL);
		static void* pObj = NULL;
		HRESULT hRes = E_POINTER;


		if (pObj)
		{
			*ppvObj = pObj;
			((LPUNKNOWN)pObj)->AddRef();
			hRes = S_OK;
		}
		else
		{
			hRes = m_pfnCreateInstance(pUnkOuter, riid, &pObj);
			*ppvObj = pObj;
		}

		return hRes;
	}
};


// CMyATLSimpleObject

class ATL_NO_VTABLE CMyATLSimpleObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyATLSimpleObject, &CLSID_MyATLSimpleObject>,
	public IConnectionPointContainerImpl<CMyATLSimpleObject>,
	public CProxy_IMyATLSimpleObjectEvents<CMyATLSimpleObject>,
	public IDispatchImpl<IMyATLSimpleObject, &IID_IMyATLSimpleObject, &LIBID_MyATLCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMyATLSimpleObject()
	{
		m_nNum = 0;
	}

//DECLARE_CLASSFACTORY_EX(CMyClassFactory)

DECLARE_CLASSFACTORY_SINGLETON(CMyATLSimpleObject)

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CMyATLSimpleObject)
	COM_INTERFACE_ENTRY(IMyATLSimpleObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CMyATLSimpleObject)
	CONNECTION_POINT_ENTRY(__uuidof(_IMyATLSimpleObjectEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

private:
	INT m_nNum;

public:
	STDMETHOD(SetNumber)(INT nNum);
	STDMETHOD(GetNumber)(INT* pnNum);


};

OBJECT_ENTRY_AUTO(__uuidof(MyATLSimpleObject), CMyATLSimpleObject)
