#include "CustomPinBPLibrary.h"

#include "CustomPin.h"

FName UCustomPinBPLibrary::TestWithListNameFromConfigPin(FCustomAttribute MyAttribute)
{
    // Do what you want here
    UE_LOG(LogTemp, Warning, TEXT("You chosen attribute: %s"), *MyAttribute.MyName.ToString());
    return MyAttribute.MyName;
}