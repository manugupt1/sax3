#include "yui.h"

#include<iostream>

namespace UI{

	//YDIALOG FUNCTIONS START
	yDialog::yDialog(int width,int height){
		dialog = YUI::widgetFactory()->createPopupDialog();
		alignment = YUI::widgetFactory()->createMinSize(dialog,width,height);
	}
	
	YAlignment * yDialog::getElement(){
		return alignment;
	}

	void yDialog::wait(){
		Event = dialog->waitForEvent();
	}
	YWidget* yDialog::eventWidget(){
		return Event->widget();
	}

	yDialog::~yDialog(){
		delete alignment;
		dialog->destroy();
	}
	void yDialog::redraw(){
		dialog->recalcLayout();
	}
	//YDIALOG FUCNTIONS END


	//YVLAYOUT FUNCTIONS BEGIN
	yVLayout::yVLayout(yDialog * parent){
		layout = YUI::widgetFactory()->createVBox(parent->getElement());
	}

	yVLayout::yVLayout(yHLayout * parent){
		layout=YUI::widgetFactory()->createVBox(parent->getElement());
	}

	yVLayout::yVLayout(yVLayout * parent){
		layout = YUI::widgetFactory()->createVBox(parent->getElement());
	}

	YLayoutBox * yVLayout::getElement(){
		return layout;
	}
	yVLayout::~yVLayout(){
		delete layout;
	}


	//YVLAYOUT FUNCTIONS END

	//YHLAYOUT FUNCTIONS BEGIN
	yHLayout::yHLayout(yDialog * parent){
		layout = YUI::widgetFactory()->createHBox(parent->getElement());
	}

	yHLayout::yHLayout(yHLayout * parent){
		layout=YUI::widgetFactory()->createHBox(parent->getElement());
	}

	yHLayout::yHLayout(yVLayout * parent){
		layout = YUI::widgetFactory()->createHBox(parent->getElement());
	}

	YLayoutBox * yHLayout::getElement(){
		return layout;
	}
	yHLayout::~yHLayout(){
		delete layout;
	}
	//YHLAYOUT FUNCTIONS END

	//YLABEL FUNCTIONS START

	yLabel::yLabel(yDialog * parent,std::string text){
		label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
	}

	yLabel::yLabel(yHLayout * parent,std::string text){
		label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
	}

	yLabel::yLabel(yVLayout * parent,std::string text){
		label = YUI::widgetFactory()->createLabel(parent->getElement(),text);
	}
	yLabel::~yLabel(){
		delete label;
	}

	//YLABEL FUNCTIONS END

	//YPUSHBUTTON FUNCTIONS START
	yPushButton::yPushButton(yDialog * parent,std::string text){
		button = YUI::widgetFactory()->createPushButton(parent->getElement(),text);
	}
	yPushButton::yPushButton(yVLayout * parent,std::string text){
		button = YUI::widgetFactory()->createPushButton(parent->getElement(),text);
	}
	yPushButton::yPushButton(yHLayout * parent,std::string text){
		button = YUI::widgetFactory()->createPushButton(parent->getElement(),text);
	}
	YPushButton* yPushButton::getElement(){
		return button;
	}
	yPushButton::~yPushButton(){
		delete button;
	}

	//YPUSHBUTTION FUNCTIONS END

	//YIMAGE FUNCTIONS START
	yImage::yImage(yDialog * parent,std::string path){
		image = YUI::widgetFactory()->createImage(parent->getElement(),path);
	}
	yImage::yImage(yHLayout * parent,std::string path){
		image = YUI::widgetFactory()->createImage(parent->getElement(),path);
	}
	yImage::yImage(yVLayout * parent,std::string path){
		image = YUI::widgetFactory()->createImage(parent->getElement(),path);
	}
	yImage::~yImage(){
		delete image;
	}
	//YIMAGE FUNCTIONS END
	
	//YCOMBOBOX FUNCTION STARTS
	yComboBox::yComboBox(yDialog * parent,std::string text){
		comboBox = YUI::widgetFactory()->createComboBox(parent->getElement(),text,false);

	}
	yComboBox::yComboBox(yHLayout * parent,std::string text){
		comboBox = YUI::widgetFactory()->createComboBox(parent->getElement(),text,false);
	}
	yComboBox::yComboBox(yVLayout* parent,std::string text){
		comboBox = YUI::widgetFactory()->createComboBox(parent->getElement(),text,false);
	}
	void yComboBox::addItem(string item){
		comboBox->addItem(item);
	}
	YComboBox * yComboBox::getElement(){
		return comboBox;
	}
	string yComboBox::value(){
		return comboBox->value();
	}
	void yComboBox::setValue(string &value){
		comboBox->setValue(value);
	}
	yComboBox::~yComboBox(){
		delete comboBox;
	}

	//YCOMBOBOX FUNCION ENDS
	
	//YMULTISELECTIONBOX FUNCTION STARTS
	yMultiSelectionBox::yMultiSelectionBox(yDialog * parent,std::string label){
		multi = YUI::widgetFactory()->createMultiSelectionBox(parent->getElement(),label);
	}
	yMultiSelectionBox::yMultiSelectionBox(yHLayout * parent,std::string label){
		multi = YUI::widgetFactory()->createMultiSelectionBox(parent->getElement(),label);
	}
	yMultiSelectionBox::yMultiSelectionBox(yVLayout * parent,std::string label){
		multi = YUI::widgetFactory()->createMultiSelectionBox(parent->getElement(),label);
	}
	void yMultiSelectionBox::addItem(string item){
		multi->addItem(item);
	}
	yMultiSelectionBox::~yMultiSelectionBox(){
		delete multi;
	}
	void yMultiSelectionBox::selectedItems(vector<string> &list){
		slist = multi->selectedItems();
		for(int i=0;i<slist.size();i++){
			list.push_back(slist.at(i)->label());
		}		
	}
	
	//YMULTISELECTIONBOX FUNCTION ENDS
}
