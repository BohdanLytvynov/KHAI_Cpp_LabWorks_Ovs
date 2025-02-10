
#ifndef MYAPP_H

#define MYAPP_H

#include <AppCore/AppCore.h>
#include"Juce.h"
#include"data_structures/data_structures.h"

using namespace ultralight;

typedef ds::linear_ds::single_linked_list<char>* SLLCHPtr;
typedef ds::linear_ds::single_linked_list<char> SLLCH;

class MyApp : public AppListener,
    public WindowListener,
    public LoadListener,
    public ViewListener {
public:
    MyApp();

    virtual ~MyApp();

    // Start the run loop.
    virtual void Run();

    // This is called continuously from the app's main loop.
    virtual void OnUpdate() override;

    // This is called when the window is closing.
    virtual void OnClose(ultralight::Window* window) override;

    // This is called whenever the window resizes.
    virtual void OnResize(ultralight::Window* window, uint32_t width, uint32_t height) override;

    // This is called when the page finishes a load in one of its frames.
    virtual void OnFinishLoading(ultralight::View* caller,
        uint64_t frame_id,
        bool is_main_frame,
        const String& url) override;

    // This is called when the DOM has loaded in one of its frames.
    virtual void OnDOMReady(ultralight::View* caller,
        uint64_t frame_id,
        bool is_main_frame,
        const String& url) override;

    // This is called when the page requests to change the Cursor.
    virtual void OnChangeCursor(ultralight::View* caller,
        Cursor cursor) override;

    virtual void OnChangeTitle(ultralight::View* caller,
        const String& title) override;

protected:
    RefPtr<App> app_;
    RefPtr<Window> window_;
    RefPtr<Overlay> overlay_;
private:
    ds::linear_ds::single_linked_list<Juce>* _juce_storage;
    const char* _path_to_localization;

    void AllocateInitFields();
    void DeallocateInitFields();
    int CalculatePathToSrc(const char* path, const char* stopWord, const char* delim, unsigned char delimCount, SLLCHPtr result, std::exception& error);
};

#endif


