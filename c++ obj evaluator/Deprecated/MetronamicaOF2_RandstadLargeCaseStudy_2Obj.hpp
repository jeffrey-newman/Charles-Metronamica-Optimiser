//
//  MetronamicaOF.hpp
//  MetronamicaCalibrator
//
//  Created by a1091793 on 9/05/2016.
//  Copyright © 2016 University of Adelaide and Bushfire and Natural Hazards CRC. All rights reserved.
//

#ifndef MetronamicaOF_hpp
#define MetronamicaOF_hpp

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <tuple>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp> // include Boost, a C++ library
#include <boost/date_time.hpp>
#include <boost/optional.hpp>
#include <boost/timer/timer.hpp>
#include "Evaluation.hpp"
#include "MapComparison_0_4.h"
#include <blink/raster/PngPlotter.h>
#include <blink/raster/utility.h>
#include "GeoprojectManipSmallCaseStudy.h"


class MetronamicaOF2RandstadLargeCaseStudy2Obj : public ObjectivesAndConstraintsBase
{
    int num_objectives;
    int num_real_decision_vars;
    int num_int_decision_vars;
    int num_constraints;
    int replicates;
    boost::filesystem::path geo_cmd;
    boost::filesystem::path java_geoproj_edit;
    boost::filesystem::path mck_cmd;
    boost::filesystem::path wine_cmd;
    boost::filesystem::path java_cmd;
    boost::filesystem::path template_dir;
    boost::filesystem::path save_dir;
    boost::filesystem::path working_dir;
    boost::filesystem::path worker_dir;
    std::string wine_temp_dir; // same path as temporary dir, but in the wine (windows) path format.
    std::string geoproject_name;
    boost::filesystem::path metro_logfile_name;
    std::string cp_metro_log_name;
    boost::filesystem::path actual_map;
    boost::filesystem::path original_map;
    boost::filesystem::path masking_map;
    boost::filesystem::path fks_coefficients;
    boost::filesystem::path wine_regedit;
    boost::filesystem::path previous_log_file;
    std::vector<int> rand_seeds { 1000,1001,1002,1003,1004,1005,1006,1007,1008,1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020 };
    int analysisNum;
    std::vector<double> min_dv_values  = {500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   500,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   -100,   -1000,   0.05,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
    std::vector<double> max_dv_values =  {5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   5000,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   100,   1000,   5,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1   };
    std::vector<int> int_lowerbounds;
    std::vector<int> int_upperbounds;
    std::vector<MinOrMaxType> minimise_or_maximise = {MAXIMISATION, MINIMISATION};
    int evaluator_id;
    bool is_logging;
    int eval_count;

    const int MAP1 = 0;
    const int MAP_ACTUAL = 0;
    const int MAP2 = 1;
    const int MAP_SIMULATED = 1;
    const int ORIGINAL = 2;

    ProblemDefinitionsSPtr prob_defs;
    std::pair<std::vector<double>, std::vector<double> > objectives_and_constrataints;

    std::vector<std::tuple<int, int, int> > colour_mapper;


    //Copies entire directory - so that each geoproject is running in a different directory.
    bool copyDir(
            boost::filesystem::path const & source,
            boost::filesystem::path const & destination
            )
    {
        namespace fs = boost::filesystem;
        try
        {
            // Check whether the function call is valid
            if(
                    !fs::exists(source) ||
                    !fs::is_directory(source)
                    )
            {
                std::cerr << "Source directory " << source.string()
                          << " does not exist or is not a directory." << '\n'
                             ;
                return false;
            }
            if(fs::exists(destination))
            {
                std::cerr << "Destination directory " << destination.string()
                          << " already exists." << '\n'
                             ;
                return false;
            }
            // Create the destination directory
            if(!fs::create_directory(destination))
            {
                std::cerr << "Unable to create destination directory"
                          << destination.string() << '\n'
                             ;
                return false;
            }
        }
        catch(fs::filesystem_error const & e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        // Iterate through the source directory
        for(
            fs::directory_iterator file(source);
            file != fs::directory_iterator(); ++file
            )
        {
            try
            {
                fs::path current(file->path());
                if(fs::is_directory(current))
                {
                    // Found directory: Recursion
                    if(
                            !copyDir(
                                current,
                                destination / current.filename()
                                )
                            )
                    {
                        return false;
                    }
                }
                else
                {
                    // Found file: Copy
                    fs::copy_file(
                                current,
                                destination / current.filename()
                                );
                }
            }
            catch(fs::filesystem_error const & e)
            {
                std:: cerr << e.what() << '\n';
            }
        }
        return true;
    }

    //Reads an entire file into string in memory
    std::string readfile(std::string file_name)
    {
        std::ifstream t(file_name.c_str());
        t.seekg(0, std::ios::end);
        size_t size = t.tellg();
        std::string buffer(size, ' ');
        t.seekg(0);
        t.read(&buffer[0], size);
        return buffer;
    }

    // Finds where the overall_difference is recorded in the file.
    double overall_diff(boost::filesystem::path & file)
    {
        std::string file_contents = readfile(file.string());
        std::string search_term_1 = "overall_difference";
        std::string search_term_2 = "\"";
        int begin = file_contents.find(search_term_1) + 20;
        int end = file_contents.find(search_term_2, begin);
        std::string diff_str = file_contents.substr(begin, (end-begin));
        double diff = std::stod(diff_str);
        return (diff);
    }




public:
    MetronamicaOF2RandstadLargeCaseStudy2Obj(boost::filesystem::path & metro_exe,
                   boost::filesystem::path & mck_exe,
                   boost::filesystem::path & wine_exe,
                   boost::filesystem::path & java_exe,
                   boost::filesystem::path & geoproj_edit_jar,
                   boost::filesystem::path & template_path,
                   boost::filesystem::path & working_dir,
                                 boost::filesystem::path & save_dir,
                   std::string &_wine_work_dir,
                   std::string &_geoproj_name,
                   boost::filesystem::path & _logfile_name,
                   boost::filesystem::path & actual_map_path,
                   boost::filesystem::path & original_map_path,
                   boost::filesystem::path & masking_map_path,
                   boost::filesystem::path &  fks_coefficients_path,
                   boost::filesystem::path & wine_regedit_path,
                   int _id = 0,
                   bool _is_logging = false,
                   int _replicates = 10)
        :   num_objectives(2),
          num_real_decision_vars(238),
          num_int_decision_vars(0),
          num_constraints(0),
          replicates(_replicates),
          geo_cmd(metro_exe),
          java_geoproj_edit(geoproj_edit_jar),
          mck_cmd(mck_exe),
          wine_cmd(wine_exe),
          java_cmd(java_exe),
          template_dir(template_path),
          working_dir(working_dir),
          save_dir(save_dir),
          wine_temp_dir(_wine_work_dir),
          geoproject_name(_geoproj_name),
          metro_logfile_name(_logfile_name),
          actual_map(actual_map_path),
          original_map(original_map_path),
          masking_map(masking_map_path),
          fks_coefficients(fks_coefficients_path),
          wine_regedit(wine_regedit_path),
          int_lowerbounds(0, std::numeric_limits<int>::min()),
          int_upperbounds(0, std::numeric_limits<int>::max()),
          prob_defs(new ProblemDefinitions(min_dv_values, max_dv_values,  int_lowerbounds, int_upperbounds, minimise_or_maximise, num_constraints)),
          objectives_and_constrataints(std::piecewise_construct, std::make_tuple(num_objectives, std::numeric_limits<double>::max()), std::make_tuple(num_constraints)),
          evaluator_id(_id),
          is_logging(_is_logging),
          eval_count(0)
    {
        analysisNum = createAnalysis();
        loadMapActual(analysisNum, actual_map.c_str());
        loadOriginalMap(analysisNum, original_map.c_str());
        loadMaskingMap(analysisNum, masking_map.c_str());
        loadTransitionFuzzyWeights(analysisNum, fks_coefficients.c_str());
        numClasses(analysisNum, 9);

        std::string temp_dir_template = "Metro_Cal_OF_worker" + std::to_string(evaluator_id) + "_%%%%-%%%%";
        worker_dir = boost::filesystem::unique_path(working_dir / temp_dir_template);
        //            create_directories(ph);
        copyDir(template_dir, worker_dir);


        namespace fs = boost::filesystem;
        std::string metro_cp_log_name = "calibration_log_%%%%-%%%%.xml";
        boost::filesystem::path metro_cp_log_path = boost::filesystem::unique_path(worker_dir / metro_cp_log_name);
        fs::copy_file(
                    metro_logfile_name,
                    metro_cp_log_path
                    );
        cp_metro_log_name = metro_cp_log_path.filename().string();

        //        std::string filename = "logWorker" + std::to_string(evaluator_id) + "_WineRegEdit_" + boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) + ".log";
        //        boost::filesystem::path log_file_name = working_dir / filename;
        //        std::ofstream logging_file;
        //        if (is_logging)
        //        {
        //            logging_file.open(log_file_name.c_str(), std::ios_base::app);
        //            if (!logging_file.is_open()) is_logging = false;
        //        }

        //        std::stringstream cmd;
        //        cmd << wine_cmd << " regedit " << wine_regedit_path;
        //        if (is_logging) cmd << " >> \"" << log_file_name.c_str() << "\" 2>&1";
        //        if (is_logging) logging_file << "Running: " << cmd.str() << "\n";
        //        system(cmd.str().c_str());

        colour_mapper.push_back(std::make_tuple(255,   255,   160));
        colour_mapper.push_back(std::make_tuple(255,   128,     0));
        colour_mapper.push_back(std::make_tuple(255,     0,     0));
        colour_mapper.push_back(std::make_tuple( 78,     0,   192));
        colour_mapper.push_back(std::make_tuple(158,    12,   234));
        colour_mapper.push_back(std::make_tuple(255,    87,   255));
        colour_mapper.push_back(std::make_tuple(  0,   192,     0));
        colour_mapper.push_back(std::make_tuple(192,   157,     0));
        colour_mapper.push_back(std::make_tuple(  0,     0,     0));
        colour_mapper.push_back(std::make_tuple(  0,   128,   255));

        //Make sure the number of dv is correct
        BOOST_ASSERT(max_dv_values.size() == 520);
    }

    ~MetronamicaOF2RandstadLargeCaseStudy2Obj()
    {
//        boost::filesystem::remove_all(worker_dir);
    }


    boost::optional<boost::filesystem::path>
    runMetro( std::string & mod_proj_file, bool is_logging, boost::filesystem::path & debug_log_file_name, std::ofstream & logging_file)
    {
        std::stringstream cmd1, cmd2;
        std::string wine_proj_path = "\"" + wine_temp_dir + "\\\\" + worker_dir.filename().string() + "\\\\" + mod_proj_file + "\"";
        std::string metro_log_path = "\"" + wine_temp_dir + "\\\\" + worker_dir.filename().string() + "\\\\" + cp_metro_log_name + "\"";
        //Call the model
        cmd1 << "timeout --kill-after=20m 19m  " << wine_cmd << " " << geo_cmd << " --Reset --Save " << wine_proj_path ;
        if (is_logging) cmd1 << " >> \"" << debug_log_file_name.c_str() << "\" 2>&1";
        if (is_logging) logging_file << "Running: " << cmd1.str() << std::endl;
        if (is_logging)  logging_file.close();
        int i1 = system(cmd1.str().c_str());
        if (is_logging) logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
        if (!logging_file.is_open()) is_logging = false;

        cmd2 << "timeout --kill-after=20m 19m  " << wine_cmd << " " << geo_cmd << " --Run --Save --LogSettings " << metro_log_path << " " << wine_proj_path ;
        if (is_logging) cmd2 << " >> \"" << debug_log_file_name.c_str() << "\" 2>&1";
        if (is_logging) logging_file << "Running: " << cmd2.str() << std::endl;
        if (is_logging) logging_file.close();
        int i2 = system(cmd2.str().c_str());
        if (is_logging) logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
        if (!logging_file.is_open()) is_logging = false;

        boost::filesystem::path output_map = worker_dir / "Log" / "Land_use" / "Land use map_2000-Jan-01 00_00_00.rst";
        if (boost::filesystem::exists(output_map))
        {
            return output_map;
        }
        else
        {
            return boost::none;
        }
    }

    double
    calcClumpDiff(int analysisNum, int luc_val, std::ostream & log)
    {
        double clump_sim = getClumpiness(analysisNum, MAP_SIMULATED, luc_val);
        double clump_act = getClumpiness(analysisNum, MAP_ACTUAL, luc_val);
        double diff = std::abs(clump_sim - clump_act);
        if (is_logging) log << "clump diff: " << clump_sim << " - " << clump_act << " = " << diff << "\n";
        return (diff);
    }

    std::pair<std::vector<double>, std::vector<double> > &
    getObjectivesAcrossReplicates(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars, boost::filesystem::path save_path, std::vector<std::pair<std::vector<double>, std::vector<double> > > & results)
    {
        if (!boost::filesystem::exists(save_path)) boost::filesystem::create_directory(save_path);

        std::pair<std::vector<double>, std::vector<double> >  objectives;
        objectives.first.resize(replicates);
        objectives.second.resize(replicates);

        std::string filename = "logWorker" + std::to_string(evaluator_id) + "_EvalNo" + std::to_string(eval_count) + "_" + boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) + ".log";
        boost::filesystem::path debug_log_file_name = save_dir / filename;
        std::ofstream logging_file;
        if (is_logging)
        {
            logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
            if (!logging_file.is_open())
            {
                is_logging = false;
                std::cout << "attempt to log failed\n";
            }
        }

        boost::filesystem::path objectives_file = save_path / "metrics_for_each_replicate.txt";
        std::ofstream objectives_fs(objectives_file.c_str());


        std::vector<double> & obj = objectives_and_constrataints.first;
        obj[0] = 0; obj[1] = 0;

        for (int j = 0; j < replicates; ++j)
        {
            std::pair<double, double> metric_vals = calcMetrics(worker_dir, real_decision_vars, int_decision_vars, is_logging, logging_file, debug_log_file_name, j);
            double fks =  metric_vals.first;
            double clump = metric_vals.second;
            objectives.first[j] = fks;
            objectives.second[j] = clump;
            objectives_fs << "replicate " << j << " fks: " << fks << " clumpiness: " << clump << "\n";
            obj[0] += fks;
            obj[1] += clump;
            boost::filesystem::path save_replicate_path = save_path / ("replicate_" + std::to_string(j));
//            if (!boost::filesystem::exists(save_replicate_path)) boost::filesystem::create_directory(save_replicate_path);
            if (boost::filesystem::exists(save_replicate_path)) boost::filesystem::remove_all(save_replicate_path);
            copyDir(worker_dir, save_replicate_path);
            boost::filesystem::path output_map = worker_dir / "Log" / "Land_use" / "Land use map_2000-Jan-01 00_00_00.rst";
            if (boost::filesystem::exists(output_map))
            {
                boost::filesystem::path png_path = save_path  / ("replicate_" + std::to_string(j) + ".png");
                blink::raster::gdal_raster<int> out_raster = blink::raster::open_gdal_raster<int>(output_map, GA_ReadOnly);
                blink::raster::printRaster2PNG(out_raster, colour_mapper, png_path);
            }

        }

        obj[0] /= replicates;
        obj[1] /= replicates;
        ++eval_count;

        if (is_logging) logging_file << "\n\n\n FKS: " << obj[0] << "\n Average Clump Diff: " << obj[1] << "\n";

        if (is_logging) logging_file.close();

//        boost::filesystem::remove_all(previous_log_file);
//        previous_log_file = debug_log_file_name;

        results.push_back(objectives);
        return (objectives_and_constrataints);
    }


    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars, boost::filesystem::path save_path)
    {
        if (!boost::filesystem::exists(save_path)) boost::filesystem::create_directory(save_path);

        std::string filename = "logWorker" + std::to_string(evaluator_id) + "_EvalNo" + std::to_string(eval_count) + "_" + boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) + ".log";
        boost::filesystem::path debug_log_file_name = save_dir / filename;
        std::ofstream logging_file;
        if (is_logging)
        {
            logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
            if (!logging_file.is_open())
            {
                is_logging = false;
                std::cout << "attempt to log failed\n";
            }
        }

