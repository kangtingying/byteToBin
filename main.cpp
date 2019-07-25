#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define mydbg qDebug()

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile f(argv[1]);
    if( !f.open(QIODevice::ReadOnly) ){
        mydbg << ("Open Error");
        return 0;
    }

    QByteArray ba = f.readAll();
    ba = ba.mid(3);

    QFile f_1(argv[2]);
    f_1.open(QIODevice::WriteOnly);
    QTextStream str(&f_1);

    for( int i = 0; i < ba.size(); i+= 8){
        QByteArray t = ba.mid(i, 8);
        const unsigned char *p = reinterpret_cast<const unsigned char *>(t.constBegin());
        //quint8 *p = (quint8 *)(t.data());
        for (const unsigned char *end = p + t.size(); p < end; ++p) {
            str.setIntegerBase( 16 );
            str.setNumberFlags( QTextStream::ShowBase );
            str << unsigned(*p);
            str << ',';
        }
        str << '\r';
        str << '\n';
    }







    return 0;
}
