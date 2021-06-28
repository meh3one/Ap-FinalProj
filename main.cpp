/********************************************************************
* Git repository ::
*
* special tnx to Mat_Mot && kianmjl  for Guildness
*
* Done By "Meh3one" As the Finale Project For Advanced Programing
* استاد Mahdavi         University of Isfahan   7/4/1400 - 28/6/2020
*
* This is a Library management system with GUI
*
*
* Sources :
*
* login page : https://unsplash.com/@matt__feeney
* Admin Page : https://unsplash.com/@henry_be
*
***********************************************************************/


#include "Login_Sign_page/login_sign_page.h"

#include <QApplication>

#include <direct.h>

int main(int argc, char *argv[])
{
QApplication a(argc, argv);

_mkdir(".\\BookFile") ;
_mkdir(".\\UsersFile") ;

    Login_Sign_page w;

        w.show();

return a.exec();
}
