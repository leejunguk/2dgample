#include <iostream>
#include <queue>

using namespace std;

const int NumberOfCPU = 4;

struct PCB {
	int PID;
	int arrive_time;
	int length;
	int executed_Length;
	int priority;
};

int current_time;

void GenerateProcess()
{
	struct data {
		int time;
		int length;
		int priority;
	};

	vector <data> proc;

	const int TOTAL_TIME = 10000;
	const int AVE_LENGTH = 10;

	for (int i = 0; i < TOTAL_TIME / AVE_LENGTH; i++)
	{
		proc.push_back(data{ rand() % TOTAL_TIME , 
			AVE_LENGTH + (rand() % AVE_LENGTH - AVE_LENGTH / 2) + 4,
			rand() % 10 });

//		proc[rand() % TOTAL_TIME] = AVE_LENGTH + (rand() % AVE_LENGTH - AVE_LENGTH / 2);
//		cout << rand() % TOTAL_TIME << " ";
//		cout << AVE_LENGTH + (rand() % AVE_LENGTH - AVE_LENGTH / 2) << " ";
//		cout << rand() % 10 << endl;
	}

	for (int i = 0; i < TOTAL_TIME; i++)
		for (auto p : proc)
			if (p.time == i) cout << i << " " << p.length << " " << p.priority << endl;
	cout << "-1 -1 -1";
}

bool GetProcess(int current_time, int * length, int *priority, bool *end_of_schedule)
{
	static int number_of_process = 0;
	static bool end_of_process = false;
	static bool have_process = false;
	static int proc_arrive_time = 0;
	static int proc_length = 0;
	static int proc_priority = 0;

	if (true == end_of_process) {
		*length = *priority = 0;
		*end_of_schedule = true;
		return false;
	}

	if (false == have_process) {
		cin >> proc_arrive_time >> proc_length >> proc_priority;
		have_process = true;
	}

	if (proc_arrive_time > current_time) {
		*length = *priority = 0;
		*end_of_schedule = false;
		return false;
	}

	if (-1 == proc_arrive_time) 	{
		end_of_process = true;
		*length = *priority = 0;
		*end_of_schedule = true;
		return false;
	}

	*length = proc_length;
	*priority = proc_priority;
	*end_of_schedule = false;
	have_process = false;
	return true;
}

void FCFS()
{
	int current_time = 0;
	queue <PCB *> ready_queue;
	PCB *current_process = nullptr;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == ready_queue.empty())
			{
				current_process = ready_queue.front();
				ready_queue.pop();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && ready_queue.empty() && (nullptr == current_process))  break;

		 if (nullptr != current_process) {
			current_process->executed_Length++;
//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		 }
//		 else { cout << "PAUSE\n";  }

		current_time++;
	}
	
	cout << "Total Execution Time = " << current_time << endl;
	cout << "Number of Processes Executed = " << total_process << endl;
	cout << "Average Return Time = " << total_return_time / total_process << endl;
	cout << "Average Wait Time = " << total_wait_time / total_process << endl;
	cout << "Average Response Time = " << total_response_time / total_process << endl;
}

