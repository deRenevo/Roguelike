// Copyright deRenevo. All rights reserved.

#include "Core/Actor/Actor.h"
#include "Core/Manager/SceneManager.h"
#include "Core/Scene/Scene.h"

AActor::AActor()
	: AActor(FVector2D{0, 0}, "Actor")
{

}

AActor::AActor(const FVector2D& location) : AActor(location, "Actor")
{

}

AActor::AActor(const std::string& name) : AActor({0, 0}, name)
{
}


AActor::AActor(const FVector2D& location, const std::string& name) : OObject(name)
{
	RootSceneComponent = std::make_unique<OSceneComponent>("RootSceneComponent");
	RootSceneComponent->SetOwner(this);
	RootSceneComponent->SetLocation(location);
}

void AActor::PreInitializeComponents()
{

}

void AActor::InitializeComponent()
{

}

void AActor::PostInitializeComponents()
{

}

AActor::~AActor()
{
	
}

void AActor::DoInitialize()
{
	PreInitializeComponents();
	InitializeComponent();
	PostInitializeComponents();
}

void AActor::BeginPlay()
{
	if (bIsHasBeginPlay) return;
	bIsHasBeginPlay = true;

	if (RootSceneComponent)
	{
		RootSceneComponent->BeginPlay();
	}
}

void AActor::Tick(float DeltaTime)
{
	if (RootSceneComponent)
	{
		RootSceneComponent->DoTick(DeltaTime);
	}
}

void AActor::Draw(const FBox2D& cameraViewportBounds)
{
	if (RootSceneComponent)
	{
		RootSceneComponent->DoDraw(cameraViewportBounds);
	}
}

void AActor::EndPlay()
{
	if (!bIsHasBeginPlay) return;

	if (RootSceneComponent)
	{
		RootSceneComponent->EndPlay();
		RootSceneComponent->OnDetach();
		RootSceneComponent = nullptr;
	}
}

void AActor::DoTick(float DeltaTime)
{
	if (GetIsPendingKill() || !bIsTickable) return;
	Tick(DeltaTime);
}

void AActor::DoDraw(const FBox2D& cameraViewportBounds)
{
	if (GetIsPendingKill()) return;
	Draw(cameraViewportBounds);
}

void AActor::SetRootSceneComponent(std::unique_ptr<OSceneComponent> rootSceneComponent)
{
	if (!rootSceneComponent)
	{
		return;
	}

	RootSceneComponent = std::move(rootSceneComponent);
	RootSceneComponent->SetOwner(this);
	if (bIsHasBeginPlay)
	{
		RootSceneComponent->BeginPlay();
		RootSceneComponent->OnAttach();
	}
}
