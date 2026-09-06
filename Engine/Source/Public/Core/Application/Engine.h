// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"
#include "Core/Scene/Scene.h"

#include <memory>

class OEngine : public OObject
{
	bool bIsRunning = false;

protected:
	virtual void Run();
	
public:
	OEngine();
	virtual ~OEngine() override = default;
	
	OEngine(const OEngine&) = delete;
	OEngine& operator=(const OEngine&) = delete;
	OEngine(OEngine&) = delete;
	OEngine& operator=(OEngine&&) = delete;

	static OEngine& GetInstance();
	
	virtual void Ini(std::unique_ptr<Scene> scene);

	virtual void Stop();
};
