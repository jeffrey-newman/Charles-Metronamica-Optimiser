//
// Created by a1091793 on 17/5/17.
//

#ifndef CHARLES_METRO_CAL_METRONAMICACALIBRATIONOBJECTIVEFUNCTION_H
#define CHARLES_METRO_CAL_METRONAMICACALIBRATIONOBJECTIVEFUNCTION_H

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
#include <blink/raster/utility.h> // To open rasters
#include <blink/iterator/zip_range.h>
#include "GeoprojectManipBigCaseStudy.h"
#include "GeoprojectManipSmallCaseStudy.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include "MetronamicaOF2Utility.h"

#include "ColourMapperParsers.h"

enum ObjectivesE {FKS_CLUMP, FKS_CLUMP_KAPPA};
enum CaseStudyE {SMALL_RANDSTAD, LARGE_RANDSTAD};

class MetronamicaCalibrationObjectiveFunction : public ObjectivesAndConstraintsBase
{
    MetronamicaOF2Parameters & params;

    boost::filesystem::path logfile;
    boost::filesystem::path previous_logfile;

    int num_constraints;
    int num_classes;

    int analysisNum;
    std::vector<double> real_lowerbounds  ; //lower bounds
    std::vector<double> real_upperbounds ; // upper bound of x
    std::vector<int> int_lowerbounds;
    std::vector<int> int_upperbounds;

    ObjectivesE obj_t;
    CaseStudyE case_t;

    std::vector<MinOrMaxType> minimise_or_maximise;

    int eval_count;

    const int MAP1 = 0;
    const int MAP_SIMULATED = 0;
    const int MAP2 = 1;
    const int MAP_ACTUAL = 1;
    const int ORIGINAL = 2;

    ProblemDefinitionsSPtr prob_defs;
    std::pair<std::vector<double>, std::vector<double> > objectives_and_constraints;

    bool delete_wine_dir_on_exit = false;
    bool delete_wine_prefix_on_exit = false;

    bool using_wine;
    bool using_timeout;

    std::vector<std::tuple<boost::filesystem::path, boost::filesystem::path, boost::shared_ptr<ColourMapperClassified>,     boost::shared_ptr<MagickWriterClassified>, std::string > > classified_img_rqsts;
    std::vector<std::tuple<boost::filesystem::path, boost::filesystem::path, boost::shared_ptr<ColourMapperGradient>, boost::shared_ptr<MagickWriterGradient>, std::string > > lin_grdnt_img_rqsts;

//    std::vector<std::tuple<int, int, int> > colour_mapper;


