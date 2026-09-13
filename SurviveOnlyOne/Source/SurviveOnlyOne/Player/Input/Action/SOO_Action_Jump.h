#pragma once

#include "CoreMinimal.h"
#include "SOO_PlayerActionBase.h"
#include "SOO_Action_Jump.generated.h"

UCLASS()
class USOO_Action_Jump : public USOO_PlayerActionBase
{
	GENERATED_BODY()

public:
	virtual bool TryActivate_Implementation(APawn* InstigatorPawn) override;
	virtual void Cancel_Implementation(APawn* InstigatorPawn) override;
};
