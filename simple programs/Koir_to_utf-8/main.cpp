
#include <iostream>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converter.h"
#include <fstream>
#include <sstream>



int main(void)
{
    char in[250]; 
    size_t len;
    Converter convert;
    convert.setCodes("UTF-8", "UTF-16");
    std::ifstream fin("TEST1", std::ios::binary);
    fin.seekg(2);
    std::stringstream ss;
    ss << fin.rdbuf();
    std::string bytes = ss.str();
    len = bytes.size();
    memcpy(in, bytes.c_str(), len);
    convert.convert(in, len);
    
    FILE * fp = fopen("TEST2", "w+");
    fprintf(fp, "%s", in);
    fclose(fp);
    fin.close();
    convert.close(); 
    /*char *in { nullptr };
    size_t len { 0 };
    ssize_t read;
    //iconv_t conv = iconv_open("KOI8-R//TRANSLIT", "GBK");
    //iconv_t conv = iconv_open("utf8", "koi8-r");
    convert.setCodes("UTF-8", "UTF-16");

    FILE * fp1 = fopen("TEST1", "r+");
    FILE * fp2 = fopen("TEST2", "w+");
    
    if (!fp1 || !fp2)
    {
       std::cout << "ERROR OPEN FILE" << std::endl;
    }

    while ((read = getline(&in, &len, fp1)) != -1) {
        std::cout << "TEST2 = " << len << std::endl;
        convert.convert(in);
        fprintf(fp2, "%s", in);
    }

    fclose(fp1);
    fclose(fp2);*/
    
    return 0;
}

/*#include <codecvt>
#include <fstream>
#include <sstream>
#include <locale>
#include <iostream>

int main(void)
{
    std::ifstream fin("TEST1", std::ios::binary);
    
    //skip BOM
    fin.seekg(2);
    
    //read as raw bytes
    std::stringstream ss;
    ss << fin.rdbuf();
    std::string bytes = ss.str();
    
    //make sure len is divisible by 2
    int len = bytes.size();
    if(len % 2) len--;
    
    std::wstring sw;
    for(size_t i = 0; i < len;)
    {
        //little-endian
        int lo = bytes[i++] & 0xFF;
        int hi = bytes[i++] & 0xFF;
        sw.push_back(hi << 8 | lo);
    }
    
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
    std::string utf8 = convert.to_bytes(sw);
    std::cout << utf8 << std::endl;
    return 0;
}*/
