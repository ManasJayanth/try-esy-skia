#include "SkCanvas.h"
#include "SkFont.h"
#include "SkGradientShader.h"
#include "SkGraphics.h"
#include "SkSurface.h"
#include "SkSerialProcs.h"
#include "SkTextBlob.h"

void draw() {

    // SkImageInfo info = SkImageInfo::MakeN32Premul(3, 3);  // device aligned, 32 bpp, Premultiplied
    // const size_t minRowBytes = info.minRowBytes();  // bytes used by one bitmap row
    // const size_t size = info.computeMinByteSize();  // bytes used by all rows
    // SkAutoTMalloc<SkPMColor> storage(size);  // allocate storage for pixels
    // SkPMColor* pixels = storage.get();  // get pointer to allocated storage
    // // create a SkCanvas backed by a raster device, and delete it when the
    // // function goes out of scope.
    // std::unique_ptr<SkCanvas> canvas = SkCanvas::MakeRasterDirect(info, pixels, minRowBytes);
    // canvas->clear(SK_ColorWHITE);  // white is Unpremultiplied, in ARGB order
    // canvas->flush();  // ensure that pixels are cleared
    // SkPMColor pmWhite = pixels[0];  // the Premultiplied format may vary
    // SkPaint paint;  // by default, draws black
    // canvas->drawPoint(1, 1, paint);  // draw in the center
    // canvas->flush();  // ensure that point was drawn
    // for (int y = 0; y < info.height(); ++y) {
    //     for (int x = 0; x < info.width(); ++x) {
    //         SkDebugf("%c", *pixels++ == pmWhite ? '-' : 'x');
    //     }
    //     SkDebugf("\n");
    // }

    SkImageInfo info = SkImageInfo::Make(2, 2, kRGB_565_SkColorType, kOpaque_SkAlphaType);    
    // SkImageInfo info = SkImageInfo::MakeN32Premul(3, 3);
    const size_t size = info.computeMinByteSize();
    SkAutoTMalloc<SkPMColor> storage(size);
    SkPMColor* pixels = storage.get();

    int height = 300, width = 400;
    sk_sp<SkSurface> surface =
        SkSurface::MakeRasterN32Premul(width, height);
    
    // sk_sp<SkSurface> surface(SkSurface::MakeRasterDirect(info, pixels, info.minRowBytes()));
    SkCanvas* canvas = surface->getCanvas();




    SkFont blobFont;
    blobFont.setSize(24);
    sk_sp<SkTextBlob> blob = SkTextBlob::MakeFromText("Hello World", 11, blobFont);
    sk_sp<SkData> data = blob->serialize(SkSerialProcs());
    sk_sp<SkTextBlob> copy = SkTextBlob::Deserialize(data->data(), data->size(), SkDeserialProcs());

    canvas->clear(SK_ColorWHITE);
    canvas->drawTextBlob(copy, 20, 20, SkPaint());
    
    
    sk_sp<SkImage> image(surface->makeImageSnapshot());
    sk_sp<SkData> jpeg(image->encodeToData(SkEncodedImageFormat::kJPEG, 100));

    SkFILEWStream * s = new SkFILEWStream("hello.jpg");
    s->write(jpeg->data(), jpeg->size());
}

#include <iostream>

int main(int argc, char** argv) {
    draw();
    std::cout << "Hey" << std::endl;
    return 0;
}
