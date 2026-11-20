// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

#include <functional>

enum class EInputType;
struct FMulticastDelegateHandle;
class InputManager;
class APawn;

class APlayerController : public AActor
{
	APawn* PlayerPawn = nullptr;

protected:
	virtual void SetupPlayerInputComponent(InputManager& inputManager);

public:
	APlayerController();
	explicit APlayerController(FVector2D worldLocation);
	APlayerController(FVector2D worldLocation, const std::string& name);
	
	virtual ~APlayerController() override;

	virtual void BeginPlay() override;

	void Possess(APawn* pawn);
	void UnPossess();
	
	//Temp code 
	
	std::vector<FMulticastDelegateHandle> InputHandlers;
	void SubscribeKey(KeyboardKey key, EInputType inputType, const std::function<void()>& callback);
	
	// =======
};
