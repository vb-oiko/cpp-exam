//
// Created by AZagorskyi on 8/23/2022.
//

#include <iostream>
using namespace std;

class Bank {
private:
    const char *name;
    int sortCode;
public:
    Bank(const char bName[], int bSortCode) {
        name = bName;
        sortCode = bSortCode;
    }

    Bank();

    friend bool operator==(Bank &, Bank &);

    void setName(const char bName[]) {
        name = bName;
    }

    const char *getName() {
        return name;
    }

    void setSortCode(int bSortCode) {
        sortCode = bSortCode;
    }

    int getSortCode() {
        return sortCode;
    }

    void print() {
        std::cout << "Bank name: " << name << " - CODE: " << sortCode << std::endl;
    }

    void printShort() {
        std::cout << name << std::endl;
    }
};

bool operator==(Bank &bank1, Bank &bank2) {
    bool equal = true;
    if (bank1.getName() != bank2.getName()) {
        equal = false;
    }
    if (bank1.getSortCode() != bank2.getSortCode()) {
        equal = false;
    }
    return equal;
};

class Account {
private:
    int number;
    double balance;
    Bank *bank;
public:
    Account(int aNumber, double aBalance, Bank *aBank) {
        number = aNumber;
        balance = aBalance;
        bank = aBank;
    }

    Account();

    friend bool operator==(Account &, Account &);

    void setNumber(int aNumber) {
        number = aNumber;
    }

    int getNumber() {
        return number;
    }

    void setBalance(double aBalance) {
        balance = aBalance;
    }

    double getBalance() {
        return balance;
    }

    void setBank(Bank *aBank) {
        bank = aBank;
    }

    Bank * getBank() {
        return bank;
    }

    virtual void print() {
        std::cout << "Account number: " << number << " - Account balance: " << balance << std::endl;
        getBank()->print();
    }

    void printShort() {
        std::cout << number << " - " << balance << std::endl;
    }
};

bool operator==(Account &account1, Account &account2) {
    bool equal = true;
    if (account1.getNumber() != account2.getNumber()) {
        equal = false;
    }
    if (account1.getBalance() != account2.getBalance()) {
        equal = false;
    }
    equal = *account1.getBank() == *account2.getBank();
    return equal;
};

class DepositAccount : public Account {
private:
    string createdDate;
    int period;
    double rate;
public:
    DepositAccount(int dNumber, double dBalance, Bank *dBank, string dCreatedDate, int dPeriod,
                   double dRate): Account(dNumber, dBalance, dBank) {
        createdDate = std::move(dCreatedDate);
        period = dPeriod;
        rate = dRate;
    }

    void setCreatedDate(string dCreatedDate) {
        createdDate = std::move(dCreatedDate);
    }

    string getCreatedDate() {
        return createdDate;
    }

    void setPeriod(int dPeriod) {
        period = dPeriod;
    }

    int getPeriod() {
        return period;
    }

    void setRate(double dRate) {
        rate = dRate;
    }

    double getRate() {
        return rate;
    }
};

class CreditAccount : public Account {
private:
    string lastOperationDate;
    double rate;
public:

    CreditAccount(int cNumber, double cBalance, Bank *cBank, string cLastOperationDate,
                  double cRate): Account(cNumber, cBalance, cBank) {
        lastOperationDate = std::move(cLastOperationDate);
        rate = cRate;
    }

    CreditAccount();

    void operator+=(double money) {
        this->setBalance(this->getBalance() + money);
    };

    friend CreditAccount operator++(CreditAccount &);
    friend bool operator<(CreditAccount &, CreditAccount &);

    void setLastOperationDate(string cLastOperationDate) {
        lastOperationDate = std::move(cLastOperationDate);
    }

    string getLastOperationDate() {
        return lastOperationDate;
    }

    void setRate(double dRate) {
        rate = dRate;
    }

    double getRate() {
        return rate;
    }
};

CreditAccount operator++(CreditAccount &account) {
    account.setBalance(account.getBalance() + 1);
    return account;
};

bool operator<(CreditAccount &account1, CreditAccount &account2) {
    return account1.getBalance() < account2.getBalance();
};

class Client {
private:
    string lastName;
    int size;
    int indexInt = 0;
    Account **accounts;
public:

    Client(string cLastName, int cSize) {
        lastName = std::move(cLastName);
        size = cSize;
        accounts = new Account*[cSize];
    }

    Client();

    void setLastName(string cLastName) {
        lastName = std::move(cLastName);
    }

    string getLastName() {
        return lastName;
    }

    void addAccount(Account *account) {
        if (indexInt < size) {
            accounts[indexInt++] = account;
        } else {
            printf("List full");
        }
    }

    Account * getAccountByIndex(int index) {
        return accounts[index];
    }
};

int main() {
    Bank *bank = new Bank("Private", 254897);
    bank->print();
    bank->printShort();

    Account *account1 = new Account( 25488, 7500.5, new Bank("Ukrsibbank", 754811));
    account1->print();
    account1->printShort();

    CreditAccount creditAccount1(25488, 7500.5, new Bank("FIDO bank", 777777), "25-04-2022", 10.5);
    CreditAccount creditAccount2(25489, 10000, new Bank("FIDO bank", 777777), "25-04-2022", 5.6);

    std::cout << "Account number: " << creditAccount1.getNumber() << ((creditAccount1 < creditAccount2) ?
                                                                      " LESS than " : " MORE than ") << " - Account number: " << creditAccount2.getNumber() << std::endl;

    ++creditAccount1;
    creditAccount1.print();

    creditAccount2 += (-6000);
    creditAccount2.print();

    std::cout << "Account number: " << creditAccount1.getNumber() << ((creditAccount1 < creditAccount2) ?
                                                                      " LESS than " : " MORE than ") << " - Account number: " << creditAccount2.getNumber() << std::endl;

    Bank bank1("Premium bank", 111111);
    Bank bank2("Premium bank", 111111);
    Bank bank3("Sigma bank", 222222);

    std::cout << "Banks " << ((bank1 == bank2) ?
                              "are same" : "are different") <<  std::endl;

    std::cout << "Banks " << ((bank1 == bank3) ?
                              "are same" : "are different") <<  std::endl;

    Account *account2 = new Account( 25488, 7500.5, new Bank("Ukrsibbank", 754811));
    Account *account3 = new Account( 25488, 7500.5, new Bank("Money Bank", 999811));

    std::cout << "Accounts " << ((*account1 == *account2) ?
                                 "are same" : "are different") <<  std::endl;

    std::cout << "Accounts " << ((*account1 == *account3) ?
                                 "are same" : "are different") <<  std::endl;

    Client *client1 = new Client("Pol", 2);
    client1->addAccount(new CreditAccount(25488, 7500.5,
                                          new Bank("FIDO bank", 777777),
                                          "25-04-2022", 10.5));
    client1->addAccount(new DepositAccount(25489, 1000,
                                           new Bank("FIDO bank", 777777),
                                           "25-04-2022", 12, 25));

    client1->getAccountByIndex(1)->print();

    Account *accountUpcasting = &creditAccount1;
    std::cout << "Account instance of " << ((dynamic_cast<Account*>(accountUpcasting) != nullptr) ?
                                            "Account type" : "another type") <<  std::endl;


    auto *accountDowncasting =  (CreditAccount *) accountUpcasting;
    std::cout << "Account instance of " << ((dynamic_cast<CreditAccount*>(accountDowncasting) != nullptr) ?
                                            "CreditAccount type" : "another type") <<  std::endl;

    return 0;
}