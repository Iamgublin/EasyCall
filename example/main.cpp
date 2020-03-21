// EasyParentCall.cpp: 定义控制台应用程序的入口点。
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
    a.EasyCall(L"class B", 1, NULL);             //A类调用B类的DoSomething方法
    b.EasyCall(L"class A", 1, NULL);
    if (a.EasyCallAsync(L"class B", 2, NULL, FALSE, &hAsyncHandle))   //A类异步调用B类的DoSomething方法
    {
        WaitForSingleObject(hAsyncHandle, INFINITE);
        CloseHandle(hAsyncHandle);
    }

    //也可以直接在类外调用指定类内方法(前提是B已经初始化了)
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
