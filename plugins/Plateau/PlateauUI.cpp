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
#include "Parameters.hpp"


START_NAMESPACE_DISTRHO

namespace Art = PlateauArtwork;

PlateauUI::PlateauUI()
    : UI(Art::backgroundWidth, Art::backgroundHeight, false),
      fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, kImageFormatBGR)
{
    Image medRoganImage(Art::medRoganData, Art::medRoganWidth, Art::medRoganHeight, kImageFormatBGRA);
    Image medSmallRoganImage(Art::medSmallRoganData, Art::medSmallRoganWidth, Art::medSmallRoganHeight, kImageFormatBGRA);
    Image smallRoganImage(Art::smallRoganData, Art::smallRoganWidth, Art::smallRoganHeight, kImageFormatBGRA);
    Image buttonOff(Art::buttonOffData, Art::buttonOffWidth, Art::buttonOffHeight, kImageFormatBGRA);
    Image buttonOn(Art::buttonOnData, Art::buttonOnWidth, Art::buttonOnHeight, kImageFormatBGRA);
    Image imgForeground(Art::foregroundData, Art::foregroundWidth, Art::foregroundHeight, kImageFormatBGRA);

    auto createKnob = [&](Parameters param, int x, int y, const Image& image) {
        ImageKnob* knob = new ImageKnob(this, image, ImageKnob::Vertical);
        knob->setId(param);
        knob->setAbsolutePos(x, y);
        knob->setRange(parameterInfos[param].min, parameterInfos[param].max);
        knob->setDefault(parameterInfos[param].def);
        knob->setRotationAngle(277);
        knob->setCallback(this);
        return knob;
    };

    fKnobPreDelay = createKnob(Parameters::kPreDelay, 140, 45, smallRoganImage);
    fKnobDry = createKnob(Parameters::kDry, 89, 109, medSmallRoganImage);
    fKnobWet = createKnob(Parameters::kWet, 180, 109, medSmallRoganImage);
    fKnobDecay = createKnob(Parameters::kDecay, 203, 298, medRoganImage);
    fKnobDiffusion = createKnob(Parameters::kDiffusion, 130, 317, medRoganImage);
    fKnobSize = createKnob(Parameters::kSize, 56, 298, medRoganImage);
    fKnobInputLowDamp = createKnob(Parameters::kInputLowDamp, 93, 198, medRoganImage);
    fKnobInputHighDamp = createKnob(Parameters::kInputHighDamp, 166, 198, medRoganImage);
    fKnobReverbLowDamp = createKnob(Parameters::kReverbLowDamp, 93, 417, medRoganImage);
    fKnobReverbHighDamp = createKnob(Parameters::kReverbHighDamp, 166, 417, medRoganImage);
    fKnobModShape = createKnob(Parameters::kModShape, 130, 543, medRoganImage);
    fKnobModSpeed = createKnob(Parameters::kModSpeed, 56, 518, medRoganImage);
    fKnobModDepth = createKnob(Parameters::kModDepth, 203, 518, medRoganImage);

    fFreezeButton = new ImageSwitch(this, buttonOff, buttonOn);
    fFreezeButton->setId(Parameters::kFreeze);
    fFreezeButton->setAbsolutePos(-24, 400);
    fFreezeButton->setCallback(this);

    fClearButton = new ImageSwitch(this, buttonOff, buttonOn);
    fClearButton->setId(Parameters::kClear);
    fClearButton->setAbsolutePos(238, 400);
    fClearButton->setCallback(this);

    fTunedModeButton = new ImageSwitch(this, buttonOff, buttonOn);
    fTunedModeButton->setId(Parameters::kTunedMode);
    fTunedModeButton->setAbsolutePos(-14, 184);
    fTunedModeButton->setCallback(this);


    fDiffuseInputButton = new ImageSwitch(this, buttonOff, buttonOn);
    fDiffuseInputButton->setId(Parameters::kDiffuseInput);
    fDiffuseInputButton->setAbsolutePos(228, 184);
    fDiffuseInputButton->setCallback(this);

    fImgForeground = new StaticImage(this, imgForeground);
}

void PlateauUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
        case Parameters::kDecay:
            fKnobDecay->setValue(value);
            break;
        case Parameters::kDiffusion:
            fKnobDiffusion->setValue(value);
            break;
        case Parameters::kSize:
            fKnobSize->setValue(value);
            break;
        case Parameters::kInputLowDamp:
            fKnobInputLowDamp->setValue(value);
            break;
        case Parameters::kInputHighDamp:
            fKnobInputHighDamp->setValue(value);
            break;
        case Parameters::kReverbLowDamp:
            fKnobReverbLowDamp->setValue(value);
            break;
        case Parameters::kReverbHighDamp:
            fKnobReverbHighDamp->setValue(value);
            break;
        case Parameters::kModShape:
            fKnobModShape->setValue(value);
            break;
        case Parameters::kModSpeed:
            fKnobModSpeed->setValue(value);
            break;
        case Parameters::kModDepth:
            fKnobModDepth->setValue(value);
            break;
        case Parameters::kDry:
            fKnobDry->setValue(value);
            break;
        case Parameters::kWet:
            fKnobWet->setValue(value);
            break;
        case Parameters::kPreDelay:
            fKnobPreDelay->setValue(value);
            break;
        case Parameters::kFreeze:
            fFreezeButton->setDown(value > 0.5f);
            break;
        case Parameters::kClear:
            fClearButton->setDown(value > 0.5f);
            break;
        case Parameters::kTunedMode:
            fTunedModeButton->setDown(value > 0.5f);
            break;
        case Parameters::kDiffuseInput:
            fDiffuseInputButton->setDown(value > 0.5f);
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

void PlateauUI::imageSwitchClicked(ImageSwitch* imageSwitch, bool down)
{
    setParameterValue(imageSwitch->getId(), down ? 1.0f : 0.0f);
}

void PlateauUI::onDisplay()
{
    const GraphicsContext& context(getGraphicsContext());

    fImgBackground.draw(context);
}

UI* createUI()
{
    return new PlateauUI();
}

END_NAMESPACE_DISTRHO