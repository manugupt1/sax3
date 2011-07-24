#include<iostream>
#include<dirent.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<vector>
extern "C"{
#include<augeas.h>
}

#include<ui/yuifactory.h>

using namespace std;

class Monitors{
	vector<string> driverList;
	vector<string> resolutionList;

	augeas * aug;char *root,*loadpath;unsigned int flag;
	
	UI::YUIFactory * factory;
	UI::yDialog * dialog;
	UI::yVLayout * vL1;
	UI::yHLayout * hL1;
	UI::yPushButton * ok,*cancel;
	UI::yComboBox * driverCombo,*resolutionCombo,*depthCombo;
	UI::yIntField * horizontalLow,*horizontalHigh;
	UI::yIntField * verticalLow,*verticalHigh;
	void fillUpDriverCombo();
	void fillUpResolutionCombo();
	void fillUpDepthCombo();
	void separateResolution(string&);
	public:
	Monitors();
	void detectDrivers();
	void detectResolution();
	void initUI();
};

void Monitors::fillUpDepthCombo(){
	depthCombo->addItem("16");
	depthCombo->addItem("24");
}

void Monitors::fillUpResolutionCombo(){
	for(int i=0;i<resolutionList.size();i++)
		resolutionCombo->addItem(resolutionList[i]);
}

void Monitors::separateResolution(string &temp){
	temp = temp.erase(0,temp.find_first_not_of(' '));
	temp = temp.erase(temp.find_first_of(' '),string::npos);
}

void Monitors::detectResolution(){
	system("xrandr > /tmp/sax3-xrandr.temp");
	string temp;int flag=0;
	ifstream file("/tmp/sax3-xrandr.temp");
	if(file.is_open()){
		while(file.good()){
			getline(file,temp);
			if(temp.find(' ')!=0 && flag)
			break;
			if(temp.find(' ')==0){
				flag=1;
				separateResolution(temp);
				resolutionList.push_back(temp);
			}
		}
	}

}

void Monitors::fillUpDriverCombo(){
	for(int i=0;i<driverList.size();i++)
		driverCombo->addItem(driverList[i]);
}
Monitors::Monitors(){
        factory = new UI::YUIFactory();
        aug=NULL;root=NULL;flag=0;loadpath=NULL;
        cout<<"Loading AUgeas";
        aug = aug_init(root,loadpath,flag);
        if(aug==NULL){
              cout<<"AUGEAS NOT LOADED";
        }
}

void Monitors::detectDrivers(){
	system("rm /tmp/sax*");
	system(" xinit `which xrandr` -- :9 -logfile `mktemp --tmpdir sax3.XXXXX`");
	string temp;
	struct dirent * ep;
	DIR * dp;
	dp = opendir("/tmp/");
	if(dp!=NULL){
		cerr<<"Directory Opened"<<endl;
		while(ep=readdir(dp)){
			temp = ep->d_name;	
			if(temp.find("sax3")!=-1 && temp.find(".old")==-1)
				break;
		};
	}
	temp =temp.insert(0,"/tmp/");
	cout<<temp;
	ifstream file(temp.c_str());
	string temp1;
	int pos;
	if(file.is_open()){
		while(file.good()){
			getline(file,temp1);
			pos = temp1.find("Matched ");
			if(pos!=-1)
				break;
		}
	}
	
	while(pos!=-1){
		cout<<temp1<<endl;
		pos = temp1.find("Matched ");
		if(pos!=-1){
			string matched = "Matched ";
			int next_pos = pos+matched.size();
			temp1.erase(0,next_pos);
			next_pos = temp1.find(' ');
			temp1.erase(next_pos,string::npos);
			driverList.push_back(temp1);
		}
		getline(file,temp1);
	};
}

void Monitors::initUI(){
	dialog = factory->createDialog(200,200);
	vL1 = factory->createVLayout(dialog);
	hL1 = factory->createHLayout(vL1);
	driverCombo = factory->createComboBox(hL1,"Select the driver");	
	fillUpDriverCombo();
	horizontalLow = factory->createIntField(hL1,"Horizontal Refresh Rate(min value)",20,40,30);
	horizontalHigh = factory->createIntField(hL1,"Horizontal Refresh Rate(max value)",20,40,30);
	verticalLow = factory->createIntField(hL1,"Vertical Refresh Rate(min value)",20,40,30);
	verticalHigh = factory->createIntField(hL1,"Vertical Refresh Rate(max value)",20,40,30);
	resolutionCombo = factory->createComboBox(hL1,"Select resolution");
	fillUpResolutionCombo();
	depthCombo = factory->createComboBox(hL1,"Depth");
	fillUpDepthCombo();
	ok = factory->createPushButton(hL1,"Ok");
	cancel = factory->createPushButton(hL1,"Cancel");
	dialog->wait();
}


int main(){
	Monitors * m = new Monitors();
	m->detectDrivers();
	m->detectResolution();
	m->initUI();
	
}
	