    //Copies entire directory - so that each geoproject is running in a different directory.
    bool copyDir(   boost::filesystem::path const & source,
                    boost::filesystem::path const & destination,
                    std::ostream & logging)
    {
        if(params.is_logging) logging << "Copying directory " << source << " to " << destination << std::endl;
        namespace fs = boost::filesystem;
        try
        {
            // Check whether the function call is valid
            if(!fs::exists(source) || !fs::is_directory(source))
            {
                if(params.is_logging) logging << "Source directory " << source.string()
                          << " does not exist or is not a directory." << '\n';
                return false;
            }
            if(fs::exists(destination))
            {
                if(params.is_logging) logging << "Destination directory " << destination.string()
                          << " already exists." << '\n';
                return false;
            }
            // Create the destination directory
            fs::copy_directory(source, destination);
            if(!fs::exists(destination) || !fs::is_directory(destination))
            {
                if(params.is_logging) logging << "Unable to create destination directory"
                          << destination.string() << '\n';
                return false;
            }
        }
        catch(fs::filesystem_error const & e)
        {
            if(params.is_logging) logging << e.what() << '\n';
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
                if(params.is_logging) logging << "descending into: " << current << std::endl;
                if(fs::is_directory(current))
                {
                    // Found directory: Recursion
                    if(!copyDir(current, destination / current.filename(), logging))
                    {
                        return false;
                    }
                }
                else
                {
                    // Found file: Copy
                    if(params.is_logging) logging << "Copying " << current << " to " << destination / current.filename() << std::endl;
                    fs::copy_file(current, destination / current.filename());
                }
            }
            catch(fs::filesystem_error const & e)
            {
                std:: cerr << e.what() << '\n';
            }
        }
        return true;
    }

    //Copies entire directory - so that each geoproject is running in a different directory.
    bool copyFilesInDir(
            boost::filesystem::path const & source,
            boost::filesystem::path const & destination,
            std::ostream & logging
    )
    {
        if(params.is_logging) logging << "Copying files in " << source << " to " << destination << std::endl;
        namespace fs = boost::filesystem;
        try
        {
            // Check whether the function call is valid
            if(!fs::exists(source) || !fs::is_directory(source))
            {
                if(params.is_logging) logging << "Source directory " << source.string()
                          << " does not exist or is not a directory." << '\n';
                return false;
            }
            if(!fs::exists(destination) || !fs::is_directory(destination))
            {
                if(params.is_logging) logging << "Destination directory " << destination.string()
                          << " does not exist or is not a directory." << '\n';
                return false;
            }

        }
        catch(fs::filesystem_error const & e)
        {
            if(params.is_logging) logging << e.what() << '\n';
            return false;
        }
        // Iterate through the source directory
        for(fs::directory_iterator file(source); file != fs::directory_iterator(); ++file )
        {
            try
            {
                fs::path current(file->path());
                if(!(fs::is_directory(current)))  // Should we be checking for other things?
                {
                    // Found file: Copy
                    if(params.is_logging) logging << "Copying " << current << " to " << destination / current.filename() << std::endl;
                    fs::copy_file(current, destination / current.filename());
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
    MetronamicaCalibrationObjectiveFunction( MetronamicaOF2Parameters & _params, ObjectivesE _obj_t, CaseStudyE _case_t, std::vector<double> & _real_lowerbounds, std::vector<double> & _real_upperbounds, int _num_classes)
            :   params(_params),
                previous_logfile("unspecified"),
                num_classes(_num_classes),
                obj_t(_obj_t),
                case_t(_case_t),
                real_lowerbounds(_real_lowerbounds),
                real_upperbounds(_real_upperbounds),
                eval_count(0),
                num_constraints(0)
    {

        std::ofstream logging_file;
        if (params.is_logging)
        {
            std::string filename = "logWorker" + std::to_string(params.evaluator_id)
                                       + "_Constructor_" + boost::posix_time::to_simple_string(
                                               boost::posix_time::second_clock::local_time()) +
                                       ".log";
                this->logfile = params.save_dir.second / filename;

            logging_file.open(this->logfile.string().c_str(), std::ios_base::app);
            if (!logging_file.is_open())
            {
                params.is_logging = false;
                std::cout << "attempt to log failed\n";
            }
        }
        boost::scoped_ptr<boost::timer::auto_cpu_timer> t(nullptr);
        if (params.is_logging) t.reset(new boost::timer::auto_cpu_timer(logging_file));

        // Set up wine prefixes and wine paths.
        using_wine = false;
        if (params.wine_cmd != "no_wine")
        {
            if (params.is_logging) logging_file << "Using wine\n";
            using_wine = true;
            // Configure Wine prefix tp use.
            if (params.wine_prefix_path.first == "use_home_path")
            {
                params.wine_prefix_path.second = boost::filesystem::path(userHomeDir()) / ".wine";
                params.wine_prefix_path.first = params.wine_prefix_path.second.string();
                if (params.is_logging) logging_file << "Using home path for wine prefix\nWine prefix is: " << params.wine_prefix_path.first << "\n";
            } else if (params.wine_prefix_path.first.substr(0, 8) == "generate")
            {
                std::string prefix_template =
                        "Metro_Cal_OF_worker" + std::to_string(params.evaluator_id) + "_wine_prefix_%%%%-%%%%";
                params.wine_prefix_path.second = boost::filesystem::unique_path(
                        params.working_dir.second / prefix_template);
                int i = 2;
                while(boost::filesystem::exists(params.wine_prefix_path.second))
                {
                    prefix_template =
                            "Metro_Cal_OF_worker" + std::to_string(params.evaluator_id) + "_wine_prefix_%%%%-%%%%_v" + std::to_string(i++);
                    params.wine_prefix_path.second = boost::filesystem::unique_path(
                            params.working_dir.second / prefix_template);
                }
                params.wine_prefix_path.first = params.wine_prefix_path.second.string();

                std::stringstream cmd;
                cmd << "WINEPREFIX=" << params.wine_prefix_path.second.string().c_str() << " " << params.wine_cmd << " winecfg";
                int return_val = system(cmd.str().c_str());
                this->delete_wine_prefix_on_exit = true;

                //Copy model into prefix
                boost::filesystem::path template_geonamica_binary_root = params.wine_prefix_path.first.substr(9);
                boost::filesystem::path copy_geonamica_binary_root =
                        params.wine_prefix_path.second / "drive_c/Program Files (x86)/Geonamica";
                copyDir(template_geonamica_binary_root, copy_geonamica_binary_root, logging_file);
                if (params.is_logging) logging_file << "Copying Geonamica Binary directory into prexisting wine prefix\nWarning: This is not supported\nWine prefix is: " << params.wine_prefix_path.first << "\n";

            } else if (params.wine_prefix_path.first.substr(0, 4) == "copy")
            {
                std::string prefix_copy_template =
                        "Metro_Cal_OF_worker" + std::to_string(params.evaluator_id) + "_wine_prefix_%%%%-%%%%";
                boost::filesystem::path prefix_copied_path = boost::filesystem::unique_path(
                        params.working_dir.second / prefix_copy_template);
                int i = 2;
                while(boost::filesystem::exists(prefix_copied_path))
                {
                    prefix_copy_template =
                            "Metro_Cal_OF_worker" + std::to_string(params.evaluator_id) + "_wine_prefix_%%%%-%%%%_v" + std::to_string(i++);
                    prefix_copied_path = boost::filesystem::unique_path(
                            params.working_dir.second / prefix_copy_template);
                }

                boost::filesystem::path prefix_template_path = params.wine_prefix_path.first.substr(5);
                boost::filesystem::create_directories(prefix_copied_path);
                copyFilesInDir(prefix_template_path, prefix_copied_path, logging_file);

                boost::filesystem::path drive_c_copied_path = prefix_copied_path / "drive_c";
                boost::filesystem::path drive_c_template_path = prefix_template_path / "drive_c";
                copyDir(drive_c_template_path, drive_c_copied_path, logging_file);

                boost::filesystem::copy_directory(prefix_template_path / "dosdevices",
                                                  prefix_copied_path / "dosdevices");
                boost::filesystem::path drive_c_link = prefix_copied_path / "dosdevices/c:";
                boost::filesystem::create_directory_symlink(drive_c_copied_path, drive_c_link);

                // Copied out because we do not actually need z drive and possibly this is causing problems on phoenix.
//                boost::filesystem::path drive_z_link = prefix_copied_path / "dosdevices/z:";
//                boost::filesystem::create_directory_symlink(boost::filesystem::path("/"), drive_z_link);

                params.wine_prefix_path.second = prefix_copied_path;
                params.wine_prefix_path.first = params.wine_prefix_path.second.string();
                this->delete_wine_prefix_on_exit = true;
                if (params.is_logging) logging_file << "Making new prefix based on template\nTemplate Wine prefix is: \nTemplate Wine prefix is: " << params.wine_prefix_path.first << "\n";
            }
            else if (params.wine_prefix_path.first.substr(0, 2) == "na")
            {
                // Do nothing, no prefix path set.
                if (params.is_logging) logging_file << "Wine prefix not needed; are we running on Windows?\n";
            }
            else
            {
                pathify_mk(params.wine_prefix_path); //although should really already exist....
                if (params.is_logging) logging_file << "Wine prefix is: " << params.wine_prefix_path.first << "\n";
            }

            // Check dosdevices path exists.
            params.wine_drive_path.second = params.wine_prefix_path.second / "dosdevices";
            params.wine_drive_path.first = params.wine_drive_path.second.string();
            if (!(boost::filesystem::exists(params.wine_drive_path.second)))
            {
                std::cout << "Could not find dosdevices in " << params.wine_prefix_path.second
                          << " Is wine installed?\n";

            }

            // Copy project directory into working directory
            std::string temp_dir_template = "Metro_Cal_OF_worker" + std::to_string(params.evaluator_id) + "_%%%%-%%%%";
            params.working_dir.second = boost::filesystem::unique_path(params.working_dir.second / temp_dir_template);
            int i = 2;
            while(boost::filesystem::exists(params.working_dir.second))
            {
                temp_dir_template = "Metro_Cal_OF_worker" + std::to_string(params.evaluator_id) + "_%%%%-%%%%_v" + std::to_string(i++);
                params.working_dir.second = boost::filesystem::unique_path(params.working_dir.second / temp_dir_template);
            }

//            temp_dir_template = params.working_dir.second.filename().string();
            if (params.is_logging) logging_file << "Copying Geoproject from : " << params.template_project_dir.second.string() << " to " << params.working_dir.second.string() << "\n";
            copyDir(params.template_project_dir.second, params.working_dir.second, logging_file);



            // Create new dosdevice drive to working geoproject file directory.
            std::vector<std::string> drive_options = {"m:", "n:", "o:", "p:", "q:", "r:", "s:", "t:", "u:", "v:", "w:",
                                                      "x:", "y:", "l:", "a:", "b:"};

            BOOST_FOREACH(std::string &drive_option, drive_options)
                        {
                            boost::filesystem::path symlinkpath_ext = params.wine_drive_path.second / drive_option;
                            //Check if symbolic link for wine J: exists.
                            boost::filesystem::file_status lnk_status = boost::filesystem::symlink_status(
                                    symlinkpath_ext);
                            if (!(boost::filesystem::is_symlink(lnk_status)) ||
                                !(boost::filesystem::exists(symlinkpath_ext)))
                            {
                                boost::filesystem::create_directory_symlink(params.working_dir.second, symlinkpath_ext);
//                                params.wine_drive_letter = drive_option;
                                params.working_dir.first = drive_option;
                                params.wine_drive_path.second = params.wine_drive_path.second / drive_option;
                                params.wine_drive_path.first = params.wine_drive_path.second.string();
                                delete_wine_dir_on_exit = true;
                                if (params.is_logging) logging_file << "Wine path to geoproject directory is : " << params.working_dir.first << "\n";
                                if (params.is_logging) logging_file << "Unix path of wine drive is : " << params.wine_drive_path.first << "\n";
                                break;
                            }
                            if (drive_option == "b:")
                                logging_file << "Could not make a symlink to the working drive for winedrive.\n";
                        }
        }

        using_timeout = false;
        if (params.timout_cmd != "no_timeout")
        {
            using_timeout = true;
        }

        // get paths of important files in working directory.
        params.geoproj_file.second = params.working_dir.second / params.geoproj_file.first;
        params.geoproj_file.first = params.working_dir.first + "\\" + params.geoproj_file.first;
        params.log_spec_file.second = params.working_dir.second / params.log_spec_file.first;
        params.log_spec_file.first = params.working_dir.first + "\\" + params.log_spec_file.first;



        if (obj_t == FKS_CLUMP)
        {
            minimise_or_maximise = {MAXIMISATION, MINIMISATION};
        }
        else if (obj_t == FKS_CLUMP_KAPPA)
        {
            minimise_or_maximise = {MAXIMISATION, MINIMISATION, MAXIMISATION};
        }

        params.actual_map_file.second = params.working_dir.second / params.actual_map_file.first;
        params.actual_map_file.first = params.actual_map_file.second.string();
        params.original_map_file.second = params.working_dir.second / params.original_map_file.first;
        params.original_map_file.first = params.original_map_file.second.string();
        params.masking_map_file.second = params.working_dir.second / params.masking_map_file.first;
        params.masking_map_file.first = params.masking_map_file.second.string();
        params.fks_coefficients_file.second = params.working_dir.second / params.fks_coefficients_file.first;
        params.fks_coefficients_file.first = params.fks_coefficients_file.second.string();
        params.simulated_map_file.second = params.working_dir.second / params.simulated_map_file.first;
        params.simulated_map_file.first = params.simulated_map_file.second.string();



        namespace qi = boost::spirit::qi;
        namespace ph = boost::phoenix;

        typedef std::vector<std::string> StringTuple;
        std::vector<StringTuple > classified_img_rqsts_tmp;
        std::vector<StringTuple> lin_grdnt_img_rqsts_tmp;
        qi::rule<std::string::iterator, std::string()> string_parser_quote_delimited = qi::lit("\"") >> +(qi::char_ - "\"") >> qi::lit("\"");   //[_val = _1]
        string_parser_quote_delimited.name("string_quote_delimited_parser");
//        qi::debug(string_parser_quote_delimited);
        qi::rule<std::string::iterator, std::string()> diff_map_parser = ( qi::lit("DIFF") >> qi::lit("=") >> string_parser_quote_delimited >> qi::lit(":") ) | qi::attr(std::string("no_diff"));
        diff_map_parser.name("diff_map_parser");
//        qi::debug(diff_map_parser);
        qi::rule<std::string::iterator, std::string()> legend_file_parser = qi::lit("LEGEND") >> qi::lit("=") >> string_parser_quote_delimited >> qi::lit(":");
        legend_file_parser.name("legend_file_parser");
//        qi::debug(legend_file_parser);
        qi::rule<std::string::iterator, std::string()> save_map_parser = qi::lit("PATH") >> qi::lit("=") >> string_parser_quote_delimited >> qi::lit(":");
        save_map_parser.name("save_map_parser");
//        qi::debug(save_map_parser);
        qi::rule<std::string::iterator, std::string()> save_as_img_parser = qi::lit("SAVE_AS") >> qi::lit("=")  >> string_parser_quote_delimited;
        save_as_img_parser.name("save_as_img_parser");
//        qi::debug(save_as_img_parser);
        qi::rule<std::string::iterator, std::vector<std::string>() > save_map_info = legend_file_parser  >> save_map_parser >> diff_map_parser >> save_as_img_parser;
        qi::rule<std::string::iterator, StringTuple()> categorised_save_map_rule = (qi::lit("CATEGORISED") | qi::lit("CAT")) >> qi::lit(":") >> save_map_info;
        categorised_save_map_rule.name("category_map_parser");
//        qi::debug(categorised_save_map_rule);
        qi::rule<std::string::iterator, StringTuple()> linear_grad_save_map_rule = (qi::lit("LINEAR_GRADIENT") | qi::lit("LIN_GRAD")) >> qi::lit(":")  >> save_map_info;
        linear_grad_save_map_rule.name("linear_grad_map_parser");
//        qi::debug(linear_grad_save_map_rule);
        qi::rule<std::string::iterator> save_maps_parser = categorised_save_map_rule [ph::push_back(ph::ref(classified_img_rqsts_tmp), qi::_1)] | linear_grad_save_map_rule[ph::push_back(ph::ref(lin_grdnt_img_rqsts_tmp), qi::_1)];
        save_maps_parser.name("save_map_parser");
//        qi::debug(save_maps_parser);
        BOOST_FOREACH(std::string & save_map, params.save_maps)
                    {
                        boost::spirit::qi::parse(save_map.begin(), save_map.end(),  save_maps_parser);
                    }
        BOOST_FOREACH(StringTuple & cat_save_map_pair, classified_img_rqsts_tmp)
                    {
//                        boost::shared_ptr<ColourMapperClassified> classified_clr_map =  parseColourMapClassified(params.working_dir.second / std::get<0>(cat_save_map_pair));
                        boost::shared_ptr<ColourMapperClassified> classified_clr_map =  parseColourMapClassified(params.working_dir.second / (cat_save_map_pair[0]));
                        boost::shared_ptr<MagickWriterClassified> classified_map_prntr(new MagickWriterClassified(*classified_clr_map));
                        boost::filesystem::path diff_map;
                        if(cat_save_map_pair[2] == "no_diff")
                        {
                            diff_map = "no_diff";
                        } else
                        {
                            diff_map = params.working_dir.second / (cat_save_map_pair[2]);
                        }
//                        classified_img_rqsts.push_back(std::make_tuple(params.working_dir.second / std::get<1>(cat_save_map_pair), classified_clr_map, classified_map_prntr, std::get<2>(cat_save_map_pair)));
                        classified_img_rqsts.push_back(std::make_tuple(params.working_dir.second / (cat_save_map_pair[1]), diff_map, classified_clr_map, classified_map_prntr, (cat_save_map_pair[3])));
                    }
        BOOST_FOREACH(StringTuple & lin_grad_save_map_pair, lin_grdnt_img_rqsts_tmp)
                    {
//                        boost::shared_ptr<ColourMapperGradient> lin_grad_clr_map = parseColourMapLinearGradient(params.working_dir.second / std::get<0>(lin_grad_save_map_pair));
                        boost::shared_ptr<ColourMapperGradient> lin_grad_clr_map = parseColourMapGradient(params.working_dir.second / (lin_grad_save_map_pair[0]));
                        boost::shared_ptr<MagickWriterGradient> lin_grad_map_prntr(new MagickWriterGradient(*lin_grad_clr_map));
                        boost::filesystem::path diff_map;
                        if(lin_grad_save_map_pair[2] == "no_diff")
                        {
                            diff_map = "no_diff";
                        } else
                        {
                            diff_map = params.working_dir.second / (lin_grad_save_map_pair[2]);
                        }
//                        lin_grdnt_img_rqsts.push_back(std::make_tuple(params.working_dir.second / std::get<1>(lin_grad_save_map_pair), lin_grad_clr_map, lin_grad_map_prntr, std::get<2>(lin_grad_save_map_pair)));
                        lin_grdnt_img_rqsts.push_back(std::make_tuple(params.working_dir.second / (lin_grad_save_map_pair[1]), diff_map, lin_grad_clr_map, lin_grad_map_prntr, (lin_grad_save_map_pair[3])));
                    }

        if (this->obj_t == FKS_CLUMP)
        {
            params.min_or_max = {MAXIMISATION, MINIMISATION};
        }
        else if (this->obj_t == FKS_CLUMP_KAPPA)
        {
            params.min_or_max = {MAXIMISATION, MINIMISATION, MAXIMISATION};
        }
        objectives_and_constraints.first.resize(params.min_or_max.size());
        objectives_and_constraints.second.resize(num_constraints);

        analysisNum = createAnalysis();
        loadMapActual(analysisNum, params.actual_map_file.second.c_str());
        loadOriginalMap(analysisNum, params.original_map_file.second.c_str());
        loadMaskingMap(analysisNum, params.masking_map_file.second.c_str());
        loadTransitionFuzzyWeights(analysisNum, params.fks_coefficients_file.second.c_str());
        numClasses(analysisNum, num_classes);

        // Make the problem defintions and intialise the objectives and constraints struct.
        prob_defs.reset(new ProblemDefinitions(real_lowerbounds, real_upperbounds, int_lowerbounds, int_upperbounds, params.min_or_max, num_constraints));
    }

    ~MetronamicaCalibrationObjectiveFunction()
    {
        if (delete_wine_dir_on_exit)
        {
            std::this_thread::sleep_for (std::chrono::seconds(1));
            //Check if symbolic link for wine J: exists.
            boost::filesystem::file_status lnk_status = boost::filesystem::symlink_status(params.wine_drive_path.second);
            if ((boost::filesystem::is_symlink(lnk_status)) && (boost::filesystem::exists(params.wine_drive_path.second)))
            {
                boost::filesystem::remove(params.wine_drive_path.second);
            }
        }

        if (delete_wine_prefix_on_exit)
        {
            std::this_thread::sleep_for (std::chrono::seconds(1));
            if (!(boost::filesystem::exists(params.wine_prefix_path.second)))
            {
                boost::filesystem::remove_all(params.wine_prefix_path.second);
            }
        }

        if (boost::filesystem::exists(params.working_dir.second))
        {
            std::this_thread::sleep_for (std::chrono::seconds(1));
            boost::filesystem::remove_all(params.working_dir.second);
        }
    }


    boost::optional<boost::filesystem::path>
    runMetro(std::string mod_geoproject_file_str, std::ofstream & logging_file)
    {
        std::stringstream cmd1, cmd2;

        if (params.with_reset_and_save)
        {
            //Call the model
            if (using_wine && params.wine_prefix_path.first != "na" && params.set_prefix_path)
                cmd1 << "WINEPREFIX=" << "\"" << params.wine_prefix_path.second.string().c_str() << "\"" << " ";
            if (using_timeout) cmd1 << params.timout_cmd << " ";
            if (using_wine) cmd1 << params.wine_cmd << " ";
            cmd1 << params.geonamica_cmd << " --Reset --Save " << "\"" << mod_geoproject_file_str << "\"";
            if (params.is_logging)
            {
                cmd1 << " >> \"" << logfile.string().c_str() << "\" 2>&1";
                logging_file << "Running: " << cmd1.str() << std::endl;
                logging_file.close();
            }

            int i1 = system(cmd1.str().c_str());
            if (params.is_logging) logging_file.open(logfile.string().c_str(), std::ios_base::app);
            if (!logging_file.is_open()) params.is_logging = false;

            if (using_wine && params.wine_prefix_path.first != "na" && params.set_prefix_path)
                cmd2 << "WINEPREFIX=" << "\"" << params.wine_prefix_path.second.string().c_str() << "\"" << " ";
            if (using_timeout) cmd2 << params.timout_cmd << " ";
            if (using_wine) cmd2 << params.wine_cmd << " ";
            cmd2 << params.geonamica_cmd << " --Run --Save --LogSettings " << "\"" << params.log_spec_file.first << "\""
                 << " " << "\"" << mod_geoproject_file_str << "\"";
            if (params.is_logging)
            {
                cmd2 << " >> \"" << logfile.string().c_str() << "\" 2>&1";
                logging_file << "Running: " << cmd2.str() << std::endl;
                logging_file.close();
            }
            int i2 = system(cmd2.str().c_str());
            if (params.is_logging) logging_file.open(logfile.string().c_str(), std::ios_base::app);
            if (!logging_file.is_open()) params.is_logging = false;
        }
        else
        {
            //Call the model
            if (using_wine && params.wine_prefix_path.first != "na" && params.set_prefix_path)
                cmd2 << "WINEPREFIX=" << "\"" << params.wine_prefix_path.second.string().c_str() << "\"" << " ";
            if (using_timeout) cmd2 << params.timout_cmd << " ";
            if (using_wine) cmd2 << params.wine_cmd << " ";
            cmd2 << params.geonamica_cmd << " --Run --LogSettings " << "\"" << params.log_spec_file.first << "\""
                 << " " << "\"" << mod_geoproject_file_str << "\"";
            if (params.is_logging)
            {
                cmd2 << " >> \"" << logfile.string().c_str() << "\" 2>&1";
                logging_file << "Running: " << cmd2.str() << std::endl;
                logging_file.close();
            }
            int i2 = system(cmd2.str().c_str());
            if (params.is_logging) logging_file.open(logfile.string().c_str(), std::ios_base::app);
            if (!logging_file.is_open()) params.is_logging = false;
        }


        boost::filesystem::path output_map = params.simulated_map_file.first;
        if (boost::filesystem::exists(output_map))
        {
            return output_map;
        }
        else
        {
            std::this_thread::sleep_for (std::chrono::seconds(3));
            if (boost::filesystem::exists(output_map))
            {
                return output_map;
            }
            else
            {
                return boost::none;
            }
        }
    }

    double
    calcClumpDiff(int analysisNum, int luc_val, std::ostream & log)
    {
        double clump_sim = getClumpiness(analysisNum, MAP_SIMULATED, luc_val);
        double clump_act = getClumpiness(analysisNum, MAP_ACTUAL, luc_val);
        double diff = std::abs(clump_sim - clump_act);
        if (params.is_logging) log << "clump diff: " << clump_sim << " - " << clump_act << " = " << diff << "\n";
        return (diff);
    }

    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars, boost::filesystem::path save_path = "no_path", boost::filesystem::path _logfile = "unspecified")
    {
        boost::filesystem::path initial_path = boost::filesystem::current_path();
        boost::filesystem::current_path(params.working_dir.second);

        std::ofstream logging_file;
        if (params.is_logging)
        {
            if ( _logfile == "unspecified")
            {
                std::string filename = "logWorker" + std::to_string(params.evaluator_id)
                                       + "_EvalNo" + std::to_string(eval_count) + "_"
                                       +
                                       boost::posix_time::to_simple_string(
                                               boost::posix_time::second_clock::local_time()) +
                                       ".log";
                this->logfile = params.save_dir.second / filename;
            }
            else
            {
                this->logfile = _logfile;
            }

            logging_file.open(this->logfile.string().c_str(), std::ios_base::app);
            if (!logging_file.is_open())
            {
                params.is_logging = false;
                std::cout << "attempt to log failed\n";
            }
            logging_file << "Evaluation started\n";
            logging_file << "number real decision vars : " << real_decision_vars.size() << "\n";

        }

        bool do_save = false;
        if (save_path != "no_path") do_save = true;
        if (do_save && !boost::filesystem::exists(save_path)) boost::filesystem::create_directory(save_path);


        boost::scoped_ptr<boost::timer::auto_cpu_timer> t(nullptr);
        if (params.is_logging) t.reset(new boost::timer::auto_cpu_timer(logging_file));

        std::ofstream objectives_fs;
        if (do_save)
        {
            boost::filesystem::path objectives_file = save_path / "metrics_for_each_replicate.txt";
            objectives_fs.open(objectives_file.c_str());
        }

        std::vector<double> & obj = objectives_and_constraints.first;
        if (this->obj_t == FKS_CLUMP)
        {
            obj[0] = 0; obj[1] = 0;
        }
        else if (this->obj_t == FKS_CLUMP_KAPPA)
        {
            obj[0] = 0; obj[1] = 0; obj[2] = 0;
        }


        for (int j = 0; j < params.replicates; ++j)
        {
            if (params.is_logging)
            {
                logging_file << "Evaluation of objectives functions for replicate " << j << "\n";
            }

            std::tuple<double, double, double> metric_vals = calcMetrics(real_decision_vars, int_decision_vars, logging_file, j, do_save, save_path);
            double fks =  std::get<0>(metric_vals);
            double clump = std::get<1>(metric_vals);
            double k = std::get<2>(metric_vals);
                obj[0] += fks;
                obj[1] += clump;
            if (this->obj_t == FKS_CLUMP_KAPPA)
            {
                obj[2] += k;
            }
            if (do_save)
            {
                objectives_fs << "replicate " << j << " fks: " << fks << " clumpiness: " << clump << " kappa: " << k << "\n";
            }
            if (params.is_logging)
            {
                logging_file << "replicate " << j << " fks: " << fks << " clumpiness: " << clump << " kappa: " << k << "\n";
            }


        }

        if (do_save)
        {
            if (objectives_fs.is_open()) objectives_fs.close();
        }

        obj[0] /= params.replicates;
        obj[1] /= params.replicates;
        if (this->obj_t == FKS_CLUMP_KAPPA)
        {
            obj[2] /= params.replicates;
        }
        ++eval_count;

        if (params.is_logging)
        {
            logging_file << "\n\n\nEvaluation complete\n";
            logging_file << "Avg FKS: " << obj[0] << "\n Average Clump Diff: " << obj[1] << "\n Avg kappa: " << obj[2] << "\n";
            logging_file << "Evaluation run time:\n";
            t->stop();
            t->report();
        }

        if (params.is_logging)
        {
            logging_file.close();
            if (previous_logfile != "unspecified") boost::filesystem::remove_all(previous_logfile);
            previous_logfile = logfile;
            logging_file << "End evaluation " << "\n";
        }

        return (objectives_and_constraints);




    }

    std::tuple<double, double, double>
    calcMetrics(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars, std::ofstream & logging_file, int rand_seed_id, bool do_save, boost::filesystem::path save_path)
    {
        logging_file << "Replicate " << rand_seed_id << ": Begin evaluation " << "\n";
        std::vector<double> obj(3, 0);

        boost::shared_ptr<boost::timer::auto_cpu_timer> timer;
        // Modify Geoproject file with decision variables and random seed
        //            {
        if (params.is_logging)
        {
            timer.reset(new boost::timer::auto_cpu_timer(logging_file));
        }
        std::string extnsn = params.geoproj_file.second.extension().string();
        std::string mod_filename = params.geoproj_file.second.stem().string() + "_mod_rep" + std::to_string(rand_seed_id) + extnsn;
        boost::filesystem::path mod_geoproject_file_pth = params.geoproj_file.second.parent_path() / mod_filename;
        int i = 2;
        while (boost::filesystem::exists(mod_geoproject_file_pth))
        {
            mod_filename = params.geoproj_file.second.stem().string() + "_mod_rep" + std::to_string(rand_seed_id) + "_v" + std::to_string(i++) + extnsn;
            mod_geoproject_file_pth = params.geoproj_file.second.parent_path() / mod_filename;

        }
        boost::filesystem::copy_file(params.geoproj_file.second, mod_geoproject_file_pth);
        std::string mod_geoproject_file_str = params.working_dir.first + "\\" + mod_filename;

        if(case_t == SMALL_RANDSTAD)
        {
            geoprojectEditSmallCaseStudy(mod_geoproject_file_pth, real_decision_vars, params.metro_rand_seeds[rand_seed_id]);
        }
        else if(case_t == LARGE_RANDSTAD)
        {
            geoprojectEditLargeCaseStudy(mod_geoproject_file_pth, real_decision_vars, params.metro_rand_seeds[rand_seed_id]);
        }

        if (params.is_logging)
        {
            logging_file << "Replicate " << rand_seed_id << ": Timing for manipulating geoproject file : " << "\n";
            timer.reset(new boost::timer::auto_cpu_timer(logging_file));
        }


        boost::optional<boost::filesystem::path> output_map = runMetro(mod_geoproject_file_str, logging_file);
        if (!output_map)
        {
            std::this_thread::sleep_for (std::chrono::seconds(3));
            output_map = runMetro(mod_geoproject_file_str, logging_file);
            if (!output_map)
            {
                //Write error message and assume infeasible set of parameters and so assign worse OF values. (-1, 10)
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Was unable to successfully run Metronamica on decision variables\n";

                obj[0] = -1;
                obj[1] = 10;
                obj[2] = -1;
                return std::make_tuple(obj[0], obj[1], obj[2]);
//                return (objectives_and_constrataints);
            }
        }
        if (params.is_logging)
        {
            logging_file << "Replicate " << rand_seed_id << ": Timing for Resetting and running Metronamica : " << std::endl;
            timer.reset(new boost::timer::auto_cpu_timer(logging_file));
        }

        if (params.is_logging)
        try
        {
            loadMapSimulated(analysisNum, (*output_map).c_str());
            if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Simulated map: " << (*output_map).string() << "\n";
            double fks = getFuzzyKappaSim(analysisNum);
            obj[0] = fks;

            if(this->obj_t == FKS_CLUMP_KAPPA)
            {
                double k = getKappa(analysisNum);
                obj[2] = k;
            }
        }
        catch (std::runtime_error err)
        {
            try
            {
                std::cout << err.what() << std::endl;
                std::this_thread::sleep_for (std::chrono::seconds(3));
                loadMapSimulated(analysisNum, (*output_map).c_str());
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Simulated map: " << (*output_map).string() << "\n";
                double fks = getFuzzyKappaSim(analysisNum);
                obj[0] = fks;

                if(this->obj_t == FKS_CLUMP_KAPPA)
                {
                    double k = getKappa(analysisNum);
                    obj[2] = k;
                }
            }
            catch (...)
            {
                //Write error message and assume infeasible set of parameters and so assign worse OF values. (-1, 10)
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Was unable to calculate FKS/kappa\n";
                obj[0] = -1;
                obj[1] = 10;
                obj[2] = -1;
                return std::make_tuple(obj[0], obj[1], obj[2]);

            }
        }
        if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Timing for Calculating FKS (and Kappa, if requested): " << std::endl;

        if (params.is_logging) timer.reset(new boost::timer::auto_cpu_timer(logging_file));
        try
        {
            double avg_clump = 0;
            if (case_t == SMALL_RANDSTAD)
            {


                // Take avg of clumpiness

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
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Greenhouses ";
                avg_clump += calcClumpDiff(analysisNum, gre_val, logging_file);
                int res_val = 2;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Residential_ ";
                avg_clump += calcClumpDiff(analysisNum, res_val, logging_file);
                int ind_val = 3;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Industry_  ";
                avg_clump += calcClumpDiff(analysisNum, ind_val, logging_file);
                int ser_val = 4;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Services_ ";
                avg_clump += calcClumpDiff(analysisNum, ser_val, logging_file);
                int scu_val = 5;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Socio cultural uses_ ";
                avg_clump += calcClumpDiff(analysisNum, scu_val, logging_file);
                int nat_val = 6;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Nature_  ";
                avg_clump += calcClumpDiff(analysisNum, nat_val, logging_file);
                int rec_val = 7;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Recreation areas_ ";
                avg_clump += calcClumpDiff(analysisNum, rec_val, logging_file);
                avg_clump /= 7;
            }
            else if (case_t == LARGE_RANDSTAD)
            {
                //		Other agriculture		0
                //		Pastures				1
                //		Arable land				2
                //		_Greenhouses_			3
                //		_Housing low density_	4
                //		_Housing high density_	5
                //		_Industry_				6
                //		_Services_				7
                //		_Socio cultural uses_	8
                //		_Forest_				9
                //		_Extensive grasslands_	10
                //		_Nature_				11
                //		_Recreation areas_		12
                //		Airport					13
                //		Fresh water				14
                //		Marine water			15

                // Greenhouses
                int gre_val = 3;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Greenhouses_ ";
                avg_clump += calcClumpDiff(analysisNum, gre_val, logging_file);
                // Housing low density
                int hld_val = 4;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Housing low density_ ";
                avg_clump += calcClumpDiff(analysisNum, hld_val, logging_file);
                // Housing high density
                int hhd_val = 5;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Housing high density_ ";
                avg_clump += calcClumpDiff(analysisNum, hhd_val, logging_file);
                // Industry
                int ind_val = 6;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Industry_  ";
                avg_clump += calcClumpDiff(analysisNum, ind_val, logging_file);
                // Services
                int ser_val = 7;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Services_ ";
                avg_clump += calcClumpDiff(analysisNum, ser_val, logging_file);
                // Socio cultural uses
                int scu_val = 8;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Socio cultural uses_ ";
                avg_clump += calcClumpDiff(analysisNum, scu_val, logging_file);
                // Forest
                int for_val = 9;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Forest_ ";
                avg_clump += calcClumpDiff(analysisNum, for_val, logging_file);
                // Extensive grasslands
                int ext_val = 10;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Extensive grasslands_ ";
                avg_clump += calcClumpDiff(analysisNum, ext_val, logging_file);
                // Nature
                int nat_val = 11;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Nature_  ";
                avg_clump += calcClumpDiff(analysisNum, nat_val, logging_file);
                // Recreation areas
                int rec_val = 12;
                if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": _Recreation areas_ ";
                avg_clump += calcClumpDiff(analysisNum, rec_val, logging_file);
                avg_clump /= 10;
            }
            obj[1] = avg_clump;
            if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Avg abs. diff clumpiness: " << avg_clump << "\n";

        }
        catch (...)
        {
            //Write error message and assume infeasible set of parameters and so assign worse OF values. (-1, 10)
            if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Was unable to calculate avg. clumpiness difference\n";
            obj[0] = -1;
            obj[1] = 10;
            obj[2] = -1;
            return std::make_tuple(obj[0], obj[1], obj[2]);
//            return (objectives_and_constrataints);
        }
        if (params.is_logging) logging_file << "Replicate " << rand_seed_id << ": Timing for Calculating Clumpiness: " << std::endl;
        if (params.is_logging) timer.reset();


        boost::filesystem::path save_replicate_path = save_path / ("replicate_" + std::to_string(rand_seed_id));
        if (do_save)
        {
//                boost::filesystem::path save_replicate_path = save_path / ("replicate_" + std::to_string(j));
            //            if (!boost::filesystem::exists(save_replicate_path)) boost::filesystem::create_directory(save_replicate_path);
            if (boost::filesystem::exists(save_replicate_path)) boost::filesystem::remove_all(save_replicate_path);
            copyDir(params.working_dir.second, save_replicate_path, logging_file);
            typedef std::tuple<boost::filesystem::path, boost::filesystem::path, boost::shared_ptr<ColourMapperClassified>,     boost::shared_ptr<MagickWriterClassified>, std::string >  ClassfdImgRqstTuple;
            typedef std::tuple<boost::filesystem::path, boost::filesystem::path, boost::shared_ptr<ColourMapperGradient>, boost::shared_ptr<MagickWriterGradient>, std::string >  LinGradntImgRqstTuple;

            boost::filesystem::path obj_file = save_replicate_path / "objectives.txt";
            std::ofstream obj_fs(obj_file.string().c_str());
            if (obj_fs.is_open())
            {
                obj_fs << " fks: " << obj[0] << " clumpiness: " << obj[1];
                if(this->obj_t == FKS_CLUMP_KAPPA)
                {
                    obj_fs << " kappa: " << obj[2];
                }
                obj_fs << "\n";
            }
            obj_fs.close();


            if (!params.bypass_save)
            {
                if (params.is_logging) logging_file << " Saving images..." << std::endl;
                BOOST_FOREACH(ClassfdImgRqstTuple &classified_img_request, classified_img_rqsts) {
                                if (params.is_logging) logging_file << " ... classified images..." << std::endl;
                                blink::raster::gdal_raster<int> map = blink::raster::open_gdal_raster<int>(
                                        std::get<0>(classified_img_request), GA_ReadOnly);
                                boost::filesystem::path save_img_path =
                                        save_replicate_path / std::get<4>(classified_img_request);
                                if (params.is_logging)
                                    logging_file << " Saving " << std::get<0>(classified_img_request) << " to "
                                                 << save_img_path.string() << "\n";
                                if ((std::get<1>(classified_img_request)).string() != "no_diff") {
                                    boost::optional<int> map_no_data = map.noDataVal();
                                    blink::raster::gdal_raster<int> diff = blink::raster::open_gdal_raster<int>(
                                            std::get<1>(classified_img_request), GA_ReadOnly);
                                    boost::optional<int> diff_no_data = diff.noDataVal();
                                    blink::raster::gdal_raster<int> out = blink::raster::create_temp_gdal_raster_from_model<int>(
                                            diff);

                                    auto zip = blink::iterator::make_zip_range(std::ref(map), std::ref(diff),
                                                                               std::ref(out));
                                    if (map_no_data || diff_no_data) {
                                        for (auto &&i : zip) {

                                            const int map_val = std::get<0>(i);
                                            const int diff_val = std::get<1>(i);
                                            if (map_val == map_no_data.value() || diff_val == diff_no_data.value()) {
                                                std::get<2>(i) = map_no_data.value();
                                            } else if (map_val != diff_val) {
                                                std::get<2>(i) = map_val;
                                            } else {
                                                std::get<2>(i) = map_no_data.value();
                                            }
                                        }
                                    } else {
                                        for (auto &&i : zip) {

                                            const int map_val = std::get<0>(i);
                                            const int diff_val = std::get<1>(i);
                                            if (map_val != diff_val) {
                                                std::get<2>(i) = map_val;
                                            } else {
                                                std::get<2>(i) = map_no_data.value();
                                            }
                                        }
                                    }
                                    if (params.is_logging) logging_file << " Rendering now... " << std::endl;
                                    std::get<3>(classified_img_request)->render(out, save_img_path);
                                } else {
                                    if (params.is_logging) logging_file << " Rendering now... " << std::endl;
                                    std::get<3>(classified_img_request)->render(map, save_img_path);
                                }

                            }
                BOOST_FOREACH(LinGradntImgRqstTuple &lin_grad_img_request, lin_grdnt_img_rqsts) {
                                if (params.is_logging) logging_file << " ... gradient images..." << std::endl;
                                blink::raster::gdal_raster<double> map = blink::raster::open_gdal_raster<double>(
                                        std::get<0>(lin_grad_img_request), GA_ReadOnly);
                                boost::filesystem::path save_img_path =
                                        save_replicate_path / std::get<4>(lin_grad_img_request);
                                if ((std::get<1>(lin_grad_img_request).string() != "no_diff")) {
                                    boost::optional<double> map_no_data = map.noDataVal();
                                    blink::raster::gdal_raster<double> diff = blink::raster::open_gdal_raster<double>(
                                            std::get<1>(lin_grad_img_request), GA_ReadOnly);
                                    boost::optional<double> diff_no_data = diff.noDataVal();
                                    blink::raster::gdal_raster<double> out = blink::raster::create_temp_gdal_raster_from_model<double>(
                                            diff);
                                    auto zip = blink::iterator::make_zip_range(std::ref(map), std::ref(diff),
                                                                               std::ref(out));
                                    if (map_no_data || diff_no_data) {
                                        for (auto &&i : zip) {

                                            const double map_val = std::get<0>(i);
                                            const double diff_val = std::get<1>(i);
                                            if (map_val == map_no_data.value() || diff_val == diff_no_data.value()) {
                                                std::get<2>(i) = map_no_data.value();
                                            } else {
                                                std::get<2>(i) = map_val - diff_val;
                                            }
                                        }
                                    } else {
                                        for (auto &&i : zip) {

                                            const double map_val = std::get<0>(i);
                                            const double diff_val = std::get<1>(i);
                                            std::get<2>(i) = map_val - diff_val;
                                        }
                                    }
                                    if (params.is_logging) logging_file << " Rendering now... " << std::endl;
                                    std::get<3>(lin_grad_img_request)->render(out, save_img_path);
                                } else {
                                    if (params.is_logging) logging_file << " Rendering now... " << std::endl;
                                    std::get<3>(lin_grad_img_request)->render(map, save_img_path);
                                }

                            }
            }
        }


        boost::filesystem::remove(mod_geoproject_file_pth);
        logging_file << "Replicate " << rand_seed_id << ": End evaluation " << "\n";
        return std::make_tuple(obj[0], obj[1], obj[2]);


    }

    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {
        boost::filesystem::path save_path = "no_path";
        boost::filesystem::path logfile = "unspecified";
        return (this->operator()(real_decision_vars, int_decision_vars, save_path, logfile));

    }

    ProblemDefinitionsSPtr getProblemDefinitions()
    {
        return (prob_defs);
    }
};








#endif //CHARLES_METRO_CAL_METRONAMICACALIBRATIONOBJECTIVEFUNCTION_H
