// Copyright deRenevo. All rights reserved.

#include "Core/Manager/TaskQueueManager.h"

void TaskQueueManager::Ini()
{
	bIsRunning.store(true);
	Run();
}

void TaskQueueManager::Run()
{
	for (uint8 i = 0; i < CountWorker; ++i)
	{
		WorkerThreads.emplace_back([this](void)
		{

			while (bIsRunning.load())
			{
				std::function<void()> Task;

				{
					std::unique_lock Lock(WorkerTasksMutex);
					WorkerConditionVariable.wait(Lock, [this](void)
					{
						return !WorkerQueueTaskFunctions.empty() || !bIsRunning.load();
					});
					if (!bIsRunning.load() && WorkerQueueTaskFunctions.empty()) break;
					if (WorkerQueueTaskFunctions.empty()) continue;

					Task = std::move(WorkerQueueTaskFunctions.front());
					WorkerQueueTaskFunctions.pop();
				}
				if (Task) Task();
			}
		});
	}
}

void TaskQueueManager::Enqueue(ETaskQueueType taskType, const std::function<void()>& task)
{
	switch (taskType)
	{
	case ETaskQueueType::Main:
	{
		std::lock_guard Lock(MainTasksMutex);
		MainQueueTaskFunctions.push(task);
		break;
	}

	case ETaskQueueType::Worker:
	{
		std::lock_guard Lock(WorkerTasksMutex);
		WorkerQueueTaskFunctions.push(task);
		WorkerConditionVariable.notify_one();
		break;
	}

	default:
	{
		std::printf("Error task type %i\n", taskType);
		break;
	}
	}
}

void TaskQueueManager::ProcessMainTasks()
{
	std::queue<std::function<void()>> Function;

	{
		std::lock_guard LockMain(MainTasksMutex);
		std::swap(Function, MainQueueTaskFunctions);
	}

	while (!Function.empty())
	{
		Function.front()();
		Function.pop();
	}
}

void TaskQueueManager::Shutdown()
{
	bIsRunning.store(false);
	WorkerConditionVariable.notify_all();
	for (auto& thread : WorkerThreads)
	{
		if (thread.joinable()) thread.join();
	}
	WorkerThreads.clear();
}
