// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintGraph/Classes/K2Node_AddPinInterface.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeK2Node_AddPinInterface() {}
// Cross Module References
	BLUEPRINTGRAPH_API UClass* Z_Construct_UClass_UK2Node_AddPinInterface_NoRegister();
	BLUEPRINTGRAPH_API UClass* Z_Construct_UClass_UK2Node_AddPinInterface();
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	UPackage* Z_Construct_UPackage__Script_BlueprintGraph();
// End Cross Module References
	void UK2Node_AddPinInterface::StaticRegisterNativesUK2Node_AddPinInterface()
	{
	}
	UClass* Z_Construct_UClass_UK2Node_AddPinInterface_NoRegister()
	{
		return UK2Node_AddPinInterface::StaticClass();
	}
	struct Z_Construct_UClass_UK2Node_AddPinInterface_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UK2Node_AddPinInterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_BlueprintGraph,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UK2Node_AddPinInterface_Statics::Class_MetaDataParams[] = {
		{ "CannotImplementInterfaceInBlueprint", "" },
		{ "ModuleRelativePath", "Classes/K2Node_AddPinInterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UK2Node_AddPinInterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IK2Node_AddPinInterface>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UK2Node_AddPinInterface_Statics::ClassParams = {
		&UK2Node_AddPinInterface::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001040A1u,
		METADATA_PARAMS(Z_Construct_UClass_UK2Node_AddPinInterface_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UK2Node_AddPinInterface_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UK2Node_AddPinInterface()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UK2Node_AddPinInterface_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UK2Node_AddPinInterface, 253545970);
	template<> BLUEPRINTGRAPH_API UClass* StaticClass<UK2Node_AddPinInterface>()
	{
		return UK2Node_AddPinInterface::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UK2Node_AddPinInterface(Z_Construct_UClass_UK2Node_AddPinInterface, &UK2Node_AddPinInterface::StaticClass, TEXT("/Script/BlueprintGraph"), TEXT("UK2Node_AddPinInterface"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UK2Node_AddPinInterface);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
