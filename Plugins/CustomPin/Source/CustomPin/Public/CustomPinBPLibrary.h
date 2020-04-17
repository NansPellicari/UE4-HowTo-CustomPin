#pragma once

#include "Attribute/NestedNameAttribute.h"
#include "Attribute/SimpleNameAttribute.h"
#include "Attribute/MultiNestedNamesAttribute.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CustomPinBPLibrary.generated.h"

UCLASS()
class UCustomPinBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // clang-format off
    /**
     * Just a function to test how our pin is working.
     * As you see our FSimpleNameAttribute struct is used as
     * param of the function to make it works.
     */
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Test my custom pin", Keywords = "CustomPin test testing"), Category = "CustomPinTesting")
    static FName TestWithListNameFromConfigPin(FSimpleNameAttribute MyAttribute);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Test my custom pin with nested value", Keywords = "CustomPin test testing"), Category = "CustomPinTesting")
    static FString TestWithNestedNameFromConfigPin(FNestedNameAttribute MyAttribute);
    
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Test my custom pin with multi nested value", Keywords = "CustomPin test testing"), Category = "CustomPinTesting")
    static FString TestWithNestedNamesFromConfigPin(FMultiNestedNamesAttribute MyAttribute);
    // clang-format on
};
