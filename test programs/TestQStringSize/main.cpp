#include <QCoreApplication>
#include <iostream>

int main()
{
    QString text {"АМКА"};
    std::cout << "TEST1 = " << text.size() << std::endl;
    std::cout << "TEST2 = " << text.length() << std::endl;
    std::cout << "TEST3 = " << text.toStdString().length() << std::endl;
    QByteArray bytes = text.toUtf8();
    std::cout << "TEST4 = " << bytes.length() << std::endl;

    return 0;
}
