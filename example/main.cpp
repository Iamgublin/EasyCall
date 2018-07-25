// EasyParentCall.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
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
    a.EasyCall(L"class B", 1, NULL);             //A类调用B类的DoSomething方法
    b.EasyCall(L"class A", 1, NULL);
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
