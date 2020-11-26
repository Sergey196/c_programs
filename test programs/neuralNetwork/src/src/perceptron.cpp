
#include "perceptron.h"
#include <iostream>
#include <fstream>

Perceptron::Perceptron(float eta, int epochs)
{
    m_epochs = epochs;
    m_eta = eta;
}

void Perceptron::fit(std::vector< std::vector<float> > X, std::vector<float> y)
{
    for (int i = 0; i < X[0].size() + 1; i++) // X[0].size() + 1 -> I am using +1 to add the bias term
    {
        m_w.push_back(0);
    }
    for (int i = 0; i < m_epochs; i++)
    {
        int errors = 0;
        for (int j = 0; j < X.size(); j++)
        {
            float update = m_eta * (y[j] - predict(X[j]));
            for (int w = 1; w < m_w.size(); w++){ m_w[w] += update * X[j][w - 1]; }
            m_w[0] = update;
            errors += update != 0 ? 1 : 0;
        }
        m_errors.push_back(errors);
    }
}

float Perceptron::netInput(std::vector<float> X)
{
    // Sum(Vector of weights * Input std::vector) + bias
    float probabilities = m_w[0];
    for (int i = 0; i < X.size(); i++)
    {
        probabilities += X[i] * m_w[i + 1];
    }
    return probabilities;
}

int Perceptron::predict(std::vector<float> X)
{
    return netInput(X) > 0 ? 1 : -1; //Step Function
}

void Perceptron::printErrors()
{
    //printVector(m_errors);
}

void Perceptron::exportWeights(std::string filename)
{
    std::ofstream outFile;
    outFile.open(filename);

    for (int i = 0; i < m_w.size(); i++)
    {
        outFile << m_w[i] << std::endl;
    }

    outFile.close();
}

void Perceptron::importWeights(std::string filename)
{
    std::ifstream inFile;
    inFile.open(filename);

    for (int i = 0; i < m_w.size(); i++)
    {
        inFile >> m_w[i];
    }
}

void Perceptron::printWeights()
{
    std::cout << "weights: ";
    for (int i = 0; i < m_w.size(); i++)
    {
        std::cout << m_w[i] << " ";
    }
    std::cout << std::endl;
}
