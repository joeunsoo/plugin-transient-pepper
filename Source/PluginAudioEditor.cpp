/*
 ==============================================================================
 
 PluginAudioEditor.cpp
 Created: 3 Sep 2025 11:11:07am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#include "PluginAudioEditor.h"

static ZipFile* getZipFile()
{
#if DEBUG
    static auto stream = createAssetInputStream ("webviewplugin-gui_1.0.0.zip", AssertAssetExists::no);
    
    if (stream == nullptr)
        return nullptr;
    
    static ZipFile f { stream.get(), false };
    return &f;
#else
    const auto resourceDir = File::getSpecialLocation (File::currentExecutableFile)
        .getParentDirectory().getParentDirectory().getChildFile ("Resources");
    const auto resourceFile = resourceDir.getChildFile ("gui.zip");
    
    static auto stream = resourceFile.createInputStream();
    
    if (stream == nullptr)
        return nullptr;
    
    static ZipFile f { stream.get(), false };
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
saturationDriveAttachment (*processorRef.state.getParameter (ID::saturationDrive.getParamID()),
                           saturationDriveSliderRelay,
                           processorRef.state.undoManager),
emphasisAttachment (*processorRef.state.getParameter (ID::emphasis.getParamID()),
                    emphasisSliderRelay,
                    processorRef.state.undoManager),
tiltAttachment (*processorRef.state.getParameter (ID::tilt.getParamID()),
                tiltSliderRelay,
                processorRef.state.undoManager),
inputGainAttachment (*processorRef.state.getParameter (ID::inputGain.getParamID()),
                     inputGainSliderRelay,
                     processorRef.state.undoManager),
outputGainAttachment (*processorRef.state.getParameter (ID::outputGain.getParamID()),
                      outputGainSliderRelay,
                      processorRef.state.undoManager),
dryWetAttachment (*processorRef.state.getParameter (ID::dryWet.getParamID()),
                  dryWetSliderRelay,
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
    switch (processorRef.windowScale)
    {
        case 100:
            setSize(500, 300);
            break;
        case 150:
            setSize(500*1.5f, 300*1.5f);
            break;
        case 200:
            setSize(500*2.0f, 300*2.0f);
            break;
        default:
            setSize(500, 300);
    }
}
