# 📱 Phone Store Management

**C++ OOP Project — Phone Store Management System**

A desktop phone store management application developed as a university **Object-Oriented Programming (OOP)** project.

---

## 🛠️ Development Environment

| Tool            | Version                    |
| --------------- | -------------------------- |
| Language        | C++17                      |
| IDE             | Visual Studio 2022 / CLion |
| Build System    | CMake                      |
| GUI Framework   | Qt 6.11.2                  |
| Compiler        | MSVC 2022 64-bit           |
| Database        | PostgreSQL 18              |
| OS              | Windows                    |
| Version Control | Git / GitHub               |

> ⚠️ Team sử dụng **Qt 6.11.2 + MSVC 2022 64-bit** làm môi trường Qt thống nhất.
>
> Thành viên có thể sử dụng **Visual Studio 2022 hoặc CLion**, miễn là sử dụng compiler MSVC và bộ Qt tương ứng.

---

## ✨ Features

The system is designed to manage the main operations of a phone store:

* 🔐 Employee login and authentication
* 📱 Product management
* 🎨 Product variant management
* 🏷️ Category and brand management
* 👥 Customer management
* 👨‍💼 Employee / staff management
* 🛒 Order management
* 🧾 Invoice management
* 📦 Inventory and product stock management
* 🔎 Search and refresh data
* 🗄️ PostgreSQL database integration

---

## 🏗️ Application Architecture

The project follows a simple layered architecture:

```text
┌─────────────────────────┐
│          GUI            │
│       Qt 6 Widgets      │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│        Manager          │
│     Business Logic      │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│       Repository        │
│      Database CRUD      │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│       PostgreSQL        │
└─────────────────────────┘
```

### Main responsibilities

* **GUI**: Display data and receive user input.
* **Manager**: Handle business logic.
* **Repository**: Execute database queries and CRUD operations.
* **Entity**: Represent objects in the system.
* **Database**: Store persistent application data.

---

## 📂 Project Structure

```text
PhoneStoreManagement/
│
├── CMakeLists.txt
├── CMakePresets.json
├── README.md
├── .gitignore
├── main.cpp
│
├── include/
│   ├── entities/
│   ├── database/
│   ├── repositories/
│   └── managers/
│
├── src/
│   ├── entities/
│   ├── database/
│   ├── repositories/
│   └── managers/
│
├── gui/
│   ├── windows/
│   │   ├── LoginWindow.*
│   │   └── DashboardWindow.*
│   │
│   ├── widgets/
│   │   ├── ProductsPage.*
│   │   ├── CustomersPage.*
│   │   ├── StaffPage.*
│   │   ├── CategoriesPage.*
│   │   ├── OrdersPage.*
│   │   └── InvoicesPage.*
│   │
│   └── resources/
│
├── sql/
│   ├── 00_create_database.sql
│   ├── 01_schema.sql
│   ├── 02_seed.sql
│   └── queries.sql
│
└── tests/
```

---

# ⚙️ Setup

## 1. Clone Repository

```bash
git clone https://github.com/nuibof/PhoneStoreManagement.git
cd PhoneStoreManagement
```

---

## 2. Install Visual Studio 2022

Install **Visual Studio 2022** with the following workload:

```text
Desktop development with C++
```

Make sure the following components are available:

```text
MSVC v143 - VS 2022 C++ x64/x86 build tools
Windows 10/11 SDK
CMake tools for Windows
```

> 💡 Visual Studio is recommended for team members who are not using CLion.

---

## 3. Install CLion

Team members may also use **CLion**.

When using CLion, make sure the project is configured to use the **MSVC toolchain**, not MinGW.

```text
Compiler:
MSVC / Visual Studio 2022
```

---

## 4. Install Qt

Download the Qt Online Installer:

