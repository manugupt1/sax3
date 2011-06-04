#ifndef _YUI_H_
#define _YUI_H_

#include "ui.h"

#define YUILogComponent "SaX3-UI-Lib-Log"
#include "YUILog.h"
#include "YUI.h"
#include "YWidgetFactory.h"
#include "YLayoutBox.h"
#include "YDialog.h"
#include "YEvent.h"
#include "YPushButton.h"
#include "YLabel.h"
#include "YWidget.h"
#include "YAlignment.h"
#include "YImage.h"

#include<iostream>

namespace UI{

	class yDialog;
	class yLayout;
	class yVLayout;
	class yHLayout;
	class yLabel;
	class yPushButton;
	class yImage;
	
	class yImage : public Image{
		YImage * image;
		public:
		yImage(yDialog *,std::string path);
		yImage(yLayout *,std::string path);

	};
	class yPushButton : public PushButton{
		YPushButton * button;
		public:
		yPushButton(yDialog *,std::string text);
		yPushButton(yLayout *,std::string text);
		

	};

	class yLayout : public Layout{
		protected :
		YLayoutBox * layout;
		public:
		YLayoutBox * getElement();

	};

	class yHLayout : public HLayout, public yLayout{
		public :
			yHLayout(yLayout *);
			yHLayout(yDialog *);
	};

	class yVLayout : public VLayout, public yLayout{
		public:
			yVLayout(yLayout *);
			yVLayout(yDialog *);
	};


	class yDialog : public Dialog{
		YDialog * dialog;
		YAlignment * alignment;
		public:
		yDialog(int width,int height);
		YAlignment * getElement();
		void event();
	};

	class yLabel : public Label{
		YLabel * label;
		public:
		yLabel(yDialog *,std::string text);
		yLabel(yLayout *,std::string text);
	};

}

#endif
