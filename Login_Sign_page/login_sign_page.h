#ifndef LOGIN_SIGN_PAGE_H
#define LOGIN_SIGN_PAGE_H

#include <QMainWindow>
#include <QFile>

#include "User.h"

namespace Ui {
class Login_Sign_page;
}

class Login_Sign_page : public QMainWindow
{
    Q_OBJECT

public:
    QList<User>  Users_list  ;
    QList<User> Admins_list ;

    explicit Login_Sign_page(QWidget *parent = nullptr);
    ~Login_Sign_page();

private slots:

    void on_SignUp_Bottom_clicked();

    void on_Login_button_clicked();

    void on_Login_To_Sign_button_clicked();

    void on_sign_to_login_button_clicked();

private:
    Ui::Login_Sign_page *ui;
};

#endif // LOGIN_SIGN_PAGE_H
