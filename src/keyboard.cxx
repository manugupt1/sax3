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
#include<vector>
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
	string s1,line,optionType;
	ifstream baseFile;
	
	augeas * aug;
	char * root,* loadpath;
	unsigned int flag;

	enum{MODEL,LAYOUT,VARIANT,OPTION};
	int type;
	
	UI::YUIFactory * factory;
	UI::yDialog * dialog;
	UI::yVLayout * mainLayout;
	UI::yLabel * label1;
	UI::yComboBox * layoutSelect;
	UI::yHLayout * buttonLayout;
	UI::yPushButton * activateMode,*saveButton,*cancelButton;
	UI::yMultiSelectionBox * multiLayoutSelect;
	UI::yComboBox * modelSelect;
	UI::yMultiSelectionBox * multiVariantSelect;
	UI::yMultiSelectionBox * multiOptionSelect;
	bool SIMPLEMODE;

	void drawSimpleMode();
	void drawExpertMode();

	void split();
	void fillUp();

	public:
	keyboard();
	void drawLayout();
	bool respondToEvent();
	bool simpleWriteConf();
	bool expertWriteConf();
};

keyboard::keyboard(){
	type=0;
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
				cout<<s1<<'\t'<<line<<endl;
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
					if(s1.find(':')==-1) { optionType.assign("["+line+"]"); continue; }
					options[line+optionType]=s1;
				}

			};
	}
	SIMPLEMODE = true;
	factory = new UI::YUIFactory();
	aug=NULL;root=NULL;flag=0;loadpath=NULL;
	aug = aug_init(root,loadpath,flag);

}

void keyboard::drawLayout(){
	if(SIMPLEMODE){
		drawSimpleMode();
	}else{
		drawExpertMode();
	}
}


void keyboard::drawSimpleMode(){
	factory = new UI::YUIFactory();
	dialog = factory->createDialog(60,20);
	mainLayout = factory->createVLayout(dialog);
	label1 = factory->createLabel(mainLayout,_("SaX3 - Keyboard Module"));
	layoutSelect = factory->createComboBox(mainLayout,_("Select your keyboard Layout"));
	buttonLayout = factory->createHLayout(mainLayout);
	activateMode = factory->createPushButton(buttonLayout,_("E&xpert Mode"));
	saveButton = factory->createPushButton(buttonLayout,_("&Ok"));
	cancelButton = factory->createPushButton(buttonLayout,_("&Cancel"));
	fillUp();
	dialog->wait();
}

void keyboard::drawExpertMode(){
	dialog = factory->createDialog(120,60);
	mainLayout = factory->createVLayout(dialog);
	label1 = factory->createLabel(mainLayout,_("SaX3 - Keyboard Module"));
	multiLayoutSelect = factory->createMultiSelectionBox(mainLayout,_("Select your keyboard Layout"));
	modelSelect = factory->createComboBox(mainLayout,_("Select your keyboard model"));
	multiVariantSelect = factory->createMultiSelectionBox(mainLayout,_("Select your keyboard Varaint"));
	multiOptionSelect = factory->createMultiSelectionBox(mainLayout,_("Select your keyboard Group"));
	buttonLayout = factory->createHLayout(mainLayout);
	activateMode = factory->createPushButton(buttonLayout,_("&Simple Mode"));
	saveButton = factory->createPushButton(buttonLayout,_("&Ok"));
	cancelButton = factory->createPushButton(buttonLayout,_("&Cancel"));
	fillUp();
	dialog->redraw();
	dialog->wait();
}

bool keyboard::respondToEvent(){
	if(activateMode->getElement()==dialog->eventWidget()){delete dialog;
		SIMPLEMODE ? SIMPLEMODE = false : SIMPLEMODE = true;
		!SIMPLEMODE ? drawExpertMode() : drawSimpleMode(); 
		return true;
	}
	if(saveButton->getElement()==dialog->eventWidget()){
		if(SIMPLEMODE){
			if(simpleWriteConf()){
				cerr<<"Successfully written";
			}else{
				cerr<<"Successfully NOT written";
			}
		}else{
			expertWriteConf();
		}
		return false;
	}
	return false;
}

