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

class Mouse{

	class Details{
		string product;
		string vendor;
		string name;
		string protocol;
		string device;
		string InvX;
		string InvY;
		string AngleOffset;
		string Emulate3Buttons;
		string Emulate3Timeout;
		string ChordMiddle;
		string EmulateWheel;
		string EmulateWheelTimeout;
		public:
		void setProduct(string);
		void setVendor(string);
		void setName(string);	
		void setDevice(string);
		void setEmulate3Buttons(string);
		void setEmulateWheel(string);
		string getName();
		string getVendor();
		string getProduct();
		Details();
	};
	
	string fileName,line;
	vector<Details*> d;

	augeas * aug;
	char * root,* loadpath;
	unsigned int flag;

	UI::YUIFactory * factory;
	UI::yDialog *dialog;
	UI::yHLayout * hl1,*enableButton3Layout,*enableWheelLayout,*buttonLayout;
	UI::yVLayout * vl1;
	UI::yPushButton *okButton,*cancelButton;
	UI::yRadioButtonGroup * button3,*wheel;
	UI::yLabel * button3Label,*enableButton3Label,*wheelLabel,*enableWheelLabel;
	UI::yIntField * timeout,*wheeltimeout,*AngleOffset;
	UI::yCheckBox * InvX,*InvY;
	UI::yComboBox * mouseList;
	void getProductVendor();
	void getName();
	void fillUpMouseList();
	bool writeConf(string &line,bool newNode,string parameter,bool isLastParameter,string extraParam,string value);
	public:
	void autodetect();
	void initUI();
	bool saveConf();
	bool respondToEvent();
	Mouse();
};

string Mouse::Details::getProduct(){
	return product;
}

string Mouse::Details::getVendor(){
	return vendor;
}

string Mouse::Details::getName(){
	return name;
}

void Mouse::Details::setProduct(string p){
	product = p;
	for(int i=0;i<4-product.size();i++)
		product.insert(product.begin(),'0');
}

void Mouse::Details::setVendor(string v){
	vendor = v;
	for(int i=0;i<4-vendor.size();i++){
		vendor.insert(vendor.begin(),'0');
	}
}

void Mouse::Details::setName(string n){
	name = n;
}

void Mouse::Details::setDevice(string d){
	device = d;
}

Mouse::Details::Details(){
	protocol = "Auto";
}

void Mouse::getProductVendor(){
	string pv = line.substr(line.find_first_of('/')+1,line.find_last_of('/'));
	string v = pv.substr(0,pv.find_first_of('/'));
	d.back()->setVendor(v);
	pv.erase(0,pv.find_first_of('/')+1);
	string p = pv.substr(0,pv.find_first_of('/'));
	d.back()->setProduct(p);
}

void Mouse::getName(){
	int x = line.find_last_of('"')-6;
	string n = line.substr(line.find_first_of('"')+1,x);
	d.back()->setName(n);
}

void Mouse::autodetect(){
	fileName = "/sys/class/input/mouse0/device/uevent";
	ifstream myfile;
	string::iterator it;
	
	for(int i=0;i<=9;i++){
		fileName.replace(fileName.begin()+22,fileName.begin()+23,1,'0'+i);
		myfile.open(fileName.c_str());
		if(myfile.is_open()){
			d.push_back(new Details());
			string device = "/dev/mouse";device.push_back('0'+i);
			d.back()->setDevice(device);
			while(myfile.good()){
				getline(myfile,line);
				if(!line.find("PRODUCT"))
					getProductVendor();
				if(!line.find("NAME"))
					getName();
			}
		}
		myfile.close();
	
	}
}

void Mouse::initUI(){
	dialog = factory->createDialog(40,10);

	vl1 = factory->createVLayout(dialog);
	hl1 = factory->createHLayout(vl1);
	
	mouseList = factory->createComboBox(vl1,"Auto Detected Mouse");
	mouseList->addItem("Generic Mouse");
	fillUpMouseList();
	button3Label = factory->createLabel(vl1,"3 button Emulation Options");
	enableButton3Layout = factory->createHLayout(vl1);
	enableButton3Label = factory->createLabel(enableButton3Layout,"Enable 3 Buttons");
	button3 = factory->createRadioButtonGroup(enableButton3Layout);
	button3->addButton("Yes");
	button3->addButton("No");
	timeout = factory->createIntField(vl1,"3 Button Timeout Time",0,1000,50);
	timeout->setDisabled();
	wheelLabel = factory->createLabel(vl1,"Wheel Emulation Options");
	enableWheelLayout = factory->createHLayout(vl1);
	enableWheelLabel = factory->createLabel(enableWheelLayout,"Enable Wheel Emulation");
	wheel = factory->createRadioButtonGroup(enableWheelLayout);
	wheel->addButton("Yes");
	wheel->addButton("No");
	wheeltimeout = factory->createIntField(vl1,"3 Button Timeout Time",0,1000,200);
	wheeltimeout->setDisabled();
	InvX = factory->createCheckBox(vl1,"Invert X Axis",false);
	InvY = factory->createCheckBox(vl1,"Invert Y Axis",false);

	AngleOffset = factory->createIntField(vl1,"Angle Offset in degrees",0,360,0);
	buttonLayout = factory->createHLayout(vl1);
	okButton = factory->createPushButton(buttonLayout,"Save");
	cancelButton = factory->createPushButton(buttonLayout,"Close");
}

