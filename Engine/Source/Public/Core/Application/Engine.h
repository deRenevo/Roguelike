// Copyright deRenevo. All rights reserved.

#pragma once

#include <memory>

class OScene;

class OEngine
{
	bool bIsRunning = false;
	std::unique_ptr<OScene> LoadThenScene = nullptr;

protected:
	virtual void Run();

public:
	OEngine();
	virtual ~OEngine() = default;

	OEngine(const OEngine&) = delete;
	OEngine& operator=(const OEngine&) = delete;
	OEngine(OEngine&) = delete;
	OEngine& operator=(OEngine&&) = delete;

	static OEngine& GetInstance();

	virtual void Ini(std::unique_ptr<OScene> scene);

	virtual void Stop();

	void LoadScene(std::unique_ptr<OScene> scene);
};
