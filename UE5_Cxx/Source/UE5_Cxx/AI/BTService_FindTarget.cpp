// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindTarget.h"
#include "AI/R1AIController.h"
#include "Character/R1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	NodeName = TEXT("FindTEargetService");
	Interval = 0.5f;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto LocalPawn =  OwnerComp.GetAIOwner()->GetPawn();
	if (LocalPawn == nullptr)
		return;

	auto World = LocalPawn->GetWorld();
	if (World == nullptr)
		return;

	FVector Location = LocalPawn->GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, LocalPawn);

	const auto bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			auto R1Character = Cast<AR1Character>(OverlapResult.GetActor());
			if (R1Character)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, R1Character);
				DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Green, false, 0.2f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, nullptr);
	DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Red, false, 0.2f);
}
