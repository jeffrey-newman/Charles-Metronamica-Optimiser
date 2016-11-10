//
//  main.cpp
//  MetronamicaCalibrator
//
//  Created by a1091793 on 9/05/2016.
//  Copyright © 2016 University of Adelaide and Bushfire and Natural Hazards CRC. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <boost/program_options.hpp>
//#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
//#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/mpi.hpp>
#include "MetronamicaOF2_SmallCaseStudy.hpp"
#include "ParallelEvaluator.hpp"
#include "NSGAII.hpp"
#include "Pathify.hpp"
#include "Checkpoints/SavePopCheckpoint.hpp"
#include "Checkpoints/MaxGenCheckpoint.hpp"
#include "Checkpoints/PlotFronts.hpp"
#include "Metrics/Hypervolume.hpp"
#include "Checkpoints/ResetMutationXoverFlags.hpp"
#include "Checkpoints/MetricLinePlot.hpp"
#include "Checkpoints/MailCheckpoint.hpp"
#include "Checkpoints/MaxGenCheckpoint.hpp"
#include "Checkpoints/SaveFirstFrontCheckpoint.hpp"

int main(int argc, char * argv[]) {
    boost::mpi::environment env(argc, argv);
    boost::mpi::communicator world;

    CmdLinePaths metro_exe;  // path to the Metronamic executable GeonamicaCmd.exe
    CmdLinePaths mck_exe;    // path to the Map comparison kit executable
    CmdLinePaths wine_exe;   // path to the wine executable (windows emulator)
    CmdLinePaths java_exe;   // Path to jvm
    CmdLinePaths geoproj_manip_jar;  // path to the java jar for manipulating geoproject files.
    CmdLinePaths template_dir;
    std::string geoproj_file;
    std::string wine_working_dir_path;
    CmdLinePaths log_file;
    CmdLinePaths wine_reg_mod_file;
    CmdLinePaths actual_map_file;
    CmdLinePaths original_map_file;
    CmdLinePaths masking_map_file;
    CmdLinePaths fks_coefficients_file;
    CmdLinePaths working_dir;
    CmdLinePaths save_dir;
    CmdLinePaths restart_pop_file;

//    boost::filesystem::path metro_exe_path;

    int pop_size; // For the GA
    int max_gen_hvol;  // Termination condition for the GA
    int max_gen;
    int mail_hvol_gen;
    int replicates;
    int save_freq;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ("metro-exe,m", po::value<std::string>(&metro_exe.first), "path to Metronamica executable GeonamicaCmd.exe")
            ("mck-exe,k", po::value<std::string>(&mck_exe.first), "path to the Map comparison kit executable")
            ("wine-exe,w", po::value<std::string>(&wine_exe.first)->default_value("wine"), "path to the wine executable (windows emulator)")
            ("java_exe,j", po::value<std::string>(&java_exe.first)->default_value("java"), "Path to jvm" )
            ("geoproj-manip,g", po::value<std::string>(&geoproj_manip_jar.first), "path to the java jar for manipulating geoproject files.")
            ("template,t", po::value<std::string>(&template_dir.first), "path to template geoproject directory")
            ("geoproj-file,f", po::value<std::string>(&geoproj_file), "name of geoproject file (without full path)")
            ("log-name,l", po::value<std::string>(&log_file.first), "path of the log settings xml file (full path in wine format)")
            ("actual-map,a", po::value<std::string>(&actual_map_file.first), "path of the actual landuse map at end of simulation to compare to")
            ("orignal-map,o", po::value<std::string>(&original_map_file.first), "path of the landuse map at start of the simulation")
            ("masking-map,s", po::value<std::string>(&masking_map_file.first), "path of the masking map to mask out/in sections of the raster")
            ("fks-coeef,c", po::value<std::string>(&fks_coefficients_file.first), "path of the fuzzy coeeficint table")
            ("working-dir,d", po::value<std::string>(&working_dir.first)->default_value(boost::filesystem::current_path().string()), "path of directory for storing temp files during running")
            ("save-dir,v", po::value<std::string>(&save_dir.first)->default_value(boost::filesystem::current_path().string()), "path of the directory for writing results and outputs to")
            ("wine-work-dir,n", po::value<std::string>(&wine_working_dir_path), "path to working directory (working-dir,d), but in wine path format - e.g. Z:\\path\\to\\working\\dir")
            ("wine-reg-edit,r", po::value<std::string>(&wine_reg_mod_file.first), "path of the wine registry file to update registry on nodes")
            ("pop-size,p", po::value<int>(&pop_size)->default_value(415), "Population size of the NSGAII")
            ("max-gen-no-hvol-improve,x", po::value<int>(&max_gen_hvol)->default_value(50), "maximum generations with no improvement in the hypervolume metric - terminaation condition")
            ("mail-gen-hvol,e", po::value<int>(&mail_hvol_gen)->default_value(10), "How often to mail the hpervolume value")
            ("save-freq,q", po::value<int>(&save_freq)->default_value(1), "how often to save first front, hypervolume metric and population")
            ("max-gen,y", po::value<int>(&max_gen)->default_value(500), "Maximum number of generations - termination condition")
            ("replicates,i", po::value<int>(&replicates)->default_value(10), "Number of times to rerun Metronamica to account for stochasticity of model for each objective function evaluation")
            ("reseed,b", po::value<std::string>(&restart_pop_file.first)->default_value("no_seed"), "File with saved population as initial seed population for GA");



    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(desc).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return EXIT_SUCCESS;
    }

    pathify(metro_exe); //.second = boost::filesystem::path(metro_exe.first);
    pathify(mck_exe);
    pathify(wine_exe);
    pathify(java_exe);
    pathify(geoproj_manip_jar);
    pathify(template_dir);
    pathify(actual_map_file);
    pathify(original_map_file);
    pathify(masking_map_file);
    pathify(fks_coefficients_file);
    pathify_mk(working_dir);
    pathify_mk(save_dir);
    pathify(wine_reg_mod_file);
    pathify(log_file);
    if (restart_pop_file.first != "no_seed")
    {
        pathify(restart_pop_file);
    }



    MetronamicaOF2SmallCaseStudy metro_eval(metro_exe.second,
                             mck_exe.second,
                             wine_exe.second,
                             java_exe.second,
                             geoproj_manip_jar.second,
                             template_dir.second,
                             working_dir.second,
                                            save_dir.second,
                             wine_working_dir_path,
                             geoproj_file,
                             log_file.second,
                             actual_map_file.second,
                             original_map_file.second,
                             masking_map_file.second,
                             fks_coefficients_file.second,
                             wine_reg_mod_file.second,
                             world.rank(),
                             true,
                             replicates);
    
    
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
        boost::filesystem::path eval_log = save_dir.second / "evaluation_timing.log";
        std::ofstream eval_strm(eval_log.c_str());
        ParallelEvaluatePopServerNonBlocking eval_server(env, world, metro_eval.getProblemDefinitions());
        if (eval_strm.is_open())
        {
            eval_server.log(ParallelEvaluatorBase::LVL1, eval_strm);
        }

        // The random number generator
        typedef std::mt19937 RNG;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        RNG rng(seed);

        // The optimiser
        NSGAII<RNG> optimiser(rng, eval_server);
        if (eval_strm.is_open())
        {
            optimiser.log(eval_strm, eval_log, NSGAII<RNG>::LVL1 );
        }
        boost::shared_ptr<SavePopCheckpoint> save_pop(new SavePopCheckpoint(save_freq, save_dir.second));
        boost::shared_ptr<SaveFirstFrontCheckpoint> save_front(new SaveFirstFrontCheckpoint(save_freq, save_dir.second));
        std::vector<double> ref_point =  {-0.1, 1};
        std::vector<double> unitise_point = {1,0};
