#pragma once

#include "CoreMinimal.h"

#include "MultiNestedNamesAttribute.generated.h"

USTRUCT(BlueprintType)
struct FMultiNestedNamesAttribute
{
    GENERATED_BODY()
public:
    // It's important to mark property as UPROPERTY(), it doesn't need to have any specifiers though.
    UPROPERTY(BlueprintReadOnly)
    FName MyName;

    UPROPERTY(BlueprintReadOnly)
    TArray<FName> MySubNames;
};