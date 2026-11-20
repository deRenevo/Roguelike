// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Actor/Actor.h"

#include <functional>

struct FMulticastDelegateHandle;
enum class EInputType;
class InputManager;
class APlayerController;

class APawn : public AActor
{
	APlayerController* OwnerPlayerController = nullptr;

protected:
	virtual void Tick(float deltaTime) override;

public:
	APawn();
	explicit APawn(FVector2D worldLocation);
	APawn(FVector2D worldLocation, const std::string& name);
	
	virtual ~APawn() override;
	
	virtual void SetupPlayerInputComponent(InputManager& inputManager);

	virtual void BeginPlay() override;

	void PossessedBy(APlayerController* playerController);
	void UnPossessed();
	
	//Temp code 
	
	std::vector<FMulticastDelegateHandle> InputHandlers;
	void SubscribeKey(KeyboardKey key, EInputType inputType, const std::function<void()>& callback);
	
	// =======
};
