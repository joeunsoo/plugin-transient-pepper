#include "Define.h"
#include "PluginWrapper.h"
#include <JuceHeader.h>

//==============================================================================
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new PluginWrapper();
}
