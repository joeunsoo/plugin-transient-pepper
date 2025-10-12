#include "KnobComponent.h"
#include "../../DefineUI.h"
#include "../../../NamespaceParameterId.h"

//==============================================================================
KnobComponent::KnobComponent(EditorProvider& ep,
                             const ScaleProvider& sp,
                             ProcessorProvider& pp,
                             const String& paramID,
                             const String labelText
                             )
: editorProvider(ep), scaleProvider(sp),
processorProvider(pp), rotarySlider(sp)
{
  parameterID = paramID;
  
  rotarySlider.setColour(
                         juce::Slider::rotarySliderFillColourId,
                         juce::Colours::orange
                         );
  
  rotarySlider.setColour(
                         juce::Slider::rotarySliderOutlineColourId,
                         juce::Colours::blue
                         );
  
  addAndMakeVisible (rotarySlider);
  
  attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
  (
   processorProvider.state(),
   parameterID,
   rotarySlider
   );
  label.setText(labelText, juce::dontSendNotification);
  label.setJustificationType(juce::Justification::centred);
  label.setColour(juce::Label::textColourId, UI_KNOB_LABEL_COLOUR);
  addAndMakeVisible(label);
  
  rotarySlider.addMouseListener(this, true);
  
  rotarySlider.onValueChange = [this] {
    if (isDrag) {
      sendTooltip();
    }
  };
  
  rotarySlider.onDragStart = [this]{
    isDrag = true;
    editorProvider.setDrag(true, parameterID);
  };
  rotarySlider.onDragEnd   = [this]{
    isDrag = false;
    editorProvider.setDrag(false, parameterID);
  };
  
}

KnobComponent::~KnobComponent()
{
  rotarySlider.removeMouseListener(this);
  rotarySlider.onValueChange = nullptr;
  rotarySlider.onDragStart = nullptr;
  rotarySlider.onDragEnd = nullptr;
  attachment.reset();
};

void KnobComponent::sendTooltip()
{
  auto scale = scaleProvider.getScale();

  if (auto* param = processorProvider.state().getParameter(parameterID)) {
    auto topLeftInEditor = editorProvider.getLocalPointInEditor(&rotarySlider, juce::Point<int>(0, 0));
    
    auto size = std::min(rotarySlider.getWidth(),rotarySlider.getHeight());
    auto top = (rotarySlider.getHeight()/2) + (size/2) + (UI_KNOB_LABEL_HEIGHT * scale);
    juce::Rectangle<int> tooltipArea(topLeftInEditor.getX(),
                                     int(topLeftInEditor.getY() + top),
                                     rotarySlider.getWidth(),
                                     int(24 * scale));
    
    editorProvider.showTooltipAt(parameterID, tooltipArea, param->getCurrentValueAsText());
  }
  editorProvider.setTooltipLabelVisible(true);
}

void KnobComponent::mouseEnter(const juce::MouseEvent&)
{
  isDrag = true;
  sendTooltip();
};

void KnobComponent::mouseExit(const juce::MouseEvent&)
{
  isDrag = false;
  editorProvider.setTooltipLabelVisible(false);
};

void KnobComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void KnobComponent::resized()
{
  auto scale = scaleProvider.getScale();
 label.setFont(FONT_PRETENDARD_REGULAR.withHeight(UI_KNOB_LABEL_FONT_HEIGHT * scale));

  auto area = getLocalBounds();
  auto size = std::min(area.getWidth(),area.getHeight()-int(UI_KNOB_LABEL_HEIGHT * scale));
  
  rotarySlider.setBounds(area.removeFromTop(area.getHeight()-int(UI_KNOB_LABEL_HEIGHT * scale)));
  
  auto labelArea = getLocalBounds();
  auto top = ((labelArea.getHeight()-int(UI_KNOB_LABEL_HEIGHT * scale)) / 2) + (size / 2);
  labelArea.setY(top);
  labelArea.setHeight(int(UI_KNOB_LABEL_HEIGHT * scale));
  label.setBounds(labelArea);
}

void KnobComponent::setColor(const String color) {
  rotarySlider.color = color;
}

void KnobComponent::setRingColor(const String color) {
  rotarySlider.ringColor = color;
}
