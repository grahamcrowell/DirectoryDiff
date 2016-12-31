#pragma once
class sync_root
{
	boost::filesystem::path _path;
	std::vector<hash_path> _files;
	void walk_directory(boost::filesystem::path _directory_path);
public:
	sync_root(boost::filesystem::path _path);
	sync_root(std::string _path);
	sync_root(std::wstring _path);
	sync_root(char* _path);
	void walk_file_system();
	std::vector<hash_path>::iterator begin();
	std::vector<hash_path>::iterator end();
	~sync_root();
};

