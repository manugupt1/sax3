#include "YUI.h"
namespace UI{


  //A Constructor Good for nothing dont know why I am using it 
  Dialog::Dialog(){
  }

  //Create A New Dialog Box - Class Dialog

  YUIDialog::YUIDialog(){
  }

  YUIDialog * YUIDialog::createDialog(int x,int y){
    dialog = YUI::widgetFactory()->createPopupDialog();
    alignment = YUI::widgetFactory()->createMinSize(dialog,x,y);
    return this;
  }

  

  //Returns the main Dialog Box responsible for the wrapper - Class Dialog
  YAlignment * YUIDialog::getElement()
  {
    return alignment;
  }

  //Event handling for Dialog Box - Class Dialog
  void YUIDialog::Event(){
    dialog->waitForEvent();
  }

  //Get Vertical Layout Box responsible for the wrapper - Class VLayout
  YLayoutBox * YUIVLayout::getElement()
  {
    return vbox;
  }
  
  //Get Horizontal Layout Box responsible for the wrapper - Class HLayout
  YLayoutBox * YUIHLayout::getElement()
  {
    return hbox;
  }
  
   //Creates a vertical Layout for a parent which can be either Dialog, VLayout or HLayout - Class VLayout
  void YUIVLayout::createVLayout(YUIDialog * parent)
  {
    vbox = YUI::widgetFactory()->createVBox(parent->getElement());
  }

  void YUIVLayout::createVLayout(YUIVLayout * parent)
  {
    vbox = YUI::widgetFactory()->createVBox(parent->getElement());
  }

  void YUIVLayout::createVLayout(YUIHLayout * parent)
  {
    vbox = YUI::widgetFactory()->createVBox(parent->getElement());
  }


   //Creates a horizontal Layout for a parent which can be either Dialog, VLayout or HLayout - Class HLayout
  void YUIHLayout::createHLayout(YUIDialog * parent)
  {
    hbox = YUI::widgetFactory()->createHBox(parent->getElement());
  }

  void YUIHLayout::createHLayout(YUIVLayout * parent)
  {
    hbox = YUI::widgetFactory()->createHBox(parent->getElement());
  }

  void YUIHLayout::createHLayout(YUIHLayout * parent)
  {
    hbox = YUI::widgetFactory()->createHBox(parent->getElement());
  }

 //Creates a Label for a parent which can be either a VLayout or HLayout - Class Label
  void YUILabel::createLabel(YUIVLayout * parent,string text)
  {
    label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
  }

  void YUILabel::createLabel(YUIHLayout* parent,string text)
  {
    label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
  }

  //Create a PushButton - Class Button

  void YUIPushButton::createButton(YUIVLayout * parent,string text){
    button = YUI::widgetFactory()->createPushButton(parent->getElement(),text);
  }
  void YUIPushButton::createButton(YUIHLayout * parent,string text){
    button = YUI::widgetFactory()->createPushButton(parent->getElement(),text);
  }
  
  //Create an Image for a parent which can be either a VLayour or  a HLayout - Class Image
  void YUIImage::createImage(YUIVLayout * parent,string path){
    image = YUI::widgetFactory()->createImage(parent->getElement(),path);
  }

  void YUIImage::createImage(YUIHLayout * parent,string path){
    image = YUI::widgetFactory()->createImage(parent->getElement(),path);
  }

  //Create Vertical Spacing --- Class VSpacing
  void YUIVSpacing::createVSpacing(YUIVLayout * parent,int dim){
    VSpace = YUI::widgetFactory()->createVSpacing(parent->getElement(),dim);
  }

  void YUIVSpacing::createVSpacing(YUIHLayout * parent, int dim){
    VSpace = YUI::widgetFactory()->createVSpacing(parent->getElement(),dim);
  }

  void YUIVSpacing::createVSpacing(YUIDialog * parent,int dim){
    VSpace = YUI::widgetFactory()->createVSpacing(parent->getElement(),dim);
  }

  
  //Create Horizontal Spacing --- Class HSpacing
  void YUIHSpacing::createHSpacing(YUIVLayout * parent,int dim){
    HSpace = YUI::widgetFactory()->createHSpacing(parent->getElement(),dim);
  }

  void YUIHSpacing::createHSpacing(YUIHLayout * parent, int dim){
    HSpace = YUI::widgetFactory()->createHSpacing(parent->getElement(),dim);
  }

  void YUIHSpacing::createHSpacing(YUIDialog * parent,int dim){
    HSpace = YUI::widgetFactory()->createHSpacing(parent->getElement(),dim);
  }

  
}
