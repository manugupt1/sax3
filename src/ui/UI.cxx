#define YUILogComponent "SaX3-UI-Lib-Log"
#include "YUILog.h"
#include "YUI.h"
#include "YWidgetFactory.h"
#include "YLayoutBox.h"
#include "YDialog.h"
#include "YEvent.h"
#include "YPushButton.h"
#include "YLabel.h"
#include "YWidget.h"
#include "UI.h"
namespace UI{


  Dialog * Dialog::createDialog(){
    dialog = YUI::widgetFactory()->createPopupDialog();
    return this;
    
  }


  Dialog::Dialog(){
    /* createDialog();
    VLayout * vbox = new VLayout()->createVLayout(dialog);
    //  YUI::widgetFactory()->createLabel(vbox,"Hello World!!");
    dialog->waitForEvent();
    dialog->destroy();*/
  }
  
  YDialog * Dialog::getElement()
  {
    return dialog;
  }
 
  YLayoutBox * VLayout::getElement()
  {
    return vbox;
  }
  
  YLayoutBox * HLayout::getElement()
  {
    return hbox;
  }
  
  void VLayout::createVLayout(Dialog * parent)
  {
    vbox = YUI::widgetFactory()->createVBox(parent->getElement());
  }

  void Label::createLabel(VLayout * parent,string text)
  {
    label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
  }

  void Label::createLabel(HLayout* parent,string text)
  {
    label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
  }
  
  

}
