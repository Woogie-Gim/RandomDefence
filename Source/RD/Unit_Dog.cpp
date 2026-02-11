


#include "Unit_Dog.h"

void AUnit_Dog::Attack()
{
	if (CurrentTarget && !CurrentTarget->bIsDead)
	{
		if (GetDistanceTo(CurrentTarget) <= AttackRange)
		{
			if (AttackMontage)
			{
				PlayAnimMontage(AttackMontage);
			}
			CurrentTarget->OnTakeDamage(AttackDamage);
		}
	}
}
