#include "../Define.h"
#include "PluginEditor.h"
#include "../AudioProcessor/PluginAudioProcessor.h"
#include "Header/HeaderComponent.h"
#include "Main/MainComponent.h"

// 생성자 정의
PluginEditor::PluginEditor(PluginAudioProcessor& p)
: AudioProcessorEditor(&p), processorRef(p)
{
  // 헤더 불러오기
  headerComponent.init(*this);
  addAndMakeVisible (headerComponent);

  mainComponent.init(*this);
  addAndMakeVisible (mainComponent);

  // 기본 크기
  setSize(640, 360);
  setScale(processorRef.windowScale);

}

// 소멸자
PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics& g)
{
  g.fillAll(SECONDARY_DARK_RGB[9]);
}

void PluginEditor::resized()
{
  // UI layout code
  auto area = getLocalBounds();
  headerComponent.setBounds(area.removeFromTop(35));
  area.setHeight(area.getHeight()-5);
  mainComponent.setBounds(area);
  
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
  
  // 전체 에디터에 transform 적용
  // setTransform(juce::AffineTransform::scale(factor));
}
