#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>

#include <User.h>
#include <Book.h>

#include <QListWidgetItem>

namespace Ui {
class AdminPage;
}

class AdminPage : public QMainWindow
{
    Q_OBJECT

public:
    QList<User>  Users_list   ;
    QList<User>  Admins_list  ;
    QList<Book>  Book_List    ;

    QListWidgetItem * Last_clicked_item ;

    QString Search_input ;
    explicit
    AdminPage(QWidget *parent = nullptr);

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

private:
    Ui::AdminPage *ui;
};

#endif // ADMINPAGE_H
