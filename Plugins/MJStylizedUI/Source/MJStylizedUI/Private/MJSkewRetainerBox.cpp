// Copyright 2022 Mark Judkins. All rights reserved.

#include "MJSkewRetainerBox.h"

#define LOCTEXT_NAMESPACE "UMG"

UMJSkewRetainerBox::UMJSkewRetainerBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = false; // No need for this to be a blueprint variable by default, since it's logic is handled here.
}

void UMJSkewRetainerBox::SynchronizeProperties()
{
	UMaterial* pShaderMat = LoadObject<UMaterial>(nullptr, TEXT("/MJStylizedUI/M_SkewEffect"));
	if (pShaderMat)
	{
		m_pDynEffectMat = UMaterialInstanceDynamic::Create(pShaderMat, this);
		SetEffectMaterial(m_pDynEffectMat);

		RefreshEffectMaterialValues();
	}

	Super::SynchronizeProperties();
}

void UMJSkewRetainerBox::RefreshEffectMaterialValues()
{
	if (m_pDynEffectMat)
	{
		m_pDynEffectMat->SetScalarParameterValue(FName("SkewRight"), m_skewRight);
		m_pDynEffectMat->SetScalarParameterValue(FName("SkewLeft"), m_skewLeft);
		m_pDynEffectMat->SetScalarParameterValue(FName("SkewTop"), m_skewTop);
		m_pDynEffectMat->SetScalarParameterValue(FName("SkewBottom"), m_skewBottom);

		m_pDynEffectMat->SetScalarParameterValue(FName("ParabolicCurveTop"), m_parabolicCurveTop);
		m_pDynEffectMat->SetScalarParameterValue(FName("ParabolicCurveBottom"), m_parabolicCurveBottom);
	}
}

#if WITH_EDITOR
bool UMJSkewRetainerBox::CanEditChange(const FProperty* inProperty) const
{
	if (!Super::CanEditChange(inProperty))
	{
		return false;
	}

	if (inProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UMJSkewRetainerBox, Phase)
		|| inProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UMJSkewRetainerBox, PhaseCount))
	{
		return RenderOnPhase && bRetainRender;
	}
	return true;
}

const FText UMJSkewRetainerBox::GetPaletteCategory()
{
	return LOCTEXT("Stylized UI", "Stylized UI");
}
#endif

#undef LOCTEXT_NAMESPACE