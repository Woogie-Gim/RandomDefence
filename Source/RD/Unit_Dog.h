

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "Unit_Dog.generated.h"

/**
 * 
 */
UCLASS()
class RD_API AUnit_Dog : public ABaseUnit
{
	GENERATED_BODY()
	
protected:
	virtual void Attack() override;
};
