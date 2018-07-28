#pragma once
#include <map>
#include <string>
#include <Windows.h>

class IEasyCall
{
public:
    IEasyCall();
    ~IEasyCall();

    BOOL RegisterCallName(std::wstring strCallName);
    BOOL UnRegisterCallName();

    BOOL EasyCall(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall = FALSE);
    static BOOL EasyCallStatic(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall = FALSE);

protected:
    virtual BOOL OnCall(int iCallType, PVOID pParam) { return FALSE; }

private:
    std::wstring m_strCallName;
    static std::map<std::wstring, IEasyCall*> m_mpAllCall;
};