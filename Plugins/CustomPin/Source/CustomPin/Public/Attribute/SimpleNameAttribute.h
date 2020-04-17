#pragma once

#include "CoreMinimal.h"

#include "SimpleNameAttribute.generated.h"

USTRUCT(BlueprintType)
struct FSimpleNameAttribute
{
    GENERATED_BODY()
public:
    // It's important to mark property as UPROPERTY(), it doesn't need to have any specifiers though.
    UPROPERTY(BlueprintReadOnly)
    FName MyName;
};