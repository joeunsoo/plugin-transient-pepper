#include "KnobComponent.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
KnobComponent::KnobComponent() {
  
}

KnobComponent::~KnobComponent() = default;

void KnobComponent::init(
                         PluginEditor& editor,
                         const String& paramID,
                         const String labelText)
{
  editorRef = &editor;
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
   editorRef->processorRef.state,
   parameterID,
   rotarySlider
   );
  
  label.setFont(editorRef->fontMedium);
  label.setText(labelText, juce::dontSendNotification);
  label.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(label);
  
  rotarySlider.addMouseListener(this, true);

  rotarySlider.onValueChange = [this] {
    sendTooltip();
    };
  
  rotarySlider.onDragStart = [this]{ editorRef->setDrag(true, parameterID); };
  rotarySlider.onDragEnd   = [this]{ editorRef->setDrag(false, parameterID); };
  
  
}

void KnobComponent::sendTooltip()
{
  if (editorRef != nullptr)
  {
    if (auto* param = editorRef->processorRef.state.getParameter(parameterID)) {
      auto topLeftInEditor = editorRef->getLocalPoint(&rotarySlider, juce::Point<int>(0, 0));

      juce::Rectangle<int> tooltipArea(topLeftInEditor.getX(),
                                       topLeftInEditor.getY() + rotarySlider.getHeight(),
                                       rotarySlider.getWidth(), 24);

      editorRef->showTooltipAt(parameterID, tooltipArea, param->getCurrentValueAsText());
    }
    editorRef->tooltipLabel->setVisible(true);
  }
}

void KnobComponent::mouseEnter(const juce::MouseEvent&)
{
  sendTooltip();
};

void KnobComponent::mouseExit(const juce::MouseEvent&)
{
  if (editorRef != nullptr)
  {
    editorRef->tooltipLabel->setVisible(false);
  }
};

void KnobComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void KnobComponent::resized()
{
  auto area = getLocalBounds();
  rotarySlider.setBounds(area.removeFromTop(area.getHeight() - 10));

  area.setY(area.getY()-10);
  label.setBounds(area);
}

void KnobComponent::setColor(const String color) {
  rotarySlider.color = color;
}

void KnobComponent::setRingColor(const String color) {
  rotarySlider.ringColor = color;
}
