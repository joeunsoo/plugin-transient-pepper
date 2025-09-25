#include "ActivateModal.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
ActivateModal::ActivateModal() {
  setInterceptsMouseClicks (true, true); // 뒤에 클릭 못 가게 막음
  setAlwaysOnTop (true);

  flexContainer.addAndMakeVisible(pluginNameLabel);
   
  
  pluginNameLabel.setText ("Transient Pepper", juce::dontSendNotification);
  
  pluginNameLabel.setJustificationType (juce::Justification::centred);
  
  pluginNameLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  
  addAndMakeVisible (flexContainer);

}

ActivateModal::~ActivateModal() = default;

void ActivateModal::init(PluginEditor& editor)
{
  editorRef = &editor;
  pluginNameLabel.setFont(editorRef->fontBold.withHeight(14));
}

void ActivateModal::resized()
{
  flexContainer.setBounds(getLocalBounds().withSizeKeepingCentre(250, 200));

  juce::FlexBox flexBox;
  flexBox.flexDirection = FlexBox::Direction::column;
  flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
  flexBox.alignItems = juce::FlexBox::AlignItems::center;
  
  auto flexItemSetting = [](juce::Component& child, int height, float marginBottom) {
    return FlexItem(child)
      .withWidth(300)
      .withMinHeight(height)
      .withMargin(FlexItem::Margin{0, 0, marginBottom, 0})
    ;
  };

  flexBox.items.add(flexItemSetting(pluginNameLabel,14,4.0f));
  flexBox.performLayout (flexContainer.getLocalBounds()); // [6]
}

void ActivateModal::paint (juce::Graphics& g)
{
  // 반투명 배경
  g.fillAll (juce::Colours::black.withAlpha (0.5f));
  
  // FlexContainer 배경색
  g.setColour(DARK_RGB[7]);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS);
}

void ActivateModal::mouseUp (const juce::MouseEvent&)
{
  close();
}

void ActivateModal::showIn (juce::Component& parent)
{
  parent.addAndMakeVisible (this);
  setBounds (parent.getLocalBounds());
  toFront (true); // 맨 위로
}

void ActivateModal::close()
{
  setVisible (false);
  if (auto* p = getParentComponent())
    p->removeChildComponent (this);
}
