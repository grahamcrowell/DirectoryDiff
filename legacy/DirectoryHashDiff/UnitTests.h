#pragma once

using namespace std;
using namespace boost::filesystem;

void test_bgl()
{
	auto folder_path = string(R"(C:\Users\user\Desktop\test)");
	boost::filesystem::path root_path(folder_path);
	unique_ptr<file_system_root> fsr = make_unique<file_system_root>(root_path);
	cout << *fsr << endl;
	list<hash_path> x = *fsr->get_files();
	list<hash_path>::iterator itr = x.begin(),end;
	std::iterator<hash_path, hash_path> sitr = std::iterator<hash_path, hash_path>();
	boost::iterator<hash_path, hash_path> bitr = boost::begin(x);
	//string hash_digest = fsr->getGraph()->m_vertices.at(1).m_property.m_value.get_hash_digest();

}
void test_boost_filesystem()
{
	int filecount = 0;
	std::list<path> *paths = new std::list<path>();
	auto folder_path = "C:/Users/user/Desktop/software"s;
	path *root = new path(folder_path);
	recursive_directory_iterator it = recursive_directory_iterator(*root), end;
	while (it != end)
	{
		std::cout << it->path() << std::endl;
		paths->push_front(it->path());
		++it;
		filecount += 1;
	}
	cout << filecount << " files looped" << endl;
}
void test_openssl_filehash(path path)
{
	unsigned char digest[SHA512_DIGEST_LENGTH];

	streampos size;
	char * memblock;
	std::ifstream file(path.c_str(), ios::in | ios::binary | ios::ate);

	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();
		cout << "the entire file content is in memory (" << path << ")" << endl;
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
	else cout << "Unable to open file (" << path << ")" << endl;
}
void test_openssl_filehash()
{
	auto filename = "C:/Users/user/Desktop/software/denodo/denodo-express-install-6_0-win64/denodo-install-6.0/denodo-install-6.0.dat"s;
	test_openssl_filehash(filename);
}
void test_hash_path()
{
	auto filename = "C:/Users/user/Desktop/software/denodo/denodo-express-install-6_0-win64/denodo-install-6.0/denodo-install-6.0.dat"s;
	hash_path gc = hash_path(filename);
	cout << gc.extension() << endl;
	cout << gc.get_hash_digest() << endl;
}
void test_find_if_not()
{
	vector<int> X{ 0,1,2,3,4,7,10 };
	vector<int> Y{ 0,4,5,6,7,8 };
	int x = X[0];
	auto result = find_if_not(Y.begin(), Y.end(), [&](auto& y) {return y == X[0]; });
	cout << *result << endl;
}
void test_set_difference()
{
	vector<int> X{ 0,1,2,3,4,7,10 };
	vector<int> Y{ 0,4,5,6,7,8 };
	vector<int> diff(X.size() + Y.size());
	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	auto it = set_difference(X.begin(), X.end(), Y.begin(), Y.end(), diff.begin(),
		[](auto &x, auto &y)
	{
		return x < y;
	});
	diff.resize(it - diff.begin());

	std::cout << "The difference has " << (diff.size()) << " elements:\n";
	for each (auto var in diff)
	{
		std::cout << ' ' << var;
	}
	std::cout << '\n';
	for_each(diff.begin(), diff.end(), [](auto &elem) {cout << ' ' << elem; });
	std::cout << endl;
}
void test_loops()
{
	vector<int> X{ 0,1,2,3,4,7,10 };

	for (size_t i = 0; i < X.size(); i++)
	{
		std::cout << ' ' << X[i];
	}
	for (auto it = std::begin(X); it != std::end(X); it++)
	{
		std::cout << ' ' << *it;
	}
	for (auto &x : X)
	{
		std::cout << ' ' << x;
	}
	for each (auto x in X)
	{
		std::cout << ' ' << x;
	}

	for_each(X.begin(), X.end(), [](auto x)
	{
		std::cout << ' ' << x;
	});
}