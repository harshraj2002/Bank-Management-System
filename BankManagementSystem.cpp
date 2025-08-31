#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

// Constants for minimum balances and interest rate
const int MIN_SAVINGS = 500;           // Minimum balance for savings account
const int MIN_CURRENT = 1000;          // Minimum balance for current account
const float SAVINGS_INTEREST_RATE = 0.04f; // Yearly interest rate for savings accounts

// BankAccount class to represent each account
class BankAccount {
    int accountNumber;
    char holderName[50];
    int balance;
    char accType; // C = Current, S = Savings
public:
    void openAccount();          // Create a new account
    void displayAccount() const; // Display full account details
    void updateAccount();        // Modify account details
    void depositMoney(int);      // Deposit amount
    void withdrawMoney(int);     // Withdraw amount
    void applyInterest();        // Apply yearly interest (for savings)
    void showBrief() const;      // Display brief account info

    int getAccNo() const;        // Return account number
    int getBalance() const;      // Return balance
    char getAccType() const;     // Return account type
};

// --- BankAccount Member Functions ---
// Create a new account
void BankAccount::openAccount() {
    system("CLS");
    cout << "\n\tEnter Account Number: "; cin >> accountNumber;
    cout << "\n\tEnter Account Holder Name: "; cin.ignore(); cin.getline(holderName,50);
    cout << "\n\tEnter Account Type (C/S): "; cin >> accType; accType = toupper(accType);
    cout << "\n\tEnter Initial Deposit Amount: "; cin >> balance;

    // Ensure minimum balance
    if ((accType=='S' && balance<MIN_SAVINGS) || (accType=='C' && balance<MIN_CURRENT)) {
        cout << "\n\t Minimum balance required! Setting to minimum.\n";
        balance = (accType=='S') ? MIN_SAVINGS : MIN_CURRENT;
    }
    cout << "\n\tAccount Created Successfully!\n";
}

// Display full account details
void BankAccount::displayAccount() const {
    cout << "\n\tAccount No.: " << accountNumber;
    cout << "\n\tHolder Name: " << holderName;
    cout << "\n\tAccount Type: " << accType;
    cout << "\n\tBalance: " << balance << endl;
}

// Modify account details
void BankAccount::updateAccount() {
    cout << "\n\tAccount No.: " << accountNumber;
    cout << "\n\tModify Holder Name: "; cin.ignore(); cin.getline(holderName,50);
    cout << "\n\tModify Account Type (C/S): "; cin >> accType; accType = toupper(accType);
    cout << "\n\tModify Balance: "; cin >> balance;
    // Ensure minimum balance
    if ((accType=='S' && balance<MIN_SAVINGS) || (accType=='C' && balance<MIN_CURRENT))
        balance = (accType=='S') ? MIN_SAVINGS : MIN_CURRENT;
}

// Deposit money
void BankAccount::depositMoney(int amt) { balance += amt; }

// Withdraw money
void BankAccount::withdrawMoney(int amt) { balance -= amt; }

// Apply yearly interest (only for savings accounts)
void BankAccount::applyInterest() {
    if(accType=='S') {
        int interest = static_cast<int>(balance * SAVINGS_INTEREST_RATE);
        balance += interest;
        cout << "\n\tInterest " << interest << " applied. New Balance: " << balance << endl;
    } else cout << "\n\tNo interest for current accounts.\n";
}

// Display brief account info (used in list)
void BankAccount::showBrief() const {
    cout << accountNumber << setw(12) << holderName << setw(8) << accType << setw(10) << balance << endl;
}

// Getter functions
int BankAccount::getAccNo() const { return accountNumber; }
int BankAccount::getBalance() const { return balance; }
char BankAccount::getAccType() const { return accType; }

// --- Function Prototypes ---
void createAccount();                   // Create and save a new account
void showAccount(int);                  // Show account details by account number
void modifyAccount(int);                // Modify account details by account number
void removeAccount(int);                // Delete an account
void showAllAccounts();                 // List all accounts
void depositOrWithdraw(int,int);        // Deposit or withdraw money
void applyInterestToAccount(int);       // Apply interest to a specific account
void applyInterestToAll();              // Apply interest to all savings accounts

// --- Main Function ---
int main() {
    char choice;
    int num;
    do {
        system("CLS");
        cout << "\n\n\t===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n\t1. NEW ACCOUNT";
        cout << "\n\t2. DEPOSIT AMOUNT";
        cout << "\n\t3. WITHDRAW AMOUNT";
        cout << "\n\t4. BALANCE ENQUIRY";
        cout << "\n\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t6. CLOSE AN ACCOUNT";
        cout << "\n\t7. MODIFY AN ACCOUNT";
        cout << "\n\t8. APPLY INTEREST TO ONE ACCOUNT";
        cout << "\n\t9. APPLY INTEREST TO ALL SAVINGS ACCOUNTS";
        cout << "\n\t10. EXIT";
        cout << "\n\tSelect Option (1-10): "; cin >> choice;

        switch(choice) {
            case '1': createAccount(); break;
            case '2': cout<<"\n\tEnter Account Number: "; cin>>num; depositOrWithdraw(num,1); break;
            case '3': cout<<"\n\tEnter Account Number: "; cin>>num; depositOrWithdraw(num,2); break;
            case '4': cout<<"\n\tEnter Account Number: "; cin>>num; showAccount(num); break;
            case '5': showAllAccounts(); break;
            case '6': cout<<"\n\tEnter Account Number: "; cin>>num; removeAccount(num); break;
            case '7': cout<<"\n\tEnter Account Number: "; cin>>num; modifyAccount(num); break;
            case '8': cout<<"\n\tEnter Account Number: "; cin>>num; applyInterestToAccount(num); break;
            case '9': applyInterestToAll(); break;
            case '10': cout<<"\n\tThank you for using the system!"; break;
            default: cout << "\a"; 
        }
        cin.ignore(); cin.get(); // Pause
    } while(choice != '10');
    return 0;
}

