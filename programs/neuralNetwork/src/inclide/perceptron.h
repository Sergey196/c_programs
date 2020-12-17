

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <string>

class Perceptron
{
public:
    Perceptron(float eta,int epochs);
    float netInput(std::vector<float> X);
    int predict(std::vector<float> X);
    void fit(std::vector< std::vector<float> > X, std::vector<float> y);
    void printErrors();
    void exportWeights(std::string filename);
    void importWeights(std::string filename);
    void printWeights();
private:
    float m_eta;
    int m_epochs;
    std::vector < float > m_w;
    std::vector < float > m_errors;
};

#endif // NEURON_H
