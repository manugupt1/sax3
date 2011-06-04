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

#include<iostream>

namespace UI{

	class yDialog;
	class yLayout;
	class yHLayout;
	class yVLayout;
	class yHLayout;

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
	};

}

#endif
