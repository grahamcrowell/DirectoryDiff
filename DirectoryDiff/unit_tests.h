#pragma once
//#include "hash_path.h"

void test_boost_filesystem()
{
	using namespace std::string_literals;
	int filecount = 0;
	std::list<boost::filesystem::path> *paths = new std::list<boost::filesystem::path>();
	auto folder_path = "C:/Users/user/Desktop/software"s;
	boost::filesystem::path *root = new boost::filesystem::path(folder_path);
	boost::filesystem::recursive_directory_iterator it = boost::filesystem::recursive_directory_iterator(*root), end;
	while (it != end)
	{
		std::cout << it->path() << std::endl;
		paths->push_front(it->path());
		++it;
		filecount += 1;
	}
	std::cout << filecount << " files looped" << std::endl;
}
void test_openssl_filehash(boost::filesystem::path path)
{
	unsigned char digest[SHA512_DIGEST_LENGTH];

	std::streampos size;
	char * memblock;
	std::ifstream file(path.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();
		std::cout << "the entire file content is in memory (" << path << ")" << std::endl;
		SHA512_CTX ctx;
		SHA512_Init(&ctx);
		SHA512_Update(&ctx, memblock, size);
		SHA512_Final(digest, &ctx);
		delete[] memblock;
		char mdString[SHA512_DIGEST_LENGTH * 2 + 1];
		for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
			sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
		printf("SHA512 digest: %s\n", mdString);
	}
	else std::cout << "Unable to open file (" << path << ")" << std::endl;
}
void test_openssl_filehash()
{
	using namespace std::string_literals;
	auto filename = "C:/Users/user/Desktop/software/denodo/denodo-express-install-6_0-win64/denodo-install-6.0/denodo-install-6.0.dat"s;
	test_openssl_filehash(filename);
}
void test_hash_path()
{
	using namespace std::string_literals;
	auto filename = std::string("C:/Users/user/Desktop/software/denodo/denodo-express-install-6_0-win64/denodo-install-6.0/denodo-install-6.0.dat");
	hash_path gc(filename);
	std::cout << gc.extension() << std::endl;
	std::cout << gc.get_hash_digest() << std::endl;
}