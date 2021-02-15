#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

class Student{
    public:
        char name[40]; 
        char address[120];
        char gender;
        double age;
        bool is_blabla;
};

/*struct Student
{
        char name[40]; 
        char address[120];
        char gender;
        double age;
        bool is_blabla;
};*/

int main() {

    /*Student one;
    strcpy(one.name, "Cancan Can");
    strcpy(one.address, "example example exampla");
    one.gender = 'M';
    one.age = 25;
    one.is_blabla = true;
    cout << "Student Name: " << one.name << endl;

    ofstream ofs("fifthgrade.ros", ios::binary);
    ofs.write((char *)&one, sizeof(one));
    ofs.close();

    Student two;
    ifstream ifs("fifthgrade.ros", ios::binary);
    ifs.read((char *)&two, sizeof(two));
    ifs.close();

    cout << "Student Name: " << two.name << endl;
    cout << "Student Name: " << &one << endl;
    cout << "Student Name: " << &two << endl;*/
    
    Student *one = new Student();
    strcpy(one->name, "Cancan Can");
    strcpy(one->address, "example example exampla");
    one->gender = 'M';
    one->age = 25;
    one->is_blabla = true;
    cout << "Student Name: " << one->name << endl;

    ofstream ofs("fifthgrade.ros", ios::binary);
    ofs.write((char *)one, sizeof(Student));
    ofs.close();

    Student *two = new Student();
    ifstream ifs("fifthgrade.ros", ios::binary);
    ifs.read((char *)two, sizeof(Student));
    ifs.close();

    cout << "Student Name: " << two->name << endl;
    cout << "Student Name: " << &one << endl;
    cout << "Student Name: " << &two << endl;


    return 0;
} 
