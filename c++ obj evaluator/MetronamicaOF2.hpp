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
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp> // include Boost, a C++ library
#include <boost/date_time.hpp>
#include "Evaluation.hpp"
#include "MapComparison_0_4.h"

class MetronamicaOF2 : public ObjectivesAndConstraintsBase
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
    std::vector<int> rand_seeds { 1000,1001,1002,1003,1004,1005,1006,1007,1008,1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020 };
    int analysisNum;
    std::vector<double> min_dv_values  = {500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,500,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,-1000,.05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   // lower bound of x
    std::vector<double> max_dv_values = {5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,5000,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,1000,5,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // upper bound of x
    std::vector<int> int_lowerbounds;
    std::vector<int> int_upperbounds;
    std::vector<MinOrMaxType> minimise_or_maximise = {MAXIMISATION, MINIMISATION};
    int evaluator_id;
    bool is_logging;
    int eval_count;
    
    const int MAP1 = 0;
    const int MAP_SIMULATED = 0;
    const int MAP2 = 1;
    const int MAP_ACTUAL = 1;
    const int ORIGINAL = 2;

    ProblemDefinitions prob_defs;
    std::pair<std::vector<double>, std::vector<double> > objectives_and_constrataints;

    
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
    MetronamicaOF2(boost::filesystem::path & metro_exe,
                  boost::filesystem::path & mck_exe,
                  boost::filesystem::path & wine_exe,
                  boost::filesystem::path & java_exe,
                  boost::filesystem::path & geoproj_edit_jar,
                  boost::filesystem::path & template_path,
                  boost::filesystem::path & working_dir,
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
    num_real_decision_vars(371),
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
      prob_defs(min_dv_values, max_dv_values,  int_lowerbounds, int_upperbounds, minimise_or_maximise, num_constraints),
     objectives_and_constrataints(std::piecewise_construct, std::make_tuple(num_objectives, std::numeric_limits<double>::max()), std::make_tuple(num_constraints)),
    evaluator_id(_id),
      is_logging(_is_logging),
      eval_count(0)
    {
        analysisNum = createAnalysis();
        loadMap2(analysisNum, actual_map.c_str());
        loadOriginalMap(analysisNum, original_map.c_str());
        loadMaskingMap(analysisNum, masking_map.c_str());
        loadTransitionFuzzyWeights(analysisNum, fks_coefficients.c_str());

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

        std::string filename = "logWorker" + std::to_string(evaluator_id) + "_WineRegEdit_" + boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) + ".log";
        boost::filesystem::path log_file_name = working_dir / filename;
        std::ofstream logging_file;
        if (is_logging)
        {
            logging_file.open(log_file_name.c_str(), std::ios_base::app);
            if (!logging_file.is_open()) is_logging = false;
        }

        std::stringstream cmd;
        cmd << wine_cmd << " regedit " << wine_regedit_path;
        if (is_logging) cmd << " >> \"" << log_file_name.c_str() << "\" 2>&1";
        if (is_logging) logging_file << "Running: " << cmd.str() << "\n";
        system(cmd.str().c_str());
    }

    ~MetronamicaOF2()
    {
        boost::filesystem::remove_all(worker_dir);
    }

    double
    calcClumpDiff(int analysisNum, int luc_val)
    {


        double clump_sim = getClumpiness(analysisNum, MAP_SIMULATED, luc_val);
        double clump_act = getClumpiness(analysisNum, MAP_ACTUAL, luc_val);
        double diff = std::abs(clump_sim - clump_act);
        return (diff);
    }
    
    std::pair<std::vector<double>, std::vector<double> >
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {
        std::pair<std::vector<double>, std::vector<double> > objectives_and_constrataints(std::piecewise_construct, std::make_tuple(num_objectives, std::numeric_limits<double>::max()), std::make_tuple(num_constraints));
        std::string filename = "logWorker" + std::to_string(evaluator_id) + "_EvalNo" + std::to_string(eval_count) + "_" + boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) + ".log";
        boost::filesystem::path debug_log_file_name = working_dir / filename;
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
            

            boost::filesystem::path orig_geoproj_path = worker_dir / geoproject_name;
            std::string mod_proj_file(orig_geoproj_path.stem().string() + "_mod" + orig_geoproj_path.extension().string());
            boost::filesystem::path mod_geoproj_path = worker_dir / mod_proj_file;
            //boost::filesystem::path logfile_path = temporary_dir / logfile_name;
            
            boost::filesystem::current_path(worker_dir);
            std::stringstream cmd1, cmd2, cmd3, cmd4;

            // Modify Geoproject file with decision variables and random seed
            cmd4 << java_cmd << " -jar " << java_geoproj_edit << " ";
            cmd4 << orig_geoproj_path<< " " << mod_geoproj_path;
            for (int i = 0; i < num_real_decision_vars; ++i)
            {
                cmd4 << " " << real_decision_vars[i];
            }
            cmd4 << " " << rand_seeds[j] ;
            if (is_logging) cmd4 << " >> \"" << debug_log_file_name.c_str() << "\" 2>&1";

            if (is_logging) logging_file << "Running: " << cmd4.str() << std::endl;
            if (is_logging) logging_file.close();
            int i4 = system(cmd4.str().c_str());
            if (is_logging) logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
            if (!logging_file.is_open()) is_logging = false;
            
            std::string wine_proj_path = "\"" + wine_temp_dir + "\\\\" + worker_dir.filename().string() + "\\\\" + mod_proj_file + "\"";
            std::string metro_log_path = "\"" + wine_temp_dir + "\\\\" + worker_dir.filename().string() + "\\\\" + cp_metro_log_name + "\"";
            //Call the model
            cmd1 << wine_cmd << " " << geo_cmd << " --Reset --Save " << wine_proj_path ;
            if (is_logging) cmd1 << " >> \"" << debug_log_file_name.c_str() << "\" 2>&1";
            if (is_logging) logging_file << "Running: " << cmd1.str() << std::endl;
            if (is_logging)  logging_file.close();
            int i1 = system(cmd1.str().c_str());
            if (is_logging) logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
            if (!logging_file.is_open()) is_logging = false;

            cmd2 << wine_cmd << " " << geo_cmd << " --Run --Save --LogSettings " << metro_log_path << " " << wine_proj_path ;
            if (is_logging) cmd2 << " >> \"" << debug_log_file_name.c_str() << "\" 2>&1";
            if (is_logging) logging_file << "Running: " << cmd2.str() << std::endl;
            if (is_logging) logging_file.close();
            int i2 = system(cmd2.str().c_str());
            if (is_logging) logging_file.open(debug_log_file_name.c_str(), std::ios_base::app);
            if (!logging_file.is_open()) is_logging = false;
            
            // Calc FKS
            boost::filesystem::path output_map = worker_dir / "Log" / "Land_use" / "Land use map_2000-Jan-01 00_00_00.rst";
            loadMap1(analysisNum, output_map.c_str());
            obj[0] += getFuzzyKappaSim(analysisNum);
            
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
            
            // Take avg of clumpiness
            double avg_clump = 0;            
//            _Greenhouses_               3
//            _Housing low density_       4
//            _Housing high density_      5
//            _Industry_                  6
//            _Services_                  7
//            _Socio cultural uses_       8
//            _Forest_                    9
//            _Extensive grasslands_      10
//            _Nature_                    11
//            _Recreation areas_          12
            int gre_val = 3;
            avg_clump += calcClumpDiff(analysisNum, gre_val);
            int hld_val = 4;
            avg_clump +=  calcClumpDiff(analysisNum, hld_val);
            int hhd_val = 5;
            avg_clump +=  calcClumpDiff(analysisNum, hhd_val);
            int ind_val = 6;
            avg_clump +=  calcClumpDiff(analysisNum, ind_val);
            int ser_val = 7;
            avg_clump +=  calcClumpDiff(analysisNum, ser_val);
            int scu_val = 8;
            avg_clump +=  calcClumpDiff(analysisNum, scu_val);
            int forr_val = 9;
            avg_clump +=  calcClumpDiff(analysisNum, forr_val);
            int exg_val = 10;
            avg_clump +=  calcClumpDiff(analysisNum, exg_val);
            int nat_val = 11;
            avg_clump +=  calcClumpDiff(analysisNum, nat_val);
            int rec_val = 12;
            avg_clump +=  calcClumpDiff(analysisNum, rec_val);
            avg_clump /= 10.0;
            obj[1] += avg_clump;
            
//            boost::filesystem::current_path(temporary_dir);

        }
        
        obj[0] /= replicates;
        obj[1] /= replicates;
        ++eval_count;
        if (is_logging) logging_file.close();
        return (objectives_and_constrataints);
    }
    
    ProblemDefinitions & getProblemDefinitions()
    {
        return (prob_defs);
    }
};

#endif /* MetronamicaOF_hpp */
