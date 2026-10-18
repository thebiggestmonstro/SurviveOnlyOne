// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SOO_LobbyWidget.generated.h"

class UVerticalBox;
class UButton;
class USOO_LobbyUserWidget;
class ASSO_PlayerState;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_LobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UFUNCTION(BlueprintCallable)
	void SetInfo();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ASOO_PlayerState* GetPlayerStateFromIndex(int32 Index);
	
	UFUNCTION(BlueprintCallable)
	void RefreshUI();

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UVerticalBox> UserList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Btn_GameConfig;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USOO_LobbyUserWidget> LobbyUserWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<USOO_LobbyUserWidget>> LobbyUsers;
};
