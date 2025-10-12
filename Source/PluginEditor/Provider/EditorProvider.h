#pragma once
struct EditorProvider
{
  virtual ~EditorProvider() = default;

  virtual void showTooltipAt(String id, const juce::Rectangle<int>& area, const juce::String& text) const noexcept = 0;
  virtual void setTooltipLabelVisible(bool value) const noexcept = 0;
  
  // 드래그
  virtual void setDrag(bool value, String id) noexcept = 0;
  
  
  // 모달
  virtual void showAbout() = 0;
  virtual void showActivate() = 0;
  
  // getBoundsInEditor
  virtual Point<int> getLocalPointInEditor(const juce::Component* source, Point<int> point) const = 0;
  virtual Point<float> getLocalPointInEditor(const juce::Component* child, Point<float> point) const = 0;
};
