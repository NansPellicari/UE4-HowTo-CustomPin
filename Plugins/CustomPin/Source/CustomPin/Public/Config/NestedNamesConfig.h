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

#include "NestedNamesConfig.generated.h"

USTRUCT(BlueprintType)
struct FConf
{
	GENERATED_BODY()
public:
	// It's important to mark property as UPROPERTY(), it doesn't need to have any specifiers though.
	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	FName SubName;
};

/**
 * Thanks to: https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1503868-adding-a-custom-ini-file
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Custom Config Nested Names"))
class UNestedNamesConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * This function is allow to convert each setting names to
	 * TSharedPtr which our Pin object can works on.
	 */
	static void GetNames(TMap<TSharedPtr<FName>, TArray<TSharedPtr<FName>>>& ShareableNames)
	{
		static const UNestedNamesConfig* StaticObject = GetDefault<UNestedNamesConfig>();
		TMap<FName, TSharedPtr<FName>> Names;
		for (auto It : StaticObject->ConfigNames)
		{
			if (!Names.Contains(It.Name))
			{
				Names.Add(It.Name, MakeShareable(new FName(It.Name)));
			}
		}
		for (auto It : StaticObject->ConfigNames)
		{
			FName Name = It.Name;
			FName Stack = It.SubName;
			if (!ShareableNames.Find(Names[Name]))
			{
				ShareableNames.Add(Names[Name]);
			}
			ShareableNames[Names[Name]].Add(MakeShareable(new FName(It.SubName)));
		}
	};

	UPROPERTY(config, EditAnywhere)
	TArray<FConf> ConfigNames;
};
