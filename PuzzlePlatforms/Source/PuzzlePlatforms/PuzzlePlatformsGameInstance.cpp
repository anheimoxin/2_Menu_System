// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "LogMacros.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find MenuBPClass"));
		return;
	}
	MenuClass = MenuBPClass.Class;
	UE_LOG(LogTemp, Warning, TEXT("Class name %s"), *MenuClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
};



void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}


void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass!=nullptr))
	{
		UE_LOG(LogTemp,Error,TEXT("MenuClass is nullptr"));
		return;
	}
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("Menu is nullptr"));
		return;
	}
	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController in nullptr"));
		return;
	}

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("Engine in nullptr"));
		return;
	}
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("World in nullptr"));
		return;
	}
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(FString & Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("Engine in nullptr"));
		return;
	}
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController in nullptr"));
		return;
	}
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