void SJF_EARLY_GET(void)
{
	int current_time = 0;
	int update_current_time = 0;
	queue <PCB *> ready_queue;
	queue <PCB *> change_queue;
	PCB *current_process = nullptr;
	PCB *search_process = nullptr;
	PCB *update_process = nullptr;
	PCB *tmp = nullptr;
	int update_total_return_time = 0;
	int update_total_wait_time = 0;
	int update_total_process = 0;
	int update_total_response_time = 0;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))	//ttxt 데이터.
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		
		
		if (nullptr == search_process)			//currentprocess null 다음 
		{
			if (false == ready_queue.empty()) // que가 비어있지 않다면
			{
				search_process = ready_queue.front();		//현재 프로세스는 앞에 프로세스
				ready_queue.pop();							// 팝... 
				if (0 == search_process->executed_Length)		//현재프로세스 실행길이가 0 이면, 
					update_total_response_time += update_current_time - update_process->arrive_time;			//종합 반응시간은 = 현재 시간 - 현재도착시간
			}
		}
		if (nullptr == tmp)			//currentprocess null 다음 
		{
			if (false == ready_queue.empty()) // que가 비어있지 않다면
			{
				tmp = ready_queue.front();		//현재 프로세스는 앞에 프로세스
				ready_queue.pop();							// 팝... 
				if (0 == search_process->executed_Length)		//현재프로세스 실행길이가 0 이면, 
					update_total_response_time += update_current_time - update_process->arrive_time;			//종합 반응시간은 = 현재 시간 - 현재도착시간
			}
		}

		
		
		
		//버블정렬을이용한 스케쥴링큐 재정렬
		for (search_process->PID = 0; ; search_process = ready_queue.front(),ready_queue.pop(), ++search_process->PID)  //배열크기 까지 
		{	
		
			for ( tmp->PID = 0 ; ;tmp =  ready_queue.front() ,ready_queue.pop(), ++tmp->PID)
			{
				if (current_process->length - current_process->executed_Length >= search_process->length)
				{
					change_queue.push(search_process);
				
				}
				if (true == ready_queue.empty())
					break;
			}
			if (true == ready_queue.empty())
				break;
		}



		if (nullptr != update_process)
		{																			//실행시간이, 실행길이보다 길면 
			if (update_process->executed_Length >= update_process->length) {		//현재 프로세스 null 아니라면  (실제진행)
				update_total_return_time += update_current_time - update_process->arrive_time;	//총 반환시간 += 현재시간 - 현재프로세스 도착시간
				update_total_wait_time += update_current_time - update_process->arrive_time - update_process->length;	//총 대기시간 += 현재시간 -도착시간 -현재프로세스 길이
				update_total_process++;			//총 프로세스 증가
				delete update_process;		//실행하면 delete pointer
				update_process = nullptr;	//현재 포인터 null
			}
		}

		if (nullptr == update_process)			//currentprocess null 다음 
		{
			if (false == change_queue.empty()) // que가 비어있지 않다면
			{
				update_process = change_queue.front();		//현재 프로세스는 앞에 프로세스
				change_queue.pop();							// 팝... 
				if (0 == update_process->executed_Length)		//현재프로세스 실행길이가 0 이면, 
					update_total_response_time += update_current_time - update_process->arrive_time;			//종합 반응시간은 = 현재 시간 - 현재도착시간
			}
		}

		if ((true == end_of_schedule) && change_queue.empty() && (nullptr == update_process))  break;	//queue가 비면 브레이크

		if (nullptr != update_process) {
			update_process->executed_Length++;  //null 아니면 현재프로세스 실행길이 ++
			//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		}
		//		 else { cout << "PAUSE\n";  }

		update_current_time++;		//시간변수 
	}

	cout << "Total Execution Time = " << update_current_time << endl;
	cout << "Number of Processes Executed = " << update_total_process << endl;
	cout << "Average Return Time = " << update_total_return_time / update_total_process << endl;
	cout << "Average Wait Time = " << update_total_wait_time / update_total_process << endl;
	cout << "Average Response Time = " << update_total_response_time / update_total_process << endl;

}
void priority_scedule(void)
{
	int current_time = 0;
	queue <PCB *> ready_queue;
	PCB *current_process = nullptr;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == ready_queue.empty())
			{
				current_process = ready_queue.front();
				ready_queue.pop();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && ready_queue.empty() && (nullptr == current_process))  break;

		if (nullptr != current_process) {
			current_process->executed_Length++;
			//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		}
		//		 else { cout << "PAUSE\n";  }

		current_time++;
	}

	cout << "Total Execution Time = " << current_time << endl;
	cout << "Number of Processes Executed = " << total_process << endl;
	cout << "Average Return Time = " << total_return_time / total_process << endl;
	cout << "Average Wait Time = " << total_wait_time / total_process << endl;
	cout << "Average Response Time = " << total_response_time / total_process << endl;

}

int main()
{
	
	FCFS();
	//GenerateProcess();
	SJF_EARLY_GET();
}
