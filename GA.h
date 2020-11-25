//
// Created by NaturalVStudio on 2020/11/24.
//

#ifndef GA_01BAG_GA_H
#define GA_01BAG_GA_H
#include <random>
#include <ctime>

class GA {
private: //memory
    static const int MaxPopulation = 150;
    static const int MaxDNALength = 10;
public:
    struct DNAtype{ //detailed data of DNA
        bool gene[MaxDNALength] = {false}; //gene list
        /*Encode agreement: each bit represent the corresponding item,
         * 0 for not choose, 1 for choose*/
    };
    DNAtype DNA[MaxPopulation]; //population

    int Population = 20;
    int DNALength = 8;
    int TargetGeneration = 100;
    int BestValue = 0, BestGeneration = 0;
    DNAtype BestSolution;
    int MaxWeight = 100;

    double CrossProbability = 0.5;
    double MutationProbability = 0.9;

    int weight[MaxDNALength] = {10, 5, 32, 18, 50, 2, 15, 20};
    int value[MaxDNALength] = {30, 6, 32, 35, 50, 8, 30, 5};

public:
    GA();
    ~GA();
    double GetFitness(bool[]);
    void Iteration();
    void Variation();
    void Selection();
    void Crossover();
};


#endif //GA_01BAG_GA_H
