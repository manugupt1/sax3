#include <iostream>

#include "ui/yui.h"
#include "ui/yuifactory.h"

int main(){
	
	UI::YUIFactory * factory = new UI::YUIFactory();
	UI::yDialog * dialog = factory->createDialog(5,5);
	UI::yHLayout * layout = factory->createHLayout(dialog);
	UI::yLabel * label1 = factory->createLabel(layout,"Manu");
//	UI::yLabel * label2 = factory->createLabel(layout,"Gagan");

	//UI::yPushButton * button = factory->createPushButton(dialog,"Manu");
	UI::yImage * image = factory->createImage(dialog,"/usr/share/sax3/res/mouse.png");
	dialog->event();
	return 0;
}



