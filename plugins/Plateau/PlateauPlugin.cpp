#include "DistrhoPlugin.hpp"
#include "./dsp/Dattorro.cpp"

START_NAMESPACE_DISTRHO

class Plateau : public Plugin {
    public:
        Plateau();

    protected:
        const char *getLabel() const override;
        const char *getDescription() const override;
        const char *getMaker() const override;
        const char *getLicense() const override;
        uint32_t getVersion() const override;
        int64_t getUniqueId() const override;
        void initParameter(uint32_t index, Parameter& parameter) override;
        float getParameterValue(uint32_t index) const override;
        void setParameterValue(uint32_t index, float value) override;
        void run(const float **inputs, float **outputs, uint32_t frames) override;

    private:
        Dattorro reverb;

        float dry = 1.f;
        float wet = 0.5f;
        float preDelay = 0.f;
        float inputLowDamp = 10.f;
        float inputHighDamp = 10.f;
        float size = 0.5f;
        float diffusion = 10.f;
        float decay = 0.7f;
        float reverbLowDamp = 10.f;
        float reverbHighDamp = 10.f;
        float modSpeed = 0.0f;
        float modDepth = 0.5f;
        float modShape = 0.5f;

        float diffuseInput = 1.f;

        DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Plateau)
};

Plateau::Plateau() : Plugin(kParamCount, 0, 0) {}

const char *Plateau::getLabel() const { return "Plateau"; }

const char *Plateau::getDescription() const {
    return "A Clone of the Valley Audio Plateau Reverb by Dart Spark";
}

const char *Plateau::getMaker() const { return "Dale Johnson and Dart Spark"; }

const char *Plateau::getLicense() const { return "MIT"; }

uint32_t Plateau::getVersion() const { return d_version(1,0,0); }

int64_t Plateau::getUniqueId() const { return d_cconst('P', 'L', 'T', 'U'); }

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
    {"Input High Pass", "inputLowDamp", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Input Low Pass", "inputHighDamp", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Size", "size", 0.5f, 0.0f, 1.0f, kParameterIsAutomatable},
    {"Diffusion", "diffusion", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Decay", "decay", 0.7f, 0.1f, 0.9999f, kParameterIsAutomatable},
    {"Reverb High Pass", "reverbLowDamp", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Reverb Low Pass", "reverbHighDamp", 10.0f, 0.0f, 10.0f, kParameterIsAutomatable},
    {"Modulation Speed", "modSpeed", 0.0f, 0.0f, 1.0f, kParameterIsAutomatable},
    {"Modulation Depth", "modDepth", 0.5f, 0.0f, 16.0f, kParameterIsAutomatable},
    {"Modulation Shape", "modShape", 0.5f, 0.0f, 1.0f, kParameterIsAutomatable}
};

void Plateau::initParameter(uint32_t index, Parameter& parameter) {
    if (index < sizeof(parameterInfos) / sizeof(ParameterInfo)) {
        const ParameterInfo& info = parameterInfos[index];
        parameter.name = info.name;
        parameter.symbol = info.symbol;
        parameter.ranges.def = info.def;
        parameter.ranges.min = info.min;
        parameter.ranges.max = info.max;
        parameter.hints = info.hints;
    }
}

float Plateau::getParameterValue(uint32_t index) const {
    if (index < sizeof(parameterInfos) / sizeof(ParameterInfo)) {
        return *(&dry + index);
    }
    return 0.0f;
}

void Plateau::setParameterValue(uint32_t index, float value) {
    if (index < sizeof(parameterInfos) / sizeof(ParameterInfo)) {
        *(&dry + index) = value;
    }
}

void Plateau::run(const float **inputs, float **outputs, uint32_t frames) {
    const float *const inLeft = inputs[0];
    const float *const inRight = inputs[1];
    float *const outLeft = outputs[0];
    float *const outRight = outputs[1];

    reverb.setTimeScale(size);
    reverb.setPreDelay(preDelay);
    reverb.setInputFilterLowCutoffPitch(10.f-inputLowDamp);
    reverb.setInputFilterHighCutoffPitch(inputHighDamp);
    reverb.enableInputDiffusion(diffuseInput > 0.5f);
    reverb.setDecay(2.f*decay-decay*decay);
    reverb.setTankDiffusion(diffusion);
    reverb.setTankFilterLowCutFrequency(10.f-reverbLowDamp);
    reverb.setTankFilterHighCutFrequency(reverbHighDamp);
    reverb.setTankModSpeed(modSpeed*modSpeed*99.f+1.f);
    reverb.setTankModDepth(modDepth);
    reverb.setTankModShape(modShape);


    for (uint32_t i = 0; i < frames; ++i) {
        reverb.process((double)inLeft[i], (double)inRight[i]);
        outLeft[i] = inLeft[i] * dry + (float)reverb.getLeftOutput() * wet;
        outRight[i] = inRight[i] * dry + (float)reverb.getRightOutput() * wet;
    }
}

Plugin *createPlugin() { return new Plateau(); }

END_NAMESPACE_DISTRHO