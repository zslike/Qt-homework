#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFile>

//定义命名空间SK，将文本文件划分为不同的列
namespace SK {
enum SortKind{
    col01    =   0x00000001<<0,         //!< 第1列
    col02    =   0x00000001<<1,         //!< 第2列
    col03    =   0x00000001<<2,         //!< 第3列
    col04    =   0x00000001<<3,         //!< 第4列
    col05    =   0x00000001<<4,         //!< 第5列
    col06    =   0x00000001<<5,         //!< 第6列
    col07    =   0x00000001<<6,         //!< 第7列
    col08    =   0x00000001<<7,         //!< 第8列
    col09    =   0x00000001<<8,         //!< 第9列
    col10    =   0x00000001<<9,         //!< 第10列
    col11    =   0x00000001<<10,        //!< 第11列
    col12    =   0x00000001<<11,        //!< 第12列
    col13    =   0x00000001<<12,        //!< 第13列
    col14    =   0x00000001<<13,        //!< 第14列
    col15    =   0x00000001<<14,        //!< 第15列
    col16    =   0x00000001<<15,        //!< 第16列
    col17    =   0x00000001<<16,        //!< 第17列
    col18    =   0x00000001<<17,        //!< 第18列
    col19    =   0x00000001<<18,        //!< 第19列
    col20    =   0x00000001<<19,        //!< 第20列
    col21    =   0x00000001<<20,        //!< 第21列
    col22    =   0x00000001<<21,        //!< 第22列
    col23    =   0x00000001<<22,        //!< 第23列
    col24    =   0x00000001<<23,        //!< 第24列
    col25    =   0x00000001<<24,        //!< 第25列
    col26    =   0x00000001<<25,        //!< 第26列
    col27    =   0x00000001<<26,        //!< 第27列
    col28    =   0x00000001<<27,        //!< 第28列
    col29    =   0x00000001<<28,        //!< 第29列
    col30    =   0x00000001<<29,        //!< 第30列
    col31    =   0x00000001<<30,        //!< 第31列
    col32    =   0x00000001<<31,        //!< 第32列
};
}

//信息存储结构体
typedef struct
{
    QStringList stud;  //全部为字符串型，便于存放
} studData;




QDebug operator << (QDebug d, const studData &data)
{
  // 运算符重载函数，使其可以直接输出studData结构
    for(int i=0;i<data.stud.size();i++)
    d.noquote().nospace()<<QString(data.stud.at(i))<<"\t" ;
    return d;
}


//定义比较类
class myCmp
{
public:
    myCmp(int selectedColumn) { this->currentColumn = selectedColumn; }
    bool operator() (const studData& d1,const studData& d2) ;
private:
    int currentColumn;
};


#define compare(a)   (d1.stud.at(a)>=d2.stud.at(a))?  1:0       //定义学生成绩比较宏，用于myCmp::operator()内比较


bool myCmp::operator()(const studData &d1,const  studData &d2)
{
    bool result = false;
    quint32 sortedColumn = 0x00000001<<currentColumn;
    switch (sortedColumn)
    {

       case SK::col01:result=compare(1);break;
       case SK::col02:result=compare(2);break;
       case SK::col03:result=compare(3);break;
       case SK::col04:result=compare(4);break;
       case SK::col05:result=compare(5);break;
       case SK::col06:result=compare(6);break;
       case SK::col07:result=compare(7);break;
       case SK::col08:result=compare(8);break;
       case SK::col09:result=compare(9);break;
       case SK::col10:result=compare(10);break;
       case SK::col11:result=compare(11);break;
       case SK::col12:result=compare(12);break;
       case SK::col13:result=compare(13);break;
       case SK::col14:result=compare(14);break;
       case SK::col15:result=compare(15);break;
       case SK::col16:result=compare(16);break;
       default:break;
    }
    return result;
}


//排序执行类
class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();            //读文本
    void doSort();              //文本内容排序
    QString datafile;
    QList<studData > infor;
    studData txttitle;  //txt表头
    studData getdata;  //txt数据
};


ScoreSorter::ScoreSorter(QString dataFile)
{
    this->datafile = dataFile;
}


//读取文件
void ScoreSorter::readFile()
{
    QFile file(this->datafile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<QString("打开 %1 失败").arg(this->datafile);
    }

    QString titile(file.readLine()); //读取整行，作为字符串返回
    this->txttitle.stud = titile.split(" ", QString::SkipEmptyParts);   //按空格读取

    if((this->txttitle.stud).last() == "\n")
        this->txttitle.stud.removeLast();


    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);


        getdata.stud = str.split(" ", QString::SkipEmptyParts);  //读取成绩数据

        if((getdata.stud).last() == "\n")
            getdata.stud.removeLast();

        if(getdata.stud.size()==0) continue;
            this->infor.append(getdata);  //添加数据到infor
    }
    file.close();
}


//排序函数
void ScoreSorter::doSort()
{
    for(int i=1; i<this->txttitle.stud.size(); i++)
    {
        myCmp mycmp(i-1);    //初始化排序规则对象
        std::sort(this->infor.begin() , this->infor.end() , mycmp );  //排序

        qDebug()<<"排序后输出，当前排序第 "<< i+1 <<" 列：";
        qDebug()<< "   "<<(this->txttitle);    //输出表头

        for(int i=0;i<this->infor.size();i++)  qDebug() << this->infor.at(i);  //重载输出
        qDebug()<<"---------------------------------------------------------------\n";

    }
}



void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 自定义qDebug
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    //qInstallMessageHandler(myMessageOutput);

    QString datafile = "data.txt";

    // 如果排序后文件已存在，则删除之
    QFile f("sorted_"+datafile);
    if (f.exists()){
        f.remove();
    }

    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();
    return 0;
}
