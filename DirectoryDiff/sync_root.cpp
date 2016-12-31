#include "stdafx.h"
#include "sync_root.h"


void sync_root::walk_directory(boost::filesystem::path _directory_path)
{
	std::cout << "walk_directory(" << _directory_path << ")" << std::endl;
	boost::filesystem::directory_iterator it = boost::filesystem::directory_iterator(_directory_path), end;
	while (it != end)
	{
		if (boost::filesystem::is_regular_file(it->path()))
		{
			std::cout << "file found: " << it->path() << std::endl;
			_files.push_back(it->path());
		}
		else if (boost::filesystem::is_directory(it->path()))
		{
			this->walk_directory(it->path());
		}
		++it;
	}
}

sync_root::sync_root(boost::filesystem::path _path)
{
	this->_path = _path;
}

sync_root::sync_root(std::string _path)
{
	this->_path = boost::filesystem::path(_path);
}

sync_root::sync_root(std::wstring _path)
{
	this->_path = boost::filesystem::path(_path);
}

sync_root::sync_root(char* _path)
{
	this->_path = boost::filesystem::path(_path);
}

void sync_root::walk_file_system()
{
	std::cout << "walk_file_system from: " << _path << std::endl;
	_files = std::vector<hash_path>();
	walk_directory(_path);
}

std::vector<hash_path>::iterator sync_root::begin()
{
	return _files.begin();
}

std::vector<hash_path>::iterator sync_root::end()
{
	return _files.end();
}

sync_root::~sync_root()
{
}
