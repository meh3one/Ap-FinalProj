#ifndef LOGIN_SIGN_PAGE_H
#define LOGIN_SIGN_PAGE_H

#include <QMainWindow>

namespace Ui {
class Login_Sign_page;
}

class Login_Sign_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login_Sign_page(QWidget *parent = nullptr);
    ~Login_Sign_page();

private:
    Ui::Login_Sign_page *ui;
};

#endif // LOGIN_SIGN_PAGE_H
