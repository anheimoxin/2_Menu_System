// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"
/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* MenuInterface);
	
	void Setup();
	void Teardown();

protected:
	virtual bool Initialize();

private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(Meta = (BindWidget))
		class UButton* JoinButton;

	UPROPERTY(Meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(Meta = (BindWidget))
		class UWidget* JoinMenu;

	UFUNCTION()
		void HostServer();
	UFUNCTION()
		void OpenJoinMenu();

	
	IMenuInterface* MenuInterface;
};
