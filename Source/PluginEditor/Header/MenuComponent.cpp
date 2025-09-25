#include "MenuComponent.h"
#include "../../Define.h"
#include "../PluginEditor.h"

//==============================================================================
MenuComponent::MenuComponent() {
  
}

MenuComponent::~MenuComponent()
{
  setLookAndFeel(nullptr);
};


void MenuComponent::init(PluginEditor& editor)
{
  editorRef = &editor;

  menuLaF.setFont(editorRef->fontRegular.withHeight(UI_POPUPMENU_FONT_HEIGHT));
  setLookAndFeel (&menuLaF);

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
    menuLaF.setWindowScale(editorRef->processorRef.windowScale);
    menu.setLookAndFeel(&menuLaF);
    menu.addItem ("100%", [this] { editorRef->setScale(100); });
    menu.addItem ("150%", [this] { editorRef->setScale(150); });
    menu.addItem ("200%", [this] { editorRef->setScale(200); });
    menu.addSeparator();
    menu.addItem ("Visit joeunsoo.com", [] {
      const URL newUrl = URL ("https://joeunsoo.com");
      if (newUrl.isWellFormed())
        newUrl.launchInDefaultBrowser();
    });
    menu.addItem ("About", [this] { editorRef->showAbout(); });
    menu.addSeparator();
    menu.addItem (
                  !editorRef->processorRef.licenseManager.isActivate() ? "Activate" : "Deactivate",
                  [this] { editorRef->showActivate(); });
    menu.showMenuAsync (PopupMenu::Options{}.withTargetComponent (menuButton));
  };
}

void MenuComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void MenuComponent::resized()
{
  auto area = getLocalBounds();
  // menuButton.setBounds (20, 20, 100, 30);
  menuButton.setBounds(area);
}
