//
// Created by a1091793 on 19/01/18.
//

#include <string>
#include "CalibrationMetricModule.hpp"
#include <boost/timer/timer.hpp>
#include "MapComparison_0_4.h"
#include <iostream>
#include <thread>
#include <boost/spirit/include/qi.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/bind.hpp>

template <typename IteratorType, typename SkipperType>
struct CalibratnMetricParser : boost::spirit::qi::grammar<IteratorType, SkipperType>
{
    CalibratnMetricParser(CalibrationMetricsParams& _params) : CalibratnMetricParser::base_type(start), params(_params)
    {
        namespace qi = boost::spirit::qi;
        namespace ph = boost::phoenix;

        string_parser_eol_delimited = qi::lexeme[+(qi::char_ - qi::eol)];
//        geoproj_file_parser = qi::lit("geoproj_file") >> qi::lit("=") >> string_parser_eol_delimited[ph::ref(params.geoproj_file) = qi::_1];
        logging_file_parser = qi::lit("logging_file") >> qi::lit("=") >> string_parser_eol_delimited[ph::ref(params.logging_file.first) = qi::_1];
        output_map_file_parser = qi::lit("output_map_file") >> qi::lit("=") >> string_parser_eol_delimited[ph::ref(params.output_map_file.first) = qi::_1];
        actual_map_file_parser = qi::lit("actual_map_file") >> qi::lit("=") >> string_parser_eol_delimited[ph::ref(params.actual_map_file.first) = qi::_1];
        original_map_file_parser = qi::lit("original_map_file") >> qi::lit("=") >> string_parser_eol_delimited[ph::ref(params.original_map_file.first) = qi::_1];
        masking_map_file_parser = qi::lit("masking_map_file") >> qi::lit("=") >> string_parser_eol_delimited[ph::ref(params.masking_map_file.first) = qi::_1];
        fks_coefficients_file_parser = qi::lit("fks_coefficients_file") >> qi::lit("=") >> string_parser_eol_delimited[ph::ref(params.fks_coefficients_file.first) = qi::_1];
         do_calc_Kappa_parser = qi::lit("do_calc_Kappa") >> qi::lit("=")
                                >> ((qi::lit("true") >> qi::attr(true))[ph::ref(params.do_calc_Kappa) = qi::_1]
                                    | (qi::lit("false") >> qi::attr(false))[ph::ref(params.do_calc_Kappa) = qi::_1]);
        do_calc_clump_parser = qi::lit("do_calc_clump") >> qi::lit("=")
                                >> ((qi::lit("true") >> qi::attr(true))[ph::ref(params.do_calc_clump) = qi::_1]
                                    | (qi::lit("false") >> qi::attr(false))[ph::ref(params.do_calc_clump) = qi::_1]);
        do_calc_FKS_parser = qi::lit("do_calc_FKS") >> qi::lit("=")
                                >> ((qi::lit("true") >> qi::attr(true))[ph::ref(params.do_calc_FKS) = qi::_1]
                                    | (qi::lit("false") >> qi::attr(false))[ph::ref(params.do_calc_FKS) = qi::_1]);
        clump_class_idxs_parser  = qi::lit("clump_class_idxs") >> qi::lit("=") >>
                                                     (+(qi::int_))[ph::ref(params.classes_4_clump_calc) = qi::_1];

//        start =  logging_file_parser ^ output_map_file_parser ^ actual_map_file_parser
//            ^ original_map_file_parser ^ masking_map_file_parser ^ fks_coefficients_file_parser ^ clump_class_idxs_parser
//            ^ do_calc_FKS_parser ^ do_calc_Kappa_parser ^ do_calc_clump_parser;
        start =  *(logging_file_parser | output_map_file_parser | actual_map_file_parser
            | original_map_file_parser | masking_map_file_parser | fks_coefficients_file_parser | clump_class_idxs_parser
            | do_calc_FKS_parser | do_calc_Kappa_parser | do_calc_clump_parser);
//        ^ geoproj_file_parser;
//        qi::debug(start);
    }

    CalibrationMetricsParams& params;
    boost::spirit::qi::rule<IteratorType, std::string(), SkipperType> string_parser_eol_delimited;
//    boost::spirit::qi::rule<std::string::iterator, boost::spirit::qi::space_type > geoproj_file_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > logging_file_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > output_map_file_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > actual_map_file_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > original_map_file_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > masking_map_file_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > fks_coefficients_file_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > do_calc_FKS_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > do_calc_Kappa_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > do_calc_clump_parser;
    boost::spirit::qi::rule<IteratorType, SkipperType > clump_class_idxs_parser;

