// Copyright 2020-present Nans Pellicari (nans.pellicari@gmail.com).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
