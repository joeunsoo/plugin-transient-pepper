#pragma once

#include "ScaleProvider.h"
#include "ScaleController.h"
#include "EditorProvider.h"
#include "ProcessorProvider.h"
#include "LicenseProvider.h"

struct Providers {
  EditorProvider&    editor;
  ScaleProvider&     scale;
  ScaleController&     scaleController;
  ProcessorProvider& processor;
  LicenseProvider& license;
};
