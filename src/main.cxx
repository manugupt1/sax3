#include <iostream>

#include "ui/UI.h"

int main(){

  UI::Dialog * dialog = new UI::Dialog();
  dialog = dialog->createDialog();
  
  UI::VLayout *vbox =  new UI::VLayout();
  vbox->createVLayout(dialog);

  UI::Label * label = new UI::Label();
  label->createLabel(vbox,"Hello");
  dialog->Event();
  return 0;
}


