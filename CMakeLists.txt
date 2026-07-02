cmake_minimum_required(VERSION 3.22)

project("JE Transient Pepper" VERSION 1.0.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(JUCE)

juce_add_plugin(JETransientPepper
    PLUGIN_MANUFACTURER_CODE JOES
    PLUGIN_CODE tspp

    COMPANY_NAME "JoEunsoo"
    PRODUCT_NAME "JE Transient Pepper"
    BUNDLE_ID com.JoEunsoo.JETransientPepper

    AAX_CATEGORY Effect
    AU_MAIN_TYPE kAudioUnitType_Effect
    VST_CATEGORY kPlugCategEffect
    VST3_CATEGORY Fx

    FORMATS AAX AU VST3 Standalone
    IS_SANDBOX_SAFE TRUE
    NEEDS_WEB_BROWSER FALSE
    NEEDS_CURL FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE # 빌드 후 자동 복사 활성화
)

juce_generate_juce_header(JETransientPepper)

juce_add_binary_data(JETransientPepperData
    SOURCES
        "Assets/font/PretendardStd-Regular.otf"
        "Assets/font/PretendardStd-Medium.otf"
        "Assets/font/PretendardStd-SemiBold.otf"
        "Assets/font/PretendardStd-Bold.otf"
        "Assets/icon/headphones-bold.svg"
        "Assets/icon/power-bold.svg"
        "Assets/icon/gear-six-fill.svg"
)

#target_sources(JETransientPepper
#    PRIVATE
#        ./Source/Main.cpp)
file(GLOB_RECURSE ProjectSources CONFIGURE_DEPENDS "Source/*.cpp" "Source/*.h")
target_sources(JETransientPepper PRIVATE ${ProjectSources})

target_compile_definitions(JETransientPepper
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
        JUCE_VST3_CAN_REPLACE_VST2=0

        # 💡 [추가] .jucer에 선언되어 있던 윈도우 전용 옵션 및 예제 디렉토리 맵핑
        $<$<PLATFORM_ID:Windows>:JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1>
        PIP_JUCE_EXAMPLES_DIRECTORY="L1VzZXJzL2pvZXVuc29vL0pVQ0UvZXhhbXBsZXM="
)

target_link_libraries(JETransientPepper
    PRIVATE
        JETransientPepperData
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_data_structures
        juce::juce_events
        juce::juce_core
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

if(APPLE)
    target_compile_options(JETransientPepper
        PRIVATE
            -Wall
            -Wextra
            -Wconversion
            -Wsign-conversion
            -Wshadow
            -Wpedantic
            -Wuninitialized
            -Wnull-dereference
            -Wformat
            -Wstrict-aliasing
            -Wc++20-compat
            -Wdeprecated
            -Wnon-virtual-dtor
            -Wfloat-equal
            -Wno-c++98-compat-extra-semi
    )

    # Deployment Target 선언 규칙 최적화
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "macOS Deployment Target" FORCE)
    # 인증서 지정
    set_target_properties(JETransientPepper PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY[variant=Debug] "Apple Development: Eun Soo Jo (48GXV85C7B)"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY[variant=Release] "Developer ID Application: Eun Soo Jo (U4BB4TLGPQ)"
        XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "10.13"
    )

# Windows Visual Studio 환경을 위한 대용량 오브젝트 컴파일 옵션 세팅
elseif(MSVC)
    target_compile_options(JETransientPepper PRIVATE /bigobj)
endif()