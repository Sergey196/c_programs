#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "perceptron.h"

std::vector< std::vector<float> > getIrisX();
std::vector<float> getIrisy();

int main() 
{
    std::vector< std::vector<float> > X = getIrisX();
    std::vector<float> y = getIrisy();
    std::vector<float> test1;
    
    test1.push_back(5.0);
    test1.push_back(3.3);
    test1.push_back(1.4);
    test1.push_back(0.2);

    std::vector<float> test2;
    test2.push_back(6.0);
    test2.push_back(2.2);
    test2.push_back(5.0);
    test2.push_back(1.5);
    //printVector(X);
    //for (int i = 0; i < y.size(); i++){ std::cout << y[i] << " "; }std::cout << std::endl;

    Perceptron clf(0.1, 14);
    clf.fit(X, y);
    clf.printErrors();
    std::cout << "Now Predicting: 5.0,3.3,1.4,0.2(CorrectClass=-1,Iris-setosa) -> " << clf.predict(test1) << std::endl;
    std::cout << "Now Predicting: 6.0,2.2,5.0,1.5(CorrectClass=1,Iris-virginica) -> " << clf.predict(test2) << std::endl;

    //system("PAUSE");
    return 0;
}



std::vector<float> getIrisy()
{
    std::vector<float> y;

    std::ifstream inFile;
    inFile.open("y.data");
    std::string sampleClass;
    for (int i = 0; i < 100; i++)
    {
        inFile >> sampleClass;
        if (sampleClass == "Iris-setosa")
        {
            y.push_back(-1);
        }
        else
        {
            y.push_back(1);
        }
    }

    return y;
}

std::vector< std::vector<float> > getIrisX()
{
    std::ifstream af;
    std::ifstream bf;
    std::ifstream cf;
    std::ifstream df;
    af.open("a.data");
    bf.open("b.data");
    cf.open("c.data");
    df.open("d.data");

    std::vector< std::vector<float> > X;

    for (int i = 0; i < 100; i++)
    {
        char scrap;
        int scrapN;
        af >> scrapN;
        bf >> scrapN;
        cf >> scrapN;
        df >> scrapN;

        af >> scrap;
        bf >> scrap;
        cf >> scrap;
        df >> scrap;
        float a, b, c, d;
        af >> a;
        bf >> b;
        cf >> c;
        df >> d;
        
        std::cout << "TEST1 = " << a << std::endl;
        std::cout << "TEST2 = " << b << std::endl;
        std::cout << "TEST3 = " << c << std::endl;
        std::cout << "TEST4 = " << d << std::endl;
        
        
        X.push_back(std::vector < float > {a, b, c, d});
    }

    af.close();
    bf.close();
    cf.close();
    df.close();

    return X;
}
