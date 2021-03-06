#include "EasyCall.h"

typedef struct _ASYNCALLPARAM
{
    std::wstring strCallName;
    int CallType;
    PVOID pParam;
    BOOL bFastCall;
}ASYNCALLPARAM, *PASYNCALLPARAM;

IEasyCall::IEasyCall()
{

}

IEasyCall::~IEasyCall()
{

}

BOOL IEasyCall::RegisterCallName(std::wstring strCallName)
{

#ifdef  USE_MUTEX_LOCK
    std::lock_guard<std::mutex> lock(m_mtx);
#endif

    if (m_mpAllCall.find(strCallName) != m_mpAllCall.end())
    {
        return FALSE;
    }

    m_mpAllCall[strCallName] = this;

    m_strCallName = strCallName;

    return TRUE;
}

BOOL IEasyCall::UnRegisterCallName()
{
#ifdef  USE_MUTEX_LOCK
    std::lock_guard<std::mutex> lock(m_mtx);
#endif

    if (m_mpAllCall.find(m_strCallName) == m_mpAllCall.end())
    {
        return FALSE;
    }

    m_mpAllCall.erase(m_strCallName);

    return TRUE;
}

BOOL IEasyCall::EasyCall(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall)
{
#ifdef  USE_MUTEX_LOCK
    std::lock_guard<std::mutex> lock(m_mtx);
#endif

    if (!bFastCall)
    {
        if (m_mpAllCall.find(strCallName) == m_mpAllCall.end())
        {
            return FALSE;
        }
    }

    return m_mpAllCall[strCallName]->OnCall(CallType, pParam);
}

BOOL IEasyCall::EasyCallStatic(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall)
{
#ifdef  USE_MUTEX_LOCK
    std::lock_guard<std::mutex> lock(m_stmtx);
#endif

    if (!bFastCall)
    {
        if (m_mpAllCall.find(strCallName) == m_mpAllCall.end())
        {
            return FALSE;
        }
    }

    return m_mpAllCall[strCallName]->OnCall(CallType, pParam);
}

BOOL IEasyCall::EasyCallAsync(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall, HANDLE* hSyncHandle)
{
    PASYNCALLPARAM pCallParam = new(std::nothrow) ASYNCALLPARAM();
    if (pCallParam == NULL)
    {
        return FALSE;
    }

    pCallParam->CallType = CallType;
    pCallParam->pParam = pParam;
    pCallParam->strCallName = strCallName;
    pCallParam->bFastCall = bFastCall;

    HANDLE hThread = CreateThread(NULL, 0, _EasyCallAsyncProxy, pCallParam, 0, NULL);
    if (hThread == NULL)
    {
        delete pCallParam;
        return FALSE;
    }

    if (hSyncHandle != NULL)
    {
        *hSyncHandle = hThread;
    }
    else
    {
        CloseHandle(hThread);
    }
    return TRUE;
}

BOOL IEasyCall::EasyCallStaticAsync(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall, HANDLE* hSyncHandle)
{
    PASYNCALLPARAM pCallParam = new(std::nothrow) ASYNCALLPARAM();
    if (pCallParam == NULL)
    {
        return FALSE;
    }

    pCallParam->CallType = CallType;
    pCallParam->pParam = pParam;
    pCallParam->strCallName = strCallName;
    pCallParam->bFastCall = bFastCall;

    HANDLE hThread = CreateThread(NULL, 0, _EasyCallAsyncProxy, pCallParam, 0, NULL);
    if (hThread == NULL)
    {
        delete pCallParam;
        return FALSE;
    }

    if (hSyncHandle != NULL)
    {
        *hSyncHandle = hThread;
    }
    else
    {
        CloseHandle(hThread);
    }

    return TRUE;
}

DWORD IEasyCall::_EasyCallAsyncProxy(LPVOID lpParam)
{
    if (lpParam == NULL)
        return FALSE;

    PASYNCALLPARAM pCallParam = (PASYNCALLPARAM)lpParam;

#ifdef  USE_MUTEX_LOCK
    std::lock_guard<std::mutex> lock(m_stmtx);
#endif

    if (!pCallParam->bFastCall)
    {
        if (m_mpAllCall.find(pCallParam->strCallName) == m_mpAllCall.end())
        {
            delete lpParam;
            return FALSE;
        }
    }

    BOOL bRet = m_mpAllCall[pCallParam->strCallName]->OnCall(pCallParam->CallType, pCallParam->pParam);
    delete lpParam;

    return bRet;
}

#ifdef  USE_MUTEX_LOCK
std::mutex IEasyCall::m_stmtx;
#endif

std::map<std::wstring, IEasyCall*> IEasyCall::m_mpAllCall = {};
