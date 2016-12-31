#include "stdafx.h"
//#include "UnitTests.h"

//using namespace boost::filesystem;
////using namespace std::string_literals; // https://msdn.microsoft.com/en-CA/library/69ze775t.aspx
//using namespace std;
//
//void test_file_system_root()
//{
//	auto folder_path = "C:/Users/user/Desktop/software"s;
//	path root = path(folder_path);
//	file_system_root fsr(folder_path);
//	fsr.populate_filesystem_graph();
//}
//void test_boost_filesystem()
//{
//	int filecount = 0;
//	std::list<path> *paths = new std::list<path>();
//	auto folder_path = "C:/Users/user/Desktop/software"s;
//	path root = path(folder_path);
//	recursive_directory_iterator it = recursive_directory_iterator(root), end;
//	while (it != end)
//	{
//		std::cout << it->path() << std::endl;
//		paths->push_front(it->path());
//		++it;
//		filecount += 1;
//	}
//	cout << filecount << " files looped" << endl;
//}
//void test_openssl_filehash(path path)
//{
//	unsigned char digest[SHA512_DIGEST_LENGTH];
//
//	streampos size;
//	char * memblock;
//	std::ifstream file(path.c_str(), ios::in | ios::binary | ios::ate);
//
//
//	if (file.is_open())
//	{
//		size = file.tellg();
//		memblock = new char[size];
//		file.seekg(0, ios::beg);
//		file.read(memblock, size);
//		file.close();
//		cout << "the entire file content is in memory (" << path << ")" << endl;
//		SHA512_CTX ctx;
//		SHA512_Init(&ctx);
//		SHA512_Update(&ctx, memblock, size);
//		SHA512_Final(digest, &ctx);
//		delete[] memblock;
//		char mdString[SHA512_DIGEST_LENGTH * 2 + 1];
//		for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
//			sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
//		printf("SHA512 digest: %s\n", mdString);
//	}
//	else cout << "Unable to open file (" << path << ")" << endl;
//}
//void test_opensslfilehash()
//{
//	auto filename = "C:/Users/user/Desktop/software/denodo/denodo-express-install-6_0-win64/denodo-install-6.0/denodo-install-6.0.dat"s;
//	test_openssl_filehash(filename);
//}
//void test_hash_path()
//{
//	auto filename = "C:/Users/user/Desktop/software/denodo/denodo-express-install-6_0-win64/denodo-install-6.0/denodo-install-6.0.dat"s;
//	hash_path gc = hash_path(filename);
//	cout << gc.extension() << endl;
//	cout << gc.get_hash() << endl;
//}
