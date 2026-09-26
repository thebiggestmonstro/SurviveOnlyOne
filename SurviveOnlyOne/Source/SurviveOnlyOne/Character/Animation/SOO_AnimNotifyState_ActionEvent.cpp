// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/SOO_AnimNotifyState_ActionEvent.h"
#include "Player/Input/SOO_ActionComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void USOO_AnimNotifyState_ActionEvent::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	SendEvent(MeshComp, TEXT("_Begin"));
}

void USOO_AnimNotifyState_ActionEvent::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	SendEvent(MeshComp, TEXT("_Tick"));
}

void USOO_AnimNotifyState_ActionEvent::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	SendEvent(MeshComp, TEXT("_End"));
}

void USOO_AnimNotifyState_ActionEvent::SendEvent(USkeletalMeshComponent* MeshComp, const TCHAR* Suffix)
{
	if (!MeshComp)
	{
		return;
	}

	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		if (USOO_ActionComponent* ActionComponent = Character->FindComponentByClass<USOO_ActionComponent>())
		{
			const FName FullEventName(*(EventName.ToString() + Suffix));
			ActionComponent->NotifyActionEvent(ActionTag, FullEventName);
		}
	}
}

#if WITH_EDITOR
FString USOO_AnimNotifyState_ActionEvent::GetNotifyName_Implementation() const
{
	return EventName.IsNone() ? Super::GetNotifyName_Implementation() : EventName.ToString();
}
#endif
