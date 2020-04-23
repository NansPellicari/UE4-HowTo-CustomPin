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

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "ListNameConfig.generated.h"

/**
 * Thanks to: https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1503868-adding-a-custom-ini-file
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Custom Config"))
class UListNameConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * This function is allow to convert each setting name to
	 * TSharedPtr which our Pin object can works on.
	 */
	static void GetNames(TArray<TSharedPtr<FName>>& ShareableNames)
	{
		static const UListNameConfig* StaticObject = GetDefault<UListNameConfig>();
		for (FName Name : StaticObject->ConfigNames)
		{
			ShareableNames.Add(MakeShareable(new FName(Name)));
		}
	};

	UPROPERTY(config, EditAnywhere)
	TArray<FName> ConfigNames;
};
