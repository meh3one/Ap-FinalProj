#ifndef READONLY_PAGE_H
#define READONLY_PAGE_H

#include <QMainWindow>

#include <QListWidgetItem>

#include <Book.h>

namespace Ui {
class ReadOnly_Page;
}

class ReadOnly_Page : public QMainWindow
{
    Q_OBJECT

public:
    QList<Book>     * Book_List    ;
    QList<QString>  * Gunres_List  ;

    QListWidgetItem * Last_clicked_item ;
    QString Search_input ;

    QWidget  * LSpage ;

    void HideAll() ;
    void RefreshList() ;


    explicit ReadOnly_Page ( QWidget *parent = nullptr , QWidget *LSpage=nullptr ,
                             QList<Book>* Book_List=nullptr , QList<QString> * Gunres_List = nullptr);

    ~ReadOnly_Page();


private slots:
    void on_Gunre_show_button_clicked();

    void on_GunreList_widget_output_itemClicked(QListWidgetItem *item) ;

    void on_Search_bar_input_textChanged(const QString &arg1) ;

    void on_BookList_Widget_output_itemClicked(QListWidgetItem * item) ;

private:
    Ui::ReadOnly_Page *ui;

};

#endif // READONLY_PAGE_H
