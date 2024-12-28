#include "SubWidget.hpp"
#include "Image.hpp"

START_NAMESPACE_DGL

template <class ImageType>
class StaticImageBase : public SubWidget
{
public:
    explicit StaticImageBase(Widget* parentWidget, const ImageType& image);
    ~StaticImageBase() override;

protected:
     void onDisplay() override;

private:
    struct PrivateData;
    PrivateData* const pData;
    
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StaticImageBase)
};

END_NAMESPACE_DGL