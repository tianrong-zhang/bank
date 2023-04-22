#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H
#include <iostream>
#include <string>
#include <vector>
#include "account.h"

class system {
public:
    system();                                               //初始化系统并设置管理员密码为”123456“
    void startMenu();                                       //显示系统界面
    void openAccount();                                     //开户
    void login();                                           //用户登陆
    void cancelAccount();                                   //销户
    void unfreeze();                                        //解冻
    void userFunction(account &curAccount);                 //用户功能
    void transfer(account &srcAccount);                     //转账
    static bool judgeOverflow(const std::string& num);      //判断输入的数字是否溢出
private:
    std::string adminPassword;                              //管理员密码
    std::vector<account> accounts;                          //账户集合
    int accountNum;                                         //账户数量
};


#endif //BANK_SYSTEM_H
