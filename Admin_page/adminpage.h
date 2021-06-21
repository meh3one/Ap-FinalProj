#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>

#include <User.h>
#include <Book.h>

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

    explicit
    AdminPage(QWidget *parent = nullptr);

    ~AdminPage();

private slots:
    void on_AddBook_botton_clicked();

private:
    Ui::AdminPage *ui;
};

#endif // ADMINPAGE_H
