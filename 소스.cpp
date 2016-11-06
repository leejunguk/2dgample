#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;
using namespace std::chrono;
mutex mylock;


const int SIZE = 100000000;
int sum = 0;
int core = 0;
bool flag[2] = {false, false};
int turn = 0;

atomic<int> atom_sum = 0;
atomic_flag p = { 0 };



void func_tas(void)
{
	for (int i = 0; i < SIZE / core; ++i)
	{
		while (atomic_flag_test_and_set(&p));
		sum += 1;
		atomic_flag_clear(&p);
	}
}

void func_mutex(void)
{
	for (int i = 0; i < SIZE / core; ++i)
	{
		mylock.lock();
		sum += 1;
		mylock.unlock();
	}
}
void func_atom(void)
{
	for (int i = 0; i < SIZE / core; ++i)
	{
		atom_sum += 1;
	}
}
void sum_thread()
{
	for (int i = 0; i < SIZE / core; ++i)
	{
		sum += 1;
	}
}

void sum_core2(int num_core)
{   
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ sum_thread };
	thread t2{ sum_thread };
	t1.join();
	t2.join();


	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = "<< num_core <<", SUM = " << sum << endl;
}
void sum_core1(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ sum_thread };

	t1.join();


	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}

void sum_core4(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ sum_thread };
	thread t2{ sum_thread };
	thread t3{ sum_thread };
	thread t4{ sum_thread };
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}

void sum_core8(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ sum_thread };
	thread t2{ sum_thread };
	thread t3{ sum_thread };
	thread t4{ sum_thread };
	thread t5{ sum_thread };
	thread t6{ sum_thread };
	thread t7{ sum_thread };
	thread t8{ sum_thread };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}


void sum_core16(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ sum_thread };
	thread t2{ sum_thread };
	thread t3{ sum_thread };
	thread t4{ sum_thread };
	thread t5{ sum_thread };
	thread t6{ sum_thread };
	thread t7{ sum_thread };
	thread t8{ sum_thread };
	thread t9{ sum_thread };
	thread t10{ sum_thread };
	thread t11{ sum_thread };
	thread t12{ sum_thread };
	thread t13{ sum_thread };
	thread t14{ sum_thread };
	thread t15{ sum_thread };
	thread t16{ sum_thread };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}

void mutex_core1(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_mutex };
	
	t1.join();
	

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}

void mutex_core2(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_mutex };
	thread t2{ func_mutex };
	t1.join();
	t2.join();


	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}

void mutex_core4(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_mutex };
	thread t2{ func_mutex };
	thread t3{ func_mutex };
	thread t4{ func_mutex };
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}

void mutex_core8(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_mutex };
	thread t2{ func_mutex };
	thread t3{ func_mutex };
	thread t4{ func_mutex };
	thread t5{ func_mutex };
	thread t6{ func_mutex };
	thread t7{ func_mutex };
	thread t8{ func_mutex };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}

void mutex_core16(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_mutex };
	thread t2{ func_mutex };
	thread t3{ func_mutex };
	thread t4{ func_mutex };
	thread t5{ func_mutex };
	thread t6{ func_mutex };
	thread t7{ func_mutex };
	thread t8{ func_mutex };
	thread t9{ func_mutex };
	thread t10{ func_mutex };
	thread t11{ func_mutex };
	thread t12{ func_mutex };
	thread t13{ func_mutex };
	thread t14{ func_mutex };
	thread t15{ func_mutex };
	thread t16{ func_mutex };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}
void atom_core1(int num_core)
{
	atom_sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_atom };

	t1.join();


	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << atom_sum << endl;
}
void atom_core2(int num_core)
{
	atom_sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_atom };
	thread t2{ func_atom };
	t1.join();
	t2.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << atom_sum << endl;
}
void atom_core4(int num_core)
{
	atom_sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_atom };
	thread t2{ func_atom };
	thread t3{ func_atom };
	thread t4{ func_atom };
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << atom_sum << endl;
}
void atom_core8(int num_core)
{
	atom_sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_atom };
	thread t2{ func_atom };
	thread t3{ func_atom };
	thread t4{ func_atom };
	thread t5{ func_atom };
	thread t6{ func_atom };
	thread t7{ func_atom };
	thread t8{ func_atom };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << atom_sum << endl;
}
void atom_core16(int num_core)
{
	atom_sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_atom };
	thread t2{ func_atom };
	thread t3{ func_atom };
	thread t4{ func_atom };
	thread t5{ func_atom };
	thread t6{ func_atom };
	thread t7{ func_atom };
	thread t8{ func_atom };
	thread t9{ func_atom };
	thread t10{ func_atom };
	thread t11{ func_atom };
	thread t12{ func_atom };
	thread t13{ func_atom };
	thread t14{ func_atom };
	thread t15{ func_atom };
	thread t16{ func_atom };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << atom_sum << endl;
}
void tas_core1(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_tas };

	t1.join();


	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}
