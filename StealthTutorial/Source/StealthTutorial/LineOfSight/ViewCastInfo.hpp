// Copyright 2021. Elysia-ff

#pragma once

#include <Engine/Classes/Engine/NetSerialization.h>

/**
 * 
 */
struct FViewCastInfo
{
	TWeakObjectPtr<AActor> Actor;
	FVector Point;
	float AngleInDegrees;
	FVector_NetQuantizeNormal Normal;

	FViewCastInfo()
		: Actor(nullptr)
		, Point(FVector::ZeroVector)
		, AngleInDegrees(0.0f)
		, Normal(FVector_NetQuantizeNormal::ZeroVector)
	{
	}

	FViewCastInfo(TWeakObjectPtr<AActor> _Actor, const FVector& _Point, float _AngleInDegrees, const FVector_NetQuantizeNormal& _Normal)
		: Actor(_Actor)
		, Point(_Point)
		, AngleInDegrees(_AngleInDegrees)
		, Normal(_Normal)
	{
	}

	bool operator==(const FViewCastInfo& Other) const
	{
		return Actor == Other.Actor && Normal == Other.Normal;
	}

	bool operator!=(const FViewCastInfo& Other) const
	{
		return !(*this == Other);
	}
};
