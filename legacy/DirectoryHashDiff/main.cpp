// DirectoryHashDiff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "UnitTests.h"
//#include "bgl_example.h"
//#include "file_system_root.h"
int main()
{
	//gc_unit_tests::test_opensslfilehash();
	//test_hash_path();
	//gc_unit_tests::create_graph();
	//gc_unit_tests::create_custom_graph();
	test_bgl();
	//test_bfs();
	//test_set_difference();
	std::cout << std::endl << "execution complete" << std::endl << "press enter to exit" << std::endl;
	getchar();
	return 0;
}