    boost::spirit::qi::rule<IteratorType, SkipperType> start;
};

const std::string
CalibrationMetricModule::name() const
{
    return std::string("Calibration metric evaluator (FKS, Kappa and CLUMP)");
}

bool
CalibrationMetricModule::filePathMakeCheck(CmdLinePaths & rel_file_path, const boost::filesystem::path& geoproj_dir)
{
    rel_file_path.second = geoproj_dir / rel_file_path.first;
    rel_file_path.first = rel_file_path.second.string();

    if (boost::filesystem::exists(rel_file_path.second))
    {
        return true;
    }
    else
    {
        return false;
    }
    return true;
}

void
CalibrationMetricModule::configure(const std::string _configure_string, const boost::filesystem::path _geoproj_dir)
{

    params.is_logging = false;
    params.do_calc_FKS = false;
    params.do_calc_Kappa = false;
    params.do_calc_clump = false;

    CalibratnMetricParser<std::string::iterator, boost::spirit::qi::space_type> parser(this->params);
    boost::filesystem::path config_file(_configure_string);
    if (!boost::filesystem::exists(config_file))
    {
        throw std::runtime_error("Calibration Metric module options file does not exist: " + _configure_string);
    }
    std::ifstream ifs(config_file.string().c_str());
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string config_contents = buffer.str();
    std::string::iterator it(config_contents.begin()), end(config_contents.end());
//    std::string config_contents((std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>());
//    ifs >> std::noskipw;
//    boost::spirit::istream_iterator f(ifs), l;
    bool ok = boost::spirit::qi::phrase_parse(
        it, end, parser, boost::spirit::qi::space);

    if (ok)
    {
        if (do_log) logging_file << "Parsing calibration metrics config file successful\n";
        else std::cout << "Parsing calibration metrics config file successful\n";
    }
    else
    {
        if (do_log) logging_file << "Parsing calibration metrics config file failed at: '" << std::string(it,end) << "'\n";
        else std::cout << "Parsing calibration metrics config file failed at: '" << std::string(it,end) << "'\n";
    }


//    filePathMakeCheck(params.geoproj_file, _geoproj_dir);
//    if (filePathMakeCheck(params.logging_file, _geoproj_dir)) params.is_logging = true;
    if (!params.logging_file.first.empty())
    {
        params.logging_file.first = params.logging_file.first + "_%%%%%%%_eval";
        params.logging_file.second = boost::filesystem::path(params.logging_file.first);
        params.logging_file.second = boost::filesystem::unique_path(params.logging_file.second);
        params.is_logging = true;
    }

    filePathMakeCheck(params.output_map_file, _geoproj_dir);
    filePathMakeCheck(params.actual_map_file, _geoproj_dir);
    filePathMakeCheck(params.original_map_file, _geoproj_dir);
    filePathMakeCheck(params.masking_map_file, _geoproj_dir);
    if (!filePathMakeCheck(params.fks_coefficients_file, _geoproj_dir)) params.do_calc_FKS = false;
    if (!(params.classes_4_clump_calc.size() > 0)) params.do_calc_clump = false;

    this->analysis_num = createAnalysis();
    loadMapActual(this->analysis_num, this->params.actual_map_file.second.c_str());
    loadOriginalMap(this->analysis_num, this->params.original_map_file.second.c_str());
    loadMaskingMap(this->analysis_num, this->params.masking_map_file.second.c_str());
    loadTransitionFuzzyWeights(this->analysis_num, this->params.fks_coefficients_file.second.c_str());
    this->params.num_classes = maxClassVal(this->analysis_num);
    numClasses(this->analysis_num, this->params.num_classes);
    setClumpinessDifferenceClasses(this->analysis_num, this->params.classes_4_clump_calc.size(), this->params.classes_4_clump_calc.data());
    if (this->params.do_calc_FKS) min_or_max.push_back(MAXIMISATION);
    if (this->params.do_calc_Kappa) min_or_max.push_back(MAXIMISATION);
    if (this->params.do_calc_clump) min_or_max.push_back(MINIMISATION);

    eval_count = 0;
}

