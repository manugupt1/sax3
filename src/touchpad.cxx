#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<string.h>
#include<cstdio>
extern "C"{
#include<augeas.h>
}

#include "ui/yuifactory.h"

using namespace std;

class touchpad{

	augeas * aug;
	char * root,* loadpath;
	unsigned int flag;
	
	UI::YUIFactory * factory;
	UI::yDialog * dialog;
	UI::yVLayout * vL1;
	UI::yHLayout * hL1;
	UI::yCheckBox * TapButton1,*TapButton2,*TapButton3,*VerticalEdgeScroll,*HorizontalEdgeScroll,*VerticalTwoFingerScroll,*HorizontalTwoFingerScroll,*CircularScroll;
	UI::yComboBox * CircularLocation;
	UI::yPushButton * cancelButton,*okButton;

	bool saveConf();
	bool writeConf(string &line,bool newNode,string parameter,bool isLastParameter,string extraParam,string value);
	
	public:
	touchpad();
	void initUI();
	void respondToEvent();

};

touchpad::touchpad(){
	factory = new UI::YUIFactory();
	aug=NULL;root=NULL;flag=0;loadpath=NULL;
	cout<<"Loading AUgeas";
	aug = aug_init(root,loadpath,flag);
	if(aug==NULL){
		cout<<"AUGEAS NOT LOADED";
	}
}

void touchpad::initUI(){
	dialog = factory->createDialog(20,20);
	vL1 = factory->createVLayout(dialog);
	TapButton1 = factory->createCheckBox(vL1,"Emulate Mouse Button with a single click",false);
	TapButton2 = factory->createCheckBox(vL1,"Emulate Mouse Button with a double click",false);
	TapButton3 = factory->createCheckBox(vL1,"Emulate Mouse Button with a triple click",false);
	VerticalEdgeScroll = factory->createCheckBox(vL1,"Enable Vertical Edge Scrolling",true);
	HorizontalEdgeScroll = factory->createCheckBox(vL1,"Enable horizontal Edge Scrolling",true);
	VerticalTwoFingerScroll = factory->createCheckBox(vL1,"Enable 2 finger Vertical Scroll",true);
	HorizontalTwoFingerScroll = factory->createCheckBox(vL1,"Enable 2 finger Horizontal Scroll",true);
	CircularScroll = factory->createCheckBox(vL1,"Enable Circular Scrolling",false);
	CircularLocation = factory->createComboBox(vL1,"Region of touchpad to start circular scrolling");
	CircularLocation->addItem("All Edges");
	CircularLocation->addItem("Top Edges");
	CircularLocation->addItem("Top Right Corner");
	CircularLocation->addItem("Right Edge ");
	CircularLocation->addItem("Bottom Right Corner");
	CircularLocation->addItem("Bottom Edge");
	CircularLocation->addItem("Bottom Left Corner");
	CircularLocation->addItem("Left Edges");
	CircularLocation->addItem("Top Left Corner");
	CircularLocation->setDisabled();
	hL1 = factory->createHLayout(vL1);
	okButton = factory->createPushButton(hL1,"Ok");
	cancelButton = factory->createPushButton(hL1,"Cancel");
}

void touchpad::respondToEvent(){
	while(1){
		dialog->wait();
		if(cancelButton->getElement()==dialog->eventWidget()){
			break;
		}
		if(okButton->getElement()==dialog->eventWidget()){
			saveConf();
		}
		if(CircularScroll->isChecked())
			CircularLocation->setEnabled();
		else
			CircularLocation->setDisabled();
	};
}

