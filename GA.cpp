// wo da yi le a:
// Created by NaturalVStudio on 2020/11/24.
// Copyright© zlt all rights Reserved.

#include "GA.h"

std::default_random_engine e((unsigned)time(nullptr));

GA::GA() {
    //init the population
    std::bernoulli_distribution u;//create random bool type by c++11 random library
    for(int i = 0; i < Population; i++){
        for(int j = 0; j < DNALength; j++){
            DNA[i].gene[j] = u(e);
        }
    }
}
GA::~GA() = default;

double GA::GetFitness(bool gene[]) {
    int Weight = 0, Value = 0;
    for(int i = 0; i < DNALength; i++){
        if(gene[i]) Weight += weight[i], Value += value[i];
    }
    if(Weight > MaxWeight) return 0;
    return Value;

}

void GA::Selection() { //Roulette
    DNAtype _DNA[MaxPopulation];
    double probability[MaxPopulation], sum_probability[MaxPopulation];
    double fitness[MaxPopulation];
    double SumFitness = 0;
    int p_DNA = 0; //_DNA
    for(int i = 0; i < Population; i++){
        SumFitness += fitness[i] = GetFitness(DNA[i].gene);
    }
    for(int i = 0; i < Population; i++){
        probability[i] = fitness[i] / SumFitness;
        sum_probability[i] = probability[i] + (i == 0 ? 0 : sum_probability[i - 1]);
        //printf("%lf ", sum_probability[i]);
    }
    //puts("");
    //std::default_random_engine e((unsigned)time(nullptr));
    std::uniform_real_distribution<double> u(0.0, 1.0);
    for(int i = 0; i < Population; i++){ //O(n^2) ng
        double A_Push = u(e);
        for(int j = 0; j < Population; j++){
            if(sum_probability[j] > A_Push){
                _DNA[i] = DNA[j];
            }
        }
    }
    for(int i = 0; i < Population; i++) DNA[i] = _DNA[i];
}

void GA::Variation() {
    std::uniform_real_distribution<double> u(0.0, 1.0);
    for(int i = 0; i < Population; i++){
        if(u(e) > MutationProbability) continue;
        std::uniform_int_distribution<unsigned> v1(0, (unsigned int)Population - 1);
        std::uniform_int_distribution<unsigned> v2(0, (unsigned int)DNALength - 1);
        unsigned pos_individual = v1(e);
        unsigned pos_gene = v2(e);
        DNA[pos_individual].gene[pos_gene] = !DNA[pos_individual].gene[pos_gene];
    }
}

void GA::Crossover() {
    std::uniform_int_distribution<unsigned> v(0, (unsigned int)Population - 1);
    int times = v(e);
    while(times--){
        int father = v(e), mother = v(e);
        int BeginPos = v(e), EndPos = v(e);
        for(int i = BeginPos; i <= EndPos; i++){
            std::swap(DNA[father].gene[i], DNA[mother].gene[i]);
        }
    }
}

void GA::Iteration() {
    for(int generation = 0; generation < TargetGeneration; generation++){
        Selection();
        Variation();
        Crossover();
        bool FindBetterSolution = false;
        int BestDNA = 0;
        for(int i = 0; i < Population; i++){
            double NowValue = GetFitness(DNA[i].gene);
            if(NowValue > BestValue){
                BestValue = (int)NowValue;
                BestSolution = DNA[i];
                BestGeneration = generation;
                BestDNA = i;
                FindBetterSolution = true;
            }
        }
        /*for(int i = 0; i < Population; i++){
            printf(" %d:", i);
            for(int j = 0; j < DNALength; j++){
                printf("%d", DNA[i].gene[j]);
            }

        }
        puts("");*/
        if(! FindBetterSolution) continue;
        printf("Find a better solution at generation %d:\n", BestGeneration);
        printf("BestValue: %d\n", BestValue);
        for(int i = 0; i < DNALength; i++){
            printf("%d", DNA[BestDNA].gene[i]);
        }
        puts("");
    }
}