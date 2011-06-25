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
	UI::yHLayout * buttonLayout,*upperLayout,*addGroupLayout;
	UI::yPushButton * activateMode,*saveButton,*cancelButton,*addLayoutVariant,*deleteLayoutVariant,*addGroup,*deleteGroup;
	UI::yComboBox * modelSelect,*variantSelect,*groupCategory,*groupOptions;
	UI::yLabel * labelSelect;
	UI::yTable * layoutTable,*groupTable;
	bool SIMPLEMODE;

	void drawSimpleMode();
	void drawExpertMode();

	void split();
	void fillUpLayoutSelect();
	void fillUpVariant();
	void fillUpModelSelect();
	void fillUpGroupCategory();
	void fillUpGroupOptions();
	bool writeConf(string &line,bool newNode,string parameter,bool isLastParameter,string extraParam,string value);
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
					options[line]=s1;
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
	fillUpLayoutSelect();
}

void keyboard::drawExpertMode(){
	dialog = factory->createDialog(30,40);
	mainLayout = factory->createVLayout(dialog);
	label1 = factory->createLabel(mainLayout,_("SaX3 - Keyboard Module"));
	
	upperLayout = factory->createHLayout(mainLayout);
	layoutSelect = factory->createComboBox(upperLayout,_("Select your keyboard Layout"));
	fillUpLayoutSelect();
	variantSelect = factory->createComboBox(upperLayout,_("Select appropriate layout"));
	addLayoutVariant = factory->createPushButton(upperLayout,_("Add"));
	layoutTable = factory->createTable(mainLayout,"Layout","Variant","");
	deleteLayoutVariant = factory->createPushButton(mainLayout,_("Delete selected Layout & Variant"));
	modelSelect = factory->createComboBox(mainLayout,_("Select your Model"));
	fillUpModelSelect();
	addGroupLayout = factory->createHLayout(mainLayout);
	groupCategory = factory->createComboBox(addGroupLayout,_("Group Category"));
	fillUpGroupCategory();
	groupOptions = factory->createComboBox(addGroupLayout,_("Options"));
	addGroup = factory->createPushButton(addGroupLayout,_("Add"));
	UI::yLabel * label3 = factory->createLabel(mainLayout,_("Another Table here"));
	groupTable = factory->createTable(mainLayout,"Group","Option","");
	deleteGroup = factory->createPushButton(mainLayout,_("Delete Selected Group"));
	buttonLayout = factory->createHLayout(mainLayout);
	activateMode = factory->createPushButton(buttonLayout,_("&Simple Mode"));
	saveButton = factory->createPushButton(buttonLayout,_("&Ok"));
	cancelButton = factory->createPushButton(buttonLayout,_("&Cancel"));
}

bool keyboard::respondToEvent(){
	while(1){
		dialog->wait();
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
		if(cancelButton->getElement()==dialog->eventWidget()){
			return false;
		}
		if(!SIMPLEMODE){
			if(layoutSelect->getElement()==dialog->eventWidget()){
				fillUpVariant();
			}
			if(groupCategory->getElement()==dialog->eventWidget()){
				fillUpGroupOptions();
			}	
			if(addLayoutVariant->getElement()==dialog->eventWidget()){
				layoutTable->addItem(layoutSelect->value(),variantSelect->value());
//				return true
				cerr<<"manu";
			}
			if(addGroup->getElement()==dialog->eventWidget()){
				groupTable->addItem(groupCategory->value(),groupOptions->value());
			}
			if(deleteGroup->getElement()==dialog->eventWidget()){
				groupTable->getElement()->selectedItem()->index();
				groupTable->deleteSelected();
				dialog->redraw();
			}
		}
	}
}

void keyboard::fillUpLayoutSelect(){
	layoutSelect->deleteAllItems();
	map<string,string>::iterator it;
	for(it=layout.begin();it!=layout.end();it++){
	        layoutSelect->addItem(it->first);
	}
}
void keyboard::fillUpModelSelect(){
	modelSelect->deleteAllItems();
	map<string,string>::iterator it;
	for(it=model.begin();it!=model.end();it++){
		modelSelect->addItem(it->first);
	}
}
void keyboard::fillUpVariant(){
	variantSelect->deleteAllItems();
	map<string,string>::iterator it;int temp;
	variantSelect->addItem("Default");
	for(it=variant.begin();it!=variant.end();it++){
		temp = it->first.find(layout[layoutSelect->value()]);
		if(temp==1){
			variantSelect->addItem(it->first);
		}
	}
}

void keyboard::fillUpGroupCategory(){
	groupCategory->deleteAllItems();
	map<string,string>::iterator it;
	for(it=options.begin();it!=options.end();it++){
		if(it->second.find(':')==string::npos)
			groupCategory->addItem(it->first);
	}
}

void keyboard::fillUpGroupOptions(){
	groupOptions->deleteAllItems();
	map<string,string>::iterator it;
	string temp = options[groupCategory->value()];
	for(it = options.begin();it!=options.end();it++){
		if(it->second.find(temp)==0){
			if(it->second.find(':')!=string::npos)
			groupOptions->addItem(it->second);
		}
	}


}

bool keyboard::writeConf(string &line,bool newNode,string parameter,bool isLastParameter,string extraParam,string value){
	string pathParam;int error;
	pathParam.assign(line);
	if(newNode==true){
		pathParam.append("[last()+1]/");
	}else{
		pathParam.append("[last()]/");
	}
	pathParam.append(parameter);
	if(isLastParameter){
		pathParam.append("[last()+1]");
	}else{
		pathParam.append("[last()]");
	}
	pathParam.append(extraParam);
	cout<<pathParam<<endl;
	error = aug_set(aug,pathParam.c_str(),value.c_str());
	
	if(error==-1)
		return false;
	return true;
}
bool keyboard::simpleWriteConf(){
	char **match;int i=0,j=0,pos=0;string line,subPath,pathParam;
	int error;
	string layoutVal = layout[layoutSelect->value()];
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
	writeConf(line,true,"Identifier",false,"","SaXKeyBoardConf") ? cout<<"no error\n" : cout<<"error\n";
	writeConf(line,false,"Option",false,"","XkbLayout") ? cout<<"no error\n" : cout<<"error\n";
	writeConf(line,false,"Option",false,"/value",layoutVal.c_str()) ? cout<<"no error\n" : cout<<"error\n";

	error = aug_save(aug);
	if(error==-1){
		aug_print(aug,stdout,"/augeas//error");
		return false;
	}
	return true;
}

bool keyboard::expertWriteConf(){
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



