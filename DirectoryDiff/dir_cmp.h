#pragma once
class dir_cmp
{
public:
	sync_root _src, _dst;
	dir_cmp(sync_root _src, sync_root _dst);
	
	~dir_cmp();
};

