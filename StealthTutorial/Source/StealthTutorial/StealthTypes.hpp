// Copyright 2021. Elysia-ff

#pragma once

#include "CoreMinimal.h"

template <ECollisionChannel Channel>
struct FCollisionChannelWrapper
{
	static const ECollisionChannel Value = Channel;

	constexpr operator ECollisionChannel()
	{
		return Value;
	};
};

static FCollisionChannelWrapper<ECC_GameTraceChannel1> ECC_ObstacleTrace;
