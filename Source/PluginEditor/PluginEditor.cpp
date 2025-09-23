#include "../Define.h"
#include "PluginEditor.h"
#include "../AudioProcessor/PluginAudioProcessor.h"

// 생성자 정의
PluginEditor::PluginEditor(PluginAudioProcessor& p)
: AudioProcessorEditor(&p), processorRef(p)
{
  addAndMakeVisible (headerComponent);
  headerComponent.setEditorRef(*this); // 생성자 안에서 안전하게 연결

  setSize(640, 360);
  
  auto* laf = new CustomLookAndFeel();
  rotarySlider.setLookAndFeel (laf);
  addAndMakeVisible (rotarySlider);
  rotarySlider.setValue (2.5);
  // addAndMakeVisible(flexDemo); // FlexBoxDemo를 Editor 안에 표시
}

// 소멸자
PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colour(SECONDARY_DARK_RGB[9]));
}

void PluginEditor::resized()
{
  auto area = getLocalBounds().reduced(10);
  headerComponent.setBounds(area.removeFromTop(60).reduced(5));
  // UI layout code
  rotarySlider.setBounds(50, 50, 100, 100);
  // rotarySlider  .setBounds (row.removeFromLeft (100).reduced (5));
}

void PluginEditor::setScale(int scale)
{
  processorRef.windowScale = scale;
  
  float factor = 1.0f;
  switch (scale)
  {
      case 150: factor = 1.5f; break;
      case 200: factor = 2.0f; break;
      default:  factor = 1.0f; break;
  }

  // 기본 크기는 고정
  setSize(640, 360);

  // 전체 에디터에 transform 적용
  setTransform(juce::AffineTransform::scale(factor));
}
