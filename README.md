
# 📘 Enhanced Bank Record System

A mini C++ project aimed at simulating a fully functional bank system with account management, secure login, transaction tracking, and customer service features. This project represents a complete overhaul of the original legacy codebase in `New_Bank_Record.cpp`, culminating in a modern, modular, and user-friendly version in `BankSystem.cpp`.

A demo video and some screenshots are attached for reference.

# 🤝Contributors
<ol type='I'>
<li>Dhruvam Panchal - 202401415</li>
<li>Dwij Patel - 202401418</li>
<li>Shubh Patel - 202401478</li>
<li>Yashraj Solanki - 202401481</li>
<br>
<hr>

## 🚀 Project Overview

The **Bank Record System** is a command-line interface (CLI) application that enables banking operations such as:

- Creating/modifying/searching bank accounts
- Deposits, withdrawals, fund transfers
- Managing customer and employee logins
- Service request queuing
- Transaction history tracking

This project demonstrates best practices in object-oriented design, file handling, data structures, and UI improvement in C++.

---

## 🔄 Major Changes from Legacy (`New_Bank_Record.cpp`) to Upgraded (`BankSystem.cpp`)

| Feature                         | Legacy (`New_Bank_Record.cpp`)                 | Upgraded (`BankSystem.cpp`)                                  |
|-------------------------------|------------------------------------------------|-------------------------------------------------------------|
| **UI/UX**                     | Monochrome CLI, static colors, limited options | Color-coded UI, structured menus, improved instructions     |
| **Modularization**            | Flat structure, spaghetti code                 | Fully OOP with encapsulated classes and functions           |
| **Data Structures**           | Arrays, flat file parsing                      | `BST`, `map`, `vector`, `stack`, `queue`                    |
| **Security**                  | Hardcoded login credentials                    | Password masking, hashed credentials (extension-ready)      |
| **Performance**               | Line-by-line CSV rewrites                      | In-memory BST with efficient lookups and updates            |
| **Data Persistence**          | Fragile CSV management                         | Cleaner CSV handling, separate credential files             |
| **Customer Service**          | Not implemented                                | Implemented via service queue (FIFO)                        |
| **Transaction History**       | Absent                                         | Supported via vector and stack tracking                     |
| **Code Readability**          | Poor                                           | Highly readable, maintainable structure                     |

---

## 🧠 In-Depth Analysis

### 💾 Data Structures Used

| Structure       | Purpose                                                                 |
|----------------|-------------------------------------------------------------------------|
| `map<string, string>` | Stores account & employee login credentials (hash map for O(1) lookup) |
| `vector<string>` | Maintains transaction history (append-only log)                     |
| `stack<string>`  | Tracks recent transactions for LIFO viewing                          |
| `queue<string>`  | Handles customer service requests (FIFO discipline)                  |
| `BST (Binary Search Tree)` | Core storage of account records for O(log n) search, insert, modify |

#### Binary Search Tree (BST) for Account Records
- **Why BST?** Efficient searching, in-order display, and scalability for large datasets.
- **Tradeoff:** Requires memory and additional code complexity compared to flat files.
- **Operations Implemented:**
  - `insert()`
  - `search()`
  - `modify()`
  - `inorder()` traversal for listing accounts

---

## 🎯 Feature Highlights

- **Account Creation & Modification**
  - Fully guided input
  - Duplicate checks
  - Password protection

- **Employee and Customer Roles**
  - Separate login interfaces
  - Role-based menus and features

- **Transaction Management**
  - Deposit, withdraw, and fund transfer
  - Balance update logic with timestamp logging

- **Transaction History**
  - Maintained using both vector and stack
  - Last 10 transactions available to user

- **Customer Service Queue**
  - Request submission
  - FIFO processing by employees
  - Service type categorization

- **UI & Experience**
  - Color-coded CLI using `SetConsoleTextAttribute()`
  - Consistent screen clearing and user prompts
  - Loading screen and instruction screens enhance user flow

---

## ⚖️ Tradeoffs Made

| Decision                          | Tradeoff Justification                                          |
|----------------------------------|-----------------------------------------------------------------|
| BST over flat file search        | Better performance, but increased code complexity               |
| Using console-based UI           | Simplified deployment, less interactive than GUI                |
| CSV storage instead of DB        | Lightweight, portable, but less robust                         |
| Windows-only `conio.h` + WinAPI  | Simplified development, but not cross-platform                  |
| No real password encryption      | Left open for extension; current approach masks password input  |

---

## 📁 Project Structure

```
Bank-Management-System/
├── BankSystem.cpp          # Final upgraded implementation
├── New_Bank_Record.cpp     # Original legacy code
├── Account_info.csv        # Stores user credentials
├── Employee_info.csv       # Stores employee credentials
├── Bank_Record.csv         # Stores all account data
└── README.md               # This file
```

---

## 📌 Future Enhancements

- Password encryption with hashing
- Multi-platform support (remove WinAPI/conio dependency)
- GUI version using Qt or web frontend
- Admin dashboard for analytics

---

## 📄 License

This project is open-source and free to use under the MIT License.
<hr>
<img src="BankSystem_1.jpg">
<hr>
<img src="BankSystem_2.jpg">
<hr>
<img src="BankSystem_3.jpg">
<hr>