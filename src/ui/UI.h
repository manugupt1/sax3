#ifndef _UI_H_
#define _UI_H_

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
namespace UI{

  class Dialog{
    YDialog * dialog;
  public:
    void Dialog();
    Dialog * createDialog();
    YDialog * getElement();
  };

  class VLayout{
    YLayoutBox * vbox;
  public:
    void VLayout();
    void createVLayout(Dialog *);
    YLayoutBox * getElement();

  };

  class HLayout{
    YLayoutBox * hbox;
  public:
    void createHLayout(Dialog *);
    YLayoutBox * getElement();
    
    

  };

  class Label{
    YLabel * label;
  public:
    void createLabel(VLayout * parent,string text);
    void createLabel(HLayout * parent,string text);
    
  };

  class PushButton{

  };

}

#endif
