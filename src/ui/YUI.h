#ifndef _YUI_H_
#define _YUI_H_

#include "UI.h"

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
#include "YSpacing.h"
#include "YAlignment.h"


namespace UI{

  class YUIHLayout;
  class YUIVLayout;
  class YUIDialog;
  class YUIPushButton;
  class YUILabel;
  class YUIVSpacing;
  class YUIHSpacing;
  class YUIImage;

  class YUIDialog : public Dialog{
    YDialog * dialog;
    YAlignment * alignment;
  public:
    YUIDialog();
    virtual YUIDialog * createDialog(int x,int y);
    virtual void Event();
    YAlignment * getElement();
  };

  class YUIVSpacing : public VSpacing{
    YSpacing * VSpace;
  public:
    virtual void createVSpacing(YUIDialog *,int dim);
    virtual void createVSpacing(YUIVLayout *,int dim);
    virtual void createVSpacing(YUIHLayout *,int dim);
  };

  class YUIHSpacing : public HSpacing{
    YSpacing * HSpace;
  public:
    virtual void createHSpacing(YUIDialog *,int dim);
    virtual void createHSpacing(YUIVLayout *,int dim);
    virtual void createHSpacing(YUIHLayout *,int dim);

  };

  class YUIVLayout : public VLayout{
    YLayoutBox * vbox;
  public:
    virtual void createVLayout(YUIDialog *);
    virtual void createVLayout(YUIVLayout *);
    virtual void createVLayout(YUIHLayout *);
    YLayoutBox * getElement();
  };

  class YUIHLayout: public HLayout{
    YLayoutBox * hbox;
  public:
    virtual void createHLayout(YUIDialog *);
    virtual void createHLayout(YUIVLayout *);
    virtual void createHLayout(YUIHLayout *);
    YLayoutBox * getElement();
  };

  class YUILabel : public Label  {
    YLabel * label;
  public: 
    virtual void createLabel(YUIVLayout * parent, string text);
    virtual void createLabel(YUIHLayout * parent, string text);

  };

  class YUIPushButton : public PushButton{
    YPushButton * button;
  public:
    void createButton(YUIVLayout * parent,string text);
    void createButton(YUIHLayout * parent,string text);

  };

  class YUIImage : public Image{
    YImage * image;
  public:
    virtual void createImage(YUIVLayout * parent,string path) = 0;
    virtual void createImage(YUIHLayout * parent,string path) = 0;
    virtual void size(int width,int height)= 0;
  };
}

#endif
