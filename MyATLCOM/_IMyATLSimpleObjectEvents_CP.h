#pragma once

using namespace ATL;

template <class T>
class CProxy_IMyATLSimpleObjectEvents : public IConnectionPointImpl<T, &__uuidof( _IMyATLSimpleObjectEvents ), CComDynamicUnkArray>
{
	// 警告:  這個類別可能是由精靈重新產生
public:
	HRESULT Fire_OnNumberChanged(INT nNum)
	{
		HRESULT hr = S_OK;
		T * pThis = static_cast<T *>(this);
		int cConnections = m_vec.GetSize();

		for (int iConnection = 0; iConnection < cConnections; iConnection++)
		{
			pThis->Lock();
			CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
			pThis->Unlock();

			IDispatch * pConnection = static_cast<IDispatch *>(punkConnection.p);

			if (pConnection)
			{
				CComVariant avarParams[1];
				avarParams[0] = nNum;
				avarParams[0].vt = VT_INT;
				CComVariant varResult;

				DISPPARAMS params = { avarParams, NULL, 1, 0 };
				hr = pConnection->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, &varResult, NULL, NULL);
			}
		}
		return hr;
	}
};
