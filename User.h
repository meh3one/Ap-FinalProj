#ifndef USER_H
#define USER_H

#include <QString>

#include <QList>

#include <QTextStream>
#include <QFile>

using namespace std ;


class User
{
private:

    QString User_name ;
    long long   User_pass_hash ;
    QString Email ;

public:
    User(QString User_name ="" , string   User_pass ="" ,QString Email ="" )
    {
    this->User_name = User_name ;
    this->User_pass_hash = std::hash<std::string>{}(User_pass); //saves the password hash
    this->Email =Email ;
    }

//getters :

QString   get_User_name()
    {
        return this->User_name;
    }

long long get_User_pass_hash()
    {
        return this->User_pass_hash ;
    }

QString get_User_email()
    {
    return this->Email ;
    }

//setters :

void  set_User_name(QString User_name)
    {
    this->User_name =User_name ;
    }

void  set_User_pass(string User_pass)
    {
    this->User_pass_hash = std::hash<std::string>{}(User_pass);
    }

void  set_user_pass_hash (long long hash)
    {
    this->User_pass_hash =hash ;
    }

bool operator == (User tmp)
{
    if(this->User_name ==tmp.User_name && this->User_pass_hash == tmp.User_pass_hash )
        return true;
    return false;
}

void  operator<< (QTextStream &qts)
{
    QStringList qsl = qts.readLine().split(':') ;

    this->User_name = qsl[0]                        ;
    this->User_pass_hash = qsl[1].toLongLong()      ;
    this->Email = qsl[2]                            ;
}

void operator>> (QTextStream &qts)
{
    qts<<User_name<<":"<<User_pass_hash<<":"<<Email<<"\n" ;
}

};


#endif // USER_H