// --- Function Implementations ---

// Create and save a new account
void createAccount() {
    BankAccount acc;
    ofstream outFile("account.dat", ios::binary|ios::app);
    acc.openAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
    outFile.close();
}

// Show account details by account number
void showAccount(int n) {
    BankAccount acc; bool found=false;
    ifstream inFile("account.dat", ios::binary);
    if(!inFile) { cout << "File could not be opened!"; return; }
    while(inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if(acc.getAccNo()==n) { acc.displayAccount(); found=true; }
    }
    inFile.close();
    if(!found) cout<<"\n\tAccount not found!";
}

// Modify account details by account number
void modifyAccount(int n) {
    BankAccount acc; bool found=false;
    fstream file("account.dat", ios::binary|ios::in|ios::out);
    if(!file) { cout<<"File could not be opened!"; return; }
    while(!file.eof() && !found) {
        file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
        if(acc.getAccNo()==n) {
            acc.displayAccount();
            cout<<"\n\tEnter New Details\n"; acc.updateAccount();
            int pos=(-1)*static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            cout<<"\n\tRecord Updated!"; found=true;
        }
    }
    file.close();
    if(!found) cout<<"\n\tRecord not found!";
}

// Delete an account
void removeAccount(int n) {
    BankAccount acc;
    ifstream inFile("account.dat", ios::binary);
    ofstream outFile("Temp.dat", ios::binary);
    if(!inFile) { cout<<"File could not be opened!"; return; }
    while(inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if(acc.getAccNo()!=n) outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
    }
    inFile.close(); outFile.close();
    remove("account.dat"); rename("Temp.dat","account.dat");
    cout<<"\n\tRecord Deleted!";
}

// Display all accounts
void showAllAccounts() {
    BankAccount acc;
    ifstream inFile("account.dat", ios::binary);
    if(!inFile) { cout<<"File could not be opened!"; return; }
    cout<<"\n\tACCOUNT HOLDER LIST\n";
    cout<<"==============================================\n";
    cout<<"A/c No.    Name       Type     Balance\n";
    cout<<"==============================================\n";
    while(inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) acc.showBrief();
    inFile.close();
}

// Deposit or withdraw money
void depositOrWithdraw(int n,int option) {
    BankAccount acc; bool found=false; int amt;
    fstream file("account.dat", ios::binary|ios::in|ios::out);
    if(!file) { cout<<"File could not be opened!"; return; }
    while(!file.eof() && !found) {
        file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
        if(acc.getAccNo()==n) {
            acc.displayAccount();
            if(option==1){ cout<<"\n\tEnter amount to deposit: "; cin>>amt; acc.depositMoney(amt); }
            else if(option==2){ cout<<"\n\tEnter amount to withdraw: "; cin>>amt;
                int remaining = acc.getBalance()-amt;
                if((acc.getAccType()=='S' && remaining<MIN_SAVINGS) || (acc.getAccType()=='C' && remaining<MIN_CURRENT))
                    cout<<"\n\t Cannot withdraw! Minimum balance required.";
                else acc.withdrawMoney(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            cout<<"\n\tTransaction completed!"; found=true;
        }
    }
    file.close();
    if(!found) cout<<"\n\tAccount not found!";
}

// Apply interest to a specific account
void applyInterestToAccount(int n) {
    BankAccount acc; bool found=false;
    fstream file("account.dat", ios::binary|ios::in|ios::out);
    if(!file) { cout<<"File could not be opened!"; return; }
    while(!file.eof() && !found) {
        file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
        if(acc.getAccNo()==n) { 
            acc.applyInterest();
            int pos=(-1)*static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            found=true;
        }
    }
    file.close();
    if(!found) cout<<"\n\tAccount not found!";
}

// Apply interest to all savings accounts
void applyInterestToAll() {
    BankAccount acc; bool found=false;
    fstream file("account.dat", ios::binary|ios::in|ios::out);
    if(!file) { cout<<"File could not be opened!"; return; }
    while(file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if(acc.getAccType()=='S') {
            acc.applyInterest();
            int pos=(-1)*static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            file.seekg(0, ios::cur); // fix pointer for next read
            found=true;
        }
    }
    file.close();
    if(found) cout<<"\n\tInterest applied to all savings accounts!";
    else cout<<"\n\tNo savings accounts found!";
}