        boost::filesystem::path objectives_file = save_path / "metrics_for_each_replicate.txt";
        std::ofstream objectives_fs(objectives_file.c_str());


        std::vector<double> & obj = objectives_and_constrataints.first;
        obj[0] = 0; obj[1] = 0;

        for (int j = 0; j < replicates; ++j)
        {
            std::pair<double, double> metric_vals = calcMetrics(worker_dir, real_decision_vars, int_decision_vars, is_logging, logging_file, debug_log_file_name, j);
            double fks =  metric_vals.first;
            double clump = metric_vals.second;
            objectives_fs << "replicate " << j << " fks: " << fks << " clumpiness: " << clump << "\n";
            obj[0] += fks;
            obj[1] += clump;
            boost::filesystem::path save_replicate_path = save_path / ("replicate_" + std::to_string(j));
//            if (!boost::filesystem::exists(save_replicate_path)) boost::filesystem::create_directory(save_replicate_path);
            if (boost::filesystem::exists(save_replicate_path)) boost::filesystem::remove_all(save_replicate_path);
            copyDir(worker_dir, save_replicate_path);
            boost::filesystem::path output_map = worker_dir / "Log" / "Land_use" / "Land use map_2000-Jan-01 00_00_00.rst";
            if (boost::filesystem::exists(output_map))
            {
                boost::filesystem::path png_path = save_path  / ("replicate_" + std::to_string(j) + ".png");
                blink::raster::gdal_raster<int> out_raster = blink::raster::open_gdal_raster<int>(output_map, GA_ReadOnly);
                blink::raster::printRaster2PNG(out_raster, colour_mapper, png_path);
            }

        }

