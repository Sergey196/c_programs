
#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LENGTNARRAY = 1000;

class Student{
    public:
        char name[40]; 
        char address[120];
        char gender;
        double age;
        bool is_blabla;
};

unsigned int CRC32_function(unsigned char *buf, unsigned long len)
{
	unsigned long crc_table[256];
	unsigned long crc;
	for (int i = 0; i < 256; i++)
	{
		crc = i;
		for (int j = 0; j < 8; j++)
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
		crc_table[i] = crc;
	};
	crc = 0xFFFFFFFFUL;
	while (len--)
	crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
	return crc ^ 0xFFFFFFFFUL;
}

int main()
{
    /*unsigned char convert_array[LENGTNARRAY];
    Student *one = new Student();
    strcpy(one->name, "Cancan Can");
    strcpy(one->address, "example example exampla");
    one->gender = 'M';
    one->age = 25;
    one->is_blabla = true;
    
    memcpy(convert_array, one, sizeof(Student));
    
    std::cout << "TEST1 = " << one->name << std::endl;
    std::cout << "TEST2 = " << one->address << std::endl;
    std::cout << "TEST3 = " << one->gender << std::endl;
    std::cout << "TEST4 = " << one->age << std::endl;
    
    Student *two = new Student();
    
    memcpy(two, convert_array, sizeof(convert_array));
    
    std::cout << "TEST5 = " << two->name << std::endl;
    std::cout << "TEST6 = " << two->address << std::endl;
    std::cout << "TEST7 = " << two->gender << std::endl;
    std::cout << "TEST8 = " << two->age << std::endl;
    
    std::cout << "TEST9 = " << one << std::endl;
    std::cout << "TEST10 = " << two << std::endl;
    
    memcpy(convert_array, one, sizeof(Student));
    std::cout << "TEST11 = " << CRC32_function(convert_array, LENGTNARRAY) << std::endl;
    
    memcpy(convert_array, two, sizeof(Student));
    std::cout << "TEST12 = " << CRC32_function(convert_array, LENGTNARRAY) << std::endl;
    
    Student *tree = new Student();
    strcpy(tree->name, "TEST1");
    strcpy(tree->address, "TEST1");
    tree->gender = 'F';
    tree->age = 23;
    tree->is_blabla = true;
    memcpy(convert_array, tree, sizeof(Student));
    std::cout << "TEST13 = " << CRC32_function(convert_array, LENGTNARRAY) << std::endl;*/
    /*std::thread([&](){
       //system("cpulimit -l 50 ./script.sh");
        system("sudo nice -n 19  ./script.sh");
    }).detach();*/
    
    FILE* pipe = popen("./checksum.sh", "r");
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
        {
            result += buffer;
        }
    }
    pclose(pipe);
    
    std::cout << "TEST8 = " << result << std::endl;
    
    //std::cout << "TEST8 = " << popen("sudo nice -n 19  ./checksum.sh", "r")<< std::endl;
    
   while(true)
   {
      usleep(1); 
   }
   
   return 0; 
}
 
