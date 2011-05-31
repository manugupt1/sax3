#include <iostream>

#include "ui/UI.h"

int main(){

  UI::Dialog * dialog = new UI::Dialog();
  dialog = dialog->createDialog();
  
  UI::VLayout *vbox =  new VLayout();
  return 0;
}


