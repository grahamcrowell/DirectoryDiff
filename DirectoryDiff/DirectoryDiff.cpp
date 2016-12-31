// DirectoryDiff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "unit_tests.h"

clock_t user_start(std::vector<std::string> argv)
{
	boost::filesystem::path exe(argv[0]);
	std::cout << "starting: " << exe.leaf().replace_extension("").generic_string() << std::endl;
	std::cout << "current working directory: " << exe.parent_path().generic_string() << std::endl << std::endl;
	clock_t start_time;
	start_time = clock();
	return start_time;
}
bool get_key_press(char *c)
{
	if (_kbhit()) // _kbhit is iso standard for kbhit
	{
		*c = _getch();  // _getch is iso standard for getch
		return true; // Key Was Hit
	}
	return false; // No keys were pressed
}
int user_exit(std::vector<std::string> argv, clock_t start_time)
{
	int exit_delay_seconds = 3;
	const int ESCAPE = 27;
	const int RETURN = 13;
	char key = ' ';
	int sleep_time_milliseconds = 10;
	int remaining_delay_milliseconds = exit_delay_seconds * 1000;
	clock_t end_time = clock();
	float runtime_ticks((float)end_time - (float)start_time);
	float runtime_seconds = runtime_ticks / CLOCKS_PER_SEC;
	std::cout << std::endl << "execution complete" << std::endl << "runtime: " << runtime_seconds << " seconds"<< std::endl << "will exit in " << exit_delay_seconds << " seconds" << std::endl;

	while (remaining_delay_milliseconds > 0)
	{
		while (!get_key_press(&key) && remaining_delay_milliseconds > 0)
		{
			//std::cout << "sleeping for: " << sleep_time << std::endl;
			remaining_delay_milliseconds -= sleep_time_milliseconds;
			boost::this_thread::sleep(boost::posix_time::milliseconds(sleep_time_milliseconds));
		}
		if (key==RETURN)
		{
			std::cout << "You Pressed: RETURN " << std::endl;
		}
		else if (key == ESCAPE)
		{
			std::cout << "ESCAPE delay override." << std::endl;
			remaining_delay_milliseconds = -1;
		}
		//std::cout << "You Pressed: " << key << std::endl;
	}

	std::cout << "exitting now." << std::endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	return 0;
}

void foo()
{
	//unit_test::test_boost_filesystem();
	test_openssl_filehash();
}

int main(int argc, char* arga[])
{
	std::vector<std::string> argv;
	for (int i = 0; i < argc; ++i)
	{
		argv.push_back(arga[i]);
	}
	clock_t start_time = user_start(argv);

	foo();

	return user_exit(argv, start_time);
}

