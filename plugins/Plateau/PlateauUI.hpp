#ifndef DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED
#define DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED

#include "DistrhoUI.hpp"
// #define DGL_CAIRO 1

#include "ImageWidgets.hpp"
#include "widgets/StaticImage.hpp"

#include "PlateauArtwork.cpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PlateauUI : public UI, public ImageKnob::Callback, public ImageSwitch::Callback
{
public:
    PlateauUI();

protected:
    // -------------------------------------------------------------------
    // DSP Callbacks

    void parameterChanged(uint32_t index, float value) override;

    // -------------------------------------------------------------------
    // Widget Callbacks

    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;

    void imageSwitchClicked(ImageSwitch* imageSwitch, bool down) override;

    void onDisplay() override;

private:
    Image fImgBackground;

    ScopedPointer<ImageKnob> fKnobPreDelay;
    ScopedPointer<ImageKnob> fKnobDry;
    ScopedPointer<ImageKnob> fKnobWet;
    ScopedPointer<ImageKnob> fKnobInputLowDamp;
    ScopedPointer<ImageKnob> fKnobInputHighDamp;
    ScopedPointer<ImageKnob> fKnobSize;
    ScopedPointer<ImageKnob> fKnobDiffusion;
    ScopedPointer<ImageKnob> fKnobDecay;
    ScopedPointer<ImageKnob> fKnobReverbLowDamp;
    ScopedPointer<ImageKnob> fKnobReverbHighDamp;
    ScopedPointer<ImageKnob> fKnobModSpeed;
    ScopedPointer<ImageKnob> fKnobModDepth;
    ScopedPointer<ImageKnob> fKnobModShape;

    ScopedPointer<ImageSwitch> fFreezeButton;
    ScopedPointer<ImageSwitch> fClearButton;
    ScopedPointer<ImageSwitch> fTunedModeButton;
    ScopedPointer<ImageSwitch> fDiffuseInputButton;
    
    ScopedPointer<StaticImage> fImgForeground;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlateauUI)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED