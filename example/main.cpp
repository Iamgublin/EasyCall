// EasyParentCall.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <map>
#include "..\EasyCall\EasyCall.h"

class A :public IEasyCall
{
public:
    A() { RegisterCallName(L"class A"); }
    ~A() { UnRegisterCallName(); }
};

class B :public IEasyCall
{
public:
    B() { RegisterCallName(L"class B"); }
    ~B() { UnRegisterCallName(); }

    virtual BOOL OnCall(int iCallType, PVOID pParam);
private:
    void DoSomething() { printf("A Call B\n"); }
};

int main()
{
    A a;
    B b;
    HANDLE hAsyncHandle = NULL;
    a.EasyCall(L"class B", 1, NULL);             //A�����B���DoSomething����
    b.EasyCall(L"class A", 1, NULL);
    if (a.EasyCallAsync(L"class B", 2, NULL, FALSE, &hAsyncHandle))   //A���첽����B���DoSomething����
    {
        WaitForSingleObject(hAsyncHandle, INFINITE);
        CloseHandle(hAsyncHandle);
    }

    //Ҳ����ֱ�����������ָ�����ڷ���(ǰ����B�Ѿ���ʼ����)
    IEasyCall::EasyCallStatic(L"class B", 3, NULL);

    return 0;
}

BOOL B::OnCall(int iCallType, PVOID pParam)
{
    if (iCallType == 1)
    {
        DoSomething();
        printf("OK\n");
        return TRUE;
    }
    else if (iCallType == 2)
    {
        DoSomething();
        printf("AsyncCall OK\n");
        return TRUE;
    }
    else if (iCallType == 3)
    {
        DoSomething();
        printf("Static Call OK\n");
        return TRUE;
    }

    return FALSE;
}
