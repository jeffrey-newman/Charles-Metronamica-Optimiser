//
// Created by a1091793 on 19/01/18.
//

#ifndef GEON_OPT_MADRIDDVSMODULE_HPP
#define GEON_OPT_MADRIDDVSMODULE_HPP

#include <Modules/DVModules/DVModuleAPI.hpp>


class MadridDVsModule : public DVModuleAPI
{
public:
    virtual const std::string name() const;
    virtual void configure(const std::string _configure_string, const boost::filesystem::path _geoproj_dir);
    virtual void setDVs(const std::vector<double>  & _real_decision_vars, const std::vector<int> & _int_decision_vars, const boost::filesystem::path _geoproj_file) const;
    virtual const Bounds<double>& realBounds() const;
    virtual const Bounds<int>& intBounds() const;

private:
    boost::filesystem::path original_bck_geoproj;
    boost::filesystem::path working_project;
    Bounds<double> real_bounds;
    Bounds<int> int_bounds;
};


#endif //GEON_OPT_MADRIDDVSMODULE_HPP
