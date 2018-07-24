// EasyParentCall.cpp: �������̨Ӧ�ó������ڵ㡣
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
private:
    void DoSomething() { printf("A Call B\n"); }
};

int main()
{
    A a;
    B b;
    a.EasyCall(L"class B", 1, NULL);             //A�����B���DoSomething����
    return 0;
}

BOOL A::OnCall(int iCallType, PVOID pParam)
{
    return 0;
}

BOOL B::OnCall(int iCallType, PVOID pParam)
{
    if (iCallType == 1)
    {
        DoSomething();
        printf("OK\n");
    }
    return 0;
}
