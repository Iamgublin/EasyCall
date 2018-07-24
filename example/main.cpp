// EasyParentCall.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "..\EasyCall\EasyCall.h"

class A :public IEasyCall
{
public:
    A() { RegisterCallName(L"class A"); }
    ~A() = default;

    virtual BOOL OnCall(int iCallType, PVOID pParam);
};

class B :public IEasyCall
{
public:
    B() { RegisterCallName(L"class B"); }
    ~B() = default;

    virtual BOOL OnCall(int iCallType, PVOID pParam);
};

int main()
{
    A a;
    B b;
    a.EasyCall(L"class B", 1, NULL);
    return 0;
}

BOOL A::OnCall(int iCallType, PVOID pParam)
{
    return 0;
}

BOOL B::OnCall(int iCallType, PVOID pParam)
{
    printf("OK\n");
    return 0;
}
