//
//  main.cpp
//  MetronamicaCalibrator
//
//  Created by a1091793 on 9/05/2016.
//  Copyright © 2016 University of Adelaide and Bushfire and Natural Hazards CRC. All rights reserved.
//


#include "MetronamicaOF2Utility.h"
#include <boost/mpi.hpp>
#include "ParallelEvaluator.hpp"


int main(int argc, char * argv[]) {
    boost::mpi::environment env(argc, argv);
    boost::mpi::communicator world;

    MetronamicaOF2Parameters params;
    int err = processOptions(argc, argv, params);
    if (err != 0)
    {
        return EXIT_SUCCESS;
    }

    std::vector<double> real_lowerbounds  = {500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
    std::vector<double> real_upperbounds =  {5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1   };
    int num_classes = 16;
    params.evaluator_id = world.rank();
    MetronamicaCalibrationObjectiveFunction metro_eval(params, FKS_CLUMP_KAPPA, LARGE_RANDSTAD, real_lowerbounds, real_upperbounds, num_classes);

    
    
    if (world.rank() == 0)
    {
//        std::ofstream ofs(time_fname.c_str());
//        if (ofs.is_open())
//        {
//            t.reset(new boost::timer::auto_cpu_timer(timer_info, 3));
//        }
//        else
//        {
//            std::cerr << "Error: Could not open file for writing time elapsed for search, using std::cout";
//            t.reset(new boost::timer::auto_cpu_timer(3));
//        }


        //create evaluator server
        boost::filesystem::path eval_log = params.save_dir.second / "evaluation_timing.log";
        std::ofstream eval_strm(eval_log.c_str());
        ParallelEvaluatePopServerNonBlocking eval_server(env, world, metro_eval.getProblemDefinitions());
        if (eval_strm.is_open())
        {
            eval_server.log(ParallelEvaluatorBase::LVL1, eval_strm);
        }

        // The random number generator
        typedef std::mt19937 RNG;
        if (params.search_rand_seed == -1) params.search_rand_seed = std::chrono::system_clock::now().time_since_epoch().count();
        RNG rng(params.search_rand_seed);


        // The optimiser
        NSGAII<RNG> optimiser(rng, eval_server);
        if (eval_strm.is_open())
        {
            optimiser.log(eval_strm, eval_log, NSGAII<RNG>::LVL1 );
        }
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


//        hvol(pop);
//        std::cout << "Hypervolume: " << hvol.getVal() << std::endl;

        // Run the optimisation
        optimiser(pop);

        postProcessResults(metro_eval, pop, params);

    }
    else
    {
        std::string log_file_name = "worker_" + std::to_string(world.rank()) + "_timing.log";
        boost::filesystem::path eval_log = params.save_dir.second / log_file_name;
        std::ofstream eval_strm(eval_log.c_str());
        ParallelEvaluatePopClientNonBlocking eval_client(env, world, metro_eval.getProblemDefinitions(), metro_eval);
        if (eval_strm.is_open())
        {
            eval_client.log(ParallelEvaluatorBase::LVL1, eval_strm);
        }

        //logging eval_client
//        std::string log_filename = "evaluation_timing_worker" + std::to_string(world.rank()) + ".log";
//        boost::filesystem::path eval_log = working_dir.second / log_filename;
//        std::ofstream eval_strm(eval_log.c_str());
//        if (eval_strm.is_open())
//        {
//            eval_client.log(ParallelEvaluatorBase::LVL1, eval_strm);
//        }
        eval_client();
    }
}
