#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>

#include <User.h>
#include <Book.h>

#include <QListWidgetItem>
#include <QList>



//==========================
namespace Ui {
class AdminPage;
}

class AdminPage : public QMainWindow
{
    Q_OBJECT

public:
    QList<User>  * Users_list   ;
    QList<User>  * Admins_list  ;
    QList<Book>  * Book_List    ;
    QList<QString>  * Gunres_List  ;

    QListWidgetItem * Last_clicked_item ;
    QString Search_input ;

    QWidget  * LSpage ;

    explicit
    AdminPage(QWidget *parent = nullptr , QWidget *LSpage=nullptr ,QList<User>  * Users_list =nullptr,
              QList<User>  * Admins_list = nullptr,QList<Book>  * Book_List  =nullptr , QList<QString> * Gunres_List = nullptr);

    ~AdminPage()       ;

    void HideAll()     ;

    void RefreshList() ;

private slots:
    void on_AddBook_botton_clicked();

    void on_BookList_Widget_output_itemClicked(QListWidgetItem *item);

    void on_BookList_Widget_output_itemDoubleClicked(QListWidgetItem *item);

    void on_Deletethebook_clicked();

    void on_AddBook_widget_botton_clicked();

    void on_Edit_button_clicked();

    void on_Gunre_commit_button_clicked();

    void on_Search_bar_input_textChanged(const QString &arg1);

    void on_Lend_botton_clicked();

    void on_retrevebotton_clicked();

    void on_Gunre_show_button_clicked();

    void on_Add_Gunre_botton_clicked();

    void on_GunreList_widget_output_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::AdminPage *ui;

};

#endif // ADMINPAGE_H