void keyboard::fillUp(){
	map<string,string>::iterator it;
	int i=0;
	if(SIMPLEMODE){
	        for(it=layout.begin();it!=layout.end();it++){
	                layoutSelect->addItem(it->first);
	        }

	}else{
		for(it=layout.begin();it!=layout.end();it++){
			multiLayoutSelect->addItem(it->first);
		}
		modelSelect->addItem("None");
		for(it=model.begin();it!=model.end();it++){
			modelSelect->addItem(it->first);
		}
		for(it=variant.begin();it!=variant.end();it++){
			multiVariantSelect->addItem(it->first);
		}
		for(it=options.begin();it!=options.end();it++,i++){
			multiOptionSelect->addItem(it->first);

		}

	}
}


bool keyboard::simpleWriteConf(){
	char **match;int i=0,j=0,pos=0;string line,subPath,pathParam;
	int error;
	string layoutVal;
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
	if(error==-1){
		aug_print(aug,stdout,"/augeas//error");
		return false;
	}
	return true;
}

bool keyboard::expertWriteConf(){
	vector<string> list;
	
	string layoutList,modelList,variantList,optionList,temp;
	multiLayoutSelect->selectedItems(list);

	for(int i=0;i<list.size();i++){
		temp = layout[list.at(i)];
		layoutList.append(temp);
		layoutList.push_back(',');
	}
	list.erase(list.begin(),list.end());

	modelList = modelSelect->value();
	multiVariantSelect->selectedItems(list);
	for(int i=0;i<list.size();i++){
		temp = variant[list.at(i)];
		variantList.append(temp);
		variantList.push_back(',');
	}
	list.erase(list.begin(),list.end());

	multiOptionSelect->selectedItems(list);
	for(int i=0;i<list.size();i++){
		temp = options[list.at(i)];
		optionList.append(temp);
		optionList.push_back(',');
	}
	list.erase(list.begin(),list.end());

	cout<<layoutList<<endl<<modelList<<endl<<variantList<<endl<<optionList<<endl;

	char **match;int i=0,j=0,pos=0;string line,subPath,pathParam;
	int error;
	string layoutVal;
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
//Option XkbLayout
	pathParam.assign(line);pathParam.append("]/Option[last()+1]");
	error = aug_set(aug,pathParam.c_str(),"XkbLayout");
	pathParam.assign(line);pathParam.append("]/Option[last()]/value");
	error = aug_set(aug,pathParam.c_str(),layoutList.c_str());
//Option Model
	if(modelList.compare("None")){
	pathParam.assign(line);pathParam.append("]/Option[last()+1]");
	error = aug_set(aug,pathParam.c_str(),"XkbModel");
	pathParam.assign(line);pathParam.append("]/Option[last()]/value");
	error = aug_set(aug,pathParam.c_str(),modelList.c_str());
	}
//Option Variant
	pathParam.assign(line);pathParam.append("]/Option[last()+1]");
	error = aug_set(aug,pathParam.c_str(),"XkbVariant");
	pathParam.assign(line);pathParam.append("]/Option[last()]/value");
	error = aug_set(aug,pathParam.c_str(),variantList.c_str());
//Option Options
	pathParam.assign(line);pathParam.append("]/Option[last()+1]");
	error = aug_set(aug,pathParam.c_str(),"XkbOptions");
	pathParam.assign(line);pathParam.append("]/Option[last()]/value");
	error = aug_set(aug,pathParam.c_str(),optionList.c_str());

	error = aug_save(aug);
	if(error==-1){
		aug_print(aug,stdout,"/augeas//error");
		return false;
	}
	return true;

}

int main(){
	
	setlocale(LC_ALL,"");
	bindtextdomain("sax3","/usr/share/locale");
	textdomain("sax3");

	keyboard * kb = new keyboard();
	kb->drawLayout();
	while(kb->respondToEvent());
	delete kb;	

	return 0;
 }



