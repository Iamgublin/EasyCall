#pragma once

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
    std::wstring m_strCallName;
    static std::map<std::wstring, IEasyCall*> m_mpAllCall;
};