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

    m_strCallName = strCallName;

    return TRUE;
}

BOOL IEasyCall::UnRegisterCallName()
{
    if (m_mpAllCall.find(m_strCallName) == m_mpAllCall.end())
    {
        return FALSE;
    }

    m_mpAllCall.erase(m_strCallName);

    return TRUE;
}

BOOL IEasyCall::EasyCall(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall = FALSE)
{
    if (!bFastCall)
    {
        if (m_mpAllCall.find(strCallName) == m_mpAllCall.end())
        {
            return FALSE;
        }
    }

    return m_mpAllCall[strCallName]->OnCall(CallType, pParam);
}

BOOL IEasyCall::EasyCallStatic(std::wstring strCallName, int CallType, PVOID pParam, BOOL bFastCall = FALSE)
{
    if (!bFastCall)
    {
        if (m_mpAllCall.find(strCallName) == m_mpAllCall.end())
        {
            return FALSE;
        }
    }

    return m_mpAllCall[strCallName]->OnCall(CallType, pParam);
}

std::map<std::wstring, IEasyCall*> IEasyCall::m_mpAllCall = {};
