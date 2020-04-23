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

#include "Pin/NestedNamesFromConfigPin.h"

#include "Attribute/NestedNameAttribute.h"
#include "Config/NestedNamesConfig.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "SNameComboBox.h"
#include "ScopedTransaction.h"
#include "SlateCore/Public/Widgets/SBoxPanel.h"

#define LOCTEXT_NAMESPACE "NestedNamesFromConfigPin"

void SNestedNamesFromConfigPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SNestedNamesFromConfigPin::GetDefaultValueWidget()
{
	UNestedNamesConfig::GetNames(AttributesList);
	for (auto Cat : AttributesList)
	{
		Categories.Add(Cat.Key);
	}

	TSharedPtr<FName> InitialSelectedName;
	// retrieve previous values selected (or first values from arrays as default)
	TSharedPtr<FName> InitialSelectedCategory = GetSelectedName(true);
	if (InitialSelectedCategory.IsValid())
	{
		UpdateNames(*InitialSelectedCategory.Get());
		InitialSelectedName = GetSelectedName(false);
		if (InitialSelectedName.IsValid())
		{
			SetPropertyWithName(*InitialSelectedCategory.Get(), *InitialSelectedName.Get());
		}
	}

	// clang-format off
	// You can really do what you want here, this is really powerfull!
	return SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(ConfigComboBox, SNameComboBox)
				.ContentPadding(FMargin(6.0f, 2.0f))
				.OptionsSource(&Categories)
				.InitiallySelectedItem(InitialSelectedCategory) 
				.OnComboBoxOpening(this, &SNestedNamesFromConfigPin::OnCategoryComboBoxOpening)
				.OnSelectionChanged(this, &SNestedNamesFromConfigPin::OnCategorySelected)
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				SNew(STextBlock) .Margin(FMargin(6.0f, 2.0f)) .Text( LOCTEXT("SubNamesLabel", "Sub names:") )
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				SAssignNew(NameComboBox, SNameComboBox)
				.ContentPadding(FMargin(6.0f, 2.0f))
				.OptionsSource(&SubNames)
				.InitiallySelectedItem(InitialSelectedName)
				.OnComboBoxOpening(this, &SNestedNamesFromConfigPin::OnNameComboBoxOpening)
				.OnSelectionChanged(this, &SNestedNamesFromConfigPin::OnNameSelected)
			];
	// clang-format on
}
void SNestedNamesFromConfigPin::OnCategorySelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		UpdateNames(*ItemSelected);
		SetPropertyWithName(*ItemSelected, *SubNames[0]);
		NameComboBox->SetSelectedItem(SubNames[0]);
	}
}
void SNestedNamesFromConfigPin::OnNameSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Name selected: %s"), *ItemSelected->ToString());
		SetPropertyWithName(*GetSelectedName(true), *ItemSelected);
	}
}

void SNestedNamesFromConfigPin::OnNameComboBoxOpening()
{
	TSharedPtr<FName> SelectedName = GetSelectedName(false);
	if (SelectedName.IsValid())
	{
		check(NameComboBox.IsValid());
		NameComboBox->SetSelectedItem(SelectedName);
	}
}
void SNestedNamesFromConfigPin::OnCategoryComboBoxOpening()
{
	TSharedPtr<FName> SelectedName = GetSelectedName(true);
	if (SelectedName.IsValid())
	{
		check(ConfigComboBox.IsValid());
		ConfigComboBox->SetSelectedItem(SelectedName);
	}
}

void SNestedNamesFromConfigPin::SetPropertyWithName(const FName& Category, const FName& Name)
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FNestedNameAttribute::StaticStruct());

	FString PinString = FString::Format(TEXT("(MyName=\"{0}\",MySubName=\"{1}\")"), {Category.ToString(), Name.ToString()});

	FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();

	if (CurrentDefaultValue != PinString)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeNestedNamesFromConfigPinValue", "Change Nested Names From Config Value"));
		GraphPinObj->Modify();

		UE_LOG(LogTemp, Warning, TEXT("Verify values old: \"%s\" chosen: \"%s\""), *CurrentDefaultValue, *PinString);

		if (PinString != GraphPinObj->GetDefaultAsString())
		{
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, PinString);
		}
	}
}

void SNestedNamesFromConfigPin::UpdateNames(const FName& Name)
{
	SubNames.Empty();
	for (auto Cat : AttributesList)
	{
		if (Name.ToString() != Cat.Key->ToString()) continue;
		for (auto SubName : Cat.Value)
		{
			SubNames.Add(SubName);
		}
		break;
	}
}

TSharedPtr<FName> SNestedNamesFromConfigPin::GetSelectedName(const bool bIsCategory) const
{
	TArray<TSharedPtr<FName>> Names = bIsCategory ? Categories : SubNames;
	int32 NameCount = Names.Num();
	if (NameCount <= 0)
	{
		return NULL;
	}

	FName Name;
	GetPropertyAsName(bIsCategory, Name);

	for (int32 NameIndex = 0; NameIndex < NameCount; ++NameIndex)
	{
		if (Name == *Names[NameIndex].Get())
		{
			return Names[NameIndex];
		}
	}
	// no value has been found, return a default value
	return Names[0];
}

void SNestedNamesFromConfigPin::GetPropertyAsName(const bool bIsCategory, FName& OutName) const
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FNestedNameAttribute::StaticStruct());

	FString PinString = GraphPinObj->GetDefaultAsString();

	if (PinString.StartsWith(TEXT("(")) && PinString.EndsWith(TEXT(")")))
	{
		PinString = PinString.LeftChop(1);
		PinString = PinString.RightChop(1);
		FString CategoryString;
		FString NameString;
		PinString.Split(TEXT(","), &CategoryString, &NameString);
		FString ResultString = bIsCategory ? CategoryString : NameString;
		ResultString.TrimStartAndEnd().Split(TEXT("="), NULL, &PinString);
		PinString = PinString.TrimQuotes();
	}

	if (!PinString.IsEmpty())
	{
		OutName = *PinString;
	}
}
#undef LOCTEXT_NAMESPACE
