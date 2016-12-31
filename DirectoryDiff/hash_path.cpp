#include "stdafx.h"
#include "hash_path.h"

std::string hash_path::get_hash_digest()
{
	std::mutex hash_mutex;
	// lock mutex before accessing file
	std::lock_guard<std::mutex> lock(hash_mutex);
	if (hash_digest == ""s)
	{
		std::cout << "attempting to calculate hash path: " << this->string() << std::endl;

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
			memblock = new char[size];
			file.seekg(0, std::ios::beg);
			file.read(memblock, size);
			file.close();
			std::cout << "\tthe entire file content is in memory (" << size << " bytes)" << std::endl;
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

hash_path::~hash_path()
{
}
