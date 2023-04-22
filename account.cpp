#include "account.h"
#include <ctime>

account::account() {
    deposit = 0;
    expenditure = 0;
    balance = 0;
    billNumber = 0;
    freezeMark = false;
}

//输入用户的姓名和密码来生成递增的8位银行卡号
void account::createAccount() {
    std::cout << "请输入姓名:" << std::endl;
    std::cin >> userName;
    std::cout << "请输入密码:" << std::endl;
    std::cin >> userPassword;
    std::cout << "您的银行卡号是:" << std::endl;
    static int cardNumber = 1e7;
    accountNumber = std::to_string(cardNumber++);
    std::cout << accountNumber << std::endl;
    std::cout << "--------------------" << std::endl;
}

//打印用户姓名、银行卡号和账户余额，并生成账单明细
void account::showAccount() {
    std::cout << "姓名: " << userName << std::endl;
    std::cout << "银行卡号:  " << accountNumber << std::endl;
    std::cout << "余额: " << balance << "元" << std::endl;
    std::cout << std::endl;

    //显示该用户的账单明细
    std::cout << "一共存在" << billNumber << "条账单，具体如下:" << std::endl;
    std::list<std::string>::iterator iter;
    for(iter = bill.begin(); iter != bill.end(); ++iter) {
        std::cout << *iter << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

//获取银行卡号
std::string account::getAccountNumber() const {
    return accountNumber;
}

//获取用户密码
std::string account::getUserPassword() const {
    return userPassword;
}

//获取冻结标志
bool account::getFreezeMark() const {
    return freezeMark;
}

//获取用户姓名
std::string account::getUserName() const {
    return userName;
}

//获取当前时间
std::string account::getTime() {
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}

//设置冻结标志
void account::setFreezeMark(const bool &flag) {
    freezeMark = flag;
}

//flag为1表示存款，2表示取款，3表示收到转账，4表示发起转账
std::string account::generateRecord(const int &flag, const std::string &name) const {
    std::string record;
    std::string string1 = "您于";
    std::string string2 = getTime();
    std::string string3;
    std::string string4;
    switch (flag) {
        case 1:
            string3 = "向账户中存款";
            string4 = std::to_string(deposit);
            break;
        case 2:
            string3 = "从账户中支出";
            string4 = std::to_string(expenditure);
            break;
        case 3:
            string3 = "收到来自";
            string3.append(name);
            string3.append("的转账");
            string4 = std::to_string(deposit);
            break;
        case 4:
            string3 = "发起对";
            string3.append(name);
            string3.append("的转账");
            string4 = std::to_string(expenditure);
            break;
        default:
            break;
    }
    std::string string5 = "元，当前余额为";
    std::string string6 = std::to_string(balance);
    std::string string7 = "元";
    record = string1 + string2 + string3 + string4 + string5 + string6 + string7;
    return record;
}

//存款
void account::saveMoney() {
    std::cout << "请输入存款金额:" << std::endl;
    std::cin >> deposit;
    balance += deposit;
    std::cout << "存款成功！当前余额为" << balance << "元" << std::endl;
    std::cout << "--------------------" << std::endl;

    //生成一条操作记录
    std::string record = generateRecord(1, "");
    bill.push_back(record);
    ++billNumber;
}

//取款
void account::takeMoney() {
    std::cout << "请输入取款金额:" << std::endl;
    std::cin >> expenditure;
    if(balance < expenditure) {
        std::cout << "取款失败，余额不足!" << std::endl;
        std::cout << "--------------------" << std::endl;
        return;
    }
    balance -= expenditure;
    std::cout << "取款成功！当前余额为" << balance << "元" << std::endl;
    std::cout << "--------------------" << std::endl;

    //生成一条操作记录
    std::string record = generateRecord(2, "");
    bill.push_back(record);
    ++billNumber;
}

//收到转账
void account::transferFrom(const int &money, const std::string &srcName) {
    deposit = money;
    balance += deposit;

    //生成一条操作记录
    std::string record = generateRecord(3, srcName);
    bill.push_back(record);
    ++billNumber;
}

//发起转账
int account::transferTo(const std::string &destName) {
    std::cout << "请输入转账金额:" << std::endl;
    std::cin >> expenditure;
    if(balance < expenditure) {
        std::cout << "转账失败，余额不足!" << std::endl;
        std::cout << "--------------------" << std::endl;
        return -1;
    }
    balance -= expenditure;
    std::cout << "转账成功！当前余额为" << balance << "元" << std::endl;
    std::cout << "--------------------" << std::endl;

    //生成一条操作记录
    std::string record = generateRecord(4, destName);
    bill.push_back(record);
    ++billNumber;
    return expenditure;
}

//修改用户密码
void account::changeUserPassword() {
    std::string curPassword;
    std::string newPassword1;
    std::string newPassword2;
    std::cout << "请输入当前密码:" << std::endl;
    std::cin >> curPassword;
    if(userPassword == curPassword) {
        std::cout << "请输入新的密码:" << std::endl;
        std::cin >> newPassword1;
        std::cout << "请再次输入新的密码:" << std::endl;
        std::cin >> newPassword2;
        if(newPassword1 == newPassword2) {
            userPassword = newPassword1;
            std::cout << "密码修改成功!" << std::endl;
            std::cout << "--------------------" << std::endl;
        } else {
            std::cout << "两次密码输入不一致!" << std::endl;
            std::cout << "--------------------" << std::endl;
        }
    } else {
        std::cout << "密码错误!" << std::endl;
        std::cout << "--------------------" << std::endl;
    }
}