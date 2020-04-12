#include "CustomPin.h"

#include "CustomPinFactory.h"

#define LOCTEXT_NAMESPACE "FCustomPinModule"

void FCustomPinModule::StartupModule()
{
    // create your factory and shared pointer to it.
    TSharedPtr<FCustomPinFactory> Factory = MakeShareable(new FCustomPinFactory());
    // and now register it.
    FEdGraphUtilities::RegisterVisualPinFactory(Factory);
}

void FCustomPinModule::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomPinModule, CustomPin)