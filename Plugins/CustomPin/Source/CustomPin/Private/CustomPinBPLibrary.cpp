#include "CustomPinBPLibrary.h"

#include "CustomPin.h"

FName UCustomPinBPLibrary::TestWithListNameFromConfigPin(FSimpleNameAttribute MyAttribute)
{
    // Do what you want here
    UE_LOG(LogTemp, Warning, TEXT("You chosen attribute: %s"), *MyAttribute.MyName.ToString());
    return MyAttribute.MyName;
}

FString UCustomPinBPLibrary::TestWithNestedNameFromConfigPin(FNestedNameAttribute MyAttribute)
{
    // Do what you want here
    FString Output = MyAttribute.MyName.ToString();
    UE_LOG(LogTemp, Warning, TEXT("You chosen name: %s"), *MyAttribute.MyName.ToString());
    UE_LOG(LogTemp, Warning, TEXT("You chosen subname: %s"), *MyAttribute.MySubName.ToString());
    Output.Append(TEXT(",")).Append(MyAttribute.MySubName.ToString());
    return Output;
}