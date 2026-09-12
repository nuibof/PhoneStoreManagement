# 📱 Phone Store Management

C++ OOP Project — Phone Store Management System.

## 🛠️ Development Environment

| Tool         | Version      |
| ------------ | ------------ |
| C++          | C++17        |
| IDE          | CLion        |
| Build System | CMake        |
| GUI          | Qt 6.11.2    |
| Compiler     | MinGW 64-bit |
| OS           | Windows      |

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
│   ├── widgets/
│   └── resources/
│
├── sql/
└── tests/
```

---

## ⚙️ Setup

### 1. Clone Repository

```bash
git clone https://github.com/nuibof/PhoneStoreManagement/
cd PhoneStoreManagement
```

### 2. Install CLion

Sử dụng **CLion** để mở và phát triển project.

### 3. Install Qt

Tải Qt Online Installer:

https://www.qt.io/download-qt-installer

Cài đặt:

```text
Qt 6.11.2
└── MinGW 64-bit
```

> ⚠️ Team sử dụng cùng **Qt 6.11.2 + MinGW 64-bit** để đảm bảo môi trường thống nhất.

### 4. Open Project

Mở thư mục `PhoneStoreManagement` bằng CLion.

CLion sẽ tự nhận:

```text
CMakeLists.txt
CMakePresets.json
```

### 5. Configure Qt

Nếu CLion không tự tìm thấy Qt, cấu hình `Qt6_DIR` tới:

```text
<Qt-installation-path>/mingw_64/lib/cmake/Qt6
```

Ví dụ:

```text
C:\Qt\6.11.2\mingw_64\lib\cmake\Qt6
```

> 💡 Đường dẫn Qt có thể khác nhau trên từng máy. Không commit đường dẫn Qt cá nhân vào Git.

### 6. Build & Run

Chọn CMake preset:

```text
windows-debug
```

Sau đó:

```text
Build → Run
```

---

## 📌 Notes

* Không commit `cmake-build-*`.
* Không commit `CMakeUserPresets.json`.
* Không đưa Qt SDK vào repository.
* Sử dụng **C++17**.
* Sử dụng **Qt 6.11.2 + MinGW 64-bit**.
