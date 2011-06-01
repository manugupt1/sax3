#include <iostream>

#include "ui/UI.h"

int main(){

  UI::Dialog * dialog = new UI::Dialog();
  dialog = dialog->createDialog();
  

  UI::VLayout * vbox = new UI::VLayout();
  vbox->createVLayout(dialog);


  //Monitor
  UI::HLayout * hboxMonitor = new UI::HLayout();
  hboxMonitor->createHLayout(vbox);
  
  UI::Image * imageMonitor = new UI::Image();
  imageMonitor->createImage(hboxMonitor,"/usr/share/sax3/res/monitor.png");

  UI::PushButton * buttonMonitor = new UI::PushButton();
  buttonMonitor->createButton(hboxMonitor,"Monitor");

  //Keyboard
  UI::HLayout * hboxKeyboard = new UI::HLayout();
  hboxKeyboard->createHLayout(vbox);

  UI::Image * imageKeyboard = new UI::Image();
  imageKeyboard->createImage(hboxKeyboard,"/usr/share/sax3/res/keyboard.png");

  UI::PushButton * buttonKeyboard = new UI::PushButton();
  buttonKeyboard->createButton(hboxKeyboard,"Keyboard");

  //Mouse
  UI::HLayout * hboxMouse = new UI::HLayout();
  hboxMouse->createHLayout(vbox);

  UI::Image * imageMouse = new UI::Image();
  imageMouse->createImage(hboxMouse,"/usr/share/sax3/res/mouse.png");

  UI::PushButton * buttonMouse = new UI::PushButton();
  buttonMouse->createButton(hboxMouse,"Mouse");

  //Touch Pad
  UI::HLayout * hboxTouchPad = new UI::HLayout();
  hboxTouchPad->createHLayout(vbox);
  
  UI::Image * imageTouchPad = new UI::Image();
  imageTouchPad->createImage(hboxTouchPad,"/usr/share/sax3/res/touchpad.png");

  UI::PushButton * buttonTouchPad = new UI::PushButton();
  buttonTouchPad->createButton(hboxTouchPad,"Touch Pad");


  dialog->Event();
  return 0;
}




