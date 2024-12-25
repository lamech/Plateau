#ifndef DISTRHO_PLUGIN_INFO_H_INCLUDED
#define DISTRHO_PLUGIN_INFO_H_INCLUDED

#define DISTRHO_PLUGIN_NAME  "Plateau"
#define DISTRHO_PLUGIN_URI   "https://dartspark.bandcamp.com"

//DSP
#define DISTRHO_PLUGIN_NUM_INPUTS   2
#define DISTRHO_PLUGIN_NUM_OUTPUTS  2
#define DISTRHO_PLUGIN_IS_RT_SAFE   1

//UI
#define DISTRHO_PLUGIN_HAS_UI 1
#define DISTRHO_UI_DEFAULT_WIDTH 315
#define DISTRHO_UI_DEFAULT_HEIGHT 665
#define DISTRHO_UI_FILE_BROWSER 0
#define DISTRHO_UI_USER_RESIZABLE 0
#define DISTRHO_UI_USE_NANOVG 1

enum Parameters {
    kDry,
    kWet,
    kPreDelay,
    kInputLowDamp,
    kInputHighDamp,
    kSize,
    kDiffusion,
    kDecay,
    kReverbLowDamp,
    kReverbHighDamp,
    kModSpeed,
    kModDepth,
    kModShape,

    kParamCount
};

#endif