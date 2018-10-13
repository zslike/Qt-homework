#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include "student.h"
using namespace std;

void foreachst(QList <Student> information);

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();

    QList <Student> information;  //定义容器存放学生对象

    Student student1 (1403130329, "鲁智深", 80, 82);
    Student student2 (1403140101, " 林冲 ", 82, 76);
    Student student3 (1403140102, " 宋江 ", 76, 85);
    Student student4 (1403140103, " 武松 ", 88, 80);

    information<<student1<<student2<<student3<<student4;  //加入学生数据
    foreachst(information);

    qDebug()<<"--------按照姓名排序--------";
    std::sort(information.begin(), information.end(), [](Student s1, Student s2)  {return s1.getname()>s2.getname();});
    foreachst(information);  //用匿名函数自定义比较方法

    qDebug()<<"--------按照课程1排序--------";
    std::sort(information.begin(), information.end(), [](Student s1, Student s2)  {return s1.getcurr1()>s2.getcurr1();});
    foreachst(information);

    qDebug()<<"--------按照课程2排序--------";
   std::sort(information.begin(), information.end(), [](Student s1, Student s2)  {return s1.getcurr2()>s2.getcurr2();});
    foreachst(information);


}

void foreachst(QList <Student> information)
{
    // 循环遍历容器学生信息

    qDebug()<<"   学号"<<"     姓名"<<"课程1"<<"课程2";
    foreach (Student infor, information) {

        infor.display(); //调用类方法输出学生信息
    };
    qDebug()<<"\n";
}


