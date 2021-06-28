#include "login_sign_page.h"
#include "ui_login_sign_page.h"

#include <QFile>
#include <QTextStream>
#include <User.h>

#include <Admin_page/adminpage.h>

//==================================forward declares
template <typename T >
void Save_File_to_List( QList <T> & List , QString FileAddress) ;

template <typename T >
void Save_List_To_File( QList <T> & List , QString FileName);

void Gunre_List_To_File (QList<QString> & Gunre) ;

void Gunre_File_to_List(QList<QString> & Gunre) ;

bool UserIsAdmin(QString & name , QList<User> & AdminList) ;

bool UserName_IS_Taken(QString & name , QList<User> & UserList) ;
//=================================================
Login_Sign_page::Login_Sign_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login_Sign_page)
{

    Save_File_to_List <User> (Users_list  , ".//UsersFile//Users.txt"  ) ;
    Save_File_to_List <User> (Admins_list , ".//UsersFile//Admins.txt" ) ;
    Save_File_to_List <Book> (Book_List   , ".//BookFile//BookData.txt") ;
    Gunre_File_to_List(Gunres_List) ;


    this->Adpage = new AdminPage(0 , this ,& Users_list ,& Admins_list ,& Book_List , & Gunres_List) ;
    this->ROpage = new ReadOnly_Page(0,this,&Book_List ,&Gunres_List)   ;

    ui->setupUi(this);
    this->ui->SignUp_Widget->setVisible(false) ;
    this->ui->Output->setVisible(false)    ;
}


Login_Sign_page::~Login_Sign_page()
{
    Save_List_To_File <User> (Users_list  , ".//UsersFile//Users.txt")  ;
    Save_List_To_File <User> (Admins_list , ".//UsersFile//Admins.txt") ;
    Save_List_To_File <Book> (Book_List   , ".//BookFile//BookData.txt") ;
    Gunre_List_To_File (Gunres_List) ;
    delete ui;   
}

//=======================================================SLOTs :

void Login_Sign_page::on_SignUp_Bottom_clicked()
{
QString UserName =  this->ui->Sign_UserName_input->text()  ;
QString Pass1    =  this->ui->Sign_PassWord_input1->text() ;
QString pass2    =  this->ui->Sign_PassWord_input2->text() ;
QString Email    =  this->ui->Sign_Email_input->text()     ;


if(UserName =="" || Pass1=="" || pass2=="" ||Email=="" )
    {
    this->ui->Output->setVisible(true)    ;
    this->ui->Output->setText("Please Fill All Forms ") ;
    return;
    }
else if( ! this->ui->term_service_ratio->isChecked())
    {
    this->ui->Output->setVisible(true)    ;
    this->ui->Output->setText("You Have To Agree To Our Terms And servicies") ;
    return;
    }
else if( UserName_IS_Taken(UserName , Users_list ) )
    {
    this->ui->Output->setVisible(true)    ;
    this->ui->Output->setText("The Username is Taken ! ") ;
    return;
    }
else if(Pass1 !=pass2)
    {
    this->ui->Output->setVisible(true)    ;
    this->ui->Output->setText ("PassWords Dont Match ")  ;
    return;
    }

User A(UserName , Pass1 , Email ) ;

Users_list.append(A) ;

this->hide()    ;
this->ROpage->show() ;
}

void Login_Sign_page::on_Login_button_clicked()
{
QString UserName = this->ui->Login_UserName_input->text() ;
QString Pass = this->ui->Login_PassWord_input->text()     ;

User tmpUser(UserName ,Pass ) ;

    if(UserName=="" || Pass=="" )
        {
        this->ui->Output->setVisible(true)    ;
        this->ui->Output->setText("please fill all forms") ;
        }
    else if  (Admins_list.contains(tmpUser))
        {
        this->hide()    ;
        this->Adpage->show() ;
        }

    else if (Users_list.contains(tmpUser))
        {
        this->hide()         ;
        this->ROpage->show() ;
        }
    else
        {
        this->ui->Output->setVisible(true)    ;
        this->ui->Output->setText("Such Username Doesnt Exist") ;
        }
}

void Login_Sign_page::on_Login_To_Sign_button_clicked()
{
this->ui->Output->setText("")   ;
this->ui->Output->setVisible(false)    ;

this->ui->Login_Widget->setVisible(0)  ;
this->ui->SignUp_Widget->setVisible(1) ;
}

void Login_Sign_page::on_sign_to_login_button_clicked()
{
this->ui->Output->setText("")   ;
this->ui->Output->setVisible(false)    ;

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
QFile File (FileAddress) ;  //oppen file
    File.open(QFile::Text | QFile::ReadOnly) ;
    QTextStream qts(&File) ;
        while(! qts.atEnd())
        {
        T Tmp ;//temporary itrator
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


void Gunre_File_to_List(QList<QString> & Gunre)
{
QFile File (".//BookFile//Gunres.txt") ;  //oppen file
    File.open(QFile::Text | QFile::ReadOnly) ;
    QTextStream qts(&File) ;
        while(! qts.atEnd())
        {
        QString Tmp ;//temporary itrator
        qts >> Tmp   ;

        if(Tmp != "")
            Gunre.append(Tmp) ;
        }
}


void Gunre_List_To_File (QList<QString> & Gunre)
{
QFile File (".//BookFile//Gunres.txt") ;  //oppen file
    File.open(QFile::Text | QFile::WriteOnly) ;
    QTextStream qts(&File) ;


    for(auto x : Gunre)
        {
        qts << x  ;
        qts<<"\n" ;
        }

    File.close() ;

}


