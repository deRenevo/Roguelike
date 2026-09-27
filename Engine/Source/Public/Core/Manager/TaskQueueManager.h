// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Math/BasicTypes.h"

#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <thread>


enum class ETaskQueueType : uint8
{
	Main,
	Worker
};

class TaskQueueManager
{
	static constexpr uint8 CountWorker = 4; 
	
	std::queue<std::function<void()>> MainQueueTaskFunctions;
	std::queue<std::function<void()>> WorkerQueueTaskFunctions;
	std::mutex MainTasksMutex;
	std::mutex WorkerTasksMutex;
	
	std::vector<std::thread> WorkerThreads;
	
	std::condition_variable WorkerConditionVariable;

	std::atomic<bool> bIsRunning = false;


	TaskQueueManager() = default;
	~TaskQueueManager() = default;

public:
	TaskQueueManager(const TaskQueueManager&) = delete;
	TaskQueueManager& operator=(const TaskQueueManager&) = delete;
	TaskQueueManager(TaskQueueManager&) = delete;
	TaskQueueManager& operator=(TaskQueueManager&&) = delete;

	void Ini();
	void Run();
	void Enqueue(ETaskQueueType taskType, const std::function<void()>& task);
	void ProcessMainTasks();
	void Shutdown();
	
	
	static TaskQueueManager& GetInstance()
	{
		static TaskQueueManager TQM;
		return TQM;
	}
};
