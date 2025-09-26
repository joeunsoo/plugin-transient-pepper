#include "AboutModal.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
AboutModal::AboutModal() {
  setInterceptsMouseClicks (true, true); // 뒤에 클릭 못 가게 막음
  setAlwaysOnTop (true);

  flexContainer.addAndMakeVisible(pluginNameLabel);
  flexContainer.addAndMakeVisible(pluginVersionLabel);
  flexContainer.addAndMakeVisible(companyNameLabel);

  pluginNameLabel.setText ("Transient Pepper", juce::dontSendNotification);
  pluginVersionLabel.setText ("v" + juce::String(JucePlugin_VersionString), juce::dontSendNotification);
  companyNameLabel.setText ("JoEunsoo", juce::dontSendNotification);
  
  pluginNameLabel.setJustificationType (juce::Justification::centred);
  pluginVersionLabel.setJustificationType (juce::Justification::centred);
  companyNameLabel.setJustificationType (juce::Justification::centred);
  
  pluginNameLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  pluginVersionLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  companyNameLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  
  addAndMakeVisible (flexContainer);
}

AboutModal::~AboutModal() = default;

void AboutModal::init(PluginEditor& editor)
{
  editorRef = &editor;
  pluginNameLabel.setFont(editorRef->fontBold.withHeight(UI_PLUGIN_NAME_FONT_HEIGHT));
  pluginVersionLabel.setFont(editorRef->fontMedium.withHeight(10));
  companyNameLabel.setFont(editorRef->fontBold.withHeight(10));

  // 클릭 이벤트 처리
  pluginNameLabel.setInterceptsMouseClicks(false, false);
  pluginVersionLabel.setInterceptsMouseClicks(false, false);
  companyNameLabel.setInterceptsMouseClicks(false, false);
  flexContainer.setInterceptsMouseClicks(false, false);
}

void AboutModal::resized()
{
  flexContainer.setBounds(getLocalBounds().withSizeKeepingCentre(250, 100));

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

  flexBox.items.add(flexItemSetting(pluginNameLabel,UI_PLUGIN_NAME_FONT_HEIGHT,4.0f));
  flexBox.items.add(flexItemSetting(pluginVersionLabel,10,15.0f));
  flexBox.items.add(flexItemSetting(companyNameLabel,10,0.0f));
  flexBox.performLayout (flexContainer.getLocalBounds()); // [6]
}

void AboutModal::paint (juce::Graphics& g)
{
  // 반투명 배경
  g.fillAll (juce::Colours::black.withAlpha (0.5f));
  
  // FlexContainer 배경색
  g.setColour(DARK_RGB[7]);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS);
}

void AboutModal::mouseUp (const juce::MouseEvent&)
{
  close();
}

void AboutModal::showIn (juce::Component& parent)
{
  parent.addAndMakeVisible (this);
  setBounds (parent.getLocalBounds());
  toFront (true); // 맨 위로
}

void AboutModal::close()
{
  setVisible (false);
  if (auto* p = getParentComponent())
    p->removeChildComponent (this);
}

