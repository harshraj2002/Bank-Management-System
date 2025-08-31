# Bank Management Syste

A **console-based Bank Management System** implemented in C++ that allows users to manage bank accounts efficiently. This project demonstrates file handling, object-oriented programming, and basic banking operations.

## Features

- **Create Account:** Add a new bank account with account number, holder name, type (Current/Savings), and initial balance.
- **Deposit Money:** Deposit amount into a specific account.
- **Withdraw Money:** Withdraw amount from a specific account, ensuring minimum balance rules.
- **Balance Enquiry:** Display account details for a given account number.
- **Modify Account:** Update account holder name, type, or balance.
- **Delete Account:** Remove an account permanently from the system.
- **List All Accounts:** Show brief details of all accounts stored in the system.
- **Apply Interest:**  
  - Apply yearly interest to a specific savings account.  
  - Apply yearly interest to all savings accounts.
- **File Handling:** All account data is stored in `account.dat` using binary files for persistence.

## Minimum Balance Rules

- **Savings Account:** ₹500  
- **Current Account:** ₹1000  

Withdrawals below the minimum balance are not allowed. Initial deposits below the minimum balance are automatically set to the minimum.

## Yearly Interest

- **Savings Account:** 4% of the balance  
- **Current Account:** No interest applied  

Interest can be applied to a **single account** or **all savings accounts** at once.

## Technologies Used

- C++ (OOP concepts: Classes, Objects, Member Functions)  
- File handling (`ifstream`, `ofstream`, `fstream`)  
- Console I/O (`cin`, `cout`)  
- Control structures (`if`, `switch`, `loops`)  

## How to Run

1. **Clone or Download** this repository.
2. Open a C++ IDE (e.g., Code::Blocks, Visual Studio, Dev C++) or a terminal with g++ compiler.
3. Compile the `BankManagementSystem.cpp` file:

```bash
   g++ -o BankManagementSystem BankManagementSystem.cpp
````

4. Run the executable:

   ```bash
   ./BankManagementSystem      # Linux/Mac
   BankManagementSystem.exe    # Windows
   ```

5. Follow the **menu-driven interface** to perform banking operations.

## File Structure

```
BankManagementSystem/
├── BankManagementSystem.cpp   # Main source code
├── account.dat                # Binary file storing account data (created automatically)
└── README.md                  # Project documentation
```

## Notes

* All data is stored in `account.dat` using **binary file handling**.
* The system ensures **minimum balance** rules are maintained.
* The console interface provides **interactive prompts** for all banking operations.

## Author

**Harsh Raj**
