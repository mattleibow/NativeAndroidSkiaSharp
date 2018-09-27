#include <jni.h>
#include <string>

#include "GrContext.h"
#include "GrBackendSurface.h"
#include "gl/GrGLInterface.h"
#include "gl/GrGLAssembleInterface.h"
#include "SkSurface.h"
#include "SkPaint.h"
#include "SkCanvas.h"

//#include "gr_context.h"
//#include "sk_surface.h"
//#include "sk_paint.h"
//#include "sk_canvas.h"

extern "C" JNIEXPORT
void JNICALL Java_com_example_matthew_myapplication_MainActivity_renderFrame(JNIEnv *env, jobject /* this */, jint width, jint height)
{
    auto gli = GrGLMakeNativeInterface();
    auto context = GrContext::MakeGL(gli);

    GrGLFramebufferInfo info;
    info.fFBOID = 0;
    info.fFormat = 0x8058; // RGBA8
    auto brt = new GrBackendRenderTarget(width, height, 0, 8, info);

    auto surface = SkSurface::MakeFromBackendRenderTarget(
            context.get(), *brt,
            GrSurfaceOrigin::kBottomLeft_GrSurfaceOrigin,
            SkColorType::kRGBA_8888_SkColorType,
            nullptr, nullptr);

    auto canvas = surface->getCanvas();
    canvas->clear(SK_ColorRED);

    auto paint = new SkPaint();

    //canvas->drawText("SkiaSharp", 9, 100, 100, *paint);

    canvas->drawRect(SkRect::MakeXYWH(20, 20, 200, 200), *paint);

    canvas->flush();
    context->flush();

    delete paint;
    delete brt;
}



//    auto gli = gr_glinterface_create_native_interface();
//    auto context = gr_context_make_gl(gli);
//
//    gr_gl_framebufferinfo_t info;
//    info.fFBOID = 0;
//    info.fFormat = 0x8058;
//    auto brt = gr_backendrendertarget_new_gl(width, height, 0, 8, &info);
//
//    auto surface = sk_surface_new_backend_render_target(context, brt, BOTTOM_LEFT_GR_SURFACE_ORIGIN, RGBA_8888_SK_COLORTYPE, nullptr, nullptr);
//
//    auto canvas = sk_surface_get_canvas(surface);
//
//    auto paint = sk_paint_new();
//
//    sk_canvas_draw_text(canvas, "SkiaSharp", 9, 100, 100, paint);
//
//    sk_paint_delete(paint);
//
//    sk_canvas_flush(canvas);
//    gr_context_flush(context);
//
//    sk_surface_unref(surface);
//
//    gr_backendrendertarget_delete(brt);
//
//    gr_context_unref(context);
//    gr_glinterface_unref(gli);