#include <QApplication>
#include "gui/windows/LoginWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Open Login Window
    LoginWindow loginWindow;
    loginWindow.show();

    return app.exec();
}