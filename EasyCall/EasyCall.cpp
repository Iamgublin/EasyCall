#include "EasyCall.h"

IEasyCall::IEasyCall()
{

}

IEasyCall::~IEasyCall()
{
}

BOOL IEasyCall::RegisterCallName(std::wstring strCallName)
{
    if (m_mpAllCall.find(strCallName) != m_mpAllCall.end())
    {
        return FALSE;
    }

    m_mpAllCall[strCallName] = this;

    return TRUE;
}

BOOL IEasyCall::EasyCall(std::wstring strCallName,int CallType,PVOID pParam)
{
    if (m_mpAllCall.find(strCallName) == m_mpAllCall.end())
    {
        return FALSE;
    }

    return m_mpAllCall[strCallName]->OnCall(CallType, pParam);
}

std::map<std::wstring, IEasyCall*> IEasyCall::m_mpAllCall = {};
