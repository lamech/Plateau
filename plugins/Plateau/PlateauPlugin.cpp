#include "DistrhoPlugin.hpp"
#include "./dsp/Dattorro.cpp"
#include "./dsp/LinearEnvelope.cpp"
#include "Parameters.hpp"

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
        LinearEnvelope envelope;

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

        float freeze = 0.f;
        float clearParam = 0.f;
        float tunedMode = 0.f;
        float diffuseInput = 1.f;

        bool clear = false;
        bool cleared = true;
        bool fadeOut = false;
        bool fadeIn = false;
        
        bool frozen = false;

        void updateReverbParameter(uint32_t index);

        DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Plateau)
};

Plateau::Plateau() : Plugin(kParamCount, 0, 0) {
    reverb.setSampleRate(getSampleRate());
    envelope.setSampleRate(getSampleRate());
    envelope.setTime(0.004f);
    envelope._value = 1.f;
}

const char *Plateau::getLabel() const { return "Plateau"; }

const char *Plateau::getDescription() const {
    return "A Clone of the Valley Audio Plateau Reverb by Dart Spark";
}

const char *Plateau::getMaker() const { return "Dale Johnson and Dart Spark"; }

const char *Plateau::getLicense() const { return "MIT"; }

uint32_t Plateau::getVersion() const { return d_version(1,0,0); }

int64_t Plateau::getUniqueId() const { return d_cconst('P', 'L', 'T', 'U'); }

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
    for (uint32_t i = 0; i < kParamCount; ++i) {
        updateReverbParameter(i);
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
        updateReverbParameter(index);
    }
}

void Plateau::updateReverbParameter(uint32_t index) {
    switch (index) {
        case kPreDelay:
            reverb.setPreDelay(preDelay);
            break;
        case kInputLowDamp:
            reverb.setInputFilterLowCutoffPitch(10.f - inputLowDamp);
            break;
        case kInputHighDamp:
            reverb.setInputFilterHighCutoffPitch(inputHighDamp);
            break;
        case kSize:
        case kTunedMode:
            if (tunedMode > 0.5f) {
                reverb.setTimeScale(0.0025f * powf(2.f, size * 5.f));
            } else {
                reverb.setTimeScale(scale(size*size, 0.f, 1.f, 0.01f, 4.0f));
            }
            break;
        case kDiffusion:
            reverb.setTankDiffusion(diffusion);
            break;
        case kDecay:
            reverb.setDecay(2.f * decay - decay * decay);
            break;
        case kReverbLowDamp:
            reverb.setTankFilterLowCutFrequency(10.f - reverbLowDamp);
            break;
        case kReverbHighDamp:
            reverb.setTankFilterHighCutFrequency(reverbHighDamp);
            break;
        case kModSpeed:
            reverb.setTankModSpeed(modSpeed * modSpeed * 99.f + 1.f);
            break;
        case kModDepth:
            reverb.setTankModDepth(modDepth);
            break;
        case kModShape:
            reverb.setTankModShape(modShape);
            break;
        case kDiffuseInput:
            reverb.enableInputDiffusion(diffuseInput > 0.5f);
            break;
    }
}

void Plateau::run(const float **inputs, float **outputs, uint32_t frames) {
    const float *const inLeft = inputs[0];
    const float *const inRight = inputs[1];
    float *const outLeft = outputs[0];
    float *const outRight = outputs[1];

    for (uint32_t i = 0; i < frames; ++i) {
        if(clearParam > 0.5f && !clear && cleared) {
            cleared = false;
            clear = true;
        }
        else if(clearParam <= 0.5f && cleared) {
            clear = false;
        }

        if(clear) {
            if(!cleared && !fadeOut && !fadeIn) {
                fadeOut = true;
                envelope.setStartEndPoints(1.f, 0.f);
                envelope.trigger();
            }
            if(fadeOut && envelope._justFinished) {
                reverb.clear();
                fadeOut = false;
                fadeIn = true;
                envelope.setStartEndPoints(0.f, 1.f);
                envelope.trigger();
            }
            if(fadeIn && envelope._justFinished) {
                fadeIn = false;
                cleared = true;
                envelope._value = 1.f;
            }
        }
        envelope.process();

        if(freeze>0.5f && !frozen) {
            frozen = true;
            reverb.freeze(frozen);
        }
        else if(freeze<=0.5f && frozen){
            frozen = false;
            reverb.freeze(frozen);
        }

        reverb.process((double)(inLeft[i] * envelope._value), (double)(inRight[i] * envelope._value));
        outLeft[i] = inLeft[i] * dry + (float)reverb.getLeftOutput() * wet;
        outRight[i] = inRight[i] * dry + (float)reverb.getRightOutput() * wet;
    }
}

Plugin *createPlugin() { return new Plateau(); }

END_NAMESPACE_DISTRHO