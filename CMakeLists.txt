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
        gui/UiStyle.h

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

        include/config/AppConfig.h
        src/config/AppConfig.cpp

        include/entities/FileExportable.h
        src/entities/FileExportable.cpp

        include/entities/Customer.h
        src/entities/Customer.cpp
        include/entities/Product.h
        src/entities/Product.cpp
        include/managers/ProductManager.h
        src/managers/ProductManager.cpp
        include/managers/CustomerManager.h
        src/managers/CustomerManager.cpp
        include/entities/Order.h
        src/entities/Order.cpp
        include/managers/OrderManager.h
        src/managers/OrderManager.cpp
        include/entities/Invoice.h
        src/entities/Invoice.cpp
        include/managers/InvoiceManager.h
        src/managers/InvoiceManager.cpp

        include/entities/ProductVariant.h
        src/entities/ProductVariant.cpp
        include/managers/VariantManager.h
        src/managers/VariantManager.cpp

        include/entities/ProductVariant.h
        src/entities/ProductVariant.cpp
        include/managers/VariantManager.h
        src/managers/VariantManager.cpp

        src/entities/Order.cpp
        src/entities/OrderDetail.cpp
        src/entities/Invoice.cpp
        src/entities/InvoiceDetail.cpp
        tests/OrderInvoiceTest.cpp
        tests/OrderInvoiceTest.h

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
        include/entities/OrderDetail.h
        src/entities/OrderDetail.cpp
        include/entities/Order.h
        src/entities/Order.cpp
        include/entities/InvoiceDetail.h
        src/entities/InvoiceDetail.cpp
        include/entities/Invoice.h
        src/entities/Invoice.cpp
        tests/OrderInvoiceTest.cpp
        tests/OrderInvoiceTest.h
)

target_link_libraries(PhoneStoreManagement
        PRIVATE Qt6::Widgets Qt6::Sql Qt6::Svg
)

target_include_directories(PhoneStoreManagement
        PRIVATE
        include
)

# Sao chep file cau hinh CSDL ra cung thu muc voi file thuc thi
add_custom_command(TARGET PhoneStoreManagement POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/config
        $<TARGET_FILE_DIR:PhoneStoreManagement>/config
)