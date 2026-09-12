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
        gui/windows/loginwindow.cpp
        gui/windows/loginwindow.h
        gui/windows/loginwindow.ui
        gui/windows/dashboardwindow.cpp
        gui/windows/dashboardwindow.h
        gui/windows/dashboardwindow.ui
        src/database/DatabaseConnection.cpp
        include/database/DatabaseConnection.h
        src/managers/DashboardManager.cpp
        include/managers/DashboardManager.h
        gui/widgets/productspage.cpp
        gui/widgets/productspage.h
        gui/widgets/productspage.ui
)

target_link_libraries(PhoneStoreManagement
        PRIVATE Qt6::Widgets Qt6::Sql
)

target_include_directories(PhoneStoreManagement
        PRIVATE
        include
)