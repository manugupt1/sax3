#include <iostream>

#include "ui/UI.h"

int main(){

  UI::Dialog * dialog = new UI::Dialog();
  dialog = dialog->createDialog();
  
  UI::VLayout *vbox =  new UI::VLayout();
  vbox->createVLayout(dialog);

  UI::Label * label = new UI::Label();
  label->createLabel(vbox,"Hello");


  UI::HLayout * hbox = new UI::HLayout();
  hbox->createHLayout(vbox);

  UI::Label * label1 = new UI::Label();
  label->createLabel(hbox,"Buddy");
  UI::Label * label2 = new UI::Label();
  label->createLabel(hbox,"Buddy");

  UI::PushButton * button = new UI::PushButton();
  button->createButton(hbox,"&Banda");

  dialog->Event();
  return 0;
}




