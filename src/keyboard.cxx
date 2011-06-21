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

	enum{MODEL,LAYOUT,VARIANT,OPTION};
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
				if(!line.compare("model")){type = MODEL;continue;}
				if(!line.compare("layout")){type = LAYOUT;continue;}
				if(!line.compare("variant")){type = VARIANT;continue;}
				if(!line.compare("option")){type = OPTION;continue;}
				
				int pos = line.find_first_of(' ');
				s1 = line.substr(0,pos);line.erase(0,pos);
				pos=line.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
				line.erase(0,pos-1);

				if(type==MODEL && line.length()!=0){
					model[line]=s1;
				}
				if(type==LAYOUT && line.length()!=0){
					layout[line]=s1;
				}
				if(type==VARIANT && line.length()!=0){
					variant[line]=s1;
				}
				if(type==OPTION && line.length()!=0){
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
	label1 = factory->createLabel(mainLayout,_("SaX3 - Keyboard Module"));
	layoutSelect = factory->createMultiSelectionBox(mainLayout,_("Select your keyboard Layout"));
	layoutSelect->addItem("Manu Gupta");
	modelSelect = factory->createComboBox(mainLayout,_("Select your keyboard model"));
	modelSelect->addItem("Manu Gupta");
	variantSelect = factory->createComboBox(mainLayout,_("Select your keyboard Varaint"));
	variantSelect->addItem("Manu Gupta");
	optionSelect = factory->createComboBox(mainLayout,_("Select your keyboard Group"));
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
	char **match;int i=0,j=0,pos=0;string line,subPath,pathParam;
	int error;
	string layoutVal;
	aug=NULL;root=NULL;flag=0;
	aug = aug_init(root,loadpath,flag);
	int cnt = aug_match(aug,"/files/etc/X11/xorg.conf.d/*/InputClass/MatchIsKeyboard",&match);
	for(i=0;i<cnt-1;i++){
		if(strcmp(match[i],match[i+1])<0)
			j = i+1;
	}
	if(cnt)
		line.assign(match[j]);
	else
		line.assign("/files/etc/X11/xorg.conf.d/99-saxkeyboard.conf/InputClass");

	subPath.assign("InputClass");
	pos = line.find(subPath);
	
	line.erase(pos+subPath.length(),line.size());
	line.append("[last()");
	pathParam.assign(line);pathParam.append("+1]/Identifier");
	error = aug_set(aug,pathParam.c_str(),"SaXKeyboardConf");
	cout<<pathParam<<endl;
	pathParam.assign(line);pathParam.append("]/MatchIsKeyboard");
	error = aug_set(aug,pathParam.c_str(),"on");
	pathParam.assign(line);pathParam.append("]/Option");
	error = aug_set(aug,pathParam.c_str(),"XkbLayout");
	pathParam.assign(line);pathParam.append("]/Option/value");

	layoutVal = layout[layoutSelect->value()];

	error = aug_set(aug,pathParam.c_str(),layoutVal.c_str());

	error = aug_save(aug);
	if(error==-1)cout<<error;
//	aug_print(aug,stdout,"/augeas//error");
	return true;
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



