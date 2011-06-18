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
/*int printModel(FILE *fp){
	char *s,*s1,*s2;
	s = new char[500];
	s1 = new char[20];
	s2 = new char[480];
	fgets(s,400,fp);
	
	int tv = strlen(s);int j=0,k=0,i=0;
	while(strcmp(s,"! layout\n") && strcmp(s,"\n")){
		while(s[i]==' '){
			i++;
		}
		while(s[i]!=' '){
			s1[j++]=s[i++];
		}
		s1[j]='\0';
		printf("%s",s1);
		while(s[i]==' '){
			i++;
		}
		for(;i<=tv;i++) s2[k++]=s[i];
		s2[--k]='\0';

		printf("\t%s",s2);
		fgets(s,400,fp);
		tv = strlen(s);
		k=i=j=0;
	}
	return 0;
}*/

class keyBoard{
	map<string,string> model;
	map<string,string> layout;
	map<string,string> variant;
	map<string,string> options;
	char *s,*s1,*s2;
	FILE * fp;

	void createMaps();
	void split();

	public:
	keyBoard(){
		fp = fopen("/usr/share/X11/xkb/rules/base.lst","r");
		
		if(fp==NULL) printf("Error Loading layours, variants and models");
		else printf("base.lst successfully loaded");

		createMaps();
	}
		
}; 

void keyBoard::split(){
	
	;int len;
	int i=0,j=0,k=0;
	len = strlen(s);
	while(s[i]==' '){
		i++;
	}
	while(s[i]!=' '){
		s1[j++]=s[i++];
	}
	s1[j]='\0';
	printf("%s",s1);
	while(s[i]==' '){
		i++;
	}
	for(;i<=len;i++) s2[k++]=s[i];
	s2[k]='\0';
	printf("\t%s",s2);
	s = fgets(s,400,fp);
	if(s!=NULL)len = strlen(s);
	k=i=j=0;
}

void keyBoard::createMaps(){

	s = new char[500];
	s1 = new char[480];
	s2 = new char[20];
	s = fgets(s,400,fp);

	if(!strcmp(s,"! model\n")){
		s = fgets(s,400,fp);
		while(strcmp(s,"! layout\n") && strcmp(s,"\n")){			
			split();
		}
	}
		
	s= fgets(s,400,fp);

	if(!strcmp(s,"! layout\n")){
		s = fgets(s,400,fp);
		while(strcmp(s,"! layout\n") && strcmp(s,"\n")){			
			split();
		}
	}

	s= fgets(s,400,fp);

	if(!strcmp(s,"! variant\n")){
		s = fgets(s,400,fp);
		while(strcmp(s,"! layout\n") && strcmp(s,"\n")){			
			split();
		}
	}


	s= fgets(s,400,fp);

	if(!strcmp(s,"! option\n")){
		s = fgets(s,400,fp);
		while(strcmp(s,"! layout\n") && strcmp(s,"\n") ){			
			split();
			if(s==NULL)break;
		}
	}


}

class expertMode{
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
		expertMode(){
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

			dialog->event();

		}
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
		simpleMode(){
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

			while(1){	
				if(activateExpertMode->getElement()==dialog->event()){
					new expertMode();
					delete this;
				}
			};

		}
};


int main(){
	
	setlocale(LC_ALL,"");
	bindtextdomain("sax3","/usr/share/locale");
	textdomain("sax3");

	new simpleMode();
//	new keyBoard();
	return 0;
}



