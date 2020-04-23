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

FString UCustomPinBPLibrary::TestWithNestedNamesFromConfigPin(FMultiNestedNamesAttribute MyAttribute)
{
	// Do what you want here
	FString Output = MyAttribute.MyName.ToString();
	UE_LOG(LogTemp, Warning, TEXT("You chosen name: %s"), *MyAttribute.MyName.ToString());
	for (FName Name : MyAttribute.MySubNames)
	{
		Output.Append(TEXT(",")).Append(Name.ToString());
		UE_LOG(LogTemp, Warning, TEXT("You chosen subname: %s"), *Name.ToString());
	}
	return Output;
}