        obj[0] /= replicates;
        obj[1] /= replicates;
        ++eval_count;

        if (is_logging) logging_file << "\n\n\n FKS: " << obj[0] << "\n Average Clump Diff: " << obj[1] << "\n";

        if (is_logging) logging_file.close();

//        boost::filesystem::remove_all(previous_log_file);
//        previous_log_file = debug_log_file_name;

        return (objectives_and_constrataints);




    }

    std::pair<double, double>
    calcMetrics(boost::filesystem::path & worker_dir, const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars, bool is_logging, std::ofstream & logging_file, boost::filesystem::path & debug_log_file_name, int rand_seed_id)
    {
        std::vector<double> obj(2, 0);
        boost::filesystem::path orig_geoproj_path = worker_dir / geoproject_name;
        std::string mod_proj_file(orig_geoproj_path.stem().string() + "_mod" + orig_geoproj_path.extension().string());
        boost::filesystem::path mod_geoproj_path = worker_dir / mod_proj_file;
        //boost::filesystem::path logfile_path = temporary_dir / logfile_name;

        boost::filesystem::current_path(worker_dir);
        std::stringstream /*cmd3,*/ cmd4;    //mcd3 is for MCK.

        boost::shared_ptr<boost::timer::auto_cpu_timer> timer;
        // Modify Geoproject file with decision variables and random seed
        //            {
        if (is_logging) timer.reset(new boost::timer::auto_cpu_timer(logging_file));
        //                boost::timer::auto_cpu_timer t(logging_file);
        if (is_logging) logging_file << "number real decision vars : " << real_decision_vars.size() << std::endl;
//        cmd4 << "timeout --kill-after=30s 27s  " << java_cmd << " -jar " << java_geoproj_edit << " ";
//        cmd4 << orig_geoproj_path<< " " << mod_geoproj_path;
//        for (int i = 0; i < num_real_decision_vars; ++i)
//        {
//            cmd4 << " " << real_decision_vars[i];
//        }
//        cmd4 << " " << rand_seeds[rand_seed_id];
//        if (is_logging) cmd4 << " >> \"" << debug_log_file_name.c_str() << "\" 2>&1";
//
//
//        if (is_logging) logging_file << "Running: " << cmd4.str() << std::endl;
//        if (is_logging) logging_file.close();
//        int i4 = system(cmd4.str().c_str());
//        if (is_logging) logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
//        if (!logging_file.is_open()) is_logging = false;
        geoprojectEdit(orig_geoproj_path, mod_geoproj_path, real_decision_vars, rand_seeds[rand_seed_id]);
        if (is_logging) logging_file << "Timing for manipulating decision variable : " << std::endl;




//        // If the java file manipulation fails, wait three seconds and try again.
//        if (!(boost::filesystem::exists(mod_geoproj_path)))
//        {
//            std::this_thread::sleep_for (std::chrono::seconds(3));
//            if (is_logging) logging_file << "Running: " << cmd4.str() << std::endl;
//            if (is_logging) logging_file.close();
//            int i4 = system(cmd4.str().c_str());
//            if (is_logging) logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
//            if (!logging_file.is_open())
//            {
//                is_logging = false;
//                std::cout << "Unable to open logging file: " << debug_log_file_name.c_str() << std::endl;
//            }
//            if (is_logging) logging_file << "Timing for manipulating decision variable : " << std::endl;
//            if (!(boost::filesystem::exists(mod_geoproj_path)))
//            {
//                // If still fails, return.
//                if (is_logging) logging_file << "Was unable to successfully run Metronamica on decision variables\n";
//                obj[0] = -1;
//                obj[1] = 10;
//                return std::make_pair(obj[0], obj[1]);
//            }
//        }


        //            }

        //            {
        if (is_logging) timer.reset(new boost::timer::auto_cpu_timer(logging_file));
        boost::optional<boost::filesystem::path> output_map = runMetro(mod_proj_file, is_logging, debug_log_file_name, logging_file);
        if (!output_map)
        {
            output_map = runMetro(mod_proj_file, is_logging, debug_log_file_name, logging_file);
            if (!output_map)
            {
                std::this_thread::sleep_for (std::chrono::seconds(3));
                //Write error message and assume infeasible set of parameters and so assign worse OF values. (-1, 10)
                if (is_logging) logging_file << "Was unable to successfully run Metronamica on decision variables\n";

                obj[0] = -1;
                obj[1] = 10;
                return std::make_pair(obj[0], obj[1]);
//                return (objectives_and_constrataints);
            }
        }
        if (is_logging) logging_file << "Timing for Resetting and running Metronamica : " << std::endl;
        //            }

        //            {
        if (is_logging) timer.reset(new boost::timer::auto_cpu_timer(logging_file));
        try
        {
            loadMapSimulated(analysisNum, (*output_map).c_str());
            if (is_logging) logging_file << "Simulated map: " << (*output_map).string() << "\n";
            double fks = getFuzzyKappaSim(analysisNum);
            obj[0] = fks;
            if (is_logging) logging_file << "FKS: " << fks << "\n";
        }
        catch (std::runtime_error err)
        {
            try
            {
                std::cout << err.what() << std::endl;
                std::this_thread::sleep_for (std::chrono::seconds(3));
                loadMapSimulated(analysisNum, (*output_map).c_str());
                if (is_logging) logging_file << "Simulated map: " << (*output_map).string() << "\n";
                double fks = getFuzzyKappaSim(analysisNum);
                obj[0] = fks;
                if (is_logging) logging_file << "FKS: " << fks;
            }
            catch (...)
            {
                //Write error message and assume infeasible set of parameters and so assign worse OF values. (-1, 10)
                if (is_logging) logging_file << "Was unable to calculate FKS\n";
                obj[0] = -1;
                obj[1] = 10;
                return std::make_pair(obj[0], obj[1]);
//                return (objectives_and_constrataints);
            }
        }
        if (is_logging) logging_file << "Timing for Calculating FKS: " << std::endl;
        //            }



        //            //Fourth calculate clumpiness values
        //            std::string clumpcsl = wine_temp_dir + "\\\\" + worker_dir.filename().string() + "\\\\Log\\\\Land_use\\\\clump.csl";
        //            std::string loglog = wine_temp_dir + "\\\\" + worker_dir.filename().string() + "\\\\Log\\\\Land_use\\\\auto_cal_log.log";
        //            std::string logdir = wine_temp_dir + "\\\\" + worker_dir.filename().string() + "\\\\Log\\\\Land_use";

        //            cmd3 << wine_cmd << " " << mck_cmd << " /RunComparisonSet \"" << clumpcsl << "\" \"" << loglog << "\" \""
        //            << logdir << "\"" ;
        //            if (is_logging) cmd3 << " >> \"" << debug_log_file_name.c_str() << "\" 2>&1";
        //            if (is_logging) logging_file << "Running: " << cmd3.str() << std::endl;
        //            if (is_logging) logging_file.close();
        //            int i3 = system(cmd3.str().c_str());
        //            if (is_logging) logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
        //            if (!logging_file.is_open()) is_logging = false;


        //            {
        if (is_logging) timer.reset(new boost::timer::auto_cpu_timer(logging_file));
        try
        {
            // Take avg of clumpiness
            double avg_clump = 0;
//            Agriculture                 0
//            _Greenhouses_               1
//            _Residential_               2
//            _Industy_                   3
//            _Services_                  4
//            _Socio-cultural uses_       5
//            _Nature_                    6
//            _Recreation areas_          7
//            Airport                     8
//            Water                       9
            int gre_val = 1;
            if (is_logging) logging_file << "Greenhouses ";
            avg_clump += calcClumpDiff(analysisNum, gre_val, logging_file);
            int res_val = 2;
            if (is_logging) logging_file << "_Residential_ ";
            avg_clump +=  calcClumpDiff(analysisNum, res_val, logging_file);
            int ind_val = 3;
            if (is_logging) logging_file << "_Industry_  ";
            avg_clump +=  calcClumpDiff(analysisNum, ind_val, logging_file);
            int ser_val = 4;
            if (is_logging) logging_file << "_Services_ ";
            avg_clump +=  calcClumpDiff(analysisNum, ser_val, logging_file);
            int scu_val = 5;
            if (is_logging) logging_file << "_Socio cultural uses_ ";
            avg_clump +=  calcClumpDiff(analysisNum, scu_val, logging_file);
            int nat_val = 6;
            if (is_logging) logging_file << "_Nature_  ";
            avg_clump +=  calcClumpDiff(analysisNum, nat_val, logging_file);
            int rec_val = 7;
            if (is_logging) logging_file << "_Recreation areas_ ";
            avg_clump +=  calcClumpDiff(analysisNum, rec_val, logging_file);
            avg_clump /= 7;
            obj[1] = avg_clump;
            if (is_logging) logging_file << "Avg abs. diff clumpiness: " << avg_clump << "\n";

        }
        catch (...)
        {
            //Write error message and assume infeasible set of parameters and so assign worse OF values. (-1, 10)
            if (is_logging) logging_file << "Was unable to calculate avg. clumpiness difference\n";
            obj[0] = -1;
            obj[1] = 10;
            return std::make_pair(obj[0], obj[1]);
//            return (objectives_and_constrataints);
        }
        if (is_logging) logging_file << "Timing for Calculating Clumpiness: " << std::endl;
        if (is_logging) timer.reset();
        //            }


        //            boost::filesystem::current_path(temporary_dir);

        return std::make_pair(obj[0], obj[1]);

    }

    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {

        std::string filename = "logWorker" + std::to_string(evaluator_id) + "_EvalNo" + std::to_string(eval_count) + "_" + boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) + ".log";
        boost::filesystem::path debug_log_file_name = save_dir / filename;
        std::ofstream logging_file;
        if (is_logging)
        {
            logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
            if (!logging_file.is_open())
            {
                is_logging = false;
                std::cout << "attempt to log failed\n";
            }
        }


        std::vector<double> & obj = objectives_and_constrataints.first;
        obj[0] = 0; obj[1] = 0;

        for (int j = 0; j < replicates; ++j)
        {
            std::pair<double, double> metric_vals = calcMetrics(worker_dir, real_decision_vars, int_decision_vars, is_logging, logging_file, debug_log_file_name, j);
            obj[0] += metric_vals.first;
            obj[1] += metric_vals.second;
        }

        obj[0] /= replicates;
        obj[1] /= replicates;
        ++eval_count;

        if (is_logging) logging_file << "\n\n\n FKS: " << obj[0] << "\n Average Clump Diff: " << obj[1] << "\n";

        if (is_logging) logging_file.close();

        boost::filesystem::remove_all(previous_log_file);
        previous_log_file = debug_log_file_name;

        return (objectives_and_constrataints);
    }

    ProblemDefinitionsSPtr getProblemDefinitions()
    {
        return (prob_defs);
    }
};

#endif /* MetronamicaOF_hpp */
