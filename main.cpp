#include <QApplication>
#include "gui/windows/LoginWindow.h"
#include "include/database/DatabaseConnection.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // If the database connection fails, show an error message and exit the application
    if (!DatabaseConnection::connect()) {
        //show error message with ok button
        QMessageBox::critical(nullptr, "Lỗi kết nối", "Truy xuất cơ sở dữ liệu thất bại. Vui lòng kiểm tra kết nối hoặc liên hệ với quản trị viên.");
        return -1;
    }

    LoginWindow loginWindow;
    loginWindow.show();

    return app.exec();
}