//
// Created by a1091793 on 17/5/17.
//

#ifndef CHARLES_METRO_CAL_METRONAMICAOF2UTILITY_H
#define CHARLES_METRO_CAL_METRONAMICAOF2UTILITY_H


#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <csignal>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include "Pathify.hpp"

#include "NSGAII.hpp"
#include "Checkpoints/SavePopCheckpoint.hpp"
#include "Checkpoints/MaxGenCheckpoint.hpp"
#include "Checkpoints/PlotFronts.hpp"
#include "Metrics/Hypervolume.hpp"
#include "Checkpoints/ResetMutationXoverFlags.hpp"
#include "Checkpoints/MetricLinePlot.hpp"
#include "Checkpoints/MaxGenCheckpoint.hpp"
#include "Checkpoints/MailCheckpoint.hpp"
#include "Checkpoints/SaveFirstFrontCheckpoint.hpp"
#include "Checkpoints/SignalCheckpoint.hpp"

struct MetronamicaOF2Parameters
{
    std::string timout_cmd; //cmd to run everything through another program which kills model on timer, incase it gets stuck/spins/hangs
    std::string wine_cmd; // cmd to run geonamica model through wine, emulation for running on linux or mac.
    std::string geonamica_cmd;  // path to geonamicaCmd.exe. Usually UNIX or Wine path both should work Z://PATH/geonamica.exe")
    bool with_reset_and_save;
    CmdLinePaths template_project_dir; // path to template project
    CmdLinePaths working_dir;
    CmdLinePaths wine_prefix_path;
    bool set_prefix_path;
    CmdLinePaths wine_drive_path;
//    std::string wine_drive_letter;
    CmdLinePaths  geoproj_file; // relative path of geoproject file from geoproject directory (head/root directory)
    CmdLinePaths log_spec_file;
    CmdLinePaths actual_map_file;
    CmdLinePaths original_map_file;
    CmdLinePaths masking_map_file;
    CmdLinePaths fks_coefficients_file;
    CmdLinePaths simulated_map_file;
    CmdLinePaths save_dir;
    CmdLinePaths pop_file_xml;
    std::vector<std::string> save_maps;
    bool is_logging = false;
    std::vector<MinOrMaxType> min_or_max; //vector of whether the objectives in the maps above are minimised or maximised.

//    boost::filesystem::path metro_exe_path;

    int pop_size; // For the GA
    int max_gen_hvol;  // Termination condition for the GA
    int max_gen;
    int mail_hvol_gen;
    int replicates;
    int save_freq;

    int evaluator_id;

    std::vector<int> metro_rand_seeds { 1000,1001,1002,1003,1004,1005,1006,1007,1008,1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020 };
    int search_rand_seed;

    CmdLinePaths pop_file_txt;

    bool bypass_save;

};

std::string
userHomeDir() {
    std::string path;
    char const *home = getenv("HOME");
    if (home or ((home = getenv("USERPROFILE")))) {
        path.append(home);
    } else {
        char const *hdrive = getenv("HOMEDRIVE"),
                *hpath = getenv("HOMEPATH");
        assert(hdrive);  // or other error handling
        assert(hpath);
        path.append(std::string(hdrive) + hpath);
    }
    return path;
}

std::pair<std::string, std::string> at_option_parser(std::string const&s)
{
    if ('@' == s[0])
        return std::make_pair(std::string("cfg-file"), s.substr(1));
    else
        return std::pair<std::string, std::string>();
}

