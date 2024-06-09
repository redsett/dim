// Copyright 2022 Mark Judkins. All rights reserved.

#include "DeformerRetainerBox.h"
#include "SDeformerRetainerWidget.h"

#define LOCTEXT_NAMESPACE "UMG"

UDeformerRetainerBox::UDeformerRetainerBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = false; // No need for this to be a blueprint variable by default, since it's logic is handled here.
}

void UDeformerRetainerBox::SynchronizeProperties()
{
	TCHAR* texturePath = TEXT("/UIDeformer/M_DeformerEffect_AlphaComposite");
	if (m_blendMode == EBlendModeType::Translut)
	{
		texturePath = TEXT("/UIDeformer/M_DeformerEffect_Translucent");
	}

	UMaterial* pShaderMat = LoadObject<UMaterial>(nullptr, texturePath);
	if (pShaderMat)
	{
		m_pDynEffectMat = UMaterialInstanceDynamic::Create(pShaderMat, this);
		SetEffectMaterial(m_pDynEffectMat);

		RefreshEffectMaterialValues();
	}

	// Set the padding on the widget.
	if (MyRetainerWidget)
	{
		const TSharedPtr<SDeformerRetainerWidget> deformerRetainerWidget = StaticCastSharedPtr<SDeformerRetainerWidget>(MyRetainerWidget);
		if (deformerRetainerWidget)
		{
			deformerRetainerWidget->m_padding = m_padding;
		}
	}

	Super::SynchronizeProperties();
}

void UDeformerRetainerBox::RefreshEffectMaterialValues()
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

TSharedRef<SWidget> UDeformerRetainerBox::RebuildWidget()
{
	MyRetainerWidget =
		SNew(SDeformerRetainerWidget)
		.RenderOnInvalidation(RenderOnInvalidation)
		.RenderOnPhase(RenderOnPhase)
		.Phase(Phase)
		.PhaseCount(PhaseCount)
#if STATS
		.StatId(FName(*FString::Printf(TEXT("%s [%s]"), *GetFName().ToString(), *GetClass()->GetName())))
#endif//STATS
		;

	if (GetChildrenCount() > 0)
	{
		MyRetainerWidget->SetContent(GetContentSlot()->Content ? GetContentSlot()->Content->TakeWidget() : SNullWidget::NullWidget);
	}

	return MyRetainerWidget.ToSharedRef();
}

#if WITH_EDITOR
bool UDeformerRetainerBox::CanEditChange(const FProperty* inProperty) const
{
	if (!Super::CanEditChange(inProperty))
	{
		return false;
	}

	if (inProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDeformerRetainerBox, Phase)
		|| inProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDeformerRetainerBox, PhaseCount))
	{
		return RenderOnPhase && bRetainRender;
	}
	return true;
}
#endif

#undef LOCTEXT_NAMESPACE