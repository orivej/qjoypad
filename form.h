#ifndef FORM_H
#define FORM_H



//Constants for you to edit!
#define NAME			"QJoyPad 1.3"		//The title on the title bar!
#define DEVICE			"/dev/input/js"	//Where your joysticks are
#define BUTTONS		10						//Maximum number of buttons on a joystick
#define JOYSTICKS		4						//Maximum number of joysticks

//Also, if you don't like the default color for the flashing buttons,
//you can go into flash.h and change HIGHLIGHT to any color you wish.


//--- --- --- --- End of editable code.






//From the QT Libraries
#include <qdialog.h>
#include <qpushbutton.h>
#include <qcolor.h>
#include <qlayout.h>
#include <qintdict.h>
#include <qcombobox.h>
#include <qptrlist.h>
#include <qinputdialog.h>
#include <qfile.h>
#include <qwidgetstack.h>
#include <qthread.h>
#include <qmessagebox.h>
#include <qslider.h>

//Used to grab the user's home directory
#include <stdlib.h>

//used for basic file transfer and the js_event type
#include <asm/types.h>
#include <fcntl.h>
#include <unistd.h>

//Used to get an input key from the user
#include "keycode.h"

//Used to send keypress events to the active window
#include "sendevent.h"

//Used to have those nifty flashing buttons
#include "flash.h"

//Don't edit these constants ;)
#define UP				BUTTONS
#define DOWN			BUTTONS + 1
#define LEFT			BUTTONS + 2
#define RIGHT			BUTTONS + 3



// Joystick device constants
#define JS_EVENT_BUTTON 0x01    /* button pressed/released */
#define JS_EVENT_AXIS   0x02    /* joystick moved */
#define JS_VERTICAL     1
#define JS_HORIZONTAL   0

// taken from the Linux kernel joystick documentation
struct js_event {
	__u32 time;     /* event timestamp in milliseconds */
	__s16 value;    /* value */
	__u8 type;      /* event type */
	__u8 number;    /* axis/button number */
};



//One keycode layout to represent one joystick.
//This is a struct only because of some of the
//limitations imposed on array types.
struct JoyKeys
{
	int Buttons[BUTTONS + 4];
	int Sensitivity;
};

//One save state consisting of one layout for each joystick
typedef JoyKeys OneSave[JOYSTICKS];

//One set of buttons representing all the keys on a joystick
//This representation also holds all the keycodes and actually
//triggers the keypress events.
class JoyKeyPad : public QWidget
{
	Q_OBJECT
	public:
		JoyKeyPad( QWidget* parent );
		JoyKeys getState();
		void flash( int index );
		void key( int type, int index );
		int sensitivity();
	public slots:	
		void clear();
		void setState( JoyKeys keys );
	private slots:
		void getKey();
		void all();
	private:
		QString Name( int index );
		void getkey( int index );
		
		GetKey* Key;
		QGridLayout* LMain;
		QSlider* Sense;
		FlashButton* Buttons[BUTTONS+4];
		int KeyCodes[BUTTONS+4];
		QPushButton* BClear;
		QPushButton* BAll;
};

//A thread used to monitor a joystick device and produce proper results.
class JoyThread : public QThread
{
	public:
		JoyThread( int index, FlashRadioArray* sticks, JoyKeyPad* pad );
		virtual void run();
		void clean();
	private:
		int Index;
		//QFile* file;
		int file;
		FlashRadioArray* Sticks;
		JoyKeyPad* Pad;
};


//The main dialog and the editable combo box
class DMain : public QDialog
{
	Q_OBJECT
	public:
		DMain();
	private slots:
		void CAdd();
		void CRem();
		void CUpdate();
		void CRevert();
	public slots:
		void done( int );
	private:	
		void Clear();
		QVBoxLayout* LMain;
		
		JoyThread* Thread[4];
	
		QFrame* CFrame;
		QGridLayout* CLayout;
		QComboBox* CCombo;
		QPushButton* CBAdd;
		QPushButton* CBRem;
		QPushButton* CBUpdate;
		QPushButton* CBRevert;
		QPtrList<OneSave> Items;
		void CSave();
		void CLoad();
		
		FlashRadioArray* JoyStick;
		QWidgetStack* Stack;
};


#endif