//        Hypervolume hvol(ref_point, save_dir.second, save_freq, Hypervolume::TERMINATION, max_gen_hvol, Hypervolume::MAXIMISE, unitise_point);
        boost::shared_ptr<Hypervolume> hvol(new Hypervolume(save_freq, save_dir.second, Hypervolume::TERMINATION, max_gen_hvol, ref_point, unitise_point, Hypervolume::MAXIMISE));
        if (eval_strm.is_open())
        {
            hvol->log(Hypervolume::LVL1, eval_strm);
        }
        boost::shared_ptr<MetricLinePlot> hvol_plot(new MetricLinePlot(hvol));
        boost::shared_ptr<MaxGenCheckpoint> maxgen(new MaxGenCheckpoint(max_gen));
        std::string mail_subj("Hypervolume of front from Metro calibrator ");
        boost::shared_ptr<MailCheckpoint> mail(new MailCheckpoint(mail_hvol_gen, hvol, mail_subj));
        std::string jeffs_address("jeffrey.newman@adelaide.edu.au");
        std::string charles_address("charles.p.newland@adelaide.edu.au");
        mail->addAddress(jeffs_address);
        mail->addAddress(charles_address);


        boost::shared_ptr<PlotFrontVTK> plotfront(new PlotFrontVTK);
    //    ResetMutXvrDebugFlags reset_flags;
    //    SerialiseCheckpoint<NSGAII<RNG> > save_state(1, optimiser, working_dir);
