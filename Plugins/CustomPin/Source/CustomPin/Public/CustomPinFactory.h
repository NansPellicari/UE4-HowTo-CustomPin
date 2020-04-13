#pragma once

#include "CustomAttribute.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "ListNameFromConfigPin.h"
#include "SlateBasics.h"

class FCustomPinFactory : public FGraphPanelPinFactory
{
    virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override
    {
        const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
        /*
         * Check if pin is struct, and then check if that pin is of struct type we want to customize
         */
        if (InPin->PinType.PinCategory == K2Schema->PC_Struct &&
            InPin->PinType.PinSubCategoryObject == FCustomAttribute::StaticStruct())
        {
            return SNew(SListNameFromConfigPin, InPin);    // and return our customized pin widget ;).
        }
        return nullptr;
    }
};