bool touchpad::saveConf(){
	char **match;int i=0,j=0,pos=0;string line,subPath,pathParam;
	int error;
	int cnt = aug_match(aug,"/files/etc/X11/xorg.conf.d/*/InputClass/MatchIsTouchpad",&match);
	for(i=0;i<cnt-1;i++){
		if(strcmp(match[i],match[i+1])<0)
			j = i+1;
	}
	if(cnt)
		line.assign(match[j]);
	else
		line.assign("/files/etc/X11/xorg.conf.d/99-saxtouchpad.conf/InputClass");

	subPath.assign("InputClass");
	pos = line.find(subPath);
	line.erase(pos+subPath.length(),line.size());
	writeConf(line,true,"Identifier",false,"","SaXTouchpadConf") ? cout<<"no error\n" : cout<<"error\n";
	writeConf(line,false,"Driver",false,"","synaptics") ? cout<<"no error\n" : cout<<"error\n";
	writeConf(line,false,"MatchIsTouchpad",false,"","on") ? cout<<"no error\n" : cout<<"error\n";

	
	writeConf(line,false,"Option",false,"","TapButton1") ? cout<<"no error\n" : cout<<"error\n";
	if(TapButton1->isChecked()){
		writeConf(line,false,"Option",false,"/value","1") ? cout<<"no error\n" : cout<<"error\n";
	}else{
		writeConf(line,false,"Option",false,"/value","0") ? cout<<"no error\n" : cout<<"error\n";
	}
	
	writeConf(line,false,"Option",false,"","TapButton2") ? cout<<"no error\n" : cout<<"error\n";
	if(TapButton1->isChecked()){
		writeConf(line,false,"Option",false,"/value","1") ? cout<<"no error\n" : cout<<"error\n";
	}else{
		writeConf(line,false,"Option",false,"/value","0") ? cout<<"no error\n" : cout<<"error\n";
	}

	
	writeConf(line,false,"Option",false,"","TapButton3") ? cout<<"no error\n" : cout<<"error\n";
	if(TapButton1->isChecked()){
		writeConf(line,false,"Option",false,"/value","1") ? cout<<"no error\n" : cout<<"error\n";
	}else{
		writeConf(line,false,"Option",false,"/value","0") ? cout<<"no error\n" : cout<<"error\n";
	}

	
	writeConf(line,false,"Option",false,"","VertEdgeScroll") ? cout<<"no error\n" : cout<<"error\n";
	if(VerticalEdgeScroll->isChecked()){
		writeConf(line,false,"Option",false,"/value","on") ? cout<<"no error\n" : cout<<"error\n";
	}else{
		writeConf(line,false,"Option",false,"/value","off") ? cout<<"no error\n" : cout<<"error\n";
	}

	writeConf(line,false,"Option",false,"","HorizEdgeScroll") ? cout<<"no error\n" : cout<<"error\n";
	if(VerticalEdgeScroll->isChecked()){
		writeConf(line,false,"Option",false,"/value","on") ? cout<<"no error\n" : cout<<"error\n";
	}else{
		writeConf(line,false,"Option",false,"/value","off") ? cout<<"no error\n" : cout<<"error\n";
	}

	writeConf(line,false,"Option",false,"","VertTwoFingerScroll") ? cout<<"no error\n" : cout<<"error\n";
	if(VerticalTwoFingerScroll->isChecked()){
		writeConf(line,false,"Option",false,"/value","on") ? cout<<"no error\n" : cout<<"error\n";
	}else{
		writeConf(line,false,"Option",false,"/value","off") ? cout<<"no error\n" : cout<<"error\n";
	}


	writeConf(line,false,"Option",false,"","HorizTwoFingerScroll") ? cout<<"no error\n" : cout<<"error\n";
	if(HorizontalTwoFingerScroll->isChecked()){
		writeConf(line,false,"Option",false,"/value","on") ? cout<<"no error\n" : cout<<"error\n";
	}else{
		writeConf(line,false,"Option",false,"/value","off") ? cout<<"no error\n" : cout<<"error\n";
	}

	writeConf(line,false,"Option",false,"","CircularScrolling") ? cout<<"no error\n" : cout<<"error\n";
	if(CircularScroll->isChecked()){
		writeConf(line,false,"Option",false,"/value","on") ? cout<<"no error\n" : cout<<"error\n";
		writeConf(line,false,"Option",false,"","CircScrollTrigger") ? cout<<"no error\n" : cout<<"error\n";
		if(!CircularLocation->value().compare("All Edges")){
			writeConf(line,false,"Option",false,"/value","0") ? cout<<"no error\n" : cout<<"error\n";
		}
		if(!CircularLocation->value().compare("Top Edges")){
			writeConf(line,false,"Option",false,"/value","1") ? cout<<"no error\n" : cout<<"error\n";
		}
		if(!CircularLocation->value().compare("Top Right Corner")){
			writeConf(line,false,"Option",false,"/value","2") ? cout<<"no error\n" : cout<<"error\n";
		}
		if(!CircularLocation->value().compare("Right Edge ")){
			writeConf(line,false,"Option",false,"/value","3") ? cout<<"no error\n" : cout<<"error\n";
		}
		if(!CircularLocation->value().compare("Bottom Right Corner")){
			writeConf(line,false,"Option",false,"/value","4") ? cout<<"no error\n" : cout<<"error\n";
		}
		if(!CircularLocation->value().compare("Bottom Edge")){
			writeConf(line,false,"Option",false,"/value","5") ? cout<<"no error\n" : cout<<"error\n";
		}
		if(!CircularLocation->value().compare("Bottom Left Corner")){
			writeConf(line,false,"Option",false,"/value","6") ? cout<<"no error\n" : cout<<"error\n";
		}
		if(!CircularLocation->value().compare("Left Edges")){
			writeConf(line,false,"Option",false,"/value","7") ? cout<<"no error\n" : cout<<"error\n";
		}
		if(!CircularLocation->value().compare("Top Left Corner")){
			writeConf(line,false,"Option",false,"/value","8") ? cout<<"no error\n" : cout<<"error\n";
		}

	}else{
		writeConf(line,false,"Option",false,"/value","off") ? cout<<"no error\n" : cout<<"error\n";
	}

	error = aug_save(aug);
	if(error==-1){
		aug_print(aug,stdout,"/augeas//error");
		return false;
	}
	return true;

}

bool touchpad::writeConf(string &line,bool newNode,string parameter,bool isLastParameter,string extraParam,string value){
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

int main(){
	touchpad * t = new touchpad();
	t->initUI();
	t->respondToEvent();
	delete t;
	return 0;
}	