void Mouse::fillUpMouseList(){
	for(int i=0;i<d.size();i++){
		if(d[i]->getName().find("ETPS")==-1 && d[i]->getName().find("ALPS")==-1)
			mouseList->addItem(d[i]->getName());
	}
}

Mouse::Mouse(){
	factory = new UI::YUIFactory();
	aug=NULL;root=NULL;flag=0;loadpath=NULL;
	cout<<"Loading AUgeas";
	aug = aug_init(root,loadpath,flag);
	if(aug==NULL){
		cout<<"AUGEAS NOT LOADED";
	}

}

bool Mouse::respondToEvent(){
	
	while(1){
		dialog->wait();
		if(cancelButton->getElement()==dialog->eventWidget()){
			cout<<"Exitting";
			break;
		}
		if(okButton->getElement()==dialog->eventWidget()){
			saveConf();
		}
	};
	return true;
}

bool Mouse::saveConf(){
	char **match;int i=0,j=0,pos=0;string line,subPath,pathParam;
	int error;

	int cnt = aug_match(aug,"/files/etc/X11/xorg.conf.d/*/InputClass/*",&match);

	for(i=0;i<cnt-1;i++){
		if(strcmp(match[i],match[i+1])<0)
			j = i;
	}

	if(cnt)
		line.assign(match[j]);
	else
		line.assign("/files/etc/X11/xorg.conf.d/99-saxkeyboard.conf/InputClass");


	subPath.assign("InputClass");
	pos = line.find(subPath);
	line.erase(pos+subPath.length(),line.size());
	cout<<endl<<line<<endl;

	string Identifier = mouseList->value();
	Identifier.append("-SaX-MouseConfig");
	cout<<Identifier;
	writeConf(line,true,"Identifier",false,"",Identifier.c_str()) ? cout<<"no error\n" : cout<<"error\n";

	for(i=0;i<d.size();i++){
		if(mouseList->value()==d[i]->getName()){
			break;
		}
	}

	writeConf(line,false,"MatchVendor",false,"",d[i]->getVendor().c_str()) ? cout<<"No Error\n" : cout<<"Error\n";
	writeConf(line,false,"MatchProduct",false,"",d[i]->getProduct().c_str()) ? cout<<"No Error\n" : cout<<"Error\n";
	writeConf(line,false,"MatchIsPointer",false,"","on") ? cout<<"No Error\n" : cout<<"Error\n";
	writeConf(line,false,"Driver",false,"","mouse") ? cout<<"No Error\n" : cout<<"Error\n";
	
	if(button3->selectedLabel()=="&Yes"){
		writeConf(line,false,"Option",true,"","Emulate3Buttons") ? cout<<"No Error\n" : cout<<"Error\n";
		writeConf(line,false,"Option",false,"/value","on")?cout<<"NoError\n":cout<<"Error\n";
		writeConf(line,false,"Option",true,"","ChordMiddle") ? cout<<"No Error\n" : cout<<"Error\n";
		writeConf(line,false,"Option",false,"/value","on")?cout<<"NoError\n":cout<<"Error\n";
		char * s = new char[4];
		sprintf(s,"%d",timeout->value());
		writeConf(line,false,"Option",true,"","Emulate3Timeout") ? cout<<"No Error\n" : cout<<"Error\n";
		writeConf(line,false,"Option",false,"/value",s)?cout<<"NoError\n":cout<<"Error\n";
		
	}
	if(wheel->selectedLabel()=="Y&es"){
		writeConf(line,false,"Option",true,"","EmulateWheel") ? cout<<"No Error\n" : cout<<"Error\n";
		writeConf(line,false,"Option",false,"/value","on")?cout<<"NoError\n":cout<<"Error\n";
		char * s = new char[4];
		sprintf(s,"%d",wheeltimeout->value());
		writeConf(line,false,"Option",true,"","EmulateWheelTimeout") ? cout<<"No Error\n" : cout<<"Error\n";
		writeConf(line,false,"Option",false,"/value",s)?cout<<"NoError\n":cout<<"Error\n";
		
	}


	if(InvX->isChecked()){
		writeConf(line,false,"Option",true,"","InvX") ? cout<<"No Error\n" : cout<<"Error\n";
		writeConf(line,false,"Option",false,"/value","on")?cout<<"NoError\n":cout<<"Error\n";
	}
	if(InvY->isChecked()){
		writeConf(line,false,"Option",true,"","InvY") ? cout<<"No Error\n" : cout<<"Error\n";
		writeConf(line,false,"Option",false,"/value","on")?cout<<"NoError\n":cout<<"Error\n";
	}

	char *s = new char[3];sprintf(s,"%d",AngleOffset->value());
	writeConf(line,false,"Option",true,"","AngleOffset") ? cout<<"No Error\n" : cout<<"Error\n";
	writeConf(line,false,"Option",false,"/value",s)?cout<<"NoError\n":cout<<"Error\n";
	error = aug_save(aug);

	if(error==-1){
		aug_print(aug,stdout,"/augeas//error");
		return false;
	}
	return true;
}

bool Mouse::writeConf(string &line,bool newNode,string parameter,bool isLastParameter,string extraParam,string value){
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
	Mouse * m = new Mouse();
	m->autodetect();
	m->initUI();
	m->respondToEvent();
	return 0;
}
