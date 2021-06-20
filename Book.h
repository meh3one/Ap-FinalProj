#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QList>

#include <QTextStream>
#include <QFile>

class Book
{
private:

    QString BookName        ;
    QString Writer          ;
    QString Publisher       ;
//  QString BookFileName    ;
    int     AvailableCopies ;

public :

    QList<QString> Gunre ;

Book (QString BookName="" , QString Writer="" , QString Publisher ="" ,int AvailableCopies = 0)
    {
    this-> BookName     = BookName ;
    this-> Writer       = Writer ;
    this-> Publisher    = Publisher ;
    this->AvailableCopies = AvailableCopies ;

//  this-> BookFileName = Writer +"-"+BookName +"\n";
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
return Writer +"-"+BookName+Publisher+".txt"  ;
}

int     getAvailableCopies() const
{
return AvailableCopies;
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
    if( this->BookName == A.BookName && this->Writer == A.Writer && this->Publisher == A.Publisher)
        return true;

    return false;
    }

void operator >> (QTextStream &qts)//write to file
{
qts<<this->BookName<<":"<<this->Writer<<":"<<this->Publisher<<":"<< this->AvailableCopies<<"|" ;

for(auto itr = this->Gunre.begin() ; itr !=this->Gunre.end() ; itr++)
    {
    if( *itr == "" )
        break;

    qts<<*itr   ;
    qts<<":"    ;
    }

qts<<"\n"  ;
}

void operator << (QTextStream &qts)//read from file
{
QStringList qsl  = qts.readLine().split('|') ;

QStringList qsl1 = qsl[0].split(':')  ;
QStringList qsl2 = qsl[1].split(':')  ;

this->BookName = qsl1[0] ;

this->Writer = qsl1[1]    ;
this->Publisher = qsl1[2] ;
this->AvailableCopies = qsl1[3].toInt() ;


for(int i=0 ; i < qsl2.size() ; i++ )
    if(qsl2[i] != "" )
        this->Gunre.append(qsl2[i]) ;

}

};

#endif // BOOK_H
