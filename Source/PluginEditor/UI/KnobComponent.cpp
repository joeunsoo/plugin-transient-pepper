#include "KnobComponent.h"
#include "../DefineUI.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
KnobComponent::KnobComponent(
                             PluginEditor& editor,
                             const String& paramID,
                             const String labelText
                             )
: editorRef(editor)
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
   editorRef.processorRef.state,
   parameterID,
   rotarySlider
   );
  label.setFont(editorRef.fontRegular.withHeight(UI_KNOB_LABEL_FONT_HEIGHT));
  label.setText(labelText, juce::dontSendNotification);
  label.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(label);
  
  rotarySlider.addMouseListener(this, true);
  
  rotarySlider.onValueChange = [this] {
    if (isDrag) {
      sendTooltip();
    }
  };
  
  rotarySlider.onDragStart = [this]{
    isDrag = true;
    editorRef.setDrag(true, parameterID);
  };
  rotarySlider.onDragEnd   = [this]{
    isDrag = false;
    editorRef.setDrag(false, parameterID);
  };
  
}

KnobComponent::~KnobComponent()
{
  attachment.reset();
  rotarySlider.removeMouseListener(this);
  rotarySlider.onValueChange = nullptr;
  rotarySlider.onDragStart = nullptr;
  rotarySlider.onDragEnd = nullptr;
  attachment.reset();
};

void KnobComponent::sendTooltip()
{
  if (auto* param = editorRef.processorRef.state.getParameter(parameterID)) {
    auto topLeftInEditor = editorRef.getLocalPoint(&rotarySlider, juce::Point<int>(0, 0));
    
    auto size = std::min(rotarySlider.getWidth(),rotarySlider.getHeight());
    auto top = (rotarySlider.getHeight()/2) + (size/2) + UI_KNOB_LABEL_HEIGHT;
    juce::Rectangle<int> tooltipArea(topLeftInEditor.getX(),
                                     topLeftInEditor.getY() + top,
                                     rotarySlider.getWidth(), 24);
    
    editorRef.showTooltipAt(parameterID, tooltipArea, param->getCurrentValueAsText());
  }
  editorRef.tooltipLabel->setVisible(true);
}

void KnobComponent::mouseEnter(const juce::MouseEvent&)
{
  isDrag = true;
  sendTooltip();
};

void KnobComponent::mouseExit(const juce::MouseEvent&)
{
  isDrag = false;
  editorRef.tooltipLabel->setVisible(false);
};

void KnobComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void KnobComponent::resized()
{
  auto area = getLocalBounds();
  auto size = std::min(area.getWidth(),area.getHeight()-UI_KNOB_LABEL_HEIGHT);
  
  rotarySlider.setBounds(area.removeFromTop(area.getHeight()-UI_KNOB_LABEL_HEIGHT));
  
  auto labelArea = getLocalBounds();
  auto top = ((labelArea.getHeight()-UI_KNOB_LABEL_HEIGHT) / 2) + (size / 2);
  labelArea.setY(top);
  labelArea.setHeight(UI_KNOB_LABEL_HEIGHT);
  label.setBounds(labelArea);
}

void KnobComponent::setColor(const String color) {
  rotarySlider.color = color;
}

void KnobComponent::setRingColor(const String color) {
  rotarySlider.ringColor = color;
}
