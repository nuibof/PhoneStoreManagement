cmake_minimum_required(VERSION 3.20)

project(PhoneStoreManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Svg)



add_executable(PhoneStoreManagement
        main.cpp
        gui/resources/resources.qrc

        gui/windows/LoginWindow.cpp
        gui/windows/LoginWindow.h
        gui/windows/LoginWindow.ui
        include/managers/AuthManager.h
        src/managers/AuthManager.cpp
        src/managers/EmployeeManager.cpp

        gui/windows/DashboardWindow.cpp
        gui/windows/DashboardWindow.h
        gui/windows/DashboardWindow.ui

        src/database/DatabaseConnection.cpp
        include/database/DatabaseConnection.h

        include/entities/Customer.h
        src/entities/Customer.cpp
        include/entities/Product.h
        src/entities/Product.cpp
        include/managers/ProductManager.h
        src/managers/ProductManager.cpp
        include/managers/CustomerManager.h
        src/managers/CustomerManager.cpp

        include/entities/ProductVariant.h
        src/entities/ProductVariant.cpp
        include/managers/VariantManager.h
        src/managers/VariantManager.cpp

        src/managers/DashboardManager.cpp
        include/managers/DashboardManager.h

        gui/widgets/ProductsPage.cpp
        gui/widgets/ProductsPage.h
        gui/widgets/ProductsPage.ui
        gui/widgets/customerspage.cpp
        gui/widgets/customerspage.h
        gui/widgets/customerspage.ui
        gui/widgets/staffpage.cpp
        gui/widgets/staffpage.h
        gui/widgets/staffpage.ui
        gui/widgets/orderspage.cpp
        gui/widgets/orderspage.h
        gui/widgets/orderspage.ui
        gui/widgets/invoicespage.cpp
        gui/widgets/invoicespage.h
        gui/widgets/invoicespage.ui

        gui/widgets/VariantsDialog.cpp
        gui/widgets/VariantsDialog.h
        gui/widgets/VariantsDialog.ui
        include/managers/EmployeeData.h
        gui/widgets/addstaffdialog.cpp
        gui/widgets/addstaffdialog.h
        gui/widgets/addstaffdialog.ui
)

target_link_libraries(PhoneStoreManagement
        PRIVATE Qt6::Widgets Qt6::Sql Qt6::Svg
)

target_include_directories(PhoneStoreManagement
        PRIVATE
        include
)