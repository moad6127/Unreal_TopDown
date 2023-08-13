#pragma once


UENUM(BlueprintType)
enum class EDeathPose :uint8
{
	EDP_Alive UMETA(DisplayName = "Alive"),
	EDP_Death UMETA(DisplayName = "Death")
};