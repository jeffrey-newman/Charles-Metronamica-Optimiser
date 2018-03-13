//
// Created by a1091793 on 19/01/18.
//

#ifndef GEON_OPT_MADRIDEVALMODULE_HPP
#define GEON_OPT_MADRIDEVALMODULE_HPP

#include <Modules/EvaluatorModules/EvaluatorModuleAPI.hpp>
#include "Pathify.hpp"
#include <vector>

struct CalibrationMetricsParams
{
    bool is_logging;
//    CmdLinePaths geoproj_file;
    CmdLinePaths logging_file;
    CmdLinePaths output_map_file;
    CmdLinePaths actual_map_file;
    CmdLinePaths original_map_file;
    CmdLinePaths masking_map_file;
    CmdLinePaths fks_coefficients_file;

    bool do_calc_FKS;
    bool do_calc_Kappa;
    bool do_calc_clump;

    int num_classes;
    std::vector<int> classes_4_clump_calc;
    std::vector<double> weights_4_clump_classes;

    std::string dummy;

};

class CalibrationMetricModule : public EvalModuleAPI
{
public:
    const std::string
    name() const;

    void
    configure(const std::string _configure_string, const boost::filesystem::path _geoproj_dir);

    virtual std::shared_ptr<const std::vector<double> >
    calculate(const std::vector<double> &_real_decision_vars, const std::vector<int> &_int_decision_vars);

    virtual const std::vector<MinOrMaxType>&
    isMinOrMax() const;

    void
    calcFKSSwitch(bool do_calc);

    void
    calcKappaSwitch(bool do_calc);

    void
    calcClumpSwitch(bool do_calc);

private:
    CalibrationMetricsParams params;
    int analysis_num;
    int num_objectives;
    const double WORST_FKS_VAL = -1.0;
    const double WORST_KAPPA_VAL = -1.0;
    const double WORST_CLUMP_VAL = 10;
    std::vector<MinOrMaxType> min_or_max;
    int eval_count;

    bool
    filePathMakeCheck(CmdLinePaths & rel_file_path, const boost::filesystem::path& geoproj_dir);
};


#endif //GEON_OPT_MADRIDEVALMODULE_HPP