[Qt Online Installer](https://www.qt.io/download-qt-installer?utm_source=chatgpt.com)

Install:

```text
Qt 6.11.2
└── MSVC 2022 64-bit
```

Recommended installation path:

```text
C:\Qt\6.11.2\msvc2022_64
```

The Qt CMake directory is:

```text
C:\Qt\6.11.2\msvc2022_64\lib\cmake\Qt6
```

> ⚠️ **Do NOT install/use the MinGW version of Qt for this project.**
>
> The compiler and Qt build must match:
>
> ```text
> MSVC → Qt MSVC
> MinGW → Qt MinGW
> ```
>
> The project standard is **MSVC 2022 64-bit**.

---

## 5. Install PostgreSQL

Install **PostgreSQL 18**.

The application uses PostgreSQL to store:

* Products
* Product variants
* Categories
* Brands
* Customers
* Employees
* Orders
* Invoices
* Inventory data

Example installation path:

```text
C:\Program Files\PostgreSQL\18
```

---

# 🗄️ Database Setup

SQL scripts are located in:

```text
sql/
```

Execute them in the following order:

```text
00_create_database.sql
        ↓
01_schema.sql
        ↓
02_seed.sql
```

Default database:

```text
phone_store
```

### Main tables

```text
categories
brands
products
colors
storage_options
ram_options
product_variants
customers
employees
orders
order_details
invoices
invoice_details
```

---

# 🔌 Database Connection

The application uses Qt SQL with the PostgreSQL driver:

```text
QPSQL
```

Database connection settings are located in:

```text
src/database/DatabaseConnection.cpp
```

Example:

```cpp
db.setHostName("localhost");
db.setPort(5432);
db.setDatabaseName("phone_store");
db.setUserName("postgres");
db.setPassword("YOUR_PASSWORD");
```

Replace:

```text
YOUR_PASSWORD
```

with the PostgreSQL password configured on your machine.

> ⚠️ Do not commit personal database passwords to GitHub.

---

# 🔧 Configure Qt

## Visual Studio

If CMake cannot find Qt, configure:

```text
Qt6_DIR
```

to:

```text
C:\Qt\6.11.2\msvc2022_64\lib\cmake\Qt6
```

Then reconfigure CMake.

---

## CLion

Configure the project to use the MSVC toolchain.

Qt path:

```text
C:\Qt\6.11.2\msvc2022_64
```

Qt CMake path:

```text
C:\Qt\6.11.2\msvc2022_64\lib\cmake\Qt6
```

> 💡 Do not hardcode personal Qt paths into `CMakeLists.txt`.

---

# 🏗️ Build & Run

## Visual Studio 2022

Open the project folder:

```text
PhoneStoreManagement/
```

Visual Studio will detect the CMake project.

Select the appropriate configuration:

```text
Debug
x64
```

Then:

```text
Build → Build All
```

and run the application.

---

## CLion

Select the CMake configuration using the MSVC toolchain.

Recommended preset:

```text
windows-debug
```

Then:

```text
Build → Run
```

---

# 📱 Product & Variant Structure

Products and product variants are managed separately.

Example:

```text
iPhone 15
│
├── Black / 128GB
├── Black / 256GB
├── Blue / 128GB
└── Blue / 256GB
```

The `products` table stores general product information.

The `product_variants` table stores variant-specific information:

* Color
* Storage
* RAM
* SKU
* Cost price
* Selling price
* Stock quantity

---

# 👨‍💼 Employee / Staff

Employee information is stored in:

```text
employees
```

Main fields:

```text
employee_id
full_name
phone
email
position
username
password
created_at
```

The C++ OOP layer can represent different employee roles using inheritance:

```text
Employee
   │
   ├── Manager
   ├── SalesEmployee
   └── WarehouseEmployee
```

---

# 🖥️ GUI Structure

The main application flow:

```text
LoginWindow
     │
     ▼
DashboardWindow
     │
     ├── Dashboard
     ├── Products
     ├── Categories
     ├── Customers
     ├── Staff
     ├── Orders
     └── Invoices
```

The GUI is implemented using **Qt Widgets**.

---

# 🔀 Git Workflow

The project uses Git and GitHub for team collaboration.

Recommended branch structure:

```text
main
 │
 └── develop
       ├── feature/product
       ├── feature/employee
       ├── feature/order
       └── feature/invoice
```

### Before starting work

```bash
git pull
```

### After finishing work

```bash
git add .
git commit -m "Describe your changes"
git push
```

If the local branch is behind the remote:

```bash
git pull
```

before:

```bash
git push
```

> ❌ Do not use `git push --force` unless the team explicitly agrees.

---

# 🚫 Git Ignore

The following files/directories should not be committed:

```text
cmake-build-debug/
cmake-build-release/

CMakeUserPresets.json

.idea/
.vs/

runtime/
Debug/
Release/
x64/
```

Do not commit:

* Qt SDK
* Generated build files
* Local IDE configuration
* Deployed DLL files
* Personal database passwords

The following **should** be committed:

```text
CMakeLists.txt
CMakePresets.json
README.md

*.cpp
*.h
*.ui
*.qrc

sql/*.sql
```

---

# 📝 Development Notes

* Use **C++17**.
* Use **Qt 6.11.2**.
* Use **MSVC 2022 64-bit**.
* Use the **MSVC build of Qt**, not MinGW.
* Visual Studio and CLion can both be used.
* Keep Qt paths machine-specific.
* Keep database credentials local.
* Follow the project architecture when implementing modules.
* GUI should communicate with Managers instead of directly executing SQL.
* SQL queries should be handled inside Repositories.
* Avoid modifying another member's module without coordination.

---

# 👥 Team Modules

| Module           | Main Responsibility                              |
| ---------------- | ------------------------------------------------ |
| Product          | Category, Brand, Product, ProductVariant         |
| Employee         | Employee, authentication and staff               |
| Customer / Order | Customer, Order, OrderDetail                     |
| Invoice          | Invoice, InvoiceDetail                           |
| Integration      | Database, GUI core, CMake and system integration |

---

# 🎯 Project Goal

The goal of this project is to apply **Object-Oriented Programming principles** to build a functional phone store management system.

The project focuses on:

* Object-oriented design
* Encapsulation
* Inheritance
* Polymorphism
* Database integration
* GUI development
* CRUD operations
* Modular architecture
* Git-based team development

---

## 📌 Status

**Under Development 🚧**

Features and modules will be implemented progressively during the project development.
