#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(500, 350);
    window.setWindowTitle("Phone Store Management");
    window.show();

    return app.exec();
}