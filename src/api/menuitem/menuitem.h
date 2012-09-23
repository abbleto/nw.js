// Copyright (c) 2012 Intel Corp
// Copyright (c) 2012 The Chromium Authors
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell co
// pies of the Software, and to permit persons to whom the Software is furnished
//  to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in al
// l copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM
// PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNES
// S FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
//  OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WH
// ETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef CONTENT_NW_SRC_API_MENUITEM_MENUITEM_H_
#define CONTENT_NW_SRC_API_MENUITEM_MENUITEM_H_ 

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "third_party/node/src/node.h"

#include <string>

#if defined(OS_MACOSX)
#if __OBJC__
@class NSMenuItem;
@class MenuItemDelegate;
#else
class NSMenuItem;
class MenuItemDelegate;
#endif  // __OBJC__
#elif defined(TOOLKIT_GTK)
class GtkMenuItem;
#elif defined(OS_WIN)
#include <windows.h>
#endif  // defined(OS_MACOSX)

namespace api {

class Menu;

class MenuItem : node::ObjectWrap {
 public:
  // Install MenuItem into an object
  static void Init(v8::Handle<v8::Object> target);

  // Call OnClick from UI thread
  void OnClickFromUI();
  // Call click callback in renderer thread
  void OnClick();

  // Different types of menu items
  enum MenuItemType {
    NORMAL,
    CHECKBOX,
    SEPARATOR
  };

 private:
  friend class Menu;

  // The menu item create properties
  struct CreationOption {
    CreationOption();

    std::string label;
    std::string icon;
    std::string tooltip;
    MenuItemType type;
    bool enabled;
    bool checked;
  };

  MenuItem(CreationOption options);
  virtual ~MenuItem();

  void SetLabel(const std::string& label);
  std::string GetLabel();
  void SetIcon(const std::string& icon);
  void SetTooltip(const std::string& tooltip);
  std::string GetTooltip();
  void SetEnabled(bool enabled);
  bool GetEnabled();
  void SetChecked(bool checked);
  bool GetChecked();
  void SetSubmenu(Menu* sub_menu);

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> PropertyGetter(v8::Local<v8::String> property,
                                              const v8::AccessorInfo& info);
  static void PropertySetter(v8::Local<v8::String> property,
                             v8::Local<v8::Value> value,
                             const v8::AccessorInfo& info);

  static v8::Persistent<v8::Function> constructor_;

  CreationOption option_;
  struct uv_async_s click_event_;

#if defined(OS_MACOSX)
  __block NSMenuItem* menu_item_;
  __block MenuItemDelegate* delegate_;
#elif defined(TOOLKIT_GTK)
  GtkMenuItem* menu_item_;
#elif defined(OS_WIN)

#endif

  DISALLOW_COPY_AND_ASSIGN(MenuItem);
};

}  // namespace api

#endif  // CONTENT_NW_SRC_API_MENUITEM_MENUITEM_H_
