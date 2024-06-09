// Copyright 2022 Mark Judkins. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Components/RetainerBox.h>
#include "DeformerRetainerBox.generated.h"

UENUM(BlueprintType)
enum class EBlendModeType : uint8
{
	AlphaComp   UMETA(DisplayName = "Alpha Composite"),
	Translut    UMETA(DisplayName = "Translucent"),
};

/**
 * RetainerBox with a set instance material and deforming properties.
 * From UI Deformer Plugin
 *
 * * Single Child
 * * Caching / Performance
 */
UCLASS()
class UIDEFORMER_API UDeformerRetainerBox : public URetainerBox
{
	GENERATED_BODY()
	
public:
	UDeformerRetainerBox(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	/**
	 *	Switches to a material that uses either Alpha Composite or Translucent as its Blend Mode.
	 *	
	 *	Both support alpha but Alpha Composite doesn't work if the texture touches the sides of the bounds.
	 *	The downside to Translucentis that it will leave a black border around the alpha.
	 *	
	 *	General rule is to use Alpha Composite unless it doesn't work for this widget.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Deformer", DisplayName = "Blend Mode")
	EBlendModeType m_blendMode = EBlendModeType::AlphaComp;

	/**
	 *	Adds padding to this widet.
	 *	Useful if the child widget is getting culled and causing artifacts.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Deformer", DisplayName = "Padding")
	int32 m_padding = 15;

	/*
	 *	Skew everything in this retainer on the right side.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Deformer|Skew", DisplayName = "Skew Right")
	float m_skewRight = 0.0f;

	/*
	 *	Skew everything in this retainer on the left side.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Deformer|Skew", DisplayName = "Skew Left")
	float m_skewLeft = 0.0f;

	/*
	 *	Skew everything in this retainer on the top.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Deformer|Skew", DisplayName = "Skew Top")
	float m_skewTop = 0.0f;

	/*
	 *	Skew everything in this retainer on the bottom.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Deformer|Skew", DisplayName = "Skew Bottom")
	float m_skewBottom = 0.0f;

	/*
	 *	Curve everything in this retainer on the top.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Deformer|Parabolic", DisplayName = "Parabolic Curve Top")
	float m_parabolicCurveTop = 0.0f;

	/*
	 *	Curve everything in this retainer on the bottom.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Deformer|Parabolic", DisplayName = "Parabolic Curve Bottom")
	float m_parabolicCurveBottom = 0.0f;

	/* Set the parameters on the effect material. */
	UFUNCTION(BlueprintCallable, Category = "UI Deformer")
	void RefreshEffectMaterialValues();

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* inProperty) const override;
#endif

private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> m_pDynEffectMat;
};
