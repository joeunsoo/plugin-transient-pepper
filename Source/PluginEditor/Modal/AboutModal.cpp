#include "AboutModal.h"
#include "../DefineUI.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
AboutModal::AboutModal(const ScaleProvider& sp)
: scaleProvider(sp)
{
  setInterceptsMouseClicks (true, true); // 뒤에 클릭 못 가게 막음
  setAlwaysOnTop (true);

  flexContainer.addAndMakeVisible(pluginNameLabel);
  flexContainer.addAndMakeVisible(pluginVersionLabel);
  flexContainer.addAndMakeVisible(companyNameLabel);

  pluginNameLabel.setText (PLUGIN_NAME, juce::dontSendNotification);
  pluginVersionLabel.setText ("v" + juce::String(JucePlugin_VersionString), juce::dontSendNotification);
  companyNameLabel.setText (COMPANY_NAME, juce::dontSendNotification);
  
  pluginNameLabel.setJustificationType (juce::Justification::centred);
  pluginVersionLabel.setJustificationType (juce::Justification::centred);
  companyNameLabel.setJustificationType (juce::Justification::centred);
  
  pluginNameLabel.setColour(juce::Label::textColourId, DARK_RGB_0);
  pluginVersionLabel.setColour(juce::Label::textColourId, DARK_RGB_0);
  companyNameLabel.setColour(juce::Label::textColourId, DARK_RGB_0);
  
  addAndMakeVisible (flexContainer);


  // 클릭 이벤트 처리
  pluginNameLabel.setInterceptsMouseClicks(false, false);
  pluginVersionLabel.setInterceptsMouseClicks(false, false);
  companyNameLabel.setInterceptsMouseClicks(false, false);
  flexContainer.setInterceptsMouseClicks(false, false);
}

AboutModal::~AboutModal() = default;

void AboutModal::resized()
{
  auto scale = scaleProvider.getScale();

  pluginNameLabel.setFont(FONT_PRETENDARD_BOLD.withHeight(UI_PLUGIN_NAME_FONT_HEIGHT * scale));
  pluginVersionLabel.setFont(FONT_PRETENDARD_MEDIUM.withHeight(10 * scale));
  companyNameLabel.setFont(FONT_PRETENDARD_BOLD.withHeight(10 * scale));

  flexContainer.setBounds(getLocalBounds().withSizeKeepingCentre(int(250 * scale), int(100 * scale)));

  juce::FlexBox flexBox;
  flexBox.flexDirection = FlexBox::Direction::column;
  flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
  flexBox.alignItems = juce::FlexBox::AlignItems::center;
  
  auto flexItemSetting = [this](juce::Component& child, int height, float marginBottom) {
    auto scale = scaleProvider.getScale();
    return FlexItem(child)
      .withWidth(300 * scale)
      .withMinHeight(height * scale)
      .withMargin(FlexItem::Margin{0, 0, marginBottom * scale, 0})
    ;
  };

  flexBox.items.add(flexItemSetting(pluginNameLabel,UI_PLUGIN_NAME_FONT_HEIGHT,6.0f));
  flexBox.items.add(flexItemSetting(pluginVersionLabel,10,15.0f));
  flexBox.items.add(flexItemSetting(companyNameLabel,10,0.0f));
  flexBox.performLayout (flexContainer.getLocalBounds()); // [6]
}

void AboutModal::paint (juce::Graphics& g)
{
  auto scale = scaleProvider.getScale();

  // 반투명 배경
  g.fillAll (juce::Colours::black.withAlpha (0.5f));
  
  // FlexContainer 배경색
  g.setColour(DARK_RGB_7);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS * scale);
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

