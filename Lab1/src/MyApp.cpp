

#include "MyApp.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include<boost/filesystem.hpp>
#include"boost/range/iterator_range.hpp"
#include<fstream>


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
    int loc_count = CalculateLocFilesCount();
    if (loc_count > 0)
    {        
        auto scoped_context = caller->LockJSContext();
        JSContextRef ctx = (*scoped_context);
        JSRetainPtr<JSStringRef> str = adopt(JSStringCreateWithUTF8CString("setLocalizationFiles"));
        JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

        if (JSValueIsObject(ctx, func))
        {
            JSObjectRef funcObj = JSValueToObject(ctx, func, 0);
            if (funcObj && JSObjectIsFunction(ctx, funcObj))
            {
                char** loc_files = new char* [loc_count];

                for (size_t i = 0; i < loc_count; i++)
                {
                    loc_files[i] = new char[1024];
                }

                GetLocalizationFiles(loc_files);
              
                JSRetainPtr<JSStringRef> json =
                    adopt(JSStringCreateWithUTF8CString(loc_files[0]));

                const JSValueRef args[] = { JSValueMakeString(ctx, json.get()) };
                
                // Count the number of arguments in the array.
                size_t num_args = sizeof(args) / sizeof(JSValueRef*);

                // Create a place to store an exception, if any
                JSValueRef exception = 0;

                // Call the ShowMessage() function with our list of arguments.
                JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0,
                    num_args, args,
                    &exception);

                if (exception) {
                    // Handle any exceptions thrown from function here.
                }

                if (result) {
                    // Handle result (if any) here.
                }

                for (size_t i = 0; i < loc_count; i++)
                {
                    delete[] loc_files[i];
                }
            }
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

    SetPathVariables();
}

void MyApp::SetPathVariables()
{
    std::exception error;

    std::unique_ptr<SLLCH> result = std::make_unique<SLLCH>();

    if (CalculatePathToSrc(__FILE__, "Lab1", "\\", 2, result.get(), error) != 0)
    {
        //Write to Log smth
    }

    _path_to_lab_folder = new char[result->length()];
    result->ToArray(_path_to_lab_folder, error);
    auto len = result->length();
    _path_to_assets = new char[len + strlen("\\assets") + 1];
    strcpy(_path_to_assets, _path_to_lab_folder);
    strcat(_path_to_assets, "\\assets");    
}

int MyApp::CalculateLocFilesCount()
{
    int count = 0;
    namespace fs = boost::filesystem;

    fs::path path_to_local(_path_to_assets);
    path_to_local.append("\\localization");
      
    for (auto& entry : boost::make_iterator_range(fs::directory_iterator(path_to_local), {}))
    {
        count++;
    }

    return count;
}

void MyApp::GetLocalizationFiles(char** jsons)
{
    namespace fs = boost::filesystem;

    fs::path path_to_local(_path_to_assets);
    path_to_local.append("\\localization");

    fs::directory_iterator iter{ path_to_local };
    fs::path path_to_file;
    int i = 0;
    for (auto& entry : boost::make_iterator_range(fs::directory_iterator(path_to_local), {}))
    {
        path_to_file = iter->path();
        std::ifstream inStr;
        inStr.open(path_to_file.c_str(), std::ifstream::in);                   
        inStr.getline(jsons[i], strlen(jsons[i]));        
        inStr.close();
        ++i;
    }
}

void MyApp::DeallocateInitFields()
{
    delete _juce_storage;
    delete[] _path_to_lab_folder;
    delete[] _path_to_assets;
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
    std::unique_ptr<SLLCH> word_temp = std::make_unique<SLLCH>();
    for (size_t i = 0; i < length; i++)
    {
        if (path[i] == *delim)
        {
            char* wordFroCompare = new char[word_temp->length() + 1];

            if (word_temp->addToEnd('\0', error) != 0)
            {
                delete[] wordFroCompare;                
                return FAILED;
            }

            if (word_temp->ToArray(wordFroCompare, error) != 0)
            {
                delete[] wordFroCompare;                
                return FAILED;
            }

            if (std::strcmp(wordFroCompare, stopWord) == 0)
            {
                if (result->addToEnd('\0', error) != 0)
                {
                    delete[] wordFroCompare;
                    return FAILED;
                }
                else
                {
                    delete[] wordFroCompare;
                    return SUCCESS;
                }
            }

            delete[] wordFroCompare;

            word_temp->clear(error);
        }
        else
            if (word_temp->addToEnd(path[i], error) != 0)
            {                
                return FAILED;
            }
        
        if (result->addToEnd(path[i], error) != 0)
        {
            return FAILED;
        }                              
    }
}