std::shared_ptr<const std::vector<double> >
CalibrationMetricModule::calculate(const std::vector<double> &_real_decision_vars,
                                const std::vector<int> &_int_decision_vars)
{
    std::ofstream logging_file;
    std::string log_file_str;
    boost::filesystem::path log_file_path;
    bool do_log = params.is_logging;
    if (do_log)
    {
        log_file_str = params.logging_file.second.string() + std::to_string(++eval_count) + ".log";
        log_file_path = boost::filesystem::path(log_file_str);
        logging_file.open(log_file_path.string().c_str(), std::ios_base::app);
        if (!logging_file.is_open())
        {
            do_log = false;
            std::cout << "attempt to log failed\n";
        }
    }

    std::shared_ptr<std::vector<double> >obj(new std::vector<double>);

    boost::shared_ptr<boost::timer::auto_cpu_timer> timer;
    // Modify Geoproject file with decision variables and random seed
    //            {
    if (do_log)
    {
        timer.reset(new boost::timer::auto_cpu_timer(logging_file));
    }
        try
        {
            loadMapSimulated(this->analysis_num, this->params.output_map_file.second.c_str());
            if (do_log) logging_file << "Calculating metrics for: " << this->params.output_map_file.second.string() << "\n";
            if (params.do_calc_FKS)
            {
                obj->push_back(getFuzzyKappaSim(this->analysis_num));
                if (do_log)
                {
                    if (do_log) logging_file  << "FKS = " << obj->back() << "\n";
                }
            }
            if (params.do_calc_Kappa)
            {
                obj->push_back(getKappa(this->analysis_num));
                if (do_log)
                {
                    if (do_log) logging_file  << "Kappa = " << obj->back() << "\n";
                }
            }
            if (params.do_calc_clump)
            {
                obj->push_back(getWeightedClumpinessDifference(this->analysis_num));
                if (do_log)
                {
                    if (do_log) logging_file << "Area weighted average clumpiness difference = " << obj->back() << "\n";
                }
            }

        }
        catch (std::runtime_error err)
        {
            try
            {
                std::cout << err.what() << std::endl;
                std::this_thread::sleep_for (std::chrono::seconds(3));
                loadMapSimulated(this->analysis_num, this->params.output_map_file.second.c_str());
                if (do_log) logging_file << "2nd attempt calculating metrics for: " << this->params.output_map_file.second.string() << "\n";
                if (params.do_calc_FKS)
                {
                    obj->push_back(getFuzzyKappaSim(this->analysis_num));
                    if (do_log)
                    {
                         if (do_log) logging_file << "FKS = " << obj->back() << "\n";
                    }
                }
                if (params.do_calc_Kappa)
                {
                    obj->push_back(getKappa(this->analysis_num));
                    if (do_log)
                    {
                         if (do_log) logging_file << "Kappa = " << obj->back() << "\n";
                    }
                }
                if (params.do_calc_clump)
                {
                    obj->push_back(getWeightedClumpinessDifference(this->analysis_num));
                    if (do_log)
                    {
                         if (do_log) logging_file << "Area weighted average clumpiness difference = " << obj->back() << "\n";
                    }
                }
            }
            catch (...)
            {
                //Write error message and assume infeasible set of parameters and so assign worse OF values. (-1, 10)
                if (do_log) logging_file << "Was unable to calculate FKS, Kappa metrics for: " << this->params.output_map_file.second.string() << "\n";
                if (this->params.do_calc_FKS) obj->push_back(WORST_FKS_VAL);
                if (this->params.do_calc_Kappa) obj->push_back(WORST_KAPPA_VAL);
                if (this->params.do_calc_clump) obj->push_back(WORST_CLUMP_VAL);
                return (obj);

            }
        }
    if (do_log)
    {
        if (logging_file.is_open()) logging_file.close();
        if (eval_count > 3)
        {
            std::string previous_log_file_str = params.logging_file.second.string() + std::to_string(eval_count - 3) + ".log";
            boost::filesystem::path previous_log_file_path(previous_log_file_str);
            try
            {
                if (boost::filesystem::exists(previous_log_file_path)) boost::filesystem::remove(previous_log_file_path);
            }
            catch(...)
            {
                 if (do_log) logging_file << "UInsuccessful remove of old log file in calibration metric evaluator module\n";
            }
        }
    }


    return (obj);


}

const std::vector<MinOrMaxType> &
CalibrationMetricModule::isMinOrMax() const
{
    return (min_or_max);
}

void
CalibrationMetricModule::calcFKSSwitch(bool do_calc)
{
    this->params.do_calc_FKS = do_calc;
}

void
CalibrationMetricModule::calcKappaSwitch(bool do_calc)
{
    this->params.do_calc_Kappa = do_calc;
}

void
CalibrationMetricModule::calcClumpSwitch(bool do_calc)
{
    this->params.do_calc_clump = do_calc;
}


extern "C" BOOST_SYMBOL_EXPORT CalibrationMetricModule eval_module;
CalibrationMetricModule eval_module;