// Copyright 2022 Mark Judkins. All rights reserved.

#include "SDeformerRetainerWidget.h"

FVector2D SDeformerRetainerWidget::ComputeDesiredSize(float scale) const
{
	return SRetainerWidget::ComputeDesiredSize(scale) + FVector2D(m_padding, m_padding);
}