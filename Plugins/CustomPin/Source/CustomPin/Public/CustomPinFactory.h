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

#include "Attribute/MultiNestedNamesAttribute.h"
#include "Attribute/NestedNameAttribute.h"
#include "Attribute/SimpleNameAttribute.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"
#include "Pin/ListNameFromConfigPin.h"
#include "Pin/MultiNestedNamesFromConfigPin.h"
#include "Pin/NestedNamesFromConfigPin.h"
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
			InPin->PinType.PinSubCategoryObject == FSimpleNameAttribute::StaticStruct())
		{
			// and return our customized pin widget ;).
			return SNew(SListNameFromConfigPin, InPin);
		}

		if (InPin->PinType.PinCategory == K2Schema->PC_Struct &&
			InPin->PinType.PinSubCategoryObject == FNestedNameAttribute::StaticStruct())
		{
			// and return our customized pin widget ;).
			return SNew(SNestedNamesFromConfigPin, InPin);
		}
		if (InPin->PinType.PinCategory == K2Schema->PC_Struct &&
			InPin->PinType.PinSubCategoryObject == FMultiNestedNamesAttribute::StaticStruct())
		{
			// and return our customized pin widget ;).
			return SNew(SMultiNestedNamesFromConfigPin, InPin);
		}
		return nullptr;
	}
};