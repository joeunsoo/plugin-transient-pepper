// ScaleProvider.h
#pragma once
struct ScaleProvider
{
  virtual ~ScaleProvider() = default;
  virtual float getScale() const noexcept = 0;
  virtual int getWindowScale() const noexcept = 0;
};
