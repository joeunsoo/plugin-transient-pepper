#include "MenuComponent.h"
#include "../DefineUI.h"

//==============================================================================
MenuComponent::MenuComponent(Providers& pv)
: editorProvider(pv.editor), scaleProvider(pv.scale), scaleController(pv.scaleController), licenseProvider(pv.license),
menuLaF(scaleProvider)
{
  setLookAndFeel (&menuLaF);

  menuButton.setClickingTogglesState (false); // 토글 버튼이면 true
  addAndMakeVisible(menuButton);
  
  std::unique_ptr<juce::Drawable> menuSvg (
      juce::Drawable::createFromImageData (BinaryData::gearsixfill_svg, BinaryData::gearsixfill_svgSize)
  );
  auto normal = menuSvg->createCopy();
  normal->replaceColour (juce::Colours::black, juce::Colours::white);

  auto over = menuSvg->createCopy();
  over->replaceColour (juce::Colours::black, DARK_RGB_1);

  auto down = menuSvg->createCopy();
  down->replaceColour (juce::Colours::black, DARK_RGB_1);

  menuButton.setImages (normal.get(), over.get(), down.get());

  menuButton.onClick = [&]
  {
    PopupMenu menu;
    menuLaF.setWindowScale(scaleProvider.getWindowScale());

    menu.setLookAndFeel(&menuLaF);
    menu.addSectionHeader("Scale");
    menu.addItem ("100%", [this] { scaleController.setScale(100); });
    menu.addItem ("150%", [this] { scaleController.setScale(150); });
    menu.addItem ("200%", [this] { scaleController.setScale(200); });
    menu.addSeparator();
    menu.addItem ("Online Manual", [] {
      const URL newUrl = URL (PLUGIN_MANUAL_URL);
      if (newUrl.isWellFormed())
        newUrl.launchInDefaultBrowser();
    });
    menu.addItem ("About", [this] { editorProvider.showAbout(); });
    menu.addSeparator();
    menu.addItem (
                  !licenseProvider.isActivate() ? "Activate" : "Deactivate",
                  [this] { editorProvider.showActivate(); });
    menu.showMenuAsync (PopupMenu::Options{}.withTargetComponent (menuButton));
  };
}

MenuComponent::~MenuComponent()
{
  setLookAndFeel(nullptr);
  menuButton.onClick = nullptr;
};

void MenuComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void MenuComponent::resized()
{
  auto scale = scaleProvider.getScale();
  menuLaF.setFont(FONT_PRETENDARD_REGULAR.withHeight(UI_POPUPMENU_FONT_HEIGHT * scale));

  auto area = getLocalBounds();
  menuButton.setBounds(area);
}
