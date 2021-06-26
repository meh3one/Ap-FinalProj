#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QList>

#include <QTextStream>
#include <QFile>

#include <User.h>

class Book
{
private:

    QString BookName        ;
    QString Writer          ;
    QString Publisher       ;
//  QString BookFileName    ;
    int     AvailableCopies ;


public :
    QList<QString> ListOfLended ;
    QList<QString> Gunre ;

Book (QString BookName="" , QString Writer="" , QString Publisher ="" ,int AvailableCopies = 0)
    {
    this-> BookName     = BookName ;
    this-> Writer       = Writer ;
    this-> Publisher    = Publisher ;
    this-> AvailableCopies = AvailableCopies ;

//  BookFileName = Writer-BookName.txt  ;
    }

//getters :

QString getBookName() const
    {
    return BookName;
    }

QString getWriter() const
    {
    return Writer;
    }

QString getPublisher() const
    {
    return Publisher;
    }

QString getBookFileName() const
    {
    return Writer +"-"+BookName+"-"+Publisher+".txt"  ;
    }

int     getAvailableCopies()
    {
    return AvailableCopies ;
    }

//setters :

void setWriter(const QString &value)
    {
    Writer = value;
    }

void setPublisher(const QString &value)
    {
    Publisher = value;
    }

void setBookName(const QString &value)
    {
    BookName = value;
    }

void setAvailableCopies(int copies)
    {
    AvailableCopies = copies;
    }

bool operator== (Book A)
    {
    if( this->BookName == A.BookName && this->Writer == A.Writer )
        return true;

    return false;
    }

void operator >> (QTextStream &qts)//write to file
{
//====How it will Look in file
//BookName:Writer:Publisher:AvailableCopies|Gunre1:Gunre2 ... |Lended1:lended2 ...

qts<<this->BookName<<":"<<this->Writer<<":"<<this->Publisher<<":"<< this->AvailableCopies<<"|" ;

for(auto x : Gunre)
    if( x != "" )
    {
    qts<< x   ;
    qts<<":"    ;
    }

qts<<"|" ;

for(auto x : ListOfLended)
    if(x !="")
    {
        qts << x ;
        qts << ":" ;
    }

qts<<"\n"  ;
}

void operator << (QTextStream &qts)//read from file
{
//====How it will Look in file
//BookName:Writer:Publisher:AvailableCopies|Gunre1:Gunre2 ... |Lended1:lended2 ...

QStringList qsl  = qts.readLine().split('|') ;

QStringList qsl1       = qsl[0].split(':')  ;



this->BookName        = qsl1[0] ;
this->Writer          = qsl1[1]    ;
this->Publisher       = qsl1[2] ;
this->AvailableCopies = qsl1[3].toInt() ;


if(qsl[1] != "")
    {
    QStringList Gunre_qsl  = qsl[1].split(':')  ;
    for(auto x :Gunre_qsl)
        if(x != "")
            this->Gunre.append(x) ;
    }

if(qsl[2] != "")
    {
    QStringList Lended_qsl = qsl[2].split(':')  ;
    for(auto x : Lended_qsl)
        if(x != "")
            this->ListOfLended.append(x) ;
    }
}

};

#endif // BOOK_H
