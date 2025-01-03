#pragma once

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
    kFreeze,
    kClear,
    kTunedMode,
    kDiffuseInput,
    kParamCount
};

struct ParameterInfo {
    const char* name;
    const char* symbol;
    float def;
    float min;
    float max;
    uint32_t hints;
};

const ParameterInfo parameterInfos[] = {
    {"Dry", "dry", 1.0f, 0.0f, 1.0f, kParameterIsAutomatable},
    {"Wet", "wet", 0.5f, 0.0f, 1.0f, kParameterIsAutomatable},
    {"Pre Delay", "preDelay", 0.0f, 0.0f, 0.5f, kParameterIsAutomatable},
    {"Input Low Damp", "inputLowDamp", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Input High Damp", "inputHighDamp", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Size", "size", 0.5f, 0.0f, 1.0f, kParameterIsAutomatable},
    {"Diffusion", "diffusion", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Decay", "decay", 0.7f, 0.1f, 0.9999f, kParameterIsAutomatable},
    {"Reverb Low Damp", "reverbLowDamp", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Reverb High Damp", "reverbHighDamp", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Modulation Speed", "modSpeed", 0.0f, 0.0f, 1.0f, kParameterIsAutomatable},
    {"Modulation Depth", "modDepth", 0.5f, 0.0f, 16.0f, kParameterIsAutomatable},
    {"Modulation Shape", "modShape", 0.5f, 0.0f, 1.0f, kParameterIsAutomatable},
    {"Freeze", "freeze", 0.0f, 0.0f, 1.0f, kParameterIsAutomatable | kParameterIsBoolean},
    {"Clear", "clearParam", 0.0f, 0.0f, 1.0f, kParameterIsAutomatable | kParameterIsTrigger},
    {"Tuned Mode", "tunedMode", 0.0f, 0.0f, 1.0f, kParameterIsAutomatable | kParameterIsBoolean},
    {"Diffuse Input", "diffuseInput", 1.0f, 0.0f, 1.0f, kParameterIsAutomatable | kParameterIsBoolean}
};
