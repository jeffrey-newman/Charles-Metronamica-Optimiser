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
#include <boost/filesystem.hpp>
#include <boost/mpi.hpp>
#include "MetronamicaOF.hpp"
#include "ParallelEvaluator.hpp"
#include "NSGAII.hpp"
#include "pathify.hpp"


int main(int argc, const char * argv[]) {
    boost::mpi::environment env;
    boost::mpi::communicator world;

    CmdLinePaths metro_exe;  // path to the Metronamic executable GeonamicaCmd.exe
    CmdLinePaths mck_exe;    // path to the Map comparison kit executable
    CmdLinePaths wine_exe;   // path to the wine executable (windows emulator)
    CmdLinePaths java_exe;   // Path to jvm
    CmdLinePaths geoproj_manip_jar;  // path to the java jar for manipulating geoproject files.
    CmdLinePaths template_dir;
    std::string geoproj_file;
    std::string wine_working_dir_path;
    std::string log_file;
    CmdLinePaths actual_map_file;
    CmdLinePaths original_map_file;
    CmdLinePaths masking_map_file;
    CmdLinePaths fks_coefficients_file;
    CmdLinePaths working_dir;

//    boost::filesystem::path metro_exe_path;

    int pop_size; // For the GA
    int max_gen;  // Termination condition for the GA

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
            ("log-name,l", po::value<std::string>(&log_file), "path of the log settings xml file (full path in wine format)")
            ("actual-map,a", po::value<std::string>(&actual_map_file.first), "path of the actual landuse map at end of simulation to compare to")
            ("orignal-map,o", po::value<std::string>(&original_map_file.first), "path of the landuse map at start of the simulation")
            ("masking-map,s", po::value<std::string>(&masking_map_file.first), "path of the masking map to mask out/in sections of the raster")
            ("fks-coeef,c", po::value<std::string>(&fks_coefficients_file.first), "path of the fuzzy coeeficint table")
            ("working-dir,d", po::value<std::string>(&working_dir.first)->default_value(boost::filesystem::current_path().string()), "path of directory for storing temp files during running")
            ("wine-work-dir,n", po::value<std::string>(&wine_working_dir_path), "path to working directory (working-dir,d), but in wine path format - e.g. Z:\\path\\to\\working\\dir")
            ("pop-size,p", po::value<int>(&pop_size)->default_value(415), "Population size of the NSGAII")
            ("max-gen,x", po::value<int>(&max_gen)->default_value(500), "maximum generations - terminaation condition");



    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(desc).run(), vm);
    po::notify(vm);

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
    pathify(working_dir);

//    pathify(metro_exe) //.second = boost::filesystem::path(metro_exe.first);
//    mck_exe.second = boost::filesystem::path(mck_exe.first);
//    wine_exe.second = boost::filesystem::path(wine_exe.first);
//    java_exe.second = boost::filesystem::path(java_exe.first);
//    geoproj_manip_jar.second = boost::filesystem::path(geoproj_manip_jar.first);
//    template_dir.second = boost::filesystem::path(template_dir.first);
//    log_file.second = boost::filesystem::path(log_file.first);
//    actual_map_file.second = boost::filesystem::path(actual_map_file.first);
//    original_map_file.second = boost::filesystem::path(original_map_file.first);
//    masking_map_file.second = boost::filesystem::path(masking_map_file.first);
//    fks_coefficients_file.second = boost::filesystem::path(fks_coefficients_file.first);
//    working_dir.second = boost::filesystem::path(working_dir.first);



    MetronamicaOF metro_eval(metro_exe.second,
                             mck_exe.second,
                             wine_exe.second,
                             java_exe.second,
                             geoproj_manip_jar.second,
                             template_dir.second,
                             working_dir.second,
                             wine_working_dir_path,
                             geoproj_file,
                             log_file,
                             actual_map_file.second,
                             original_map_file.second,
                             masking_map_file.second,
                             fks_coefficients_file.second);
    
    
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
        ParallelEvaluatePopServer eval_server(env, world, metro_eval.getProblemDefinitions());

        // The random number generator
        typedef std::mt19937 RNG;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        RNG rng(seed);

        // The optimiser
        NSGAII<RNG> optimiser(rng, eval_server, max_gen);
//        optimiser.visualise();

        // Initialise population
        PopulationSPtr pop = intialisePopulationRandomDVAssignment(pop_size, metro_eval.getProblemDefinitions(), rng);

        // Run the optimisation
        optimiser(pop);


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
        // create evaluator client
        ParallelEvaluatePopClient eval_client(env, world, metro_eval.getProblemDefinitions(), metro_eval);
        eval_client();
    }
}
