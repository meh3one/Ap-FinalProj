#include "login_sign_page.h"
#include "ui_login_sign_page.h"

#include <QFile>
#include <QTextStream>
#include <User.h>


//==================================forward declares
template <typename T >
void Save_File_to_List( QList <T> & List , QString FileAddress) ;

template <typename T >
void Save_List_To_File( QList <T> & List , QString FileName);

bool UserIsAdmin(QString & name , QList<User> & AdminList) ;

bool UserName_IS_Taken(QString & name , QList<User> & UserList) ;
//=================================================
Login_Sign_page::Login_Sign_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login_Sign_page)
{
    Save_File_to_List <User> (Users_list  , ".//UsersFile//Users.txt")  ;
    Save_File_to_List <User> (Admins_list , ".//UsersFile//Admins.txt") ;

    ui->setupUi(this);
    this->ui->SignUp_Widget->hide() ;
}

Login_Sign_page::~Login_Sign_page()
{
    Save_List_To_File <User> (Users_list  , ".//UsersFile//Users.txt")  ;
    Save_List_To_File <User> (Admins_list , ".//UsersFile//Admins.txt") ;
    delete ui;   
}
//===============================================SLOTs :
void Login_Sign_page::on_SignUp_Bottom_clicked()
{
QString UserName =  this->ui->Sign_UserName_input->text()  ;
QString Pass1    =  this->ui->Sign_PassWord_input1->text() ;
QString pass2    =  this->ui->Sign_PassWord_input2->text() ;
QString Email    =  this->ui->Sign_Email_input->text()     ;


if(UserName =="" || Pass1=="" || pass2=="" ||Email=="" )
    {
    this->ui->Output->setText("Please Fill All Forms ") ;
    return;
    }
else if( ! this->ui->term_service_ratio->isChecked())
    {
    this->ui->Output->setText("You Have To Agree To Our Terms And servicies") ;
    return;
    }
else if( UserName_IS_Taken(UserName , Users_list ) )
    {
    this->ui->Output->setText("The Username is Taken ! ") ;
    return;
    }
else if(Pass1 !=pass2)
    {
    this->ui->Output->setText ("PassWords Dont Match ")  ;
    return;
    }

User A(UserName , Pass1 , Email ) ;

Users_list.append(A) ;

//+++++++++++++++++++++++++++++++++++++++++++Go to Read Only mode
}

void Login_Sign_page::on_Login_button_clicked()
{
QString UserName = this->ui->Login_UserName_input->text() ;
QString Pass = this->ui->Login_PassWord_input->text()     ;

User tmpUser(UserName ,Pass ) ;

    if(UserName=="" || Pass=="" )
        this->ui->Output->setText("please fill all forms") ;

    else if  (Admins_list.contains(tmpUser))
        this->ui->Output->setText("Going to admin page") ;

    else if (Users_list.contains(tmpUser))
        this->ui->Output->setText("going to user page") ;
    else
        this->ui->Output->setText("Such Username Doesnt Exist") ;

}

void Login_Sign_page::on_Login_To_Sign_button_clicked()
{
this->ui->Login_Widget->setVisible(0) ;
this->ui->SignUp_Widget->setVisible(1) ;
}

void Login_Sign_page::on_sign_to_login_button_clicked()
{
this->ui->Login_Widget->setVisible(1) ;
this->ui->SignUp_Widget->setVisible(0) ;
}

//======================================================other funcs
bool UserName_IS_Taken(QString & name , QList<User> & UserList)
{
    for(auto & x : UserList)
        if(x.get_User_name() == name)
            return true;

    return false;
}

bool UserIsAdmin(QString & name , QList<User> & AdminList)
{
    for(auto & x : AdminList)
        if(x.get_User_name() == name)
            return true;

    return false;
}


template <typename T >
void Save_File_to_List(QList<T> & List , QString FileAddress)
{
T Tmp ;//temporary itrator
QFile File (FileAddress) ;  //oppen file
    File.open(QFile::Text | QFile::ReadOnly) ;
    QTextStream qts(&File) ;
        while(! qts.atEnd())
        {
        Tmp << qts  ;
        List.append(Tmp) ;
        }
}


template <typename T >
void Save_List_To_File(QList<T> & List , QString FileAddress)
{
    QFile File(FileAddress) ;  //oppen file
        File.open(QFile::Text | QFile::WriteOnly) ;
        QTextStream qts(&File) ;

        for( auto itr =List.begin();itr !=List.end(); itr++ )
            *itr >> qts ;

        File.close() ;

}





