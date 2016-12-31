#pragma once
#include <boost/filesystem/path.hpp>

class sync_root
{
public:

	sync_root();
	std::pair<std::iterator<boost::filesystem::path, boost::filesystem::path>, std::iterator<boost::filesystem::path, boost::filesystem::path>> 
		get_path_iterator();
	std::pair<std::iterator<std::string, std::string>, std::iterator<std::string, std::string>> 
		get_hash_iterator();

	~sync_root() {}
};
