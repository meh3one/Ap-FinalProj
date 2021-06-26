#include "adminpage.h"
#include "ui_adminpage.h"

#include <string>

//forward declares
template <typename T >
void Save_File_to_List(QList<T> & List , QString FileAddress) ;

template <typename T >
void Save_List_To_File(QList<T> & List , QString FileAddress) ;

int FindBook_Index(QListWidgetItem *item ,QList<Book> & Book_List ) ;

//===========================================Constractor
AdminPage::AdminPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPage)
{
Save_File_to_List <User> (Users_list  , ".//UsersFile//Users.txt")   ;
Save_File_to_List <User> (Admins_list , ".//UsersFile//Admins.txt")  ;
Save_File_to_List <Book> (Book_List   , ".//BookFile//BookData.txt") ;


    ui->setupUi(this);


RefreshList() ;
HideAll()     ;

}

AdminPage::~AdminPage()
{
    Save_List_To_File <User> (Users_list  , ".//UsersFile//Users.txt")   ;
    Save_List_To_File <User> (Admins_list , ".//UsersFile//Admins.txt")  ;
    Save_List_To_File <Book> (Book_List   , ".//BookFile//BookData.txt") ;

    delete ui;
}

//===========================================Slots

void AdminPage::on_AddBook_widget_botton_clicked()
{
    HideAll()     ;
    this->ui->AddBook_DigCoppy->setVisible(false) ;
    this->ui->AddBook_Widget ->setVisible(true) ;
}

void AdminPage::on_AddBook_botton_clicked()
{

QString BookName        = this->ui->AddBook_Name_input->text() ;
QString Writer          = this->ui->AddBook_Writer_input->text() ;
QString Publisher       = this->ui->AddBook_Pub_input->text() ;
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
            qts << Text ;

        File.close() ;
        }

RefreshList() ;

}

void AdminPage::on_BookList_Widget_output_itemClicked(QListWidgetItem * item)
{    
Last_clicked_item =item ;
item=nullptr ;
Book TheBook = Book_List[ FindBook_Index( Last_clicked_item , Book_List) ] ;
Last_clicked_item = nullptr ;

this->ui->Read_Name_lable     -> setText("BookName  :  " + TheBook.getBookName ())  ;
this->ui->Read_Writer_lable   -> setText("TheWriter :  " + TheBook.getWriter   ())  ;
this->ui->Read_pub_lable      -> setText("ThePublisher : "+ TheBook.getPublisher())  ;
this->ui->Read_avalablecopies -> setText("copies       : " + QString::number ( TheBook.getAvailableCopies())  ) ;


//Read Book Text from file:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Check if the book has a file
QFile File(".//BookFile//" + TheBook.getBookFileName() ) ;
    File.open(QFile::Text | QFile::ReadOnly) ;
    QTextStream qts(&File) ;

this->ui->Read__output ->setText( qts .readAll() ) ;

    File.close() ;
//close the file


RefreshList() ;
HideAll()     ;
this->ui->Read_widget ->setVisible(true) ;
}

void AdminPage::on_BookList_Widget_output_itemDoubleClicked(QListWidgetItem *item)
{
Last_clicked_item = item ;
item =nullptr ;

HideAll()     ;

this->ui->Edit_name_lable -> setText( Last_clicked_item -> text()) ;

this->ui->BookEdit_Widget->setVisible (true) ;

}


void AdminPage::on_Deletethebook_clicked()
{

int TheBook_index = FindBook_Index( Last_clicked_item , Book_List) ;
Last_clicked_item = nullptr ;

QFile :: remove(".//BookFile//" + Book_List.at(TheBook_index).getBookFileName()) ;

Book_List.removeAt( TheBook_index ) ;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Print that the book was deleted

RefreshList() ;
HideAll() ;
}


//============================================Other Functions
void AdminPage::HideAll()
{

this->ui->AddBook_Widget->setVisible (false) ;
this->ui->BookEdit_Widget->setVisible(false) ;
this->ui->Read_widget ->setVisible   (false) ;

//one object must be seted visible after this function
//item index must be setted
}

void AdminPage::RefreshList()
{
ui->BookList_Widget_output->clear() ;                        //UpDates The List of Books
for(auto x : Book_List)
    this->ui->BookList_Widget_output->addItem( x.getBookName() + "-" + x.getWriter() ) ;

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


int FindBook_Index(QListWidgetItem *item ,QList<Book> & Book_List )
{

    QStringList qsl = item ->text().split('-') ;
    Book TheBook(qsl[0] , qsl[1] ) ;

    int index = Book_List.indexOf(TheBook) ; //finds where is the book with this name and writer

    return index ;
}





