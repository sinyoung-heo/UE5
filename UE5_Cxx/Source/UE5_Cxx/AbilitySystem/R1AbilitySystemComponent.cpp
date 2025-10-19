// Fill out your copyright notice in the Description page of Project Settings.


#include "R1AbilitySystemComponent.h"

void UR1AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities)
{
	for (auto& AbilityClass : StartupAbilities)
	{
		auto AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		auto SpecHandle = GiveAbility(AbilitySpec);

		auto& a = ActivatableAbilities;

		//TryActivateAbility(SpecHandle);
		//GiveAbilityAndActivateOnce(AbilitySpec);
		
		SpecHandles.Add(SpecHandle);
	}
}

void UR1AbilitySystemComponent::ActivateAbility(FGameplayTag AbilityTag)
{
	for (auto& SpecHandle : SpecHandles)
	{
		//TODO
		TryActivateAbility(SpecHandle);
	}
}

