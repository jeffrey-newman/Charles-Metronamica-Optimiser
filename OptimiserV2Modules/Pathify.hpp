#ifndef PATHIFY_H
#define PATHIFY_H

#include <string>
#include <boost/filesystem.hpp>
#include <boost/config.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

typedef std::pair<std::string, boost::filesystem::path> CmdLinePaths;

bool
pathify(CmdLinePaths & path);

bool
pathify_mk(CmdLinePaths & path);

namespace boost
{
namespace serialization
{

template<class Archive>
void serialize(Archive& ar, boost::filesystem::path& p,
               const unsigned int version)
{
    std::string s;
    if(Archive::is_saving::value)
        s = p.string();
    ar & boost::serialization::make_nvp("string", s);
    if(Archive::is_loading::value)
        p = s;
}


template<class Archive>
void serialize(Archive& ar, CmdLinePaths& p, const unsigned int version)
{
    std::string s;
    if(Archive::is_saving::value)
        s = p.second.string();
    ar & boost::serialization::make_nvp("fs", s);
    ar & boost::serialization::make_nvp("str", p.first);
    if(Archive::is_loading::value)
        p.second = s;
}

}
}


#endif // PATHIFY_H
