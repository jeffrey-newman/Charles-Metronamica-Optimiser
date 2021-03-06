//
// Created by a1091793 on 18/5/17.
//


//
//
//  // Created by a1091793 on 18/5/17.
//  Copyright © 2016 University of Adelaide and Bushfire and Natural Hazards CRC. All rights reserved.
//


#include "MetronamicaOF2Utility.h"

int main(int argc, char * argv[]) {

    MetronamicaOF2Parameters params;
    int err = processOptions(argc, argv, params);
    if (err != 0)
    {
        return EXIT_SUCCESS;
    }

    std::vector<double> real_lowerbounds  = {100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //lower bounds
    std::vector<double> real_upperbounds = {5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // upper bound of x
    int num_classes = 9;
    params.evaluator_id = 0;
    MetronamicaCalibrationObjectiveFunction metro_eval(params, FKS_CLUMP_KAPPA, SMALL_RANDSTAD, real_lowerbounds, real_upperbounds, num_classes);


    typedef std::mt19937 RNG;
    if (params.search_rand_seed == -1) params.search_rand_seed = std::chrono::system_clock::now().time_since_epoch().count();
    RNG rng(params.search_rand_seed);



    // Initialise population
    PopulationSPtr pop(new Population);
    if (params.pop_file_xml.first != "none")
    {
        pop = restore_population(params.pop_file_xml.second);
    }
    else if (params.pop_file_txt.first != "none")
    {
        pop.reset(new Population(params.pop_file_txt.second, metro_eval.getProblemDefinitions()));
    }
    else
    {
        std::cerr << "Warning: a file of solutions was not give. evaluating a random population\n";
        pop = intialisePopulationRandomDVAssignment(params.pop_size, metro_eval.getProblemDefinitions(), rng);
    }

    postProcessResults(metro_eval, pop, params);
    return EXIT_SUCCESS;

}