cmake_minimum_required(VERSION 3.22)

project(AUDIO_PLUGIN_EXAMPLE VERSION 1.0.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(JUCE)

juce_add_plugin(JETransientPepper
    PLUGIN_MANUFACTURER_CODE JOES
    PLUGIN_CODE tspp
                                                
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "JE Transient Pepper"
    NEEDS_WEB_BROWSER FALSE
    NEEDS_CURL FALSE)

target_sources(JETransientPepper
    PRIVATE
        ./Sources/PluginEditor.cpp
        ./Sources/PluginProcessor.cpp)

target_compile_definitions(JETransientPepper
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(JETransientPepper
    PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
