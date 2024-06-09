// Copyright 2022 Mark Judkins. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include "Slate/SRetainerWidget.h"

class UIDEFORMER_API SDeformerRetainerWidget : public SRetainerWidget
{	
public:
	int32 m_padding = 0;

protected:
	virtual FVector2D ComputeDesiredSize(float scale) const override;
};
