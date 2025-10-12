// ScaleProvider.h
#pragma once
struct ScaleController
{
  virtual ~ScaleController() = default;
  virtual void setScale(int value) noexcept = 0;
};
