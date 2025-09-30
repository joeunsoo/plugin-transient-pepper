#include <JuceHeader.h>
#include "Define.h"
#include "PluginWrapper.h"

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new PluginWrapper();
}
