#include "student.h"
#include <QDebug>

Student::Student( int number, QString name, int curriculum1, int curriculum2)
{
    this->number = number;
    this->name = name;
    this->curriculum1 = curriculum1;
    this->curriculum2 = curriculum2;

}

void Student::display()
{
    qDebug()<<number<<name<<curriculum1<<'\t'<<curriculum2;

}

QString Student::getname()
{
    return name;
}

int Student::getcurr1()
{
    return curriculum1;
}

int Student::getcurr2()
{
    return curriculum2;
}

