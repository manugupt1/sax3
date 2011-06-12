#include <iostream>

#include<locale.h>
#include<libintl.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include<list>

extern "C"{
#include<augeas.h>
}

#include "ui/yuifactory.h"

#define _(STRING) gettext(STRING)

int main(){
	
	setlocale(LC_ALL,"");
	bindtextdomain("sax3","/usr/share/locale");
	textdomain("sax3");

	UI::YUIFactory * factory = new UI::YUIFactory();
	UI::yDialog * dialog = factory->createDialog(60,20);

	UI::yVLayout * mainLayout = factory->createVLayout(dialog);

	UI::yLabel * label1 = factory->createLabel(mainLayout,_("              SaX3 - Keyboard Module"));

	UI::yVLayout * KeyBoardLayout = factory->createVLayout(mainLayout);
	UI::yLabel *  layout = factory->createLabel(KeyBoardLayout,_("    Layout    "));

	
	dialog->event();
	return 0;
}



