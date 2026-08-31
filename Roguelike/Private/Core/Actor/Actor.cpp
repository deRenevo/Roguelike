// Copyright deRenevo. All rights reserved.

#include <Core/Actor/Actor.h>
#include <Core/Scene/SceneManager.h>
#include <Core/Scene/Scene.h>
#include <Roguelike.h>


AActor::AActor() : OObject(), ActorWorldLocation({0, 0})
{

}

AActor::AActor(Vector2 worldLocation) : OObject(), ActorWorldLocation(worldLocation)
{

}

AActor::AActor(Vector2 worldLocation, std::string name)
	: OObject(name), ActorWorldLocation(worldLocation)
{

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
	if (bIsHasBeginPLay) return;
	bIsHasBeginPLay = true;
}

void AActor::Tick(float DeltaTime)
{

}

void AActor::Draw()
{

}

void AActor::EndPlay()
{
	if (!bIsHasBeginPLay) return;
}

void AActor::DoTick(float DeltaTime)
{

	if (GetIsPendingKill()) return;
	Tick(DeltaTime);
}

void AActor::DoDraw()
{
	if (GetIsPendingKill()) return;
	Draw();
}

void AActor::SetActorLocation(const Vector2& location)
{
	ActorWorldLocation = location;
}

Vector2 AActor::GetActorLocation() const
{
	return ActorWorldLocation;
}