int processOptions(int argc, char * argv[], MetronamicaOF2Parameters & params)
{
    try
    {
        boost::filesystem::path deafult_working_dir = boost::filesystem::path(userHomeDir()) / ".geonamicaZonalOpt/working_dir";

        namespace po = boost::program_options;
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help,h", "produce help message")
                ("timeout-cmd,u", po::value<std::string>(&params.timout_cmd)->default_value("no_timeout"), "[optional] excutable string that will run the timeout cmd --- to run everything through another program which kills model on timer, incase it gets stuck/spins/hangs")
                ("wine-cmd,f", po::value<std::string>(&params.wine_cmd)->default_value("no_wine"), "[optional] path to wine (emulator) excutable ")
                ("geonamica-cmd,m", po::value<std::string>(&params.geonamica_cmd), "excutable string that will run the geonamica model --- without command flags/arguments (like Z://PATH/geonamica.exe\")")
                ("with-reset-and-save", po::value<bool>(&params.with_reset_and_save)->default_value(true), "whether the --save flag is used with respective --reset for each simulation")
                ("template,t", po::value<std::string>(&params.template_project_dir.first), "path to template geoproject directory")
                ("working-dir,d", po::value<std::string>(&params.working_dir.first)->default_value(deafult_working_dir.string()), "path of directory for storing temp files during running")
                ("wine-prefix-path,w", po::value<std::string>(&params.wine_prefix_path.first)->default_value("na"), "Path to the wine prefix to use. Subfolder should contain dosdevices. To use default in home drive, specify <use_home_drive> to generate new prefix use <generate>")
                ("set-prefix-env-var", po::value<bool>(&params.set_prefix_path)->default_value(true), "If using crossover, the prefix is set as part of wine command, and so can be switched off.")
                ("geoproj-file,g", po::value<std::string>(&params.geoproj_file.first), "name of geoproject file (without full path), relative to template geoproject directory. Needs to be in top level at the moment")
                ("log-spec,l", po::value<std::string>(&params.log_spec_file.first),"path of the log settings xml file relative to template geoproject directory")
                ("actual-map,a", po::value<std::string>(&params.actual_map_file.first),"path of the actual landuse map at end of simulation to compare to,  relative to template geoproject directory")
                ("original-map,o", po::value<std::string>(&params.original_map_file.first),"path of the landuse map at start of the simulation,  relative to template geoproject directory")
                ("masking-map,n", po::value<std::string>(&params.masking_map_file.first),"path of the masking map to mask out/in sections of the raster,  relative to template geoproject directory")
                ("simulated-map,s", po::value<std::string>(&params.simulated_map_file.first),"path of the simulated map to assess quality of,  relative to template geoproject directory")
                ("fks-coef,c", po::value<std::string>(&params.fks_coefficients_file.first),"path of the fuzzy coeeficint table,  relative to template geoproject directory")
                ("save-dir,v", po::value<std::string>(&params.save_dir.first)->default_value(boost::filesystem::current_path().string()),"path of the directory for writing results and outputs to")
                ("save-map,k", po::value<std::vector<std::string> >(&params.save_maps)->multitoken(), "save maps of results when optimisation completes. Format: [CATEGORISED/LINEAR_GRADIENT]:LEGEND=[\"legend_specification_file_relative_to_template_directory\"]\":PATH=[\"path_of_map_relative_to_geoproject\"]:DIFF=[\"optional_path_of_differencing_map_relative_to_geoproject\"]:SAVE_AS=[\"file_name\"]")
                ("pop-size,p", po::value<int>(&params.pop_size)->default_value(415), "Population size of the NSGAII")
                ("max-gen-no-hvol-improve,x", po::value<int>(&params.max_gen_hvol)->default_value(50),"maximum generations with no improvement in the hypervolume metric - terminaation condition")
                ("mail-gen-hvol,e", po::value<int>(&params.mail_hvol_gen)->default_value(10),"How often to mail the hpervolume value")
                ("save-freq,q", po::value<int>(&params.save_freq)->default_value(1),"how often to save first front, hypervolume metric and population")
                ("max-gen,y", po::value<int>(&params.max_gen)->default_value(500), "Maximum number of generations - termination condition")
                ("replicates,i", po::value<int>(&params.replicates)->default_value(10), "Number of times to rerun Metronamica to account for stochasticity of model for each objective function evaluation")
                ("pop-file-xml,b", po::value<std::string>(&params.pop_file_xml.first)->default_value("none"),"File with saved population as initial seed population for GA")
                ("pop-file-txt", po::value<std::string>(&params.pop_file_txt.first)->default_value("none"), "Path to file which contains individuals to test evaluation on")
                ("is-logging,j", po::value<bool>(&params.is_logging)->default_value(false), "TRUE or FALSE whether to log the evaluation")
                ("bypass-save", po::value<bool>(&params.bypass_save)->default_value(false), "Bypass save as this is causing seg fault in Image Magick on Phoenix at the moment")
                ("rng-seed", po::value<int>(&params.search_rand_seed)->default_value(-1), "Positive random number seed (integer) for use in the search (not Metronamica)")
                ("cfg-file,c", po::value<std::string>(), "can be specified with '@name', too");

//r and z still available.
        po::variables_map vm;

        try
        {
            po::store(po::command_line_parser(argc, argv).
                    options(desc).extra_parser(at_option_parser).run(), vm);


            if (vm.count("help"))
            {
                std::cout << desc << "\n";
                return 1;
            }
            if (vm.count("cfg-file"))
            {
                // Load the file and tokenize it
                std::ifstream ifs(vm["cfg-file"].as<std::string>().c_str());
                if (!ifs)
                {
                    std::cout << "Could not open the cfg file\n";
                    return 1;
                }
                po::store(po::parse_config_file(ifs, desc), vm);
            }

            po::notify(vm);


            pathify_mk(params.working_dir);
            pathify_mk(params.save_dir);
            pathify(params.template_project_dir);

            if (params.pop_file_xml.first != "none")
            {
                pathify(params.pop_file_xml);
            }
            if (params.pop_file_txt.first != "none")
            {
                pathify(params.pop_file_txt);
            }
        }
        catch (po::error &e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            return 1;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    catch(...)
    {
        std::cerr << "Unknown error!" << "\n";
        return 1;
    }

    return (0);
}


template<typename RNG>
void
createCheckpoints(NSGAII<RNG> & optimiser, MetronamicaOF2Parameters & params, std::vector<double> & ref_point, std::vector<double> & unitise_point)
{
    boost::shared_ptr<SavePopCheckpoint> save_pop(new SavePopCheckpoint(params.save_freq, params.save_dir.second));
    boost::shared_ptr<SaveFirstFrontCheckpoint> save_front(new SaveFirstFrontCheckpoint(params.save_freq, params.save_dir.second));
    boost::shared_ptr<Hypervolume> hvol(new Hypervolume(params.save_freq, params.save_dir.second, Hypervolume::TERMINATION, params.max_gen_hvol, ref_point, unitise_point, Hypervolume::MAXIMISE));
    boost::shared_ptr<MetricLinePlot> hvol_plot(new MetricLinePlot(hvol));
    boost::shared_ptr<MaxGenCheckpoint> maxgen(new MaxGenCheckpoint(params.max_gen));
    std::string mail_subj("Hypervolume of front from Metro calibrator ");
    boost::shared_ptr<MailCheckpoint> mail(new MailCheckpoint(params.mail_hvol_gen, hvol, mail_subj, params.save_dir.second / "mail_log.log"));
    std::string jeffs_address("jeffrey.newman@adelaide.edu.au");
    std::string charles_address("charles.p.newland@adelaide.edu.au");
    mail->addAddress(jeffs_address);
    mail->addAddress(charles_address);
    boost::shared_ptr<PlotFrontVTK> plotfront(new PlotFrontVTK);
    boost::shared_ptr<SignalCheckpoint> signal_handler(new SignalCheckpoint(SIGINT));

    optimiser.add_checkpoint(save_pop);
    optimiser.add_checkpoint(save_front);
    optimiser.add_checkpoint(hvol);
    optimiser.add_checkpoint(mail);
    optimiser.add_checkpoint(hvol_plot);
    optimiser.add_checkpoint(plotfront);
    optimiser.add_checkpoint(maxgen);
    optimiser.add_checkpoint(signal_handler);
}

#include "MetronamicaCalibrationObjectiveFunction.h"

void
postProcessResults(MetronamicaCalibrationObjectiveFunction & metro_eval, PopulationSPtr pop, MetronamicaOF2Parameters & params)
{
    Population & first_front = pop->getFronts()->at(0);

    int i = 0;
    BOOST_FOREACH(IndividualSPtr ind, first_front)
                {
                    std::vector<double> objectives;
                    std::vector<double> constraints;
                    boost::filesystem::path save_ind_dir = params.save_dir.second / ("individual_" + std::to_string(i++));
                    if (!boost::filesystem::exists(save_ind_dir)) boost::filesystem::create_directory(save_ind_dir);
                    std::tie(objectives, constraints) = metro_eval(ind->getRealDVVector(), ind->getIntDVVector(), save_ind_dir);
                    ind->setObjectives(objectives);
                    ind->setConstraints(constraints);
                    std::cout << *ind << std::endl;
                }

    boost::filesystem::path save_file = params.save_dir.second / "final_front.xml";
    std::ofstream ofs(save_file.c_str());
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(first_front);

    boost::filesystem::path save_file2 = params.save_dir.second /  "final_front.txt";
    std::ofstream ofs2(save_file2.c_str());
    assert(ofs2.good());
    ofs2 << first_front;
}

#endif //CHARLES_METRO_CAL_METRONAMICAOF2UTILITY_H
