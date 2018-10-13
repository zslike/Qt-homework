#ifndef STUDENT_H
#define STUDENT_H
#include <QString>


class Student
{
public:
    Student(int number, QString name, int curriculum1, int curriculum2);

private:
    int number;
    QString name;
    int curriculum1;
    int curriculum2;

public:
    void display();
    QString getname();
    int getcurr1();
    int getcurr2();

};
#endif // STUDENT_H
