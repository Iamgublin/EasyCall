#pragma once

#include <map>
#include <string>
#include <mutex>
#include <Windows.h>

//#define USE_MUTEX_LOCK

class IEasyCall
{
public:
    IEasyCall();
    ~IEasyCall();

    BOOL RegisterCallName(std::wstring strCallName);
    BOOL UnRegisterCallName();

    BOOL EasyCall(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall = FALSE);
    static BOOL EasyCallStatic(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall = FALSE);

    BOOL EasyCallAsync(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall = FALSE, HANDLE* hSyncHandle = NULL);
    static BOOL EasyCallStaticAsync(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall = FALSE, HANDLE* hSyncHandle = NULL);
protected:
    virtual BOOL OnCall(int iCallType, PVOID pParam) { return FALSE; }

private:
    static DWORD __stdcall _EasyCallAsyncProxy(LPVOID lpParam);

private:

#ifdef  USE_MUTEX_LOCK
    std::mutex m_mtx;
    static std::mutex m_stmtx;
#endif //  USE_MUTEX_LOCK

    std::wstring m_strCallName;
    static std::map<std::wstring, IEasyCall*> m_mpAllCall;
};