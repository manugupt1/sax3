/*
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
*/
#include "UI.h"
namespace UI{


  //A Constructor Good for nothing dont know why I am using it 
  Dialog::Dialog(){
  }

  //Create A New Dialog Box - Class Dialog
  Dialog * Dialog::createDialog(){
    dialog = YUI::widgetFactory()->createPopupDialog();
    return this;
  }

  //Returns the main Dialog Box responsible for the wrapper - Class Dialog
  YDialog * Dialog::getElement()
  {
    return dialog;
  }

  //Event handling for Dialog Box - Class Dialog
  void Dialog::Event(){
    dialog->waitForEvent();
  }

  //Get Vertical Layout Box responsible for the wrapper - Class VLayout
  YLayoutBox * VLayout::getElement()
  {
    return vbox;
  }
  
  //Get Horizontal Layout Box responsible for the wrapper - Class HLayout
  YLayoutBox * HLayout::getElement()
  {
    return hbox;
  }
  
   //Creates a vertical Layout for a parent which can be either Dialog, VLayout or HLayout - Class VLayout
  void VLayout::createVLayout(Dialog * parent)
  {
    vbox = YUI::widgetFactory()->createVBox(parent->getElement());
  }

  void VLayout::createVLayout(VLayout * parent)
  {
    vbox = YUI::widgetFactory()->createVBox(parent->getElement());
  }

  void VLayout::createVLayout(HLayout * parent)
  {
    vbox = YUI::widgetFactory()->createVBox(parent->getElement());
  }


   //Creates a horizontal Layout for a parent which can be either Dialog, VLayout or HLayout - Class HLayout
  void HLayout::createHLayout(Dialog * parent)
  {
    hbox = YUI::widgetFactory()->createHBox(parent->getElement());
  }

  void HLayout::createHLayout(VLayout * parent)
  {
    hbox = YUI::widgetFactory()->createHBox(parent->getElement());
  }

  void HLayout::createHLayout(HLayout * parent)
  {
    hbox = YUI::widgetFactory()->createHBox(parent->getElement());
  }

 //Creates a Label for a parent which can be either a VLayout or HLayout - Class Label
  void Label::createLabel(VLayout * parent,string text)
  {
    label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
  }

  void Label::createLabel(HLayout* parent,string text)
  {
    label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
  }

  //Create a PushButton - Class Button

  void PushButton::createButton(VLayout * parent,string text){
    button = YUI::widgetFactory()->createPushButton(parent->getElement(),text);
  }
  void PushButton::createButton(HLayout * parent,string text){
    button = YUI::widgetFactory()->createPushButton(parent->getElement(),text);
  }
  
  //Create an Image for a parent which can be either a VLayour or  a HLayout - Class Image
  void Image::createImage(VLayout * parent,string path){
    image = YUI::widgetFactory()->createImage(parent->getElement(),path);
  }

  void Image::createImage(HLayout * parent,string path){
    image = YUI::widgetFactory()->createImage(parent->getElement(),path);
  }
}
