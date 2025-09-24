#include "MenuComponent.h"
#include "../PluginEditor.h"
#include "../LookAndFeelDemo.h"

//==============================================================================
MenuComponent::MenuComponent() {
  
}

MenuComponent::~MenuComponent() = default;

void MenuComponent::setEditorRef(PluginEditor& editor)
{
  editorRef = &editor;
  
  menuLnF.setTypeface(editorRef->pretendardMediumTypeface);
  
  addAndMakeVisible(menuButton);
  menuButton.setButtonText("Right Button");
  DBG("test");
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
