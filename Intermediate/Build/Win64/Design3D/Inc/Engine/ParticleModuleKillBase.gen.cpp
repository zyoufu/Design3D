// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Engine/Classes/Particles/Kill/ParticleModuleKillBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeParticleModuleKillBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UParticleModuleKillBase_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UParticleModuleKillBase();
	ENGINE_API UClass* Z_Construct_UClass_UParticleModule();
	UPackage* Z_Construct_UPackage__Script_Engine();
// End Cross Module References
	void UParticleModuleKillBase::StaticRegisterNativesUParticleModuleKillBase()
	{
	}
	UClass* Z_Construct_UClass_UParticleModuleKillBase_NoRegister()
	{
		return UParticleModuleKillBase::StaticClass();
	}
	struct Z_Construct_UClass_UParticleModuleKillBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UParticleModuleKillBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UParticleModule,
		(UObject* (*)())Z_Construct_UPackage__Script_Engine,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UParticleModuleKillBase_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "Kill" },
		{ "HideCategories", "Object Object" },
		{ "IncludePath", "Particles/Kill/ParticleModuleKillBase.h" },
		{ "ModuleRelativePath", "Classes/Particles/Kill/ParticleModuleKillBase.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UParticleModuleKillBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UParticleModuleKillBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UParticleModuleKillBase_Statics::ClassParams = {
		&UParticleModuleKillBase::StaticClass,
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
		0x000010A1u,
		METADATA_PARAMS(Z_Construct_UClass_UParticleModuleKillBase_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UParticleModuleKillBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UParticleModuleKillBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UParticleModuleKillBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UParticleModuleKillBase, 1443596912);
	template<> ENGINE_API UClass* StaticClass<UParticleModuleKillBase>()
	{
		return UParticleModuleKillBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UParticleModuleKillBase(Z_Construct_UClass_UParticleModuleKillBase, &UParticleModuleKillBase::StaticClass, TEXT("/Script/Engine"), TEXT("UParticleModuleKillBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UParticleModuleKillBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif