#include <iostream>

#include "ui/yui.h"
#include "ui/yuifactory.h"

int main(){
	
	UI::YUIFactory * factory = new UI::YUIFactory();
	UI::yDialog * dialog = factory->createDialog(5,5);
	UI::yHLayout * layout = factory->createHLayout(dialog);
	return 0;
}



