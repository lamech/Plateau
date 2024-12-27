/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2021 Filipe Coelho <falktx@falktx.com>
 * Copyright (C) 2019-2021 Jean Pierre Cimalando <jp-dev@inbox.ru>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "PlateauUI.hpp"


START_NAMESPACE_DISTRHO

namespace Art = PlateauArtwork;

PlateauUI::PlateauUI()
    : UI(Art::backgroundWidth, Art::backgroundHeight, true),
      fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, kImageFormatBGR), fImgForeground(Art::foregroundData, Art::foregroundWidth, Art::foregroundHeight, kImageFormatBGRA),
      fRenderBackground(true) // Initialize the boolean
{
    Image medRoganImage(Art::medRoganData, Art::medRoganWidth, Art::medRoganHeight, kImageFormatBGRA);
    Image medRoganFGImage(Art::medRoganData, Art::medRoganWidth, Art::medRoganHeight, kImageFormatBGRA);

    fKnobDecay = new ImageKnob(this, medRoganImage, ImageKnob::Vertical);
    fKnobDecay->setId(7);
    fKnobDecay->setAbsolutePos(203, 298);
    fKnobDecay->setRange(0.1f, 0.9999f);
    fKnobDecay->setDefault(0.7f);
    fKnobDecay->setRotationAngle(277);
    fKnobDecay->setCallback(this);
};

void PlateauUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
        case Parameters::kDecay:
            fKnobDecay->setValue(value);
            break;
    }
}

void PlateauUI::imageKnobDragStarted(ImageKnob* knob)
{
    editParameter(knob->getId(), true);
}

void PlateauUI::imageKnobDragFinished(ImageKnob* knob)
{
    editParameter(knob->getId(), false);
}

void PlateauUI::imageKnobValueChanged(ImageKnob* knob, float value)
{
    setParameterValue(knob->getId(), value);
}

void PlateauUI::onDisplay()
{
    const GraphicsContext& context(getGraphicsContext());

    if (fRenderBackground) {
        fImgBackground.draw(context);
    }
    fRenderBackground = !fRenderBackground; // Toggle the boolean
}

UI* createUI()
{
    return new PlateauUI();
}

END_NAMESPACE_DISTRHO
