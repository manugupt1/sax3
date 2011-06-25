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
	int yDialog::eventReason(){
		return Event->eventType();
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
	void yLabel::setValue(std::string text){
		label->setValue(text);
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
		comboBox->setNotify(true);

	}
	yComboBox::yComboBox(yHLayout * parent,std::string text){
		comboBox = YUI::widgetFactory()->createComboBox(parent->getElement(),text,false);
		comboBox->setNotify(true);
	}
	yComboBox::yComboBox(yVLayout* parent,std::string text){
		comboBox = YUI::widgetFactory()->createComboBox(parent->getElement(),text,false);
		comboBox->setNotify(true);
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
	void yComboBox::deleteAllItems(){
		comboBox->deleteAllItems();
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
		for(unsigned i=0;i<slist.size();i++){
			list.push_back(slist.at(i)->label());
		}		
	}
	
	//YMULTISELECTIONBOX FUNCTION ENDS
	
	//YTABLE FUNCTION STARTS
	yTable::yTable(yDialog* parent,std::string HeaderCol1,std::string HeaderCol2,std::string HeaderCol3=""){
		header = new YTableHeader();
		YUI_CHECK_NEW(header);
		header->addColumn(HeaderCol1);
		header->addColumn(HeaderCol2);
		if(HeaderCol3!="")header->addColumn(HeaderCol3);	
		table=YUI::widgetFactory()->createTable(parent->getElement(),header);
		table->setNotify(true);
	}
	yTable::yTable(yHLayout* parent,std::string HeaderCol1,std::string HeaderCol2,std::string HeaderCol3=""){
		header = new YTableHeader();
		YUI_CHECK_NEW(header);
		header->addColumn(HeaderCol1);
		header->addColumn(HeaderCol2);
		if(HeaderCol3!="")header->addColumn(HeaderCol3);	
		table=YUI::widgetFactory()->createTable(parent->getElement(),header);
		table->setNotify(true);
	}
	yTable::yTable(yVLayout* parent,std::string HeaderCol1,std::string HeaderCol2,std::string HeaderCol3=""){
		header = new YTableHeader();
		YUI_CHECK_NEW(header);
		header->addColumn(HeaderCol1);
		header->addColumn(HeaderCol2);
		if(HeaderCol3!="")header->addColumn(HeaderCol3);	
		table=YUI::widgetFactory()->createTable(parent->getElement(),header);
		table->setNotify(true);
	}
	void yTable::addItem(std::string item1,std::string item2){
		table->addItem(new YTableItem(item1,item2));
		i.push_back(std::make_pair<string,string> (item1,item2));	
	}
	void yTable::deleteSelected(){
		YItemIterator it = table->itemsBegin();
		std::vector<P>::iterator ii = i.begin();
		while(it!=table->itemsEnd()){
			YItem * item = *it;
			++it;++ii;
			if(*it==table->selectedItem())
				break;
			
		}
		table->deleteAllItems();
		i.erase(ii);
		items = createList();
		table->addItems(items);
	}
	YItemCollection yTable::createList(){
		YItemCollection list;
		std::vector<P>::iterator ii;
		ii = i.begin();
		while(ii!=i.end()){
			list.push_back(new YTableItem(ii->first,ii->second));
			ii++;
		}
		return list;
	}

	YTable* yTable::getElement(){
		return table;
	}
	//YTABLE FUNCTION ENDS
}
