#pragma once
#include <JuceHeader.h>

struct LicenseProvider {
  virtual ~LicenseProvider() = default;

  // 상태 조회
  virtual bool isActivate() const noexcept = 0;
  virtual bool isTrialExpired() const noexcept = 0;
  virtual juce::String getActivate() const = 0; // 이메일/계정 등

  // 상태 변경
  virtual void setActivate(juce::String email) = 0;
  virtual void setDeactivate() = 0;

  // 네트워크 활성화 요청
  // return: (HTTP status code, message)
  virtual std::pair<int, juce::String> sendActivationRequest(juce::String userEmail,
                                                             juce::String userPassword) = 0;

  // 트라이얼
  virtual int64 getTrial() const noexcept = 0;
  virtual int getTrialDays() const noexcept = 0;
  virtual int64 startTrial() = 0; // 트라이얼 시작 timestamp(ms) 반환
};
