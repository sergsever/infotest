#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <queue>
#include <mutex>
#include <future>
#include <vector>


/*Дано*/
	const int NumberOfThreads = 2;
	class Request
	{};
	Request* GetRequest() throw();
	void ProcessRequest(std::queue<Request*>* requests) throw();
/*---*/
	const int NumberOfTestRequests = 10;
	std::atomic<int> CurrNumberOfThreads = 0;
	int CurrNumerOfTestRequests = 0;
