// Copyright 2021. Elysia-ff

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpottableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpottable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STEALTHTUTORIAL_API ISpottable
{
	GENERATED_BODY()

	friend class ULosComponent;

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetSpotPointLocation() const = 0;

	bool IsSpotting() const { return bIsSpotting; };

	virtual void OnBeginSpotted() {}

	virtual void OnEndSpotted() {}

private:
	bool bIsSpotting;
};
