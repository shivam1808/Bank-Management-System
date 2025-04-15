/* ===========================================
   Enhanced Bank Record System - Mini Project
   ===========================================*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cstdio>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <windows.h>
#include <functional>

using namespace std;

// Global variables
int main_exit;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Data structures
map<string, string> accountCredentials;  // Hash table for account credentials
map<string, string> employeeCredentials; // Hash table for employee credentials
vector<string> transactionHistory;       // Vector to store transaction history
queue<string> serviceQueue;              // Queue for customer service
stack<string> recentTransactions;        // Stack for recent transactions

// Function prototypes
void fordelay(int);
void close(void);
int main();
void menu_e();
void employee();
void customer();
void menu_c();
void displayTitle();
void loginPage();
void signupPage();
void displayInstructions();
void displayLoadingScreen();
void setColor(int color);
void loadCredentials();
void saveCredentials();

// Bank Account Class
class Bank
{
private:
    struct AccountNode
    {
        string account_number;
        string name;
        string dob;
        string age;
        string address;
        string phone;
        string balance;
        string acc_type;
        string creation_date;
        string last_transaction;
        AccountNode *left;
        AccountNode *right;

        AccountNode(string acc_no, string n, string d, string a,
                    string addr, string ph, string bal, string type,
                    string date)
            : account_number(acc_no), name(n), dob(d), age(a),
              address(addr), phone(ph), balance(bal), acc_type(type),
              creation_date(date), last_transaction(date), left(nullptr), right(nullptr) {}
    };

    AccountNode *root;

    AccountNode *insert(AccountNode *node, string acc_no, string n, string d, string a,
                        string addr, string ph, string bal, string type, string date)
    {
        if (node == nullptr)
        {
            return new AccountNode(acc_no, n, d, a, addr, ph, bal, type, date);
        }
        if (acc_no < node->account_number)
        {
            node->left = insert(node->left, acc_no, n, d, a, addr, ph, bal, type, date);
        }
        else
        {
            node->right = insert(node->right, acc_no, n, d, a, addr, ph, bal, type, date);
        }
        return node;
    }

    AccountNode *search(AccountNode *node, string acc_no)
    {
        if (node == nullptr || node->account_number == acc_no)
        {
            return node;
        }
        if (acc_no < node->account_number)
        {
            return search(node->left, acc_no);
        }
        return search(node->right, acc_no);
    }

    void inorder(AccountNode *node)
    {
        if (node != nullptr)
        {
            inorder(node->left);
            cout << "\t" << left
                 << setw(20) << node->account_number
                 << setw(30) << node->name
                 << setw(20) << node->acc_type
                 << "Rs " << node->balance << "\n";
            inorder(node->right);
        }
    }

    void clearTree(AccountNode *node)
    {
        if (node != nullptr)
        {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

public:
    Bank() : root(nullptr)
    {
        loadAccountsFromFile();
    }

    ~Bank()
    {
        clearTree(root);
    }

    void loadAccountsFromFile()
    {
        ifstream file("Bank_Record.csv");
        if (!file.is_open())
            return;

        string line;
        while (getline(file, line))
        {
            vector<string> tokens;
            string token;
            size_t pos = 0;
            while ((pos = line.find(',')) != string::npos)
            {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() >= 9)
            {
                root = insert(root, tokens[0], tokens[1], tokens[2], tokens[3],
                              tokens[4], tokens[5], tokens[6], tokens[7], tokens[8]);
            }
        }
        file.close();
    }

    void saveAccountsToFile()
    {
        ofstream file("Bank_Record.csv");
        if (!file.is_open())
            return;

        saveAccountsToFileHelper(root, file);
        file.close();
    }

    void saveAccountsToFileHelper(AccountNode *node, ofstream &file)
    {
        if (node != nullptr)
        {
            saveAccountsToFileHelper(node->left, file);
            file << node->account_number << "," << node->name << "," << node->dob << ","
                 << node->age << "," << node->address << "," << node->phone << ","
                 << node->balance << "," << node->acc_type << "," << node->creation_date << "\n";
            saveAccountsToFileHelper(node->right, file);
        }
    }

    void read_data();
    void acc_write();
    void modify_account();
    void search_rec();
    void deposit_withdraw();
    void display_all();
    void transfer();
    void view_transaction_history();
    void request_service();
    void process_service_queue();
};

// Utility Functions
void setColor(int color)
{
    SetConsoleTextAttribute(hConsole, color);
}

void displayTitle()
{
    system("cls");
    setColor(11);
    cout << "\n\n\t\t*********************************************";
    cout << "\n\t\t*                                           *";
    cout << "\n\t\t*       STATE BANK OF INDIA - ATM SYSTEM    *";
    cout << "\n\t\t*                                           *";
    cout << "\n\t\t*********************************************\n\n";
    setColor(7);
}

void displayLoadingScreen()
{
    system("cls");
    setColor(10);
    cout << "\n\n\n\n\n\t\t\tLoading";
    for (int i = 0; i < 6; i++)
    {
        fordelay(100000000);
        cout << ".";
    }
    system("cls");
}

void displayInstructions()
{
    displayTitle();
    setColor(14);
    cout << "\n\t\tIMPORTANT INSTRUCTIONS:\n";
    setColor(7);
    cout << "\n\t1. Keep your account number and password confidential.";
    cout << "\n\t2. Do not share your OTP or password with anyone.";
    cout << "\n\t3. Always log out after completing your transactions.";
    cout << "\n\t4. Report any suspicious activity to bank immediately.";
    cout << "\n\t5. Regularly update your password for security.";
    cout << "\n\n\tPress any key to continue...";
    _getch();
}

void loginPage()
{
    displayTitle();
    setColor(14);
    cout << "\n\t\tLOGIN PAGE\n";
    setColor(7);
    cout << "\n\t1. Employee Login";
    cout << "\n\t2. Customer Login";
    cout << "\n\t3. New Customer Registration";
    cout << "\n\t4. Return to Main Menu";
    cout << "\n\t5. Exit";
    cout << "\n\n\tEnter your choice: ";
}

void signupPage()
{
    displayTitle();
    setColor(14);
    cout << "\n\t\tNEW CUSTOMER REGISTRATION\n";
    setColor(7);
}

void fordelay(int j)
{
    for (int i = 0; i < j; i++)
        ;
}

string getPasswordInput()
{
    string password;
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == 13) // Enter key
            break;
        else if (ch == 8) // Backspace
        {
            if (!password.empty())
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else if (isprint(ch))
        {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void close(void)
{
    displayTitle();
    setColor(12);
    cout << "\n\n\n\n\t\tThank you for using our banking system!";
    setColor(7);
    cout << "\n\n\t\tProgram is now closing...\n\n";
    exit(0);
}

// Load and save credentials
void loadCredentials()
{
    // Load account credentials
    ifstream accFile("Account_info.csv");
    if (accFile.is_open())
    {
        string line;
        while (getline(accFile, line))
        {
            size_t pos = line.find(',');
            if (pos != string::npos)
            {
                string acc_no = line.substr(0, pos);
                string pass = line.substr(pos + 1);
                accountCredentials[acc_no] = pass;
            }
        }
        accFile.close();
    }

    // Load employee credentials
    ifstream empFile("Employee_info.csv");
    if (empFile.is_open())
    {
        string line;
        while (getline(empFile, line))
        {
            size_t pos = line.find(',');
            if (pos != string::npos)
            {
                string emp_id = line.substr(0, pos);
                string pass = line.substr(pos + 1);
                employeeCredentials[emp_id] = pass;
            }
        }
        empFile.close();
    }
    else
    {
        // Create default admin if file doesn't exist
        employeeCredentials["admin"] = "admin123";
        saveCredentials();
    }
}

void saveCredentials()
{
    // Save employee credentials
    ofstream empFile("Employee_info.csv");
    if (empFile.is_open())
    {
        for (const auto &pair : employeeCredentials)
        {
            empFile << pair.first << "," << pair.second << "\n";
        }
        empFile.close();
    }
}

// Bank Class Member Functions
void Bank::read_data()
{
    int x, i = 0;
    string account_number, name, dob, age, address, phone, depo, acc_type, date, password;

Retry:
    displayTitle();
    cout << "\n\t\tACCOUNT CREATION\n";
    cout << "\n\tEnter Account Number: ";
    cin >> account_number;

    if (accountCredentials.find(account_number) != accountCredentials.end())
    {
        cout << "\n\tAccount No. Matches with Existing Account!";
        cout << "\n\t1. Try Again!\n\t2. Login To Account\n\tChoice: ";
        cin >> x;
        if (x == 1)
            goto Retry;
        else
            customer();
    }

    cout << "\n\tEnter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "\n\tEnter Date of Birth (mm/dd/yyyy): ";
    cin >> dob;

    cout << "\n\tEnter Age: ";
    cin >> age;

    cout << "\n\tEnter Address: ";
    cin.ignore();
    getline(cin, address);

    cout << "\n\tEnter Phone Number: ";
    cin >> phone;

    cout << "\n\tDo you want to deposit amount?\n\t1. Yes\n\t2. No\n\tChoice: ";
    cin >> x;
    if (x == 1)
    {
        cout << "\n\tEnter the amount to deposit: Rs ";
        cin >> depo;
    }
    else
    {
        depo = "0";
    }

    cout << "\n\tType of account:\n\t1. Saving\n\t2. Current\n\tChoice: ";
    cin >> x;
    acc_type = (x == 1) ? "Saving" : "Current";

    time_t now = time(0);
    string dt = ctime(&now);
    date = dt;

    cout << "\n\tEnter Password For Your Account: ";
    password = getPasswordInput();

    // Add to credentials map
    accountCredentials[account_number] = password;

    // Save to the file immediately
    ofstream accFile("Account_info.csv", ios::app);
    if (accFile.is_open())
    {
        accFile << account_number << "," << password << "\n";
        accFile.close();
    }

    setColor(10);
    cout << "\n\tAccount created successfully!";
    setColor(7);

    int choice;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice == 0)
    {
        close();
    }
    else if (choice == 2)
    {
        menu_c();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_c();
    }
}

void Bank::acc_write()
{
    string account_number, name, dob, age, address, phone, depo, acc_type, date, password;

    displayTitle();
    cout << "\n\t\tACCOUNT CREATION\n";
    cout << "\n\tEnter Account Number: ";
    cin >> account_number;

    if (accountCredentials.find(account_number) != accountCredentials.end())
    {
        cout << "\n\tAccount No. Matches with Existing Account!";
        cout << "\n\t1. Try Again!\n\t2. Login To Account\n\tChoice: ";
        int x;
        cin >> x;
        if (x == 1)
            acc_write();
        else
            customer();
        return;
    }

    cout << "\n\tEnter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "\n\tEnter Date of Birth (mm/dd/yyyy): ";
    cin >> dob;

    cout << "\n\tEnter Age: ";
    cin >> age;

    cout << "\n\tEnter Address: ";
    cin.ignore();
    getline(cin, address);

    cout << "\n\tEnter Phone Number: ";
    cin >> phone;

    int x;
    cout << "\n\tDo you want to deposit amount?\n\t1. Yes\n\t2. No\n\tChoice: ";
    cin >> x;
    if (x == 1)
    {
        cout << "\n\tEnter the amount to deposit: Rs ";
        cin >> depo;
    }
    else
    {
        depo = "0";
    }

    cout << "\n\tType of account:\n\t1. Saving\n\t2. Current\n\tChoice: ";
    cin >> x;
    acc_type = (x == 1) ? "Saving" : "Current";

    time_t now = time(0);
    string dt = ctime(&now);
    date = dt;

    cout << "\n\tEnter Password For Your Account: ";
    password = getPasswordInput();

    // Add to credentials map
    accountCredentials[account_number] = password;

    ofstream MyFile1, MyFile2;
    MyFile1.open("Bank_Record.csv", ios::out | ios::app);
    MyFile1 << account_number << "," << name << "," << dob << ","
            << age << "," << address << "," << phone << "," << depo
            << "," << acc_type << "," << date << "\n";
    MyFile1.close();

    MyFile2.open("Account_info.csv", ios::out | ios::app);
    MyFile2 << account_number << "," << password << "\n";
    MyFile2.close();

    // Add to BST
    root = insert(root, account_number, name, dob, age, address, phone, depo, acc_type, date);

    setColor(10);
    cout << "\n\tAccount created successfully!";
    setColor(7);

    int choice;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice == 0)
    {
        close();
    }
    else if (choice == 2)
    {
        menu_c();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_c();
    }
}

void Bank::modify_account()
{
    displayTitle();
    cout << "\n\t\tACCOUNT MODIFICATION\n";

    string acc_no;
    cout << "\n\tEnter the Account Number: ";
    cin >> acc_no;

    AccountNode *account = search(root, acc_no);
    if (account == nullptr)
    {
        setColor(12);
        cout << "\n\tAccount Doesn't Exist!";
        setColor(7);
    }
    else
    {
        setColor(11);
        cout << "\n\tAccount Found! Current Details:";
        setColor(7);
        cout << "\n\tAccount NO.: " << account->account_number;
        cout << "\n\tName: " << account->name;
        cout << "\n\tDOB: " << account->dob;
        cout << "\n\tAge: " << account->age;
        cout << "\n\tAddress: " << account->address;
        cout << "\n\tPhone number: " << account->phone;
        cout << "\n\tType Of Account: " << account->acc_type;
        cout << "\n\tDate of Account creation: " << account->creation_date;
        cout << "\n\tAmount deposited: " << account->balance;

        int choice;
        do
        {
            cout << "\n\n\tWhat would you like to update?";
            cout << "\n\t1. Name";
            cout << "\n\t2. Date of Birth";
            cout << "\n\t3. Age";
            cout << "\n\t4. Address";
            cout << "\n\t5. Phone Number";
            cout << "\n\t6. Done Updating";
            cout << "\n\tChoice: ";
            cin >> choice;

            string newValue;
            cin.ignore();
            switch (choice)
            {
            case 1:
                cout << "\n\tEnter New Name: ";
                getline(cin, newValue);
                account->name = newValue;
                break;
            case 2:
                cout << "\n\tEnter New Date of Birth (mm/dd/yyyy): ";
                cin >> newValue;
                account->dob = newValue;
                break;
            case 3:
                cout << "\n\tEnter New Age: ";
                cin >> newValue;
                account->age = newValue;
                break;
            case 4:
                cout << "\n\tEnter New Address: ";
                getline(cin, newValue);
                account->address = newValue;
                break;
            case 5:
                cout << "\n\tEnter New Phone Number: ";
                cin >> newValue;
                account->phone = newValue;
                break;
            case 6:
                break;
            default:
                setColor(12);
                cout << "\n\tInvalid Choice!";
                setColor(7);
            }
        } while (choice != 6);

        // Update the file
        saveAccountsToFile();
        setColor(10);
        cout << "\n\tAccount updated successfully!";
        setColor(7);
    }

    int choice;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice == 0)
    {
        close();
    }
    else if (choice == 2)
    {
        menu_c();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_c();
    }
}

void Bank::search_rec()
{
    displayTitle();
    cout << "\n\t\tACCOUNT SEARCH\n";

    int choice;
    cout << "\n\tSearch by:\n\t1. Account Number\n\t2. Name\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        string acc_no;
        cout << "\n\tEnter Account Number: ";
        cin >> acc_no;

        AccountNode *account = search(root, acc_no);
        if (account == nullptr)
        {
            setColor(12);
            cout << "\n\tAccount Doesn't Exist!";
            setColor(7);
        }
        else
        {
            setColor(11);
            cout << "\n\tAccount Details:";
            setColor(7);
            cout << "\n\tAccount NO.: " << account->account_number;
            cout << "\n\tName: " << account->name;
            cout << "\n\tDOB: " << account->dob;
            cout << "\n\tAge: " << account->age;
            cout << "\n\tAddress: " << account->address;
            cout << "\n\tPhone number: " << account->phone;
            cout << "\n\tType Of Account: " << account->acc_type;
            cout << "\n\tDate of Account creation: " << account->creation_date;
            cout << "\n\tBalance: Rs " << account->balance;
        }
    }
    else if (choice == 2)
    {
        string name_search;
        cout << "\n\tEnter Name: ";
        cin.ignore();
        getline(cin, name_search);

        // Search by name in the BST
        bool found = false;
        function<void(AccountNode *)> searchByName = [&](AccountNode *node)
        {
            if (node == nullptr)
                return;

            searchByName(node->left);

            if (node->name.find(name_search) != string::npos)
            {
                if (!found)
                {
                    setColor(11);
                    cout << "\n\tAccounts Found:";
                    setColor(7);
                    found = true;
                }

                cout << "\n\n\tAccount NO.: " << node->account_number;
                cout << "\n\tName: " << node->name;
                cout << "\n\tType Of Account: " << node->acc_type;
                cout << "\n\tBalance: Rs " << node->balance;
                cout << "\n\t---------------------------";
            }

            searchByName(node->right);
        };

        searchByName(root);

        if (!found)
        {
            setColor(12);
            cout << "\n\tNo accounts with that name were found!";
            setColor(7);
        }
    }
    else
    {
        setColor(12);
        cout << "\n\tInvalid Choice!";
        setColor(7);
    }

    int choice2;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice2;

    if (choice2 == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice2 == 0)
    {
        close();
    }
    else if (choice2 == 2)
    {
        menu_c();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_c();
    }
}

void Bank::deposit_withdraw()
{
    displayTitle();
    cout << "\n\t\tTRANSACTIONS\n";

    string acc_no;
    cout << "\n\tEnter Account Number: ";
    cin >> acc_no;

    AccountNode *account = search(root, acc_no);
    if (account == nullptr)
    {
        setColor(12);
        cout << "\n\tAccount Doesn't Exist!";
        setColor(7);
    }
    else
    {
        setColor(11);
        cout << "\n\tAccount Details:";
        setColor(7);
        cout << "\n\tAccount NO.: " << account->account_number;
        cout << "\n\tName: " << account->name;
        cout << "\n\tCurrent Balance: Rs " << account->balance;

        int choice;
        cout << "\n\n\t1. Deposit\n\t2. Withdraw\n\tChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            float amount;
            cout << "\n\tEnter Amount to Deposit: Rs ";
            cin >> amount;

            float current = stof(account->balance);
            current += amount;
            account->balance = to_string(current);

            // Record transaction
            string trans = "Deposit: +Rs " + to_string(amount) + " to " + acc_no;
            transactionHistory.push_back(trans);
            recentTransactions.push(trans);

            // Update last transaction date
            time_t now = time(0);
            account->last_transaction = ctime(&now);

            setColor(10);
            cout << "\n\tDeposit Successful! New Balance: Rs " << account->balance;
            setColor(7);
        }
        else if (choice == 2)
        {
            float amount;
            cout << "\n\tEnter Amount to Withdraw: Rs ";
            cin >> amount;

            float current = stof(account->balance);
            if (amount > current)
            {
                setColor(12);
                cout << "\n\tInsufficient Balance!";
                setColor(7);
            }
            else
            {
                current -= amount;
                account->balance = to_string(current);

                // Record transaction
                string trans = "Withdrawal: -Rs " + to_string(amount) + " from " + acc_no;
                transactionHistory.push_back(trans);
                recentTransactions.push(trans);

                // Update last transaction date
                time_t now = time(0);
                account->last_transaction = ctime(&now);

                setColor(10);
                cout << "\n\tWithdrawal Successful! New Balance: Rs " << account->balance;
                setColor(7);
            }
        }
        else
        {
            setColor(12);
            cout << "\n\tInvalid Choice!";
            setColor(7);
        }

        // Update the file
        saveAccountsToFile();
    }

    int choice2;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice2;

    if (choice2 == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice2 == 0)
    {
        close();
    }
    else if (choice2 == 2)
    {
        menu_c();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_c();
    }
}

void Bank::display_all()
{
    displayTitle();
    cout << "\n\t\tALL ACCOUNT HOLDERS\n";

    setColor(14);
    cout << left
         << "\n\t" << setw(20) << "Account No."
         << setw(30) << "Name"
         << setw(20) << "Type"
         << setw(15) << "Balance" << "\n";
    cout << "\t" << string(85, '-') << "\n";
    setColor(7);

    inorder(root);

    int choice;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice == 0)
    {
        close();
    }
    else if (choice == 2)
    {
        menu_e();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_e();
    }
}

void Bank::transfer()
{
    displayTitle();
    cout << "\n\t\tFUND TRANSFER\n";

    string from_acc, to_acc;
    cout << "\n\tEnter Your Account Number: ";
    cin >> from_acc;

    AccountNode *from_account = search(root, from_acc);
    if (from_account == nullptr)
    {
        setColor(12);
        cout << "\n\tYour Account Doesn't Exist!";
        setColor(7);

        int choice;
        cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            displayLoadingScreen();
            main();
        }
        else if (choice == 0)
        {
            close();
        }
        else
        {
            menu_c();
        }
        return;
    }

    cout << "\n\tEnter Recipient Account Number: ";
    cin >> to_acc;

    AccountNode *to_account = search(root, to_acc);
    if (to_account == nullptr)
    {
        setColor(12);
        cout << "\n\tRecipient Account Doesn't Exist!";
        setColor(7);

        int choice;
        cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            displayLoadingScreen();
            main();
        }
        else if (choice == 0)
        {
            close();
        }
        else
        {
            menu_c();
        }
        return;
    }

    float amount;
    cout << "\n\tEnter Amount to Transfer: Rs ";
    cin >> amount;

    float from_balance = stof(from_account->balance);
    if (amount > from_balance)
    {
        setColor(12);
        cout << "\n\tInsufficient Balance!";
        setColor(7);
    }
    else
    {
        from_balance -= amount;
        from_account->balance = to_string(from_balance);

        float to_balance = stof(to_account->balance);
        to_balance += amount;
        to_account->balance = to_string(to_balance);

        // Update last transaction date for both accounts
        time_t now = time(0);
        string transaction_time = ctime(&now);
        from_account->last_transaction = transaction_time;
        to_account->last_transaction = transaction_time;

        // Record transaction
        string trans = "Transfer: Rs " + to_string(amount) + " from " + from_acc + " to " + to_acc;
        transactionHistory.push_back(trans);
        recentTransactions.push(trans);

        // Update the file
        saveAccountsToFile();

        setColor(10);
        cout << "\n\tTransfer Successful!";
        cout << "\n\tYour New Balance: Rs " << from_account->balance;
        setColor(7);
    }

    int choice;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice == 0)
    {
        close();
    }
    else if (choice == 2)
    {
        menu_c();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_c();
    }
}

void Bank::view_transaction_history()
{
    displayTitle();
    cout << "\n\t\tTRANSACTION HISTORY\n";

    if (transactionHistory.empty())
    {
        setColor(12);
        cout << "\n\tNo transactions have been recorded yet.";
        setColor(7);
    }
    else
    {
        setColor(14);
        cout << "\n\tRecent Transactions (newest first):";
        setColor(7);
        cout << "\n\t--------------------------------------------------\n";

        // Create a temporary stack to display transactions
        stack<string> tempStack = recentTransactions;
        int count = 0;

        while (!tempStack.empty() && count < 10)
        {
            cout << "\t" << tempStack.top() << "\n";
            tempStack.pop();
            count++;
        }
    }

    int choice;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice == 0)
    {
        close();
    }
    else if (choice == 2)
    {
        menu_c();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_c();
    }
}

void Bank::request_service()
{
    displayTitle();
    cout << "\n\t\tREQUEST CUSTOMER SERVICE\n";

    string acc_no, request;
    cout << "\n\tEnter Your Account Number: ";
    cin >> acc_no;

    AccountNode *account = search(root, acc_no);
    if (account == nullptr)
    {
        setColor(12);
        cout << "\n\tAccount Doesn't Exist!";
        setColor(7);
    }
    else
    {
        cout << "\n\tSelect service type:";
        cout << "\n\t1. Technical Issue";
        cout << "\n\t2. Account Query";
        cout << "\n\t3. Loan Information";
        cout << "\n\t4. Other";
        cout << "\n\tChoice: ";

        int choice;
        cin >> choice;

        string service_type;
        switch (choice)
        {
        case 1:
            service_type = "Technical Issue";
            break;
        case 2:
            service_type = "Account Query";
            break;
        case 3:
            service_type = "Loan Information";
            break;
        default:
            service_type = "Other";
            break;
        }

        cout << "\n\tPlease describe your request (single line): ";
        cin.ignore();
        getline(cin, request);

        // Add to queue
        string service_request = acc_no + " - " + account->name + " - " + service_type + ": " + request;
        serviceQueue.push(service_request);

        setColor(10);
        cout << "\n\tYour service request has been queued!";
        cout << "\n\tCurrent queue position: " << serviceQueue.size();
        setColor(7);
    }

    int choice;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice == 0)
    {
        close();
    }
    else if (choice == 2)
    {
        menu_c();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_c();
    }
}

void Bank::process_service_queue()
{
    displayTitle();
    cout << "\n\t\tSERVICE QUEUE MANAGEMENT\n";

    if (serviceQueue.empty())
    {
        setColor(12);
        cout << "\n\tNo pending service requests.";
        setColor(7);
    }
    else
    {
        setColor(14);
        cout << "\n\tPending Service Requests: " << serviceQueue.size();
        setColor(7);
        cout << "\n\t--------------------------------------------------\n";
        cout << "\n\tNext in queue: " << serviceQueue.front();

        cout << "\n\n\tWhat would you like to do?";
        cout << "\n\t1. Process Next Request";
        cout << "\n\t2. View All Requests";
        cout << "\n\t3. Return to Menu";
        cout << "\n\tChoice: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "\n\tProcessing request: " << serviceQueue.front();
            serviceQueue.pop();
            setColor(10);
            cout << "\n\tRequest processed successfully!";
            setColor(7);
            cout << "\n\tRemaining requests: " << serviceQueue.size();
        }
        else if (choice == 2)
        {
            queue<string> tempQueue = serviceQueue;
            int count = 1;

            cout << "\n\tAll pending requests:";
            while (!tempQueue.empty())
            {
                cout << "\n\t" << count << ". " << tempQueue.front();
                tempQueue.pop();
                count++;
            }
        }
    }

    int choice;
    cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
    cin >> choice;

    if (choice == 1)
    {
        displayLoadingScreen();
        main();
    }
    else if (choice == 0)
    {
        close();
    }
    else if (choice == 2)
    {
        menu_e();
    }
    else
    {
        cout << "\n\tInvalid Choice!";
        fordelay(100000000);
        menu_e();
    }
}

// Menu Functions
void menu_c()
{
    Bank bank;

    displayTitle();
    setColor(14);
    cout << "\n\t\tCUSTOMER MENU\n";
    setColor(7);
    cout << "\n\t1. Create New Account";
    cout << "\n\t2. Search Account";
    cout << "\n\t3. Deposit/Withdraw";
    cout << "\n\t4. Modify Account";
    cout << "\n\t5. Fund Transfer";
    cout << "\n\t6. Transaction History";
    cout << "\n\t7. Request Customer Service";
    cout << "\n\t8. Log Out";
    cout << "\n\t0. Exit";
    cout << "\n\n\tEnter your choice: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        bank.acc_write();
        break;
    case 2:
        bank.search_rec();
        break;
    case 3:
        bank.deposit_withdraw();
        break;
    case 4:
        bank.modify_account();
        break;
    case 5:
        bank.transfer();
        break;
    case 6:
        bank.view_transaction_history();
        break;
    case 7:
        bank.request_service();
        break;
    case 8:
        displayLoadingScreen();
        main();
        break;
    case 0:
        close();
        break;
    default:
        cout << "\n\tInvalid choice!";
        fordelay(100000000);
        menu_c();
    }
}

void menu_e()
{
    Bank bank;

    displayTitle();
    setColor(14);
    cout << "\n\t\tEMPLOYEE MENU\n";
    setColor(7);
    cout << "\n\t1. Create Customer Account";
    cout << "\n\t2. Search Customer Account";
    cout << "\n\t3. Modify Account";
    cout << "\n\t4. View All Accounts";
    cout << "\n\t5. Process Service Requests";
    cout << "\n\t6. Add Employee Account";
    cout << "\n\t7. Log Out";
    cout << "\n\t0. Exit";
    cout << "\n\n\tEnter your choice: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        bank.acc_write();
        break;
    case 2:
        bank.search_rec();
        break;
    case 3:
        bank.modify_account();
        break;
    case 4:
        bank.display_all();
        break;
    case 5:
        bank.process_service_queue();
        break;
    case 6:
        // Add Employee Account
        {
            displayTitle();
            cout << "\n\t\tADD EMPLOYEE ACCOUNT\n";

            string emp_id, password;
            cout << "\n\tEnter Employee ID: ";
            cin >> emp_id;

            if (employeeCredentials.find(emp_id) != employeeCredentials.end())
            {
                setColor(12);
                cout << "\n\tEmployee ID already exists!";
                setColor(7);
            }
            else
            {
                cout << "\n\tEnter Password: ";
                cin >> password;

                employeeCredentials[emp_id] = password;
                saveCredentials();

                setColor(10);
                cout << "\n\tEmployee account created successfully!";
                setColor(7);
            }

            int choice;
            cout << "\n\n\t1. Main Menu\n\t2. Previous Menu\n\t0. Exit\n\tChoice: ";
            cin >> choice;

            if (choice == 1)
            {
                displayLoadingScreen();
                main();
            }
            else if (choice == 0)
            {
                close();
            }
            else
            {
                menu_e();
            }
        }
        break;
    case 7:
        displayLoadingScreen();
        main();
        break;
    case 0:
        close();
        break;
    default:
        cout << "\n\tInvalid choice!";
        fordelay(100000000);
        menu_e();
    }
}

void employee()
{
    system("cls");
    displayTitle();

    string emp_id, password;
    cout << "\n\t\tEMPLOYEE LOGIN\n";
    cout << "\n\tEnter Employee ID: ";
    cin >> emp_id;
    cout << "\n\tEnter Password: ";
    password = getPasswordInput();

    if (employeeCredentials.find(emp_id) != employeeCredentials.end() &&
        employeeCredentials[emp_id] == password)
    {
        setColor(10);
        cout << "\n\tLogin Successful! Welcome, " << emp_id << "!";
        setColor(7);
        fordelay(100000000);
        menu_e();
    }
    else
    {
        setColor(12);
        cout << "\n\tInvalid Employee ID or Password!";
        setColor(7);

        int choice;
        cout << "\n\n\t1. Try Again\n\t2. Main Menu\n\t0. Exit\n\tChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            employee();
        }
        else if (choice == 0)
        {
            close();
        }
        else
        {
            main();
        }
    }
}

void customer()
{
    system("cls");
    displayTitle();

    string acc_no, password;
    cout << "\n\t\tCUSTOMER LOGIN\n";
    cout << "\n\tEnter Account Number: ";
    cin >> acc_no;
    cout << "\n\tEnter Password: ";
    password = getPasswordInput();

    if (accountCredentials.find(acc_no) != accountCredentials.end() &&
        accountCredentials[acc_no] == password)
    {
        setColor(10);
        cout << "\n\tLogin Successful!";
        setColor(7);
        fordelay(100000000);
        menu_c();
    }
    else
    {
        setColor(12);
        cout << "\n\tInvalid Account Number or Password!";
        setColor(7);

        int choice;
        cout << "\n\n\t1. Try Again\n\t2. Main Menu\n\t0. Exit\n\tChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            customer();
        }
        else if (choice == 0)
        {
            close();
        }
        else
        {
            main();
        }
    }
}

int main()
{
    // Load credentials at startup
    loadCredentials();

    // Set random seed
    srand(time(0));

    // Display welcome screen
    displayLoadingScreen();
    displayTitle();

    setColor(14);
    cout << "\n\t\tWELCOME TO STATE BANK OF INDIA\n";
    setColor(7);
    cout << "\n\t1. Login";
    cout << "\n\t2. Instructions";
    cout << "\n\t0. Exit";
    cout << "\n\n\tEnter your choice: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        loginPage();
        int login_choice;
        cin >> login_choice;

        switch (login_choice)
        {
        case 1:
            employee();
            break;
        case 2:
            customer();
            break;
        case 3:
        {
            Bank bank;
            bank.read_data();
        }
        break;
        case 4:
            main();
            break;
        case 5:
            close();
            break;
        default:
            cout << "\n\tInvalid choice!";
            fordelay(100000000);
            main();
        }
        break;
    case 2:
        displayInstructions();
        main();
        break;
    case 0:
        close();
        break;
    default:
        cout << "\n\tInvalid choice!";
        fordelay(100000000);
        main();
    }

    return 0;
}