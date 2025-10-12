// WrapperLicenseProvider.h
#pragma once
#include <JuceHeader.h>
#include "../../PluginWrapper.h"
#include "LicenseProvider.h"

struct WrapperLicenseProvider : LicenseProvider {
  PluginWrapper& wrapper;
  explicit WrapperLicenseProvider(PluginWrapper& w) : wrapper(w) {}

  // 조회
  bool isActivate() const noexcept override { return wrapper.licenseManager.isActivate(); }
  bool isTrialExpired() const noexcept override { return wrapper.licenseManager.isTrialExpired(); }
  juce::String getActivate() const override { return wrapper.licenseManager.getActivate(); }

  // 변경
  void setActivate(juce::String email) override { wrapper.licenseManager.setActivate(email); }
  void setDeactivate() override { wrapper.licenseManager.setDeactivate(); }

  // 네트워크 요청
  std::pair<int, juce::String> sendActivationRequest(juce::String userEmail,
                                                     juce::String userPassword) override {
    return wrapper.licenseManager.sendActivationRequest(userEmail, userPassword);
  }

  // 트라이얼
  int64 getTrial() const noexcept override {
    return wrapper.licenseManager.getTrial();
  }
  int getTrialDays() const noexcept override {
    return wrapper.licenseManager.getTrialDays();
  }
  int64 startTrial() override {
    return wrapper.licenseManager.startTrial();
  }
};
