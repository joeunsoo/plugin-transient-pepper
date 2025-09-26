/*
  ==============================================================================

    Define.h
    Created: 9 Sep 2025 2:30:00pm
    Author:  JoEunsoo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define CHECK_ENV false
#define CHECK_SIDECHAIN false
#define DISABLE_DCOFFSET_FILTER false
#define ADVANCED false

#define PLUGIN_CODE "transient-pepper"

#define UI_TIMER_HZ 60

#define UI_SECTION_LABEL_HEIGHT 20
#define UI_SECTION_LABEL_FONT_HEIGHT 13.f
#define UI_BUTTON_HEIGHT 30
#define UI_BUTTON_FONT_HEIGHT 9.0f
#define UI_BUTTON_BORDER_RADIUS 4.0f
#define UI_BUTTON_SVG_PADDING 7
#define UI_BUTTON_PADDING_LEFT 1
#define UI_BUTTON_PADDING_TOP 0
#define UI_BUTTON_PADDING_RIGHT 1
#define UI_BUTTON_PADDING_BOTTOM 5

#define UI_KNOB_LABEL_HEIGHT 11
#define UI_KNOB_LABEL_FONT_HEIGHT 9.0f
#define UI_KNOB_WIDTH 70
#define UI_KNOB_HEIGHT 75

#define UI_STEREO_METER_MAX_WIDTH 35
#define UI_METER_BORDER_RADIUS 4.0f
#define UI_METER_PADDING_LEFT 2
#define UI_METER_PADDING_TOP 0
#define UI_METER_PADDING_RIGHT 2
#define UI_METER_PADDING_BOTTOM 5

#define UI_GRAPH_BORDER_RADIUS 10.0f
#define UI_GRAPH_PADDING_LEFT 5
#define UI_GRAPH_PADDING_TOP 0
#define UI_GRAPH_PADDING_RIGHT 5
#define UI_GRAPH_PADDING_BOTTOM 5

#define UI_TOOLTIP_FONT_HEIGHT 9.0f
#define UI_TOOLTIP_BORDER_RADIUS 4.0f
#define UI_TOOLTIP_OFFSET_TOP 4
#define UI_TOOLTIP_PADDING_X 4
#define UI_TOOLTIP_PADDING_Y 2
#define UI_GAP_SIZE 2
#define UI_POPUPMENU_FONT_HEIGHT 10.0f
#define UI_POPUPMENU_BORDER_RADIUS 4.0f

#define UI_MODAL_BORDER_RADIUS 4.0f
#define UI_MODAL_BUTTON_BORDER_RADIUS 4.0f
#define UI_MODAL_TEXT_LABEL_HEIGHT 9.0f
#define UI_MODAL_TEXT_LABEL_FONT_HEIGHT 9.0f
#define UI_MODAL_TEXT_EDITOR_LABEL_HEIGHT 9.0f
#define UI_MODAL_TEXT_EDITOR_LABEL_FONT_HEIGHT 9.0f
#define UI_MODAL_TEXT_EDITOR_BORDER_RADIUS 4.0f
#define UI_MODAL_TEXT_EDITOR_HEIGHT 20
#define UI_MODAL_TEXT_EDITOR_FONT_HEIGHT 10.0f

#define UI_PLUGIN_NAME_FONT_HEIGHT 14

#define  DISABLED_ALPHA 0.5f

static const juce::Colour PRIMARY_RGB[] = {
  juce::Colour(0xFFffffff),
  juce::Colour(0xFFe0e0e1),
  juce::Colour(0xFFc2c2c3),
  juce::Colour(0xFFa5a5a6),
  juce::Colour(0xFF88888a),
  juce::Colour(0xFF6d6d6f),
  juce::Colour(0xFF535355),
  juce::Colour(0xFF383839),
  juce::Colour(0xFF1f1f20),
  juce::Colour(0xFF000000)
};
static const juce::Colour PRIMARY_LIGHT_RGB[] = {
  juce::Colour(0xFFffffff),
  juce::Colour(0xFFeaeaeb),
  juce::Colour(0xFFd6d6d7),
  juce::Colour(0xFFc2c2c3),
  juce::Colour(0xFFaeaeaf),
  juce::Colour(0xFF9b9b9c),
  juce::Colour(0xFF88888a),
  juce::Colour(0xFF767678),
  juce::Colour(0xFF646466),
  juce::Colour(0xFF535355)
};

static const juce::Colour PRIMARY_DARK_RGB[] = {
  juce::Colour(0xFF535355),
  juce::Colour(0xFF4a4a4c),
  juce::Colour(0xFF424243),
  juce::Colour(0xFF3a3a3b),
  juce::Colour(0xFF323233),
  juce::Colour(0xFF2a2a2a),
  juce::Colour(0xFF222223),
  juce::Colour(0xFF1b1b1b),
  juce::Colour(0xFF131313),
  juce::Colour(0xFF080808)
};
static const juce::Colour SECONDARY_RGB[] = {
  juce::Colour(0xFFffffff),
  juce::Colour(0xFFffdfd8),
  juce::Colour(0xFFffbfb2),
  juce::Colour(0xFFfd9e8d),
  juce::Colour(0xFFf67d69),
  juce::Colour(0xFFec5847),
  juce::Colour(0xFFdf2926),
  juce::Colour(0xFFa71f1e),
  juce::Colour(0xFF721616),
  juce::Colour(0xFF420c0b)
};
static const juce::Colour SECONDARY_LIGHT_RGB[] = {
  juce::Colour(0xFFffffff),
  juce::Colour(0xFFffeae5),
  juce::Colour(0xFFffd4cb),
  juce::Colour(0xFFffbfb2),
  juce::Colour(0xFFffa999),
  juce::Colour(0xFFfb9381),
  juce::Colour(0xFFf67d69),
  juce::Colour(0xFFef6552),
  juce::Colour(0xFFe84b3c),
  juce::Colour(0xFFdf2926)
};
static const juce::Colour SECONDARY_DARK_RGB[] = {
  juce::Colour(0xFFdf2926),
  juce::Colour(0xFFc62723),
  juce::Colour(0xFFad2520),
  juce::Colour(0xFF95231d),
  juce::Colour(0xFF7e201a),
  juce::Colour(0xFF671c17),
  juce::Colour(0xFF511914),
  juce::Colour(0xFF3c1410),
  juce::Colour(0xFF290f0a),
  juce::Colour(0xFF160403)
};

static const juce::Colour INFO_RGB[] = {
    juce::Colour(0xFFffffff),
    juce::Colour(0xFFe6dae1),
    juce::Colour(0xFFcdb6c4),
    juce::Colour(0xFFb593a8),
    juce::Colour(0xFF9c728c),
    juce::Colour(0xFF845172),
    juce::Colour(0xFF6b3058),
    juce::Colour(0xFF47233b),
    juce::Colour(0xFF261620),
    juce::Colour(0xFF000000)
};

static const juce::Colour DARK_RGB[] = {
    juce::Colour(0xFFC9C9C9),
    juce::Colour(0xFFb8b8b8),
    juce::Colour(0xFF828282),
    juce::Colour(0xFF696969),
    juce::Colour(0xFF424242),
    juce::Colour(0xFF3b3b3b),
    juce::Colour(0xFF2e2e2e),
    juce::Colour(0xFF242424),
    juce::Colour(0xFF1f1f1f),
    juce::Colour(0xFF141414)
};
