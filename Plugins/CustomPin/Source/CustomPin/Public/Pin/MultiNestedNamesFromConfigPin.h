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
#include "SGraphPin.h"
#include "SlateBasics.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"

class SNameComboBox;
class SVerticalBox;
class SCheckBox;

// You can also check files in the engine to see a lot of examples here:
// [UE4 directory]\Engine\Source\Editor\GraphEditor\Private\KismetPins\SGraphPinCollisionProfile.h

class SMultiNestedNamesFromConfigPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SMultiNestedNamesFromConfigPin) {}
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	// this override is used to display slate widget used for customization.
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	void OnCategorySelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo);
	void OnCategoryComboBoxOpening();
	void OnCheckboxChanged(ECheckBoxState State);
	void UpdateNames(const FName& Name);

	TSharedPtr<FName> GetSelectedCategory() const;

	void SetPropertyWithName(const FName& Category);
	void GetPropertyAsCategory(FName& OutName) const;
	void RetrievePropertyAsNames();
	void BuildCheckbox();

private:
	TMap<TSharedPtr<FName>, TArray<TSharedPtr<FName>>> AttributesList;
	TArray<TSharedPtr<FName>> Categories;
	TArray<TSharedPtr<FName>> SubNames;
	TArray<TPair<TSharedPtr<SCheckBox>, TSharedPtr<STextBlock>>> Checkboxes;
	TArray<TSharedPtr<FName>> ChoosenNames;
	TSharedPtr<SVerticalBox> ParentWidget;
	TSharedPtr<SNameComboBox> ConfigComboBox;
	TSharedPtr<SVerticalBox> CheckboxWidget;
};
