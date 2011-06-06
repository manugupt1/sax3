#include <iostream>

#include<locale.h>
#include<libintl.h>

#include "ui/yui.h"
#include "ui/yuifactory.h"

#define _(STRING) gettext(STRING)

int main(){
	
	setlocale(LC_ALL,"");
	bindtextdomain("sax3","/usr/share/locale");
	textdomain("sax3");

	UI::YUIFactory * factory = new UI::YUIFactory();
	UI::yDialog * dialog = factory->createDialog(30,10);

	UI::yVLayout * mainLayout = factory->createVLayout(dialog);

	UI::yLabel * label1 = factory->createLabel(mainLayout,_("SaX3 Control Center"));

	UI::yHLayout * KeyBoardLayout = factory->createHLayout(mainLayout);
	UI::yImage * KeyBoardImage = factory->createImage(KeyBoardLayout,"/usr/share/sax3/res/keyboard.png");
	UI::yPushButton * KeyBoardButton = factory->createPushButton(KeyBoardLayout,_("&Key Board"));
	
	UI::yHLayout * MouseLayout = factory->createHLayout(mainLayout);
	UI::yImage * MouseImage = factory->createImage(MouseLayout,"/usr/share/sax3/res/mouse.png");
	UI::yPushButton * MouseButton = factory->createPushButton(MouseLayout,_("&Mouse"));

	UI::yHLayout * MonitorLayout = factory->createHLayout(mainLayout);
	UI::yImage * MonitorImage = factory->createImage(MonitorLayout,"/usr/share/sax3/res/monitor.png");
	UI::yPushButton * MonitorButton = factory->createPushButton(MonitorLayout,_("Mo&nitor"));

	UI::yHLayout * TouchPadLayout = factory->createHLayout(mainLayout);
	UI::yImage * TouchPadImage = factory->createImage(TouchPadLayout,"/usr/share/sax3/res/touchpad.png");
	UI::yPushButton * TouchPadButton = factory->createPushButton(TouchPadLayout,_("&Touch Pad"));

	dialog->event();
	return 0;
}



