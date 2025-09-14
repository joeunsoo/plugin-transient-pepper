/*
 ==============================================================================
 
 PluginAudioEditor.cpp
 Created: 3 Sep 2025 11:11:07am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#include "PluginAudioEditor.h"
#include "Define.h"

static ZipFile* getZipFile()
{
#if DEBUG
  static auto stream = createAssetInputStream ("webviewplugin-gui_1.0.0.zip", AssertAssetExists::no);
  
  if (stream == nullptr)
    return nullptr;
  
  static ZipFile f { stream.get(), false };
  return &f;
#else
  static MemoryInputStream stream { BinaryData::gui_zip, BinaryData::gui_zipSize, false };

  static ZipFile f { &stream, false };
  return &f;
#endif
}

static const char* getMimeForExtension (const String& extension)
{
  static const std::unordered_map<String, const char*> mimeMap =
  {
    { { "htm"   },  "text/html"                },
    { { "html"  },  "text/html"                },
    { { "txt"   },  "text/plain"               },
    { { "jpg"   },  "image/jpeg"               },
    { { "jpeg"  },  "image/jpeg"               },
    { { "svg"   },  "image/svg+xml"            },
    { { "ico"   },  "image/vnd.microsoft.icon" },
    { { "json"  },  "application/json"         },
    { { "png"   },  "image/png"                },
    { { "css"   },  "text/css"                 },
    { { "map"   },  "application/json"         },
    { { "js"    },  "text/javascript"          },
    { { "woff2" },  "font/woff2"               }
  };
  
  if (const auto it = mimeMap.find (extension.toLowerCase()); it != mimeMap.end())
    return it->second;
  
  jassertfalse;
  return "";
}

static String getExtension (String filename)
{
  return filename.fromLastOccurrenceOf (".", false, false);
}

static auto streamToVector (InputStream& stream)
{
  std::vector<std::byte> result ((size_t) stream.getTotalLength());
  stream.setPosition (0);
  [[maybe_unused]] const auto bytesRead = stream.read (result.data(), result.size());
  jassert (bytesRead == (ssize_t) result.size());
  return result;
}

std::optional<WebBrowserComponent::Resource> PluginAudioEditor::getResource (const String& url)
{
  const auto urlToRetrive = url == "/" ? String { "index.html" }
  : url.fromFirstOccurrenceOf ("/", false, false);
  
  if (auto* archive = getZipFile())
  {
    if (auto* entry = archive->getEntry (urlToRetrive))
    {
      auto stream = rawToUniquePtr (archive->createStreamForEntry (*entry));
      auto v = streamToVector (*stream);
      auto mime = getMimeForExtension (getExtension (entry->filename).toLowerCase());
      return WebBrowserComponent::Resource { std::move (v),
        std::move (mime) };
    }
  }
  
  if (urlToRetrive == "index.html")
  {
    auto fallbackIndexHtml = createAssetInputStream ("webviewplugin-gui-fallback.html");
    return WebBrowserComponent::Resource { streamToVector (*fallbackIndexHtml),
      String { "text/html" } };
  }
  
  if (urlToRetrive == "data.txt")
  {
    WebBrowserComponent::Resource resource;
    static constexpr char testData[] = "testdata";
    MemoryInputStream stream { testData, numElementsInArray (testData) - 1, false };
    return WebBrowserComponent::Resource { streamToVector (stream), String { "text/html" } };
  }
  
  if (urlToRetrive == "analysisData.json")
  {
    Array<var> frames;
    
    // 현재 시간(ms) 기준으로 시작
    
    for (const auto& frame : analysisDataFrames)
    {
      auto* frameObj = new DynamicObject();
      frameObj->setProperty("timeMs", Time::getCurrentTime().toMilliseconds());

      frameObj->setProperty("values", frame);         // 기존 frame 값
      frames.add(var(frameObj));  // ← var로 래핑
    }
    
    DynamicObject::Ptr d (new DynamicObject());
    d->setProperty ("outputNumChannels", processorRef.getTotalNumOutputChannels());
    d->setProperty ("timeResolutionMs", getTimerInterval());
    d->setProperty ("frames", std::move (frames));
    
    const auto s = JSON::toString (d.get());
    MemoryInputStream stream { s.getCharPointer(), s.getNumBytesAsUTF8(), false };
    return WebBrowserComponent::Resource { streamToVector (stream), String { "application/json" } };
  }
  
  return std::nullopt;
}

#if JUCE_ANDROID
// The localhost is available on this address to the emulator
const String localDevServerAddress = "http://10.0.2.2:3000/";
#else
const String localDevServerAddress = "http://localhost:3000/";
#endif

bool SinglePageBrowser::pageAboutToLoad (const String& newURL)
{
  return newURL == localDevServerAddress || newURL == getResourceProviderRoot();
}

//==============================================================================
PluginAudioEditor::PluginAudioEditor (PluginAudioProcessor& p)
: AudioProcessorEditor (&p), processorRef (p),

bypassAttachment (*processorRef.state.getParameter (ID::bypass.getParamID()),
                  bypassToggleRelay,
                  processorRef.state.undoManager),
#if ADVANCED
generatorTypeAttachment (*processorRef.state.getParameter (ID::generatorType.getParamID()),
                  generatorTypeComboRelay,
                  processorRef.state.undoManager),
#endif
attackAttachment (*processorRef.state.getParameter (ID::attack.getParamID()),
                  attackSliderRelay,
                  processorRef.state.undoManager),
releaseAttachment (*processorRef.state.getParameter (ID::release.getParamID()),
                   releaseSliderRelay,
                   processorRef.state.undoManager),

thresholdAttachment (*processorRef.state.getParameter (ID::threshold.getParamID()),
                     thresholdSliderRelay,
                     processorRef.state.undoManager),
bpfPowerAttachment (*processorRef.state.getParameter (ID::bpfPower.getParamID()),
                    bpfPowerToggleRelay,
                    processorRef.state.undoManager),
bpfFrequencyAttachment (*processorRef.state.getParameter (ID::bpfFrequency.getParamID()),
                        bpfFrequencySliderRelay,
                        processorRef.state.undoManager),

tiltAttachment (*processorRef.state.getParameter (ID::tilt.getParamID()),
                tiltSliderRelay,
                processorRef.state.undoManager),

midSideAttachment (*processorRef.state.getParameter (ID::midSide.getParamID()),
                   midSideSliderRelay,
                   processorRef.state.undoManager),

noiseLevelGainAttachment (*processorRef.state.getParameter (ID::noiseLevelGain.getParamID()),
                          noiseLevelGainSliderRelay,
                          processorRef.state.undoManager),

outputGainAttachment (*processorRef.state.getParameter (ID::outputGain.getParamID()),
                      outputGainSliderRelay,
                      processorRef.state.undoManager),

dryWetAttachment (*processorRef.state.getParameter (ID::dryWet.getParamID()),
                  dryWetSliderRelay,
                  processorRef.state.undoManager),

#if ADVANCED
fastAttackAttachment (*processorRef.state.getParameter (ID::fastAttack.getParamID()),
                      fastAttackSliderRelay,
                      processorRef.state.undoManager),
fastReleaseAttachment (*processorRef.state.getParameter (ID::fastRelease.getParamID()),
                       fastReleaseSliderRelay,
                       processorRef.state.undoManager),
slowAttackAttachment (*processorRef.state.getParameter (ID::slowAttack.getParamID()),
                      slowAttackSliderRelay,
                      processorRef.state.undoManager),
slowReleaseAttachment (*processorRef.state.getParameter (ID::slowRelease.getParamID()),
                       slowReleaseSliderRelay,
                       processorRef.state.undoManager),
#endif

wetSoloAttachment (*processorRef.state.getParameter (ID::wetSolo.getParamID()),
                   wetSoloToggleRelay,
                   processorRef.state.undoManager),

linkChannelsAttachment (*processorRef.state.getParameter (ID::linkChannels.getParamID()),
                        linkChannelsToggleRelay,
                        processorRef.state.undoManager)
{
  addAndMakeVisible (webComponent);
  
#if DEBUG
  webComponent.goToURL (localDevServerAddress);
#else
  webComponent.goToURL (WebBrowserComponent::getResourceProviderRoot());
#endif
  
  setScale(processorRef.windowScale);
  startTimerHz (20);
}

//==============================================================================
void PluginAudioEditor::paint (Graphics& g)
{
  // (Our component is opaque, so we must completely fill the background with a solid colour)
  g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void PluginAudioEditor::resized()
{
  webComponent.setBounds (getLocalBounds());
}

void PluginAudioEditor::setScale(int scale)
{
  processorRef.windowScale = scale;
  
  int width = 640;
  int height = 360;
  
  switch (processorRef.windowScale)
  {
    case 100:
      setSize(width, height);
      break;
    case 150:
      setSize(width*1.5f, height*1.5f);
      break;
    case 200:
      setSize(width*2.0f, height*2.0f);
      break;
    default:
      setSize(width, height);
  }
}
