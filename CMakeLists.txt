cmake_minimum_required(VERSION 3.20)

project(PhoneStoreManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

add_executable(PhoneStoreManagement
        main.cpp

        gui/windows/LoginWindow.cpp
        gui/windows/LoginWindow.h
        gui/windows/LoginWindow.ui

        gui/windows/DashboardWindow.cpp
        gui/windows/DashboardWindow.h
        gui/windows/DashboardWindow.ui

        src/database/DatabaseConnection.cpp
        include/database/DatabaseConnection.h

        src/managers/DashboardManager.cpp
        include/managers/DashboardManager.h

        gui/widgets/ProductsPage.cpp
        gui/widgets/ProductsPage.h
        gui/widgets/ProductsPage.ui
)

target_link_libraries(PhoneStoreManagement
        PRIVATE Qt6::Widgets Qt6::Sql
)

target_include_directories(PhoneStoreManagement
        PRIVATE
        include
)