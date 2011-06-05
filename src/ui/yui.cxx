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

	void yDialog::event(){
		dialog->waitForEvent();
	}

	yDialog::~yDialog(){
		delete alignment;
		dialog->destroy();
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
}