void tas_core2(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_tas };
	thread t2{ func_tas };
	t1.join();
	t2.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}
void tas_core4(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_tas };
	thread t2{ func_tas };
	thread t3{ func_tas };
	thread t4{ func_tas };
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}
void tas_core8(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_tas };
	thread t2{ func_tas };
	thread t3{ func_tas };
	thread t4{ func_tas };
	thread t5{ func_tas };
	thread t6{ func_tas };
	thread t7{ func_tas };
	thread t8{ func_tas };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}
void tas_core16(int num_core)
{
	sum = 0;
	auto start_t = high_resolution_clock::now();

	core = num_core;
	thread t1{ func_tas };
	thread t2{ func_tas };
	thread t3{ func_tas };
	thread t4{ func_tas };
	thread t5{ func_tas };
	thread t6{ func_tas };
	thread t7{ func_tas };
	thread t8{ func_tas };
	thread t9{ func_tas };
	thread t10{ func_tas };
	thread t11{ func_tas };
	thread t12{ func_tas };
	thread t13{ func_tas };
	thread t14{ func_tas };
	thread t15{ func_tas };
	thread t16{ func_tas };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << num_core << ", SUM = " << sum << endl;
}

void decker1(void)
{
	
	for (int i = 0; i < SIZE / 2; ++i)
	{
		flag[0] = true;
		while (flag[1] == true) 
		{
			if(turn == 1)
			{
				flag[0] = false;
				
				while (turn == 1)
				{
				}flag[0] = true;

			}
		}
		++sum;

		turn = 1;
		flag[0] = false;
	}

}

void decker2(void)
{

	for (int i = 0; i < SIZE / 2; ++i)
	{
		flag[1] = true;
		while (flag[0] == true)
		{
			if (turn == 0)
			{
				flag[1] = false;

				while (turn == 0)
				{

				}
				flag[1] = true;

			}
		}
		++sum;

		turn = 0;
		flag[1] = false;
	}

}

void deckerstart(void)
{
	sum = 0;
	core = 2;
	auto start_t = high_resolution_clock::now();
	thread t1{ decker1 };
	thread t2{ decker2 };
	t1.join();
	t2.join();


	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << core << ", SUM = " << sum << endl;
}

int main()
{
	cout << "샘플프로그램" << endl;
	
	sum = 0;
	auto start_t = high_resolution_clock::now();
	for (int i = 0; i < 100000000; i++) sum = sum + 1;
	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = 1, SUM = " << sum << endl;
	
	cout << endl;
	cout << endl;
	cout << "조건2: 1,2,4,8,16개 스레드 나누기" << endl;
	sum_core1(1);
	sum_core2(2);
	sum_core4(4);
	sum_core8(8);
	sum_core16(16);
	cout << endl;
	cout << endl;
	cout << "조건3:데커알고리즘" << endl;
	deckerstart();

	cout << endl;
	cout << endl;
	cout << "조건4:mutex 실행" << endl;
	mutex_core1(1);
	mutex_core2(2);
	mutex_core4(4);
	mutex_core8(8);
	mutex_core16(16);

	cout << endl;
	cout << endl;
	cout << "조건5:atom 실행" << endl;
	atom_core1(1);
	atom_core2(2);
	atom_core4(4);
	atom_core8(8);
	atom_core16(16);

	cout << endl;
	cout << endl;
	cout << "조건6:tas 실행" << endl;
	tas_core1(1);
	tas_core2(2);
	tas_core4(4);
	tas_core8(8);
	tas_core16(16);
}


