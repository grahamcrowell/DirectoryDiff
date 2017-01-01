#include "stdafx.h"
#include "hash_path.h"


/**
 * \brief lazy, thread safe computation of SHA512 hash digest of file using openssl. 
 * \return SHA512 hash digest
 */
std::string hash_path::get_hash_digest()
{
	// TODO: add exception handling

	std::mutex hash_mutex;
	// lock mutex before accessing file
	std::lock_guard<std::mutex> lock(hash_mutex);
	if (last_write_time == 0)
	{
		last_write_time = boost::filesystem::last_write_time(this->string());
	}
	if (hash_digest == ""s)
	{
		//std::cout << "attempting to calculate hash path: " << this->string() << std::endl;

		if (boost::filesystem::is_directory(this->string()))
		{
			std::cout << "path is a directory." << std::endl;
		}

		std::streampos size;
		char* memblock;
		std::ifstream file(this->c_str(), std::ios::in | std::ios::binary | std::ios::ate);

		if (file.is_open())
		{
			size = file.tellg();
			file_size = size;
			memblock = new char[size];
			file.seekg(0, std::ios::beg);
			file.read(memblock, size);
			file.close();
			//std::cout << "\tthe entire file content is in memory (" << file_size << " bytes)" << std::endl;
			SHA512_CTX ctx;
			SHA512_Init(&ctx);
			SHA512_Update(&ctx, memblock, size);
			SHA512_Final(digest, &ctx);
			delete[] memblock;
			char mdString[SHA512_DIGEST_LENGTH * 2 + 1];
			for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
				sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

			// set instance variable hash_digest
			hash_digest = std::string(mdString);
			return hash_digest;
		}
		else std::cout << "Hashing Error: Unable to open file: " << this->string() << "" << std::endl;
		return{};
	}
	else
	{
		std::cout << "\thash for " << this->string() << " already calculated as \n\t" << hash_digest << std::endl;
		return hash_digest;
	}
}

hash_cmp hash_path::get_hash_digest_lt()
{
	struct hash_digest_cmp
	{
		bool operator()(hash_path& lhs, hash_path& rhs) const
		{
			return lhs.get_hash_digest() < rhs.get_hash_digest();
		}
	};
	hash_cmp cmp = hash_digest_cmp();
	return cmp;
}

hash_cmp hash_path::get_hash_digest_eq()
{
	struct hash_digest_cmp
	{
		bool operator()(hash_path& lhs, hash_path& rhs) const
		{
			return lhs.get_hash_digest() == rhs.get_hash_digest();
		}
	};
	hash_cmp cmp = hash_digest_cmp();
	return cmp;
}

hash_cmp hash_path::get_full_path_lt()
{
	struct full_path_cmp
	{
		bool operator()(hash_path& lhs, hash_path& rhs) const
		{
			return lhs.generic_string() < rhs.generic_string();
		}
	};
	hash_cmp cmp = full_path_cmp();
	return cmp;
}

hash_cmp hash_path::get_full_path_eq()
{
	struct full_path_cmp
	{
		bool operator()(hash_path& lhs, hash_path& rhs) const
		{
			return lhs.generic_string() == rhs.generic_string();
		}
	};
	hash_cmp cmp = full_path_cmp();
	return cmp;
}

hash_path::~hash_path()
{
}

std::ostream& operator<<(std::ostream& os, const hash_path& sr)
{
	std::time_t last_write_time = boost::filesystem::last_write_time(sr);
	os << sr.generic_string() << std::endl
		<< "\t" << std::ctime(&last_write_time) << std::endl
	;
}
