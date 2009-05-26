#ifndef AXIS_EDIT_H
#define AXIS_EDIT_H

//for building up the dialog we need
#include <qdialog.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qlabel.h>

//for my home-brewed widgets
#include "joyslider.h"
#include "keycode.h"

//to refer to the axis we're editing
#include "axis.h"

class AxisEdit : public QDialog {
	Q_OBJECT
	public:
		AxisEdit(Axis* ax);
		//show the dialog (modal)
		void show();
		//set the current state of the axis (adjusts the JoySlider for real time
		//notification of the state to the user)
		void setState( int val );
	protected slots:
		//slots for GUI events
		void CModeChanged( int index );
		void CThrottleChanged( int index );
		void accept();
	protected:
		//the associated Axis that needs to be set.
		Axis *axis;
		//the important parts of the dialog:
		QCheckBox *CGradient;
		QComboBox *CMode, *CThrottle;
		QFrame *MouseBox, *KeyBox;
		QSpinBox *SSpeed;
		KeyButton *BNeg, *BPos;
		JoySlider *Slider;
		QPushButton *BOkay, *BCancel;
};

#endif
