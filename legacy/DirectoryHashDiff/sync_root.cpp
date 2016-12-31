#include "stdafx.h"
#include "sync_root.h"


sync_root::sync_root()
{
}

std::pair<std::iterator<boost::filesystem::path, boost::filesystem::path>, std::iterator<boost::filesystem::path, boost::filesystem::path>> sync_root::get_path_iterator()
{
	return std::pair<std::iterator<boost::filesystem::path, boost::filesystem::path>, std::iterator<boost::filesystem::path, boost::filesystem::path>>();
}

std::pair<std::iterator<std::string, std::string>, std::iterator<std::string, std::string>> sync_root::get_hash_iterator()
{
	return std::pair<std::iterator<std::string, std::string>, std::iterator<std::string, std::string>>();
}
