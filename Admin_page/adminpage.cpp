#include "adminpage.h"
#include "ui_adminpage.h"


//forward declares
template <typename T >
void Save_File_to_List(QList<T> & List , QString FileAddress) ;

template <typename T >
void Save_List_To_File(QList<T> & List , QString FileAddress) ;;

//
AdminPage::AdminPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPage)
{
Save_File_to_List <User> (Users_list  , ".//UsersFile//Users.txt")   ;
Save_File_to_List <User> (Admins_list , ".//UsersFile//Admins.txt")  ;
Save_File_to_List <Book> (Book_List   , ".//BookFile//BookData.txt") ;


    ui->setupUi(this);

//this->ui ->label_2->setText("test1") ;

for(auto x : Book_List)                                                 //UpDates The List of Books
    this->ui->BookList_Widget_output->addItem( x.getBookName() ) ;

}

AdminPage::~AdminPage()
{
    Save_List_To_File <User> (Users_list  , ".//UsersFile//Users.txt")   ;
    Save_List_To_File <User> (Admins_list , ".//UsersFile//Admins.txt")  ;
    Save_List_To_File <Book> (Book_List   , ".//BookFile//BookData.txt") ;

    delete ui;
}
//===========================================Slots

void AdminPage::on_AddBook_botton_clicked()
{
QString BookName = this->ui->AddBook_Name_input->text() ;
QString Writer   = this->ui->AddBook_Writer_input->text() ;
QString Publisher = this->ui->AddBook_Pub_input->text() ;
QString AvailableCopies = this->ui->AddBook_copies_input->text() ;

QString Text = this->ui->AddBook_DigCoppy->toPlainText() ;

    if(BookName=="" || Writer=="" ||Publisher=="" || AvailableCopies=="" )
        {
        this->ui->AddBook__output->setText("Please Fill ALl Forms") ;
        return;
        }
    else if( Text == "" )
        {
        this->ui->AddBook_DigCoppy->setVisible(1) ;
        this->ui->AddBook__output->setText("please insert the digital coppy") ;
        return;
        }

    //++++++++++++++++++++++++++++++++++++++++check if available coppy is a valid number

    Book NewBook(BookName , Writer , Publisher, AvailableCopies.toInt()) ;


    if(Book_List.contains(NewBook))
        {
        this->ui->AddBook__output->setText("The Book Alredy exist") ;
        return;
        }
    else
        {
        Book_List.append(NewBook) ;

        this->ui->AddBook__output->setText("Book was added") ;

        QFile File(".//BookFile//"+ NewBook.getBookFileName() ) ;  //oppen file
            File.open(QFile::Text | QFile::WriteOnly) ;
            QTextStream qts(&File) ;
            qts <<Text ;

        File.close() ;
        }

}






//============================================Other Functions
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

