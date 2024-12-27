#ifndef DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED
#define DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED

#include "DistrhoUI.hpp"
// #define DGL_CAIRO 1

#include "ImageWidgets.hpp"

#include "PlateauArtwork.cpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PlateauUI : public UI, public ImageKnob::Callback
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

    void onDisplay() override;

private:
    Image fImgBackground;
    Image fImgForeground;
    bool fRenderBackground; // Add this line

    ScopedPointer<ImageKnob> fKnobDecay;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlateauUI)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_PINGPONGPAN_HPP_INCLUDED