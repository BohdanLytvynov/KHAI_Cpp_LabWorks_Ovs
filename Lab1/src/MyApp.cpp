

#include "MyApp.h"
#include <JavaScriptCore/JSRetainPtr.h>



#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 400

MyApp::MyApp() {
  ///
  /// Create our main App instance.
  ///
  app_ = App::Create();

  ///
  /// Create a resizable window by passing by OR'ing our window flags with
  /// kWindowFlags_Resizable.
  ///
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
    false, kWindowFlags_Titled | kWindowFlags_Resizable);

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

  ///
  /// Force a call to OnResize to perform size/layout of our overlay.
  ///
  OnResize(window_.get(), window_->width(), window_->height());

  ///
  /// Load a page into our overlay's View
  ///
  overlay_->view()->LoadURL("file:///html/app.html");

  ///
  /// Register our MyApp instance as an AppListener so we can handle the
  /// App's OnUpdate event below.
  ///
  app_->set_listener(this);

  ///
  /// Register our MyApp instance as a WindowListener so we can handle the
  /// Window's OnResize event below.
  ///
  window_->set_listener(this);

  ///
  /// Register our MyApp instance as a LoadListener so we can handle the
  /// View's OnFinishLoading and OnDOMReady events below.
  ///
  overlay_->view()->set_load_listener(this);

  ///
  /// Register our MyApp instance as a ViewListener so we can handle the
  /// View's OnChangeCursor and OnChangeTitle events below.
  ///
  overlay_->view()->set_view_listener(this);

  //Allocate initial fields with values
  AllocateInitFields();
}

MyApp::~MyApp() {
    DeallocateInitFields();
}

void MyApp::Run() {
  app_->Run();
}

void MyApp::OnUpdate() {
  ///
  /// This is called repeatedly from the application's update loop.
  ///
  /// You should update any app logic here.
  ///
}

void MyApp::OnClose(ultralight::Window* window) {
  app_->Quit();
}

void MyApp::OnResize(ultralight::Window* window, uint32_t width, uint32_t height) {
  ///
  /// This is called whenever the window changes size (values in pixels).
  ///
  /// We resize our overlay here to take up the entire window.
  ///
  overlay_->Resize(width, height);
}

void MyApp::OnFinishLoading(ultralight::View* caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String& url) {
  ///
  /// This is called when a frame finishes loading on the page.
  ///
}

void MyApp::OnDOMReady(ultralight::View* caller,
                       uint64_t frame_id,
                       bool is_main_frame,
                       const String& url) {
  ///
  /// This is called when a frame's DOM has finished loading on the page.
  ///
  /// This is the best time to setup any JavaScript bindings.
  ///
    auto scoped_context = caller->LockJSContext();
    JSContextRef ctx = (*scoped_context);
    JSRetainPtr<JSStringRef> str = adopt(JSStringCreateWithUTF8CString("setLocalizationFiles"));
    JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

    if (JSValueIsObject(ctx, func))
    {
        JSObjectRef funcObj = JSValueToObject(ctx, func, 0);
        if (funcObj && JSObjectIsFunction(ctx, funcObj))
        {
            //Get all json files


            JSRetainPtr<JSStringRef> msg =
                adopt(JSStringCreateWithUTF8CString("Howdy!"));
        }
    }

}

void MyApp::OnChangeCursor(ultralight::View* caller,
                           Cursor cursor) {
  ///
  /// This is called whenever the page requests to change the cursor.
  ///
  /// We update the main window's cursor here.
  ///
  window_->SetCursor(cursor);
}

void MyApp::OnChangeTitle(ultralight::View* caller,
                          const String& title) {
  ///
  /// This is called whenever the page requests to change the title.
  ///
  /// We update the main window's title here.
  ///
  window_->SetTitle(title.utf8().data());
}

void MyApp::AllocateInitFields()
{
    MyApp::_juce_storage = new ds::linear_ds::single_linked_list<Juce>();
    MyApp::_path_to_localization;

    std::exception error;

    SLLCHPtr result = new SLLCH;

    if (CalculatePathToSrc(__FILE__, "Lab1", "\\", 2, result, error) != 0)
    {
        delete result;
    }

    char* calcPathToLab = new char[result->length()];
    result->ToArray(calcPathToLab, error);

    auto len = strlen(calcPathToLab);

   
}

void MyApp::DeallocateInitFields()
{
    delete _juce_storage;
}

int MyApp::CalculatePathToSrc(
    const char* path, 
    const char* stopWord, 
    const char* delim, 
    unsigned char delimCount, 
    SLLCHPtr result,
    std::exception& error)
{
    if (path == nullptr)
        throw std::exception("Path pointer was nullptr!");

    if (stopWord == nullptr)
        throw std::exception("stopWord parameter was nullptr!");

    if (delim == nullptr)
        throw std::exception("delim parameter was nullptr!");

    if (result == nullptr)
        throw std::exception("result parameter was nullptr!");
   
    size_t length = std::strlen(path);
    unsigned char delimCountTemp = 0;
    SLLCHPtr word_temp = new SLLCH;
    for (size_t i = 0; i < length; i++)
    {
        if (path[i] == *delim)
        {
            char* wordFroCompare = new char[word_temp->length() + 1];

            if (word_temp->addToEnd('\0', error) != 0)
            {
                delete wordFroCompare;
                delete word_temp;
                return FAILED;
            }

            if (word_temp->ToArray(wordFroCompare, error) != 0)
            {
                delete wordFroCompare;
                delete word_temp;
                return FAILED;
            }

            if (std::strcmp(wordFroCompare, stopWord) == 0)
            {
                if (result->addToEnd('\0', error) != 0)
                {
                    delete wordFroCompare;
                    return FAILED;
                }
                else
                {
                    delete wordFroCompare;
                    return SUCCESS;
                }
            }

            delete wordFroCompare;

            word_temp->clear(error);
        }
        else
            if (word_temp->addToEnd(path[i], error) != 0)
            {
                delete word_temp;
                return FAILED;
            }
        
        if (result->addToEnd(path[i], error) != 0)
        {
            return FAILED;
        }                              
    }
}
