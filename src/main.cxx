#include <iostream>

#include "ui/yui.h"
#include "ui/yuifactory.h"

int main(){
	
	UI::YUIFactory * factory = new UI::YUIFactory();
	UI::yDialog * dialog = factory->createDialog(30,10);

	UI::yVLayout * mainLayout = factory->createVLayout(dialog);

	UI::yLabel * label1 = factory->createLabel(mainLayout,"SaX3 Control Center");

	UI::yHLayout * KeyBoardLayout = factory->createHLayout(mainLayout);
	UI::yImage * KeyBoardImage = factory->createImage(KeyBoardLayout,"/usr/share/sax3/res/keyboard.png");
	UI::yPushButton * KeyBoardButton = factory->createPushButton(KeyBoardLayout,"&Key Board");
	
	UI::yHLayout * MouseLayout = factory->createHLayout(mainLayout);
	UI::yImage * MouseImage = factory->createImage(MouseLayout,"/usr/share/sax3/res/mouse.png");
	UI::yPushButton * MouseButton = factory->createPushButton(MouseLayout,"&Mouse");

	UI::yHLayout * MonitorLayout = factory->createHLayout(mainLayout);
	UI::yImage * MonitorImage = factory->createImage(MonitorLayout,"/usr/share/sax3/res/monitor.png");
	UI::yPushButton * MonitorButton = factory->createPushButton(MonitorLayout,"Mo&nitor");

	UI::yHLayout * TouchPadLayout = factory->createHLayout(mainLayout);
	UI::yImage * TouchPadImage = factory->createImage(TouchPadLayout,"/usr/share/sax3/res/touchpad.png");
	UI::yPushButton * TouchPadButton = factory->createPushButton(TouchPadLayout,"&Touch Pad");

	dialog->event();
	return 0;
}



