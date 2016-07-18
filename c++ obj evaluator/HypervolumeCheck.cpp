//
//  main.cpp
//  MetronamicaCalibrator
//
//  Created by a1091793 on 9/05/2016.
//  Copyright © 2016 University of Adelaide and Bushfire and Natural Hazards CRC. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "ProblemDefinitions.hpp"
#include "Individual.hpp"
#include "Population.hpp"
#include "Metrics/Hypervolume.hpp"
#include <boost/filesystem.hpp>

int main(int argc, char * argv[])
{

    boost::filesystem::path dir = boost::filesystem::initial_path();

    std::vector<double> min_dv_values  = {500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   // lower bound of x
    std::vector<double> max_dv_values = {5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // upper bound of x
    int num_real_decision_vars(371);
    int num_int_decision_vars(0);
    int num_constraints(0);
    std::vector<int> int_lowerbounds(0, std::numeric_limits<int>::min());
    std::vector<int> int_upperbounds(0, std::numeric_limits<int>::max());
    std::vector<MinOrMaxType> minimise_or_maximise = {MAXIMISATION, MINIMISATION};
    ProblemDefinitions prob_defs(min_dv_values, max_dv_values,  int_lowerbounds, int_upperbounds, minimise_or_maximise, num_constraints);
    std::vector<double> ref_point =  {-1, 9.764}; //From Charle's email 23rd June
    int max_gen_hvol = 10;
    Hypervolume hvol(ref_point, dir, 1, Hypervolume::TERMINATION, max_gen_hvol);
    PopulationSPtr pop(new Population);
//    FrontsSPtr fronts(pop->getFronts());
    IndividualSPtr ind1(new Individual(prob_defs)); ind1->setObjectives(std::vector<double> {-0.9, 0.1}); pop->push_back(ind1);
    IndividualSPtr ind2(new Individual(prob_defs)); ind2->setObjectives(std::vector<double> {-0.4, 1.5});pop->push_back(ind2);
    IndividualSPtr ind3(new Individual(prob_defs)); ind3->setObjectives(std::vector<double> {0, 3}); pop->push_back(ind3);
    IndividualSPtr ind4(new Individual(prob_defs)); ind4->setObjectives(std::vector<double> {0.4, 6}); pop->push_back(ind4);
    IndividualSPtr ind5(new Individual(prob_defs)); ind5->setObjectives(std::vector<double> {0.9, 9}); pop->push_back(ind5);
    hvol(pop);
    std::cout << "Hypervolume 1: " << hvol.getVal() << std::endl;

    PopulationSPtr pop2(new Population);
//    FrontsSPtr fronts2(pop2->getFronts());
    pop2->push_back(ind3);

    hvol(pop2);
    std::cout << "Hypervolume 2: " << hvol.getVal() << std::endl;

    PopulationSPtr pop3(new Population);
//    FrontsSPtr fronts(pop2->getFronts());
//    std::cout << "front size: " << pop3->getFronts()->size() << std::endl;

    hvol(pop3);
    std::cout << "Hypervolume 2: " << hvol.getVal() << std::endl;

}
