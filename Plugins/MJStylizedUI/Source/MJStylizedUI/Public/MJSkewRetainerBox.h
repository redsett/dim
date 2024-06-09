// Copyright 2022 Mark Judkins. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/RetainerBox.h"
#include "MJSkewRetainerBox.generated.h"

/** RetainerBox with a set instance material with skewing properties. */
UCLASS()
class MJSTYLIZEDUI_API UMJSkewRetainerBox : public URetainerBox
{
	GENERATED_BODY()
	
public:
	UMJSkewRetainerBox(const FObjectInitializer& ObjectInitializer);

	virtual void SynchronizeProperties() override;

	/*
	 *	Skew everything in this retainer on the right side.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StylizedUI|Skew", DisplayName = "Skew Right")
	float m_skewRight = 0.0f;

	/*
	 *	Skew everything in this retainer on the left side.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StylizedUI|Skew", DisplayName = "Skew Left")
	float m_skewLeft = 0.0f;

	/*
	 *	Skew everything in this retainer on the top.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StylizedUI|Skew", DisplayName = "Skew Top")
	float m_skewTop = 0.0f;

	/*
	 *	Skew everything in this retainer on the bottom.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StylizedUI|Skew", DisplayName = "Skew Bottom")
	float m_skewBottom = 0.0f;

	/*
	 *	Curve the top of the render.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StylizedUI|Parabolic", DisplayName = "Parabolic Curve Top")
	float m_parabolicCurveTop = 0.0f;

	/*
	 *	Curve the bottom of the render.
	 *	NOTE: This only shows up in-game. Not in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StylizedUI|Parabolic", DisplayName = "Parabolic Curve Bottom")
	float m_parabolicCurveBottom = 0.0f;

	/* Set the parameters on the effect material. */
	UFUNCTION(BlueprintCallable, Category = "StylizedUI")
	void RefreshEffectMaterialValues();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* inProperty) const override;
#endif

private:
	UPROPERTY()
	UMaterialInstanceDynamic* m_pDynEffectMat = nullptr;
};
