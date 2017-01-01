#pragma once
class dir_cmp
{

public:
	sync_root _src, _dst;
	dir_cmp(sync_root _src, sync_root _dst);
	/*
	 * TODO 
	 */
	std::pair<std::vector<hash_path>::iterator, std::vector<hash_path>::iterator> get_missing_files();
	~dir_cmp();
};

