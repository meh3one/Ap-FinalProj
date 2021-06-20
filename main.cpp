#include "Login_Sign_page/login_sign_page.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login_Sign_page w;
    w.show();

    return a.exec();
}
