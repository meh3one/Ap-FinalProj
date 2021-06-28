#include "readonly_page.h"
#include "ui_readonly_page.h"



ReadOnly_Page::ReadOnly_Page( QWidget *parent  , QWidget *LSpage ,
                              QList<Book>* Book_List, QList<QString> * Gunres_List ) :
    QMainWindow(parent),
    ui(new Ui::ReadOnly_Page)
{
    this->LSpage      = LSpage      ;
    this->Book_List   = Book_List   ;
    this->Gunres_List = Gunres_List ;

    ui->setupUi(this);


    HideAll() ;
    RefreshList() ;
}

ReadOnly_Page::~ReadOnly_Page()
{
    delete ui;
}

//============================Forwars declare
int FindBook_Index(QListWidgetItem *item ,QList<Book> * Book_List ) ;

bool Book_be_shown(Book & x  , QString & Search_input ) ;
//=========================================slots


void ReadOnly_Page::on_BookList_Widget_output_itemClicked(QListWidgetItem * item)
{
Last_clicked_item =item ;
item=nullptr ;
Book TheBook = (*Book_List)[ FindBook_Index( Last_clicked_item , Book_List) ] ;
Last_clicked_item = nullptr ;

this->ui->Read_Name_lable         -> setText("BookName  :  " + TheBook.getBookName ())  ;
this->ui->Read_Writer_lable       -> setText("TheWriter :  " + TheBook.getWriter   ())  ;
this->ui->Read_pub_lable          -> setText("ThePublisher : "+ TheBook.getPublisher())  ;
this->ui->Read_avalablecopies     -> setText("copies       : " + QString::number ( TheBook.getAvailableCopies())  ) ;
this->ui->Read_lendedCopies_lable -> setText("Lended copies: " + QString::number (TheBook.ListOfLended.size  ())  ) ;

QString Gunres ="Gunres : " ;

for(auto x : TheBook.Gunre )
    Gunres = Gunres + x + " - " ;

this->ui->Read_Gunre_lable->setText(Gunres) ;


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

void ReadOnly_Page::on_Search_bar_input_textChanged(const QString &arg1)
{
Search_input = arg1 ;
RefreshList() ;
}

void ReadOnly_Page::on_Gunre_show_button_clicked()
{
HideAll() ;
this->ui->Gunre_output_widget ->setVisible(true) ;


this->ui->GunreList_widget_output->clear() ;
    for(auto x : *Gunres_List)
        this->ui->GunreList_widget_output->addItem(x) ;

}

void ReadOnly_Page::on_GunreList_widget_output_itemClicked(QListWidgetItem *item)
{
this->ui->Search_bar_input->setText(item->text()) ;
RefreshList() ;
}


//==============================================other funcs

void ReadOnly_Page::HideAll()
{

this->ui-> Read_widget         -> setVisible (false) ;
this->ui-> Gunre_output_widget -> setVisible (false) ;


//one object must be seted visible after this function
}

void ReadOnly_Page::RefreshList()
{
ui->BookList_Widget_output->clear() ;                        //UpDates The List of Books
for(auto x : *Book_List)
    {
    if( Book_be_shown(x , Search_input) )
        this->ui->BookList_Widget_output->addItem( x.getBookName() + "-" + x.getWriter() ) ;
    }
}

void ReadOnly_Page::on_pushButton_clicked()
{
this ->hide() ;

this->LSpage ->show() ;
}
