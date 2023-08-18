// infotest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "infotest.h"

	Request* GetRequest()
	{
		if (CurrNumerOfTestRequests < NumberOfTestRequests)
		{
			CurrNumerOfTestRequests++;
			return new Request();
		}
		else
		{
			return nullptr;
		}
}
	std::atomic<bool> isActive = true;

	std::queue<Request*> requests;

	std::vector<std::thread> pool;

	std::mutex lock;

	void ProcessRequest(std::queue<Request*>* requests)
	{
		while (isActive)
		{
			std::cout << "is active\n";
			lock.lock();
			if (!requests->empty())
			{
				Request* request = requests->front();
				std::cout << "process a request by " << std::this_thread::get_id() << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			lock.unlock();

		}
		std::cout << "End of ProcessRequest\n";
	}
	void waitForNumberOfThread()
	{
		while (CurrNumberOfThreads == NumberOfThreads)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		return;
	}

	std::thread threads[NumberOfThreads];

	void exec()
	{
		while (isActive)
		{
			std::cout << "exec\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}

	void DoProcess()
	{
		for (int i = 0; i < NumberOfThreads; i++)
		{
			threads[i] = std::thread(ProcessRequest, &requests);
			threads[i].detach();
		}
/*
		for (int i = 0; i < pool.size(); i++)
		{
			//pool[i] = std::thread(&ProcessRequest, &requests);
			pool[i].detach();
		}
*/
	}

	int main()
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		std::cout << "Test\n";
		DoProcess();

		while (true)
		{
			Request* request = GetRequest();
			if (request != nullptr)
			{
				std::cout << "pushing a request\n";
				lock.lock();
				requests.push(request);
				lock.unlock();
				std::this_thread::sleep_for(std::chrono::microseconds(100));
			}

		
			else
			{
				for (int i = 0; i < pool.size(); i++)
				{
					if (pool[i].joinable())
						pool[i].join();
				}

				isActive = false;
				std::cout << "End of the queue\n";
				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				std::cout << "duration: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "c." << std::endl;
				exit(0);
			}
			for (int i = 0; i < pool.size(); i++)
			{
				if (pool[i].joinable())
					pool[i].join();
			}

	}
	}


