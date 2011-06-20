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

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<utility>

#define _(STRING) gettext(STRING)

using namespace std;

class simpleMode;
class expertMode;

class keyboard{
	protected:
	map<string,string> layout;
	map<string,string> model;
	map<string,string> variant;
	map<string,string> options;
	string s1,line;
	ifstream baseFile;
	
	augeas * aug;
	char * root,* loadpath;
	unsigned int flag;

	int type;
	void split();
	public:
	keyboard();
};

keyboard::keyboard(){
	string line;type=0;
	baseFile.open("/usr/share/X11/xkb/rules/base.lst",ios::in);
	if(baseFile.is_open()){
			while(baseFile.good()){
				getline(baseFile,line);
				line.erase(0,2);
				if(!line.compare("model")){type = 1;continue;}
				if(!line.compare("layout")){type = 2;continue;}
				if(!line.compare("variant")){type = 3;continue;}
				if(!line.compare("option")){type = 4;continue;}
				
				if(type==1 && line.length()!=0){
					int pos = line.find_first_of(' ');
					s1 = line.substr(0,pos);line.erase(0,pos);
					pos=line.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
					line.erase(0,pos-1);
					cout<<s1<<'\t'<<line<<endl;
					model[line]=s1;
				}
				if(type==2 && line.length()!=0){
					int pos = line.find_first_of(' ');
					s1 = line.substr(0,pos);line.erase(0,pos);
					pos=line.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
					line.erase(0,pos-1);
					cout<<s1<<'\t'<<line<<endl;
					layout[line]=s1;
				}
				if(type==3 && line.length()!=0){
					int pos = line.find_first_of(' ');
					s1 = line.substr(0,pos);line.erase(0,pos);
					pos=line.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
					line.erase(0,pos-1);
					cout<<s1<<'\t'<<line<<endl;
					variant[line]=s1;
				}
				if(type==4 && line.length()!=0){
					int pos = line.find_first_of(' ');
					s1 = line.substr(0,pos);line.erase(0,pos);
					pos=line.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
					line.erase(0,pos-1);
					cout<<s1<<'\t'<<line<<endl;
					options[line]=s1;
				}
				
			};
	}

}

class expertMode {
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

class simpleMode : protected keyboard{
	UI::YUIFactory * factory;
	UI::yDialog * dialog;
	UI::yVLayout * mainLayout;
	UI::yLabel * label1;
	UI::yComboBox * layoutSelect;
	UI::yHLayout * buttonLayout;
	UI::yPushButton * activateExpertMode,*saveButton,*cancelButton;
	public:
		simpleMode();
		bool writeConf();
		void fillUp();
			
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
	dialog->wait();
/*	if(activateSimpleMode->getElement()==dialog->event()){
		delete this;new simpleMode();
	}*/
}

simpleMode::simpleMode(){
	factory = new UI::YUIFactory();
	dialog = factory->createDialog(60,20);
	mainLayout = factory->createVLayout(dialog);
	label1 = factory->createLabel(mainLayout,_("              SaX3 - Keyboard Module"));
	layoutSelect = factory->createComboBox(mainLayout,_("Select your keyboard Layout                               "));
	buttonLayout = factory->createHLayout(mainLayout);
	activateExpertMode = factory->createPushButton(buttonLayout,_("E&xpert Mode"));
	saveButton = factory->createPushButton(buttonLayout,_("&Ok"));
	cancelButton = factory->createPushButton(buttonLayout,_("&Cancel"));

	fillUp();

	dialog->wait();

	if(activateExpertMode->getElement()==dialog->eventWidget()){
		delete this;new expertMode();
	}
	if(saveButton->getElement()==dialog->eventWidget()){
		writeConf();cout<<endl;
	}
}

bool simpleMode::writeConf(){
	cout<<"Hello World";
	aug=NULL;root=NULL;flag=0;
	aug = aug_init(root,loadpath,flag);
	aug_set(aug,"/files/etc/X11/xorg.conf.d/99-saxkeyboard.conf/InputClass/Idenifier","SaX Keyboard Conf");
	aug_set(aug,"/files/etc/X11/xorg.conf.d/99-saxkeyboard.conf/InputClass/MatchIsKeyboard","on");
	aug_set(aug,"/files/etc/X11/xorg.conf.d/99-saxkeyboard.conf/InputClass/Option","XkbLayout");
	aug_set(aug,"/files/etc/X11/xorg.conf.d/99-saxkeyboard.conf/InputClass/Option/value","us");
	aug_save(aug);
}

void simpleMode::fillUp(){
	map<string,string>::iterator it;
	for(it=layout.begin();it!=layout.end();it++){
		layoutSelect->addItem(it->first);
	}
}
int main(){
	
	setlocale(LC_ALL,"");
	bindtextdomain("sax3","/usr/share/locale");
	textdomain("sax3");

	new simpleMode();
	new keyboard();
	return 0;
}



