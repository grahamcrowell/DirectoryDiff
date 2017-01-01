#pragma once
#include "stdafx.h"

using namespace std::string_literals;

class hash_path : public boost::filesystem::path
{
	//std::mutex hash_mutex;
	std::string hash_digest = ""s;
public:
	//hash_path() = delete;
	hash_path() {}
	hash_path(boost::filesystem::path _path) : path(_path) {}
	hash_path(std::string _path) : path(_path) {}
	hash_path(std::wstring _path) : path(_path) {}
	hash_path(char* _path) : path(_path) {}
	hash_path(wchar_t* _path) : path(_path) {}

	std::string get_hash_digest(void);

	~hash_path();
protected:
	unsigned char digest[SHA512_DIGEST_LENGTH];



};
inline bool operator==(hash_path& lhs, hash_path& rhs)
{
	return lhs.get_hash_digest() == rhs.get_hash_digest();
}
inline bool operator!=(hash_path& lhs, hash_path& rhs) { return !operator==(lhs, rhs); }
inline bool operator< (hash_path& lhs, hash_path& rhs)
{
	return lhs.get_hash_digest() < rhs.get_hash_digest();
}
inline bool operator> (hash_path& lhs, hash_path& rhs) { return  operator< (rhs, lhs); }
inline bool operator<=(hash_path& lhs, hash_path& rhs) { return !operator> (lhs, rhs); }
inline bool operator>=(hash_path& lhs, hash_path& rhs) { return !operator< (lhs, rhs); }