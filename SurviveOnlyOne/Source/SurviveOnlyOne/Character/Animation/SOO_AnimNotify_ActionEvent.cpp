// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Animation/SOO_AnimNotify_ActionEvent.h"
#include "Player/Input/SOO_ActionComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void USOO_AnimNotify_ActionEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		if (USOO_ActionComponent* ActionComponent = Character->FindComponentByClass<USOO_ActionComponent>())
		{
			ActionComponent->NotifyActionEvent(ActionTag, EventName);
		}
	}
}

#if WITH_EDITOR
FString USOO_AnimNotify_ActionEvent::GetNotifyName_Implementation() const
{
	return EventName.IsNone() ? Super::GetNotifyName_Implementation() : EventName.ToString();
}
#endif
