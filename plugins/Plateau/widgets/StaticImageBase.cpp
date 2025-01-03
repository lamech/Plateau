#include "StaticImageBase.hpp"

START_NAMESPACE_DGL
template <class ImageType>
struct StaticImageBase<ImageType>::PrivateData  {
    ImageType image;

    PrivateData(const ImageType& image)
        : image(image) {}

    DISTRHO_DECLARE_NON_COPYABLE(PrivateData)
};

// --------------------------------------------------------------------------------------------------------------------

template <class ImageType>
StaticImageBase<ImageType>::StaticImageBase(Widget* const parentWidget, const ImageType& image)
    : SubWidget(parentWidget),
      pData(new PrivateData(image))
{
    setSize(image.getSize());
}

template <class ImageType>
StaticImageBase<ImageType>::~StaticImageBase()
{
    delete pData;
}

template <class ImageType>
void StaticImageBase<ImageType>::onDisplay()
{
    const GraphicsContext& context(getGraphicsContext());
    pData->image.draw(context);
}

template class StaticImageBase<OpenGLImage>;

END_NAMESPACE_DGL