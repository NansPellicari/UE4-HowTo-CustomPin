#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"
#include "SlateBasics.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"

class SNameComboBox;

// You can also check files in the engine to see a lot of examples here:
// [UE4 directory]\Engine\Source\Editor\GraphEditor\Private\KismetPins\SGraphPinCollisionProfile.h

class SNestedNamesFromConfigPin : public SGraphPin
{
public:
    SLATE_BEGIN_ARGS(SNestedNamesFromConfigPin) {}
    SLATE_END_ARGS()
public:
    void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
    // this override is used to display slate widget used for customization.
    virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
    void OnCategorySelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo);
    void OnNameSelected(TSharedPtr<FName> ItemSelected, ESelectInfo::Type SelectInfo);
    void OnCategoryComboBoxOpening();
    void OnNameComboBoxOpening();
    void UpdateNames(const FName& Name);

    TSharedPtr<FName> GetSelectedName(const bool bIsCategory) const;

    void SetPropertyWithName(const FName& Category, const FName& Name);
    void GetPropertyAsName(const bool bIsCategory, FName& OutName) const;

private:
    TMap<TSharedPtr<FName>, TArray<TSharedPtr<FName>>> AttributesList;
    TArray<TSharedPtr<FName>> Categories;
    TArray<TSharedPtr<FName>> SubNames;
    TSharedPtr<SNameComboBox> ConfigComboBox;
    TSharedPtr<SNameComboBox> NameComboBox;
};