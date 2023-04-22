#include "system.h"

//设置初始管理员密码
system::system() {
    adminPassword = "123456";
    accountNum = 0;
}

//显示系统界面
void system::startMenu() {
    bool flag = true;
    while(flag) {
        std::cout << "欢迎使用银行管理系统!" << std::endl;
        std::cout << "请选择功能:" << std::endl;
        std::cout << "1. 开户" << std::endl;
        std::cout << "2. 登陆" << std::endl;
        std::cout << "3. 销户" << std::endl;
        std::cout << "4. 解冻" << std::endl;
        std::cout << "5. 退出" << std::endl;
        std::string num;
        std::cin >> num;
        if(!judgeOverflow(num)) {
            std::cout << "您输入的数字有误!" << std::endl;
            continue;
        }
        switch (std::stoi(num)) {
            case 1:
                openAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                cancelAccount();
                break;
            case 4:
                unfreeze();
                break;
            case 5:;
                flag = false;
                break;
            default:
                std::cout << "您输入的数字有误，请重新输入!" << std::endl;
                std::cout << "--------------------" << std::endl;
                break;
        }
    }
}

//开户
void system::openAccount() {
    std::string password;
    std::cout << "请输入管理员密码:" << std::endl;
    std::cin >> password;
    if(password == adminPassword) {
        account newAccount;
        newAccount.createAccount();
        std::cout << "开户成功!" << std::endl;
        ++accountNum;
        std::cout << "您现在是否想要存款:" << std::endl;
        std::cout << "1. 是" << std::endl;
        std::cout << "2. 否" << std::endl;
        std::string num;
        bool flag = true;
        while(flag) {
            std::cin >> num;
            if(!judgeOverflow(num)) {
                std::cout << "您输入的数字有误，请重新输入!" << std::endl;
            } else {
                flag = false;
                if(std::stoi(num) == 1) {
                    newAccount.saveMoney();
                } else if(std::stoi(num) != 2){
                    flag = true;
                    std::cout << "您输入的数字有误，请重新输入!" << std::endl;
                }
            }
        }
        accounts.push_back(newAccount);
        newAccount.showAccount();
    } else {
        std::cout << "管理员密码错误!" << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

//用户登录
void system::login() {
    std::string number;
    std::string password;
    std::cout << "请输入银行卡号:" << std::endl;
    std::cin >> number;
    std::vector<account>::iterator iter;
    for(iter = accounts.begin(); iter != accounts.end(); ++iter) {
        if(iter->getAccountNumber() == number) {
            //在银行数据库中找到了输入的银行卡号
            if(!iter->getFreezeMark()) {
                //如果没有冻结，就让用户输入密码
                for(int i = 2; i >= 0; --i) {
                    std::cout << "请输入密码:" << std::endl;
                    std::cin >> password;
                    if(iter->getUserPassword() == password) {
                        //用户密码匹配成功，以当前用户登陆
                        userFunction(*iter);
                        return;
                    } else {
                        std::cout << "密码错误!您还有" << i << "次机会" << std::endl;
                    }
                }
                iter->setFreezeMark(true);
                std::cout << "连续三次输入密码错误，您的账户已被冻结!" << std::endl;
                std::cout << "--------------------" << std::endl;
                return;
            } else {
                std::cout << "您的账户正处于冻结状态中，请先解冻!" << std::endl;
                std::cout << "--------------------" << std::endl;
                return;
            }
        }
    }
    std::cout << "银行卡号输入有误!" << std::endl;
    std::cout << "--------------------" << std::endl;
}

//用户功能
void system::userFunction(account &curAccount) {
    bool flag = true;
    while(flag) {
        std::cout << "尊敬的用户您好，请选择您需要使用的功能:" << std::endl;
        std::cout << "1. 存款" << std::endl;
        std::cout << "2. 取款" << std::endl;
        std::cout << "3. 转账" << std::endl;
        std::cout << "4. 查询" << std::endl;
        std::cout << "5. 修改密码" << std::endl;
        std::cout << "6. 退出" << std::endl;
        std::string num;
        std::cin >> num;
        if(!judgeOverflow(num)) {
            std::cout << "您输入的数字有误!" << std::endl;
            continue;
        }
        switch (std::stoi(num)) {
            case 1:
                curAccount.saveMoney();
                break;
            case 2:
                curAccount.takeMoney();
                break;
            case 3:
                transfer(curAccount);
                break;
            case 4:
                curAccount.showAccount();
                break;
            case 5:
                curAccount.changeUserPassword();
                break;
            case 6:
                flag = false;
                std::cout << "--------------------" << std::endl;
                break;
            default:
                std::cout << "您输入的数字有误，请重新输入!" << std::endl;
                std::cout << "--------------------" << std::endl;
                break;
        }
    }

}

//转账
void system::transfer(account &srcAccount) {
    std::string srcNumber = srcAccount.getAccountNumber();
    std::string destNumber;
    std::cout << "请输入对方银行卡号:" << std::endl;
    std::cin >> destNumber;
    if(srcNumber == destNumber) {
        std::cout << "转账失败，无法转账给自己!" << std::endl;
        std::cout << "--------------------" << std::endl;
        return;
    }
    std::vector<account>::iterator iter;
    for(iter = accounts.begin(); iter != accounts.end(); ++iter) {
        if(iter->getAccountNumber() == destNumber) {
            //找到了转账的目标账户
            std::string srcName = srcAccount.getUserName();
            std::string destName = iter->getUserName();
            int money = srcAccount.transferTo(destName);
            if(money > 0) {
                //转账成功
                iter->transferFrom(money, srcName);
            }
            std::cout << "--------------------" << std::endl;
            return;
        }
    }
    std::cout << "银行卡号输入有误!" << std::endl;
    std::cout << "--------------------" << std::endl;
}

//销户
void system::cancelAccount() {
    std::string password;
    std::cout << "请输入管理员密码:" << std::endl;
    std::cin >> password;
    if(adminPassword == password) {
        std::string number;
        std::cout << "请输入要注销的银行卡号:" << std::endl;
        std::cin >> number;
        std::vector<account>::iterator iter;
        for(iter = accounts.begin(); iter != accounts.end(); ++iter) {
            if(iter->getAccountNumber() == number) {
                //找到了需要注销的账户
                accounts.erase(iter);
                --accountNum;
                std::cout << "注销成功!" << std::endl;
                std::cout << "--------------------" << std::endl;
                return;
            }
        }
        std::cout << "银行卡号输入有误!" << std::endl;
        std::cout << "--------------------" << std::endl;
    } else {
        std::cout << "管理员密码错误!" << std::endl;
        std::cout << "--------------------" << std::endl;
    }
}

//解冻账户
void system::unfreeze() {
    std::string password;
    std::cout << "请输入管理员密码:" << std::endl;
    std::cin >> password;
    if(adminPassword == password) {
        std::string number;
        std::cout << "请输入要解冻的银行卡号:" << std::endl;
        std::cin >> number;
        std::vector<account>::iterator iter;
        for(iter = accounts.begin(); iter != accounts.end(); ++iter) {
            if(iter->getAccountNumber() == number) {
                //找到了需要解冻的账户
                if(!iter->getFreezeMark()) {
                    std::cout << "您的账户未冻结!" << std::endl;
                } else {
                    iter->setFreezeMark(false);
                    std::cout << "解冻成功!" << std::endl;
                }
                std::cout << "--------------------" << std::endl;
                return;
            }
        }
        std::cout << "银行卡号输入有误!" << std::endl;
        std::cout << "--------------------" << std::endl;
    } else {
        std::cout << "管理员密码输入有误!" << std::endl;
        std::cout << "--------------------" << std::endl;
    }
}

//判断输入的数字是否溢出
bool system::judgeOverflow(const std::string& num) {
    int rev = 0;
    for(char i : num) {
        int pop = i - '0';
        if(rev > INT32_MAX / 10 || (rev == INT32_MAX / 10 && pop > 7)) {
            return false;
        }
        if(rev < INT32_MIN / 10 || (rev == INT32_MIN / 10 && pop < -8)) {
            return false;
        }
        rev = rev * 10 + pop;
    }
    return true;
}