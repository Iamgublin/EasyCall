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
    BOOL EasyCall(std::wstring strCallName, int CallType, PVOID pParam);

protected:
    virtual BOOL OnCall(int iCallType, PVOID pParam) { return FALSE; }

private:
    static std::map<std::wstring, IEasyCall*> m_mpAllCall;
};