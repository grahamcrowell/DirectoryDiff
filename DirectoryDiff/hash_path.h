#pragma once
#include "stdafx.h"

using namespace std::string_literals;

class hash_path;
typedef boost::function<bool(hash_path& lhs, hash_path& rhs)> hash_cmp;

/**
 * \brief extends boost::filesystem::path with openssl SHA512 hashing
 */
class hash_path : public boost::filesystem::path
{
	//std::mutex hash_mutex;
	std::string hash_digest = ""s;
	std::int32_t file_size = -1;
	std::time_t last_write_time = 0;
public:
	//hash_path() = delete;
	hash_path() {}
	hash_path(boost::filesystem::path _path) : path(_path) {}
	hash_path(std::string _path) : path(_path) {}
	hash_path(std::wstring _path) : path(_path) {}
	hash_path(char* _path) : path(_path) {}
	hash_path(wchar_t* _path) : path(_path) {}

	std::string get_hash_digest(void);

	// TODO template functors
	// comparison functors for std algorithms
	hash_cmp static get_hash_digest_lt();
	hash_cmp static get_hash_digest_eq();
	hash_cmp static get_full_path_lt();
	hash_cmp static get_full_path_eq();
	
	friend std::ostream & operator<<(std::ostream &os, const hash_path& sr);

	~hash_path();
protected:
	unsigned char digest[SHA512_DIGEST_LENGTH];
};
//inline bool operator==(hash_path& lhs, hash_path& rhs)
//{
//	return lhs.get_hash_digest() == rhs.get_hash_digest();
//}
//inline bool operator!=(hash_path& lhs, hash_path& rhs) { return !operator==(lhs, rhs); }
//inline bool operator< (hash_path& lhs, hash_path& rhs)
//{
//	return lhs.get_hash_digest() < rhs.get_hash_digest();
//}
//inline bool operator> (hash_path& lhs, hash_path& rhs) { return  operator< (rhs, lhs); }
//inline bool operator<=(hash_path& lhs, hash_path& rhs) { return !operator> (lhs, rhs); }
//inline bool operator>=(hash_path& lhs, hash_path& rhs) { return !operator< (lhs, rhs); }