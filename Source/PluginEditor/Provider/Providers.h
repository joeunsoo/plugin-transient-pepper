#pragma once

#include "EditorProvider.h"
#include "LicenseProvider.h"
#include "ProcessorProvider.h"
#include "ScaleController.h"
#include "ScaleProvider.h"

struct Providers {
  EditorProvider &editor;
  ScaleProvider &scale;
  ScaleController &scaleController;
  ProcessorProvider &processor;
  LicenseProvider &license;
};
