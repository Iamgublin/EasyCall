EasyCall
========================
主要内容
----------------------------------------
解决各个类之间相互调用的问题，特别是类中声明的成员类，成员类想调用自己类中的方法会十分困难，在嵌套数很多的时候，各个
类之间的调用将会变得尤其的复杂，这个库便是为了解决这个问题而写的 。


使用方法:
1.所有类都继承这个基类
2.在构造函数中调用注册函数注册自己
3.重载OnCall函数
4.调用EasyCall函数，使用方法和SendMessage类似，传入注册时指定的名字即可轻松完成对其他类的调用