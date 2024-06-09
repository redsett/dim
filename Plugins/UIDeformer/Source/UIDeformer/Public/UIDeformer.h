// Copyright 2022 Mark Judkins. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FUIDeformerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
