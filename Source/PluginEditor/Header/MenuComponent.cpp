#include "MenuComponent.h"
#include "../PluginEditor.h"

//==============================================================================
MenuComponent::MenuComponent() {
  
}

MenuComponent::~MenuComponent() = default;

void MenuComponent::setEditorRef(PluginEditor& editor)
{
  editorRef = &editor;
  
  menuLnF.setTypeface(editorRef->pretendardMediumTypeface);
  
  menuButton.setClickingTogglesState (false); // 토글 버튼이면 true
  addAndMakeVisible(menuButton);
  
  std::unique_ptr<juce::Drawable> menuSvg (
      juce::Drawable::createFromImageData (BinaryData::gearsixfill_svg, BinaryData::gearsixfill_svgSize)
  );
  auto normal = menuSvg->createCopy();
  normal->replaceColour (juce::Colours::black, juce::Colours::white);

  auto over = menuSvg->createCopy();
  over->replaceColour (juce::Colours::black, DARK_RGB[1]);

  auto down = menuSvg->createCopy();
  down->replaceColour (juce::Colours::black, DARK_RGB[1]);

  menuButton.setImages (normal.get(), over.get(), down.get());

  // menuButton.setImages (menuSvg.get());

  menuButton.onClick = [&]
  {
    PopupMenu menu;
    menu.setLookAndFeel (&menuLnF);
    menu.addItem ("100%", [this] { editorRef->setScale(100); });
    menu.addItem ("150%", [this] { editorRef->setScale(150); });
    menu.addItem ("200%", [this] { editorRef->setScale(200); });
    menu.addSeparator();
    menu.addItem ("Visit joeunsoo.com", nullptr);
    menu.addItem ("About", nullptr);
    menu.addSeparator();
    menu.addItem ("Activate", nullptr);
    menu.showMenuAsync (PopupMenu::Options{}.withTargetComponent (menuButton));
  };
}

void MenuComponent::paint(juce::Graphics& g)
{
  // g.fillAll(juce::Colour(SECONDARY_DARK_RGB[5]));
}

void MenuComponent::resized()
{
  auto area = getLocalBounds();
  // menuButton.setBounds (20, 20, 100, 30);
  menuButton.setBounds(area);
  DBG(area.getX() << ',' << area.getY() << ',' << area.getWidth() << ',' << area.getHeight());
}
