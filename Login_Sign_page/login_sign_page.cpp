#include "login_sign_page.h"
#include "ui_login_sign_page.h"

Login_Sign_page::Login_Sign_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login_Sign_page)
{
    ui->setupUi(this);
}

Login_Sign_page::~Login_Sign_page()
{
    delete ui;
}
