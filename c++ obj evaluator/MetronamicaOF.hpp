//
//  MetronamicaOF.hpp
//  MetronamicaCalibrator
//
//  Created by a1091793 on 9/05/2016.
//  Copyright © 2016 University of Adelaide and Bushfire and Natural Hazards CRC. All rights reserved.
//

#ifndef MetronamicaOF_hpp
#define MetronamicaOF_hpp

#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include "Evaluation.hpp"

class MetronamicaOF : public EvaluatorBase
{
    int num_objectives;
    int num_real_decision_vars;
    int num_int_decision_vars;
    int num_constraints;
    int replicates;
    double min_dv_value;
    double max_dv_value;
    std::string geo_cmd;
    boost::filesystem::path java_geoproj_edit;
    std::string mck_cmd;
    std::string wine_temporary_dir;
    boost::filesystem::path template_dir;
    boost::filesystem::path temporary_dir;
    std::string geoproject_name;
    std::string logfile_name;
    std::string actual_map;
    std::string original_map;
    std::string masking_map;
    std::string fks_coefficients;
    std::vector<int> rand_seeds { 1000,1001,1002,1003,1004,10005,1006,1007,1008,1009 };
    
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
        return true
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
        int begin = file_contents.find(search_term) + 20;
        int end = file_contents.find(search_term_2, begin);
        std::string diff_str = file_contents.substr(begin, (begin-end));
        double diff = std::stod(diff_str);
        return (diff);
    }


public:
    MetronamicOF()
    :   num_objectives(2),
    num_real_decision_vars(371),
    num_int_decision_vars(0),
    num_constraints(0),
    min_dv_value(0),
    max_dv_value(1),
    prob_defs(num_real_decision_vars, min_dv_value, max_dv_value,  num_int_decision_vars, 0, 0, num_objectives, MINIMISATION, num_constraints),
    objectives_and_constrataints(std::piecewise_construct, std::make_tuple(num_objectives, std::numeric_limits<double>::max()), std::make_tuple(num_constraints))
    {
        analysisNum = createAnalysis();
        loadMap1(analysisNum, actual_map);
        loadOriginalMap(analysisNum, original_map);
        loadMaskingMap(analysisNum, masking_map);
        loadTransitionFuzzyWeights(analysisNum, fks_coefficients);
        
        
    }
    
    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {
        std::vector<double> & obj = this->objectives_and_constrataints.first;
        obj[0] = 0; obj[1] = 0;
        
        for (int j = 0; j < 10; ++j)
        {
            
            boost::filesystem::path ph = boost::filesystem::unique_path(temporary_dir / "%%%%-%%%%-%%%%-%%%%");
            create_directories(ph);
            copyDir(template_dir, ph)
            std::string tmp_dir_name = ph.filename.string();
            std::string geoproject_path = wine_temporary_dir + "\\" + tmp_dir_name + "\\" + geoproject_name;
            std::string logfile_path = wine_temporary_dir + "\\" + tmp_dir_name + "\\"  + logfile_name;
            
            boost::filesystem::current_path(ph);
            std::stringstream cmd1, cmd2, cmd3, cmd4;
            
            // Modify Geoproject file with decision variables and random seed
            cmd4 << "java -jar " << java_geoproj_edit.string();
            for (int i = 0; i < num_real_decision_vars; ++i)
            {
                cmd4 << " " << num_real_decision_vars[i];
            }
            cmd4 << " " << rand_seeds[j];
            int i4 = system(cmd4.c_str());
            
            
            //Call the model
            cmd1 << "wine " << geo_cmd << " --Reset --Save " << geoproject_path;
            int i1 = system(cmd1.c_str());
            cmd2 << geo_cmd << " --Run --Save --LogSettings " << logfile_path << " " << geoproject_path;
            int i2 = system(cmd2.c_str());
            
            // Calc FKS
            output_map = ph / "Log" / "Land_use" / "Land use map_2000-Jan-01 00_00_00.rst"
            loadMap2(analysisNum, output_map);
            obj[0] += getFuzzyKappaSim(analysisNum);
            
            //Fourth calculate clumpiness values
            std::string clumpcsl = wine_temporary_dir + "\\" + tmp_dir_name\\Log\\Land_use\\clump.csl";
            std::string loglog = wine_temporary_dir + "\\tmp_dir_name\\Log\\Land_use\\auto_cal_log.log";
            std::string logdir = wine_temporary_dir + "\\tmp_dir_name\\Log\\Land_use";
            cmd3 << "wine " << mck_cmd << " /RunComparisonSet " << clumpcsl << " " << loglog << " "
            << logdir;
            int i3 = system(cmd3.c_str());
            
            // Take avg of clumpiness
            double avg_clump = 0;
            boost::filesystem::path gre = ph / "Log" / "Land_use" / "moving window based structure_4.sts";
            avg_clump += abs(overall_diff(gre));
            boost::filesystem::path hld = ph / "Log" / "Land_use" / "moving window based structure_5.sts";
            avg_clump += abs(overall_diff(hld));
            boost::filesystem::path hhd = ph / "Log" / "Land_use" / "moving window based structure_6.sts";
            avg_clump += abs(overall_diff(hhd));
            boost::filesystem::path ind = ph / "Log" / "Land_use" / "moving window based structure_7.sts";
            avg_clump += abs(overall_diff(ind));
            boost::filesystem::path ser = ph / "Log" / "Land_use" / "moving window based structure_8.sts";
            avg_clump += abs(overall_diff(ser));
            boost::filesystem::path scu = ph / "Log" / "Land_use" / "moving window based structure_9.sts";
            avg_clump += abs(overall_diff(scu));
            boost::filesystem::path forr = ph / "Log" / "Land_use" / "moving window based structure_10.sts";
            avg_clump += abs(overall_diff(forr));
            boost::filesystem::path exg = ph / "Log" / "Land_use" / "moving window based structure_11.sts";
            avg_clump += abs(overall_diff(exg));
            boost::filesystem::path nat = ph / "Log" / "Land_use" / "moving window based structure_12.sts";
            avg_clump += abs(overall_diff(nat));
            boost::filesystem::path rec = ph / "Log" / "Land_use" / "moving window based structure_13.sts";
            avg_clump += abs(overall_diff(rec));
            avg_clump /= 10.0;
            obj[1] += avg_clump;
            
            boost::filesystem::current_path(temporary_dir);
            boost::filesystem::remove_all(ph)
        }
        
        obj[0] /= replicates;
        obj[1] /= replicates;
        return (this->objectives_and_constrataints)
    }
    
    ProblemDefinitions & getProblemDefinitions()
    {
        return (prob_defs);
    }
};

#endif /* MetronamicaOF_hpp */
