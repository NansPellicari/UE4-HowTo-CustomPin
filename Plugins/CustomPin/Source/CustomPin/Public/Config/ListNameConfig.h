
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