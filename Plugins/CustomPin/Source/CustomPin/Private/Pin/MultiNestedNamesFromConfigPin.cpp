#include "Pin/MultiNestedNamesFromConfigPin.h"

#include "Attribute/MultiNestedNamesAttribute.h"
#include "Config/NestedNamesConfig.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "SNameComboBox.h"
#include "ScopedTransaction.h"
#include "Slate/Public/Widgets/Text/STextBlock.h"
#include "SlateCore/Public/Widgets/SBoxPanel.h"

#define LOCTEXT_NAMESPACE "NestedNamesFromConfigPin"

void SMultiNestedNamesFromConfigPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
    SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SMultiNestedNamesFromConfigPin::GetDefaultValueWidget()
{
    UNestedNamesConfig::GetNames(AttributesList);
    for (auto Cat : AttributesList)
    {
        Categories.Add(Cat.Key);
    }

    TSharedPtr<FName> InitialSelectedName;
    // retrieve the previous value selected (or the first value as default)
    TSharedPtr<FName> InitialSelectedCategory = GetSelectedCategory();
    if (InitialSelectedCategory.IsValid())
    {
        UpdateNames(*InitialSelectedCategory.Get());
        RetrievePropertyAsNames();
        SetPropertyWithName(*InitialSelectedCategory.Get());
    }

    // clang-format off
    SAssignNew(ParentWidget, SVerticalBox)
    
        // Top-Aligned Fixed Size
        +SVerticalBox::Slot()
        .AutoHeight()
        [
            SAssignNew(ConfigComboBox, SNameComboBox)
            .ContentPadding(FMargin(6.0f, 2.0f))
            .OptionsSource(&Categories)
            .InitiallySelectedItem(InitialSelectedCategory)
            .OnComboBoxOpening(this, &SMultiNestedNamesFromConfigPin::OnCategoryComboBoxOpening)
            .OnSelectionChanged(this, &SMultiNestedNamesFromConfigPin::OnCategorySelected)
        ]
        +SVerticalBox::Slot().AutoHeight()
        [
            SNew(STextBlock) .Margin(FMargin(6.0f, 2.0f)) .Text( LOCTEXT("SubNamesLabel", "Sub names:") )
        ]
        +SVerticalBox::Slot().AutoHeight()
        [
            SAssignNew(CheckboxWidget, SVerticalBox)
        ]
        ;
    BuildCheckbox();
    // clang-format on
    return ParentWidget.ToSharedRef();
}
void SMultiNestedNamesFromConfigPin::BuildCheckbox()
{
    CheckboxWidget->ClearChildren();
    Checkboxes.Empty();
    if (SubNames.Num() <= 0) return;
    for (auto Name : SubNames)
    {
        FString StrName = Name->ToString();
        bool bIsChecked = false;
        for (auto ChoosenName : ChoosenNames)
        {
            if (StrName != ChoosenName->ToString()) continue;
            bIsChecked = true;
        }

        UE_LOG(LogTemp, Warning, TEXT("Is in? %i"), bIsChecked);
        TPair<TSharedPtr<SCheckBox>, TSharedPtr<STextBlock>> Checkbox;
        // clang-format off
        CheckboxWidget->AddSlot()
        .AutoHeight()
        [
            SAssignNew(Checkbox.Key, SCheckBox)
            .IsChecked(bIsChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
            .OnCheckStateChanged(this, &SMultiNestedNamesFromConfigPin::OnCheckboxChanged)
            [
                SAssignNew(Checkbox.Value, STextBlock).Text(FText::FromName(*Name))
            ]
        ];
        // clang-format on
        Checkboxes.Add(Checkbox);
    }
}

void SMultiNestedNamesFromConfigPin::OnCheckboxChanged(ECheckBoxState State)
{
    ChoosenNames.Empty();
    UE_LOG(LogTemp, Display, TEXT("Refresh---"));
    for (auto Pair : Checkboxes)
    {
        TSharedPtr<SCheckBox> Checkbox = Pair.Key;
        TSharedPtr<STextBlock> Text = Pair.Value;
        if (Checkbox == nullptr || !Checkbox->IsChecked()) continue;

        FString StrName = Text->GetText().ToString();
        for (auto SubName : SubNames)
        {
            if (StrName != SubName->ToString()) continue;

            ChoosenNames.Add(SubName);
            UE_LOG(LogTemp, Warning, TEXT("Check %i %s"), Checkbox->IsChecked(), *Text->GetText().ToString());
            break;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Cat selected: %s"), *ConfigComboBox->GetSelectedItem()->ToString());
    SetPropertyWithName(*ConfigComboBox->GetSelectedItem().Get());
}
void SMultiNestedNamesFromConfigPin::OnCategorySelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo)
{
    if (ItemSelected.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: check if not the same as previous value"), ANSI_TO_TCHAR(__FUNCTION__));
        UpdateNames(*ItemSelected);
        RetrievePropertyAsNames();
        BuildCheckbox();
        SetPropertyWithName(*ItemSelected);
    }
}

void SMultiNestedNamesFromConfigPin::OnCategoryComboBoxOpening()
{
    TSharedPtr<FName> SelectedName = GetSelectedCategory();
    if (SelectedName.IsValid())
    {
        check(ConfigComboBox.IsValid());
        UpdateNames(*SelectedName);
        RetrievePropertyAsNames();
        ConfigComboBox->SetSelectedItem(SelectedName);
    }
}

void SMultiNestedNamesFromConfigPin::SetPropertyWithName(const FName& Category)
{
    check(GraphPinObj);
    check(GraphPinObj->PinType.PinSubCategoryObject == FMultiNestedNamesAttribute::StaticStruct());
    FString NamesValue;
    for (auto Name : ChoosenNames)
    {
        NamesValue.Append("\"").Append(Name->ToString()).Append("\",");
    }
    // To remove the last comma
    NamesValue = NamesValue.LeftChop(1);
    FString PinString = FString::Format(TEXT("(MyName=\"{0}\",MySubNames=({1}))"), {Category.ToString(), NamesValue});
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

void SMultiNestedNamesFromConfigPin::UpdateNames(const FName& Name)
{
    SubNames.Empty();
    for (auto Cat : AttributesList)
    {
        if (Name.ToString() != Cat.Key->ToString()) continue;
        for (auto SubName : Cat.Value)
        {
            SubNames.Add(SubName);
            UE_LOG(LogTemp, Warning, TEXT("Subnames choices: %s"), *SubName->ToString());
        }
        break;
    }

    UE_LOG(LogTemp, Warning, TEXT("Your name choice: %s"), *Name.ToString());
}

TSharedPtr<FName> SMultiNestedNamesFromConfigPin::GetSelectedCategory() const
{
    TArray<TSharedPtr<FName>> Names = Categories;
    int32 NameCount = Names.Num();
    if (NameCount <= 0)
    {
        return NULL;
    }

    FName Name;
    GetPropertyAsCategory(Name);

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

void SMultiNestedNamesFromConfigPin::GetPropertyAsCategory(FName& OutName) const
{
    check(GraphPinObj);
    check(GraphPinObj->PinType.PinSubCategoryObject == FMultiNestedNamesAttribute::StaticStruct());

    FString PinString = GraphPinObj->GetDefaultAsString();

    if (PinString.StartsWith(TEXT("(")) && PinString.EndsWith(TEXT(")")))
    {
        PinString = PinString.LeftChop(1);
        PinString = PinString.RightChop(1);
        FString ResultString;
        PinString.Split(TEXT(","), &ResultString, NULL);
        ResultString.TrimStartAndEnd().Split(TEXT("="), NULL, &PinString);
        PinString = PinString.TrimQuotes();
    }

    if (!PinString.IsEmpty())
    {
        OutName = *PinString;
    }
}

void SMultiNestedNamesFromConfigPin::RetrievePropertyAsNames()
{
    check(GraphPinObj);
    check(GraphPinObj->PinType.PinSubCategoryObject == FMultiNestedNamesAttribute::StaticStruct());

    UE_LOG(LogTemp, Display, TEXT("----- %s"), ANSI_TO_TCHAR(__FUNCTION__));
    FString PinString = GraphPinObj->GetDefaultAsString();
    UE_LOG(LogTemp, Display, TEXT("> Value %s"), *PinString);

    if (PinString.StartsWith(TEXT("(")) && PinString.EndsWith(TEXT(")")))
    {
        PinString = PinString.LeftChop(1);
        PinString = PinString.RightChop(1);
        FString ResultString;
        PinString.Split(TEXT("\","), NULL, &ResultString);
        UE_LOG(LogTemp, Warning, TEXT("Value: %s"), *ResultString);
        ResultString.TrimStartAndEnd().Split(TEXT("="), NULL, &PinString);
        PinString = PinString.TrimQuotes();
        UE_LOG(LogTemp, Warning, TEXT("Value2: %s"), *PinString);
        PinString = PinString.LeftChop(1);
        PinString = PinString.RightChop(1);
        while (PinString.Split(TEXT(","), &ResultString, &PinString))
        {
            ChoosenNames.Add(MakeShareable<FName>(new FName(*ResultString.TrimQuotes())));
        }

        ChoosenNames.Add(MakeShareable<FName>(new FName(*PinString.TrimQuotes())));
        UE_LOG(LogTemp, Warning, TEXT("length %d"), ChoosenNames.Num());
    }
}

#undef LOCTEXT_NAMESPACE
