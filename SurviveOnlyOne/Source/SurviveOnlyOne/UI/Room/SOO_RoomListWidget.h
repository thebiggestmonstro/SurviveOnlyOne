// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionsCallbackProxy.h"
#include "SOO_RoomListWidget.generated.h"

class UWrapBox;
class UButton;
class USOO_RoomItemWidget;

/**
 * 
 */
UCLASS()
class SURVIVEONLYONE_API USOO_RoomListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
	void SetInfo();

	UFUNCTION(BlueprintCallable)
	void RefreshUI();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWrapBox> RoomList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Refresh;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Btn_CreateGame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Close;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USOO_RoomItemWidget> RoomItemWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<USOO_RoomItemWidget>> Rooms;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBlueprintSessionResult> SessionInfos;
};
