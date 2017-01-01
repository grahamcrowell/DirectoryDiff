#pragma once
//#include "hash_path.h"



void test_set_diff()
{
	auto src_dir = std::string(R"(C:\Users\user\Desktop\sync_test\testSrc)");
	sync_root src_sr(src_dir);
	src_sr.walk_file_system();
	std::sort(src_sr.begin(), src_sr.end(), hash_path::get_hash_digest_lt());
	
	auto dst_dir = std::string(R"(C:\Users\user\Desktop\sync_test\testDst)");
	sync_root dst_sr(dst_dir);
	dst_sr.walk_file_system();
	std::sort(dst_sr.begin(), dst_sr.end(), hash_path::get_hash_digest_lt());
	
	std::vector<hash_path> diff;
	std::set_difference(src_sr.begin(), src_sr.end(), dst_sr.begin(), dst_sr.end(),
		std::inserter(diff, diff.begin()),hash_path::get_hash_digest_lt());
	
	std::cout << src_sr << std::endl;
	//for (auto i : src_sr._files) std::cout << i << ' ';
	std::cout << "minus ";
	//for (auto i : dst_sr._files) std::cout << i << ' ';
	std::cout << dst_sr << std::endl;
	std::cout << "is: ";

	for (auto i : diff) std::cout << i.generic_string() << std::endl;
	std::cout << '\n';
	
	std::cout << diff.size() << std::endl;
}

void test_sync_root_sort()
{
	auto folder_path = std::string(R"(C:\Users\user\Desktop\sync_test\testSrc)");
	sync_root sr(folder_path);
	sr.walk_file_system();
	std::cout << sr << std::endl;
	std::random_shuffle(sr.begin(), sr.end());
	std::cout << sr << std::endl;
	std::sort(sr.begin(), sr.end(), hash_path::get_hash_digest_lt());
	std::cout << sr << std::endl;
	std::sort(sr.begin(), sr.end(), hash_path::get_full_path_lt());
	std::cout << sr << std::endl;
}

void test_sync_root()
{
	auto folder_path = std::string(R"(C:\Users\user\Desktop\sync_test\testSrc)");
	sync_root sr(folder_path);
	sr.walk_file_system();
	std::cout << sr.begin()->get_hash_digest() << std::endl;
}

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
