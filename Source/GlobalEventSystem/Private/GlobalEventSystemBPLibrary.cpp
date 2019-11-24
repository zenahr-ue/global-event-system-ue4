// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GlobalEventSystemBPLibrary.h"
#include "GlobalEventSystem.h"

UGlobalEventSystemBPLibrary::UGlobalEventSystemBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UGlobalEventSystemBPLibrary::GESUnbindEvent(UObject* WorldContextObject, const FString& Domain /*= TEXT("global.default")*/, const FString& Event /*= TEXT("")*/, const FString& ReceivingFunction /*= TEXT("")*/)
{
	FGESEventListener Listener;
	Listener.Receiver = WorldContextObject;
	Listener.FunctionName = ReceivingFunction;

	FGESHandler::DefaultHandler()->RemoveListener(Domain, Event, Listener);
}

void UGlobalEventSystemBPLibrary::GESBindEvent(UObject* WorldContextObject, const FString& Domain /*= TEXT("global.default")*/, const FString& Event /*= TEXT("")*/, const FString& ReceivingFunction /*= TEXT("")*/)
{
	FGESEventListener Listener;
	Listener.Receiver = WorldContextObject;
	Listener.FunctionName = ReceivingFunction;
	Listener.LinkFunction();	//this makes the function valid by finding a reference to it

	FGESHandler::DefaultHandler()->AddListener(Domain, Event, Listener);
}

void UGlobalEventSystemBPLibrary::HandleEmit(const FGESEmitData& EmitData)
{
	FGESHandler::DefaultHandler()->EmitEvent(EmitData);
}

void UGlobalEventSystemBPLibrary::GESEmitEventOneParam(bool bPinned /*= false*/, const FString& Domain /*= TEXT("global.default")*/, const FString& Event /*= TEXT("")*/, UProperty* ParameterData /*= nullptr*/)
{
	//this never gets called due to custom thunk
}

void UGlobalEventSystemBPLibrary::GESEmitEvent(bool bPinned /*= false*/, const FString& Domain /*= TEXT("global.default")*/, const FString& EventName /*= TEXT("")*/)
{
	FGESEmitData EmitData;
	EmitData.bPinned = bPinned;
	EmitData.Domain = Domain;
	EmitData.Event = EventName;
	FGESHandler::DefaultHandler()->EmitEvent(EmitData);
}

void UGlobalEventSystemBPLibrary::GESUnpinEvent(UObject* WorldContextObject, const FString& Domain /*= TEXT("global.default")*/, const FString& Event /*= TEXT("")*/)
{
	FGESHandler::DefaultHandler()->UnpinEvent(Domain, Event);
}