//        optimiser.add_checkpoint(max_gen_terminate);
    //    optimiser.add_checkpoint(save_state);
        optimiser.add_checkpoint(save_pop);
        optimiser.add_checkpoint(save_front);
        optimiser.add_checkpoint(hvol);
        optimiser.add_checkpoint(mail);
        optimiser.add_checkpoint(hvol_plot);
        optimiser.add_checkpoint(plotfront);
        optimiser.add_checkpoint(maxgen);

//        optimiser.visualise();

        // Initialise population

        PopulationSPtr pop(new Population);
        if (restart_pop_file.first == "no_seed")
        {
            pop = intialisePopulationRandomDVAssignment(pop_size, metro_eval.getProblemDefinitions(), rng);
        }
        else
        {
            pop = restore_population(restart_pop_file.second);
        }



//        hvol(pop);
//        std::cout << "Hypervolume: " << hvol.getVal() << std::endl;

        // Run the optimisation
        optimiser(pop);

        Population & first_front = pop->getFronts()->at(0);

        int i = 0;
        BOOST_FOREACH(IndividualSPtr ind, first_front)
        {
            std::vector<double> objectives;
            std::vector<double> constraints;
            boost::filesystem::path save_ind_dir = save_dir.second / ("individual_" + std::to_string(i++));
            if (!boost::filesystem::exists(save_ind_dir)) boost::filesystem::create_directory(save_ind_dir);
            std::tie(objectives, constraints) = metro_eval(ind->getRealDVVector(), ind->getIntDVVector(), save_ind_dir);
            ind->setObjectives(objectives);
            ind->setConstraints(constraints);
            std::cout << *ind << std::endl;
        }

        boost::filesystem::path save_file = save_dir.second / "final_front.xml";
        std::ofstream ofs(save_file.c_str());
        assert(ofs.good());
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(first_front);

        boost::filesystem::path save_file2 = save_dir.second /  "final_front.txt";
        std::ofstream ofs2(save_file2.c_str());
        assert(ofs2.good());
        ofs2 << pop;

//        t.reset((boost::timer::auto_cpu_timer *) nullptr);
//        if (ofs.is_open())
//        {
//            ofs << timer_info.str();
//            ofs.close();
//        }
//        std::cout << timer_info.str() << std::endl;

    }
    else
    {
        std::string log_file_name = "worker_" + std::to_string(world.rank()) + "_timing.log";
        boost::filesystem::path eval_log = save_dir.second / log_file_name;
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
