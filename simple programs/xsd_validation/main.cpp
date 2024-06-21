#include <QCoreApplication>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QFile>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QXmlSchema schema;
    schema.load(QUrl("description.xsd"));
    if(schema.isValid()) {
        QFile file("description.xml");
        file.open(QIODevice::ReadOnly);

        QXmlSchemaValidator validator(schema);
        if (validator.validate(&file, QUrl::fromLocalFile(file.fileName()))) {
           std::cout << "instance document is valid" << std::endl;
        } else {
           std::cout << "instance document is invalid" << std::endl;
        }
    } else {
       std::cout << "xsd document is invalid" << std::endl;
    }
    std::cout << "END" << std::endl;
    return a.exec();
}
