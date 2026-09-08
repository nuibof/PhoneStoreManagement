cmake_minimum_required(VERSION 3.20)

project(PhoneStoreManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(PhoneStoreManagement
        main.cpp
)

target_link_libraries(PhoneStoreManagement
        PRIVATE Qt6::Widgets
)