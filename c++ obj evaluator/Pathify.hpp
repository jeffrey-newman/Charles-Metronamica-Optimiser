#ifndef PATHIFY_H
#define PATHIFY_H

#include <boost/filesystem.hpp>

typedef std::pair<std::string, boost::filesystem::path> CmdLinePaths;

void
pathify(CmdLinePaths & path)
{
    path.second = boost::filesystem::path(path.first);
    if (!(boost::filesystem::exists(path.second)))
    {
        std::cout << "Warning: path " << path.first << " does not exist\n";
    }
}

void
pathify_mk(CmdLinePaths & path)
{
    path.second = boost::filesystem::path(path.first);
    if (!(boost::filesystem::exists(path.second)))
    {
        boost::filesystem::create_directories(path.second);
        std::cout << "path " << path.first << " did not exist, so created\n";
    }
}

#endif // PATHIFY_H
