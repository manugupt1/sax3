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
#include "YSpacing.h"
#include "YAlignment.h"

namespace UI{

  class HLayout;
  class VLayout;
  class Dialog;
  class PushButton;
  class Label;
  class VSpacing;
  class HSpacing;
  class Image;


  class YUIHLayout;
  class YUIVLayout;
  class YUIDialog;
  class YUIPushButton;
  class YUILabel;
  class YUIVSpacing;
  class YUIHSpacing;
  class YUIImage;



  class Dialog{
  public:
    Dialog();
    virtual Dialog * createDialog(int, int) = 0;
    virtual void Event() = 0;
  };

  class YUIDialog : public Dialog{
    YDialog * dialog;
    YAlignment * alignment;
  public:
    YUIDialog();
    virtual YUIDialog * createDialog(int x,int y);
    virtual void Event();
    YAlignment * getElement();
  };

  
  class VSpacing{
  public:
    virtual void createVSpacing(Dialog *,int dim) = 0;
    virtual void createVSpacing(VLayout *,int dim) = 0;
    virtual void createVSpacing(HLayout *,int dim) = 0;

  };

  class YUIVSpacing : public VSpacing{
    YSpacing * VSpace;
  public:
    virtual void createVSpacing(YUIDialog *,int dim);
    virtual void createVSpacing(YUIVLayout *,int dim);
    virtual void createVSpacing(YUIHLayout *,int dim);
  };

  class HSpacing{
  public:
    virtual void createHSpacing(Dialog *,int dim) = 0;
    virtual void createHSpacing(VLayout *,int dim) = 0;
    virtual void createHSpacing(HLayout *,int dim) = 0;

  };

  class YUIHSpacing : public HSpacing{
    YSpacing * HSpace;
  public:
    virtual void createHSpacing(YUIDialog *,int dim);
    virtual void createHSpacing(YUIVLayout *,int dim);
    virtual void createHSpacing(YUIHLayout *,int dim);

  };


  class VLayout{
  public:
    virtual void createVLayout(Dialog *) = 0;
    virtual void createVLayout(VLayout *) = 0;
    virtual void createVLayout(HLayout *) = 0;
  };


  class YUIVLayout : public VLayout{
    YLayoutBox * vbox;
  public:
    virtual void createVLayout(YUIDialog *);
    virtual void createVLayout(YUIVLayout *);
    virtual void createVLayout(YUIHLayout *);
    YLayoutBox * getElement();
  };

  class HLayout{
  public:
    virtual void createHLayout(Dialog *) = 0;
    virtual void createHLayout(VLayout *) = 0;
    virtual void createHLayout(HLayout *) = 0;
  };
  
  class YUIHLayout: public HLayout{
    YLayoutBox * hbox;
  public:
    virtual void createHLayout(YUIDialog *);
    virtual void createHLayout(YUIVLayout *);
    virtual void createHLayout(YUIHLayout *);
    YLayoutBox * getElement();
  };

  class Label{
    
  public:
    virtual void createLabel(VLayout * parent,string text)=0;
    virtual void createLabel(HLayout * parent,string text)=0;
  };

  class YUILabel : public Label  {
    YLabel * label;
  public: 
    virtual void createLabel(YUIVLayout * parent, string text);
    virtual void createLabel(YUIHLayout * parent, string text);

  };


  class PushButton{
  public:
    virtual void createButton(VLayout * parent,string text)=0;
    virtual void createButton(HLayout * parent,string text)=0;
  };

  class YUIPushButton : public PushButton{
    YPushButton * button;
  public:
    void createButton(YUIVLayout * parent,string text);
    void createButton(YUIHLayout * parent,string text);

  };

  class Image{
  public:
    virtual void createImage(VLayout * parent,string path)=0;
    virtual void createImage(HLayout * parent,string path)=0;
    virtual void size(int width,int height);
    
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
