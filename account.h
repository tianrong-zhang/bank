#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H
#include <iostream>
#include <string>
#include <list>

class account {
public:
    account();                                                                  //初始化账户信息
    void createAccount();                                                       //创建账户
    void showAccount();                                                         //打印账户信息
    static std::string getTime() ;                                              //获取当前时间
    std::string getAccountNumber() const;                                       //获取银行卡号
    std::string getUserPassword() const;                                        //获取用户密码
    bool getFreezeMark() const;                                                 //获取冻结标志
    std::string getUserName() const;                                            //获取用户姓名
    void setFreezeMark(const bool &flag);                                       //设置冻结标志
    std::string generateRecord(const int &flag, const std::string &name) const; //更新记录
    void saveMoney();                                                           //存款
    void takeMoney();                                                           //取款
    void transferFrom(const int &money, const std::string &srcName);            //收到转账
    int transferTo(const std::string &destName);                                //发起转账
    void changeUserPassword();                                                  //修改用户密码

private:
    std::string userName;                                                       //用户姓名
    std::string accountNumber;                                                  //银行卡号
    std::string userPassword;                                                   //用户密码
    int deposit;                                                                //存入
    int expenditure;                                                            //支出
    int balance;                                                                //余额
    std::string updateTime;                                                     //更新时间
    std::string remark;                                                         //备注
    std::list<std::string> bill;                                                //账单
    int billNumber;                                                             //账单数目
    bool freezeMark;                                                            //冻结标志
};


#endif //BANK_ACCOUNT_H
