#pragma once

#include "CustomAttribute.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CustomPinBPLibrary.generated.h"

UCLASS()
class UCustomPinBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // clang-format off
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Test my custom pin", Keywords = "CustomPin test testing"), Category = "CustomPinTesting")
    static FName TestWithListNameFromConfigPin(FCustomAttribute MyAttribute);
    // clang-format on
};
