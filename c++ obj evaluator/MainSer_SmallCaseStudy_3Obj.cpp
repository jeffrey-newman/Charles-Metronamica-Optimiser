 
//
//  main.cpp
//  MetronamicaCalibrator
//
//  Created by a1091793 on 9/05/2016.
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


    params.evaluator_id = 0;
    std::vector<double> real_lowerbounds  = {100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,100,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,-50,-1000,0.05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //lower bounds
    std::vector<double> real_upperbounds = {5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,100,1000,5,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // upper bound of x
    int num_classes = 9;


    MetronamicaCalibrationObjectiveFunction metro_eval(params, FKS_CLUMP_KAPPA, SMALL_RANDSTAD, real_lowerbounds, real_upperbounds, num_classes);


        // The random number generator
    typedef std::mt19937 RNG;
    if (params.search_rand_seed == -1) params.search_rand_seed = std::chrono::system_clock::now().time_since_epoch().count();
    RNG rng(params.search_rand_seed);


    // The optimiser
        NSGAII<RNG> optimiser(rng, metro_eval);
    std::vector<double> ref_point =  {-0.1, 1, -0.1};
    std::vector<double> unitise_point = {1,0, 1};
    createCheckpoints(optimiser, params, ref_point, unitise_point);

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
        pop = intialisePopulationRandomDVAssignment(params.pop_size, metro_eval.getProblemDefinitions(), rng);
    }
        optimiser.getRealMutationOperator().setMutationInverseDVSize(pop->at(0));
//        SetMutationInverseDVSize(pop->at(0), optimiser.getRealMutationOperator());

//        hvol(pop);
//        std::cout << "Hypervolume: " << hvol.getVal() << std::endl;

        // Run the optimisation
        optimiser(pop);

    postProcessResults(metro_eval, pop, params);


}
