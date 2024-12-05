#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Account {
private:
    string AccountNo, Password;
    int Balance;

public:
    Account() : AccountNo(""), Password(""), Balance(0) {}

    void setAccountNo(string id) {
        AccountNo = id;
    }

    void setPassword(string pw) {
        Password = pw;
    }

    void setBalance(int balance) {
        Balance = balance;
    }

    string getAccountNo() {
        return AccountNo;
    }

    string getPassword() {
        return Password;
    }

    int getBalance() {
        return Balance;
    }
};

void openAccount(Account& user) {
    system("cls");
    string id, pw;

    cout << "\tEnter Account No: ";
    cin >> id;
    user.setAccountNo(id);

    cout << "\tEnter A Strong Password: ";
    cin >> pw;
    user.setPassword(pw);

    user.setBalance(0);

    ofstream outfile("Account.txt", ios::app);
    if (!outfile) {
        cout << "\tError: File Can't Open!" << endl;
    } else {
        outfile << user.getAccountNo() << " : " << user.getPassword() << " : " << user.getBalance() << endl;
        cout << "\tAccount Created Successfully!" << endl;
    }
    outfile.close();
    Sleep(2000);
}

void addCash() {
    system("cls");
    string id;
    cout << "\tEnter Account No: ";
    cin >> id;

    ifstream infile("Account.txt");
    ofstream outfile("Account_Temp.txt");
    if (!infile || !outfile) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        string userID, userPW;
        int userBalance;
        char delimiter;

        ss >> userID >> delimiter >> userPW >> delimiter >> userBalance;
        if (id == userID) {
            found = true;
            int cash;
            cout << "\tEnter Cash: ";
            cin >> cash;

            userBalance += cash;
            outfile << userID << " : " << userPW << " : " << userBalance << endl;
            cout << "\tNew Balance Is: " << userBalance << endl;
        } else {
            outfile << line << endl;
        }
    }
    if (!found) {
        cout << "\tEnter Valid Account No!" << endl;
    }
    outfile.close();
    infile.close();
    remove("Account.txt");
    rename("Account_Temp.txt", "Account.txt");
    Sleep(2000);
}

void withdraw() {
    system("cls");
    string id, pw;
    cout << "\tEnter Account No: ";
    cin >> id;

    cout << "\tEnter Password: ";
    cin >> pw;

    ifstream infile("Account.txt");
    ofstream outfile("Account_Temp.txt");
    if (!infile || !outfile) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        string userID, userPW;
        int userBalance;
        char delimiter;

        ss >> userID >> delimiter >> userPW >> delimiter >> userBalance;

        if (id == userID && pw == userPW) {
            found = true;
            int cash;
            cout << "\tEnter Cash: ";
            cin >> cash;
            if (cash <= userBalance) {
                userBalance -= cash;
                outfile << userID << " : " << userPW << " : " << userBalance << endl;
                cout << "\tTransaction Was Successful!" << endl;
                cout << "\tRemaining Balance: " << userBalance << endl;
            } else {
                cout << "\tInsufficient Balance!" << endl;
                outfile << userID << " : " << userPW << " : " << userBalance << endl;
            }
        } else {
            outfile << line << endl;
        }
    }
    if (!found) {
        cout << "\tInvalid Account No or Password!" << endl;
    }
    outfile.close();
    infile.close();
    remove("Account.txt");
    rename("Account_Temp.txt", "Account.txt");
    Sleep(2000);
}

int main() {
    Account user;

    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Bank Account Management System" << endl;
        cout << "\t*****************************************" << endl;
        cout << "\t1. Open New Account." << endl;
        cout << "\t2. Add Cash." << endl;
        cout << "\t3. Withdraw Cash." << endl;
        cout << "\t4. Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        switch (val) {
        case 1:
            openAccount(user);
            break;
        case 2:
            addCash();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            exit = true;
            system("cls");
            cout << "\tGood Luck!" << endl;
            Sleep(2000);
            break;
        default:
            cout << "\tInvalid Choice!" << endl;
            Sleep(2000);
        }
    }
    return 0;
}
