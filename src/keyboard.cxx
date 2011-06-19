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

#include<stdio.h>
#include<string>
#include<map>
#include<utility>

#define _(STRING) gettext(STRING)

using namespace std;

class simpleMode;
class expertMode;

class keyBoard{
	protected:
	map<char *,char *> model;
	map<char *,char *> layout;
	map<char *,char *> variant;
	map<char *,char *> options;
	char *s,*s1,*s2;
	FILE * fp;
	void split(map<char*,char*>);
	void createMaps();
	public:
	keyBoard();		
}; 

keyBoard::keyBoard(){
	fp = fopen("/usr/share/X11/xkb/rules/base.lst","r");

	if(fp==NULL) printf("Error Loading layours, variants and models");
	else printf("base.lst successfully loaded");
	createMaps();
}

void keyBoard::split(map<char*,char*> Map){
	
	int len;
	int i=0,j=0,k=0;
	len = strlen(s);
	while(s[i]==' '){
		i++;
	}
	while(s[i]!=' '){
		s1[j++]=s[i++];
	}
	s1[j]='\0';
//	printf("%s",s1);
	while(s[i]==' '){
		i++;
	}
	for(;i<=len;i++) s2[k++]=s[i];
	s2[--k]='\0';
//	printf("\t%s",s2);
	s = fgets(s,400,fp);
	if(s!=NULL){ len = strlen(s); Map[s1]=s2;}
	k=i=j=0;
}

void keyBoard::createMaps(){

	s = new char[500];
	s1 = new char[480];
	s2 = new char[20];
	s = fgets(s,400,fp);

	if(!strcmp(s,"! model\n")){
		s = fgets(s,400,fp);
		while(strcmp(s,"\n")){			
			split(model);
		}
	}
		
	s= fgets(s,400,fp);

	if(!strcmp(s,"! layout\n")){
		s = fgets(s,400,fp);
		while(strcmp(s,"\n")){			
			split(layout);
		}
	}

	s= fgets(s,400,fp);

	if(!strcmp(s,"! variant\n")){
		s = fgets(s,400,fp);
		while(strcmp(s,"\n")){			
			split(variant);
		}
	}


	s= fgets(s,400,fp);

	if(!strcmp(s,"! option\n")){
		s = fgets(s,400,fp);
		while(strcmp(s,"\n") ){			
			split(options);
			if(s==NULL)break;
		}
	}

//	delete s;
}

class expertMode : protected keyBoard{
	UI::YUIFactory * factory;
	UI::yDialog * dialog;
	UI::yVLayout * mainLayout;
	UI::yLabel * label1;
	UI::yMultiSelectionBox * layoutSelect;
	UI::yComboBox * modelSelect;
	UI::yComboBox * variantSelect;
	UI::yComboBox * optionSelect;
	UI::yHLayout * buttonLayout;
	UI::yPushButton * activateSimpleMode,*saveButton,*cancelButton;
	public:
		expertMode();
};

class simpleMode{
	UI::YUIFactory * factory;
	UI::yDialog * dialog;
	UI::yVLayout * mainLayout;
	UI::yLabel * label1;
	UI::yComboBox * layoutSelect;
	UI::yHLayout * buttonLayout;
	UI::yPushButton * activateExpertMode,*saveButton,*cancelButton;
	public:
		simpleMode();
			
};

expertMode::expertMode(){
factory = new UI::YUIFactory();
	dialog = factory->createDialog(60,20);
	mainLayout = factory->createVLayout(dialog);
	label1 = factory->createLabel(mainLayout,_("              SaX3 - Keyboard Module"));
	layoutSelect = factory->createMultiSelectionBox(mainLayout,_("Select your keyboard Layout                                       "));
	layoutSelect->addItem("Manu Gupta");
	modelSelect = factory->createComboBox(mainLayout,_("Select your keyboard model                                        "));
	modelSelect->addItem("Manu Gupta");
	variantSelect = factory->createComboBox(mainLayout,_("Select your keyboard Varaint                                      "));
	variantSelect->addItem("Manu Gupta");
	optionSelect = factory->createComboBox(mainLayout,_("Select your keyboard Group                                        "));
	optionSelect->addItem("Manu Gupta");
	buttonLayout = factory->createHLayout(mainLayout);
	activateSimpleMode = factory->createPushButton(buttonLayout,_("&Simple Mode"));
	saveButton = factory->createPushButton(buttonLayout,_("&Ok"));
	cancelButton = factory->createPushButton(buttonLayout,_("&Cancel"));
	if(activateSimpleMode->getElement()==dialog->event()){
		delete this;new simpleMode();
	}
}

simpleMode::simpleMode(){
	factory = new UI::YUIFactory();
	dialog = factory->createDialog(60,20);
	mainLayout = factory->createVLayout(dialog);
	label1 = factory->createLabel(mainLayout,_("              SaX3 - Keyboard Module"));
	layoutSelect = factory->createComboBox(mainLayout,_("Select your keyboard Layout                               "));
	layoutSelect->addItem("Manu Gupta");
	buttonLayout = factory->createHLayout(mainLayout);
	activateExpertMode = factory->createPushButton(buttonLayout,_("E&xpert Mode"));
	saveButton = factory->createPushButton(buttonLayout,_("&Ok"));
	cancelButton = factory->createPushButton(buttonLayout,_("&Cancel"));
	
	if(activateExpertMode->getElement()==dialog->event()){
		delete this;new expertMode();
	}

}

int main(){
	
	setlocale(LC_ALL,"");
	bindtextdomain("sax3","/usr/share/locale");
	textdomain("sax3");

	new expertMode();
	return 0;
}



