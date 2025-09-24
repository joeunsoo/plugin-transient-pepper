#include "BypassComponent.h"
#include "../PluginEditor.h"

//==============================================================================
BypassComponent::BypassComponent() {
  
}

BypassComponent::~BypassComponent() = default;

void BypassComponent::setEditorRef(PluginEditor& editor)
{
  editorRef = &editor;
  
  menuButton.setClickingTogglesState (false); // 토글 버튼이면 true
  addAndMakeVisible(menuButton);
  
  std::unique_ptr<juce::Drawable> menuSvg (
      juce::Drawable::createFromImageData (BinaryData::powerbold_svg, BinaryData::powerbold_svgSize)
  );
  auto normal = menuSvg->createCopy();
  normal->replaceColour (juce::Colours::black, juce::Colours::white);

  auto over = menuSvg->createCopy();
  over->replaceColour (juce::Colours::black, DARK_RGB[1]);

  auto down = menuSvg->createCopy();
  down->replaceColour (juce::Colours::black, DARK_RGB[1]);

  menuButton.setImages (normal.get(), over.get(), down.get());

}

void BypassComponent::paint(juce::Graphics& g)
{
  // g.fillAll(juce::Colour(SECONDARY_DARK_RGB[5]));
}

void BypassComponent::resized()
{
  auto area = getLocalBounds();
  menuButton.setBounds(area);
}
