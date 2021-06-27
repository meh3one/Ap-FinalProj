#include "Login_Sign_page/login_sign_page.h"
#include "Admin_page/adminpage.h"

#include <QApplication>

#include <direct.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    _mkdir(".\\BookFile") ;
    _mkdir(".\\UsersFile") ;

    Login_Sign_page w;
    w.show();

//    AdminPage ap ;
//    ap.show() ;

    return a.exec();
}
