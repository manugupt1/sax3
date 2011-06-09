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


class Init{

	DIR * dp;
	struct dirent * ep;
	
	augeas * aug;
	char  *root,*loadpath;
	unsigned int flag;
	const char *value;
	int err;
	char* getEntry;
	protected:
		void makeEntry(char s1[],char s2[],char s3[]){
			strcpy(getEntry,s1);
			strcat(getEntry,s2);
			strcat(getEntry,s3);
		}

	public:
	Init(){
		aug=NULL;root=NULL;loadpath=NULL;flag=0;
		UI::YUIFactory * factory = new UI::YUIFactory();
		UI::yDialog * dialog = factory->createDialog(30,10);
		UI::yVLayout * mainLayout = factory->createVLayout(dialog);
		dp = opendir("/usr/share/sax3/modules.d/");
		aug = aug_init(root,loadpath,flag);
		aug_set(aug,"/augeas/load/Desktop/incl[last()+1]","/usr/share/sax3/modules.d/*");
		err = aug_load(aug);
		
		if(dp!=NULL){
			while(ep = readdir(dp)){
				if(strcmp(ep->d_name,".") && strcmp(ep->d_name,"..")){
				
					UI::yHLayout * hLayout = factory->createHLayout(mainLayout);
					getEntry = new char[300];
					makeEntry("/files/usr/share/sax3/modules.d/",ep->d_name,"/*/Icon");
					err = aug_get(aug,getEntry,&value);
					if(err==1)
					UI::yImage * image = factory->createImage(hLayout,value);
					delete getEntry;

					getEntry = new char[100];
					makeEntry("/files/usr/share/sax3/modules.d/",ep->d_name,"/*/Name");
					err = aug_get(aug,getEntry,&value);
					if(err==1)
					UI::yLabel * button = factory->createButton(hLayout,value);
					delete getEntry;	
				}
			}

		}	
		dialog->event();
		
	}
};

int main(){
	
	setlocale(LC_ALL,"");
	bindtextdomain("sax3","/usr/share/locale");
	textdomain("sax3");

	new Init();
/*	UI::YUIFactory * factory = new UI::YUIFactory();
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

	dialog->event();*/
	return 0;
}



