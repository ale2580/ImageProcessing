//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"
#include <iostream> 
using namespace std;

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------



void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}



//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;
	
	pDoc->activity(type);
	pDoc->setBrushType(type);
}

//gradient choice call back
void ImpressionistUI::cb_gradientChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;
	
	pDoc->strokeDirection(type);
	//pDoc->setBrushType(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

//swap original button
void ImpressionistUI::cb_swap(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->swap();
}

void ImpressionistUI::cb_swaptwo(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->swaptwo();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_widthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nWidth = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_angleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAngle = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = double(((Fl_Slider*)o)->value());
	
}

void ImpressionistUI::cb_threshold_slide(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->threshold = int(((Fl_Slider*)o)->value());

}

void ImpressionistUI::cb_blur(Fl_Widget* o, void* v)
{
	
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->GaussianBlur();
	
}

void ImpressionistUI::cb_fry(Fl_Widget* o, void* v)
{

	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->DeepFry();

}

void ImpressionistUI::cb_edges(Fl_Widget* o, void* v)
{

	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->edges();
	//pDoc->posterize();

}

void ImpressionistUI::cb_posterize_slider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->level = int(((Fl_Slider*)o)->value());

}

void ImpressionistUI::cb_posterize(Fl_Widget* o, void* v)
{

	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	
	pDoc->posterize();

}

void ImpressionistUI::cb_solarize(Fl_Widget* o, void* v)
{

	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	
	pDoc->solarize();
	
	//pDoc->swap();
	

}

void ImpressionistUI::cb_paint(Fl_Widget* o, void* v)
{

	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	
	//pDoc->solarize();
	//pDoc->cartoon();
	pDoc->painter();

}

void ImpressionistUI::cb_addEdges(Fl_Widget* o, void* v)
{

	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	
	pDoc->addEdges();
	//pDoc->cartoon();
//	pDoc->noiseTime();


}

void ImpressionistUI::cb_red_slider(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->r = float(((Fl_Slider*)o)->value());
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->cartoon();
}
void ImpressionistUI::cb_green_slider(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->g = float(((Fl_Slider*)o)->value());
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->cartoon();

}
void ImpressionistUI::cb_blue_slider(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->b = float(((Fl_Slider*)o)->value());
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->cartoon();
	
}

void ImpressionistUI::cb_radius_slider(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->radius = float(((Fl_Slider*)o)->value());
	//ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	//pDoc->painte();

}
void ImpressionistUI::cb_intensity_slider(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->intensity = float(((Fl_Slider*)o)->value());
	//ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	//pDoc->painte();

}
//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//check for rmb
void ImpressionistUI::rmb() {
	cout << 'test' << endl;
	//cout << m_paintView->handle(Fl::event_button2()) << endl;
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
	
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//return linewidth
int ImpressionistUI:: getWidth() {

	return m_nWidth;
}

int ImpressionistUI::getAngle() {

	return m_nAngle;
}

double ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}

int ImpressionistUI::getThreshold()
{
	return threshold;
}

int ImpressionistUI::getlevel() {

	return level;

}

float ImpressionistUI:: getRed() {
	return r;

}

float ImpressionistUI::getBlue() {
	return b;

}

float ImpressionistUI::getGreen() {
	return g;

}

int ImpressionistUI::getRadius() {
	return radius;
}

int ImpressionistUI::getIntensity() {

	return intensity;
}

void ImpressionistUI::setAngle(int angle) {
	cout << angle << endl;
	m_nAngle = angle;
	if (angle <= 359 && angle>=0)
		line_angle_slider->value(angle);

}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {0}
};

//gradient menu
// Brush choice menu definition

Fl_Menu_Item ImpressionistUI::GradientTypeMenu[4] = {
  {"Slider/Right Mouse",			FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_gradientChoice,(void*)1},
  {"Gradient",				FL_ALT + 'g', (Fl_Callback*)ImpressionistUI::cb_gradientChoice, (void*)2},
  {"Brush Direction",			FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_gradientChoice, (void*)3},
  {0}
};

//---The light button callback---------------------
void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->myBool == TRUE) pUI->myBool = FALSE;
	else pUI->myBool = TRUE;
}

void ImpressionistUI::cb_effectTarget(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->target == TRUE) pUI->target = FALSE;
	else pUI->target = TRUE;
}



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);
			
			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nWidth = 1;
	m_nAngle = 0;
	m_nAlpha = 1;
	threshold = 500;
	myBool = false;
	target = true;
	level = 100;
	r = 1;
	g = 1;
	b = 1;
	radius = 2;
	intensity = 10;
	or = 255;
	og = 255;
	ob = 255;

	// brush dialog definition
	m_brushDialog = new Fl_Window(600, 900, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		//Add brush line width slider
		line_width_slider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		line_width_slider->user_data((void*)(this));	// record self to be used by static callback functions
		line_width_slider->type(FL_HOR_NICE_SLIDER);
		line_width_slider->labelfont(FL_COURIER);
		line_width_slider->labelsize(12);
		line_width_slider->minimum(1);
		line_width_slider->maximum(40);
		line_width_slider->step(1);
		line_width_slider->value(m_nWidth);
		line_width_slider->align(FL_ALIGN_RIGHT);
		line_width_slider->callback(cb_widthSlides);
		line_width_slider->deactivate();

		//Add line angle slider
		line_angle_slider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		line_angle_slider->user_data((void*)(this));	// record self to be used by static callback functions
		line_angle_slider->type(FL_HOR_NICE_SLIDER);
		line_angle_slider->labelfont(FL_COURIER);
		line_angle_slider->labelsize(12);
		line_angle_slider->minimum(0);
		line_angle_slider->maximum(359);
		line_angle_slider->step(1);
		line_angle_slider->value(m_nAngle);
		line_angle_slider->align(FL_ALIGN_RIGHT);
		line_angle_slider->callback(cb_angleSlides);
		line_angle_slider->deactivate();
	
		
		
		
		//Alpha Slider
		line_alpha_slider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		line_alpha_slider->user_data((void*)(this));	// record self to be used by static callback functions
		line_alpha_slider->type(FL_HOR_NICE_SLIDER);
		line_alpha_slider->labelfont(FL_COURIER);
		line_alpha_slider->labelsize(12);
		line_alpha_slider->minimum(0);
		line_alpha_slider->maximum(1);
		line_alpha_slider->step(0.01);
		line_alpha_slider->value(m_nAlpha);
		line_alpha_slider->align(FL_ALIGN_RIGHT);
		line_alpha_slider->callback(cb_alphaSlides);


		myLightButton = new Fl_Light_Button(10, 200, 120, 20, "Edge Clipping");
		myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
		myLightButton->callback(cb_myLightButton);

		myLightButton = new Fl_Light_Button(10, 560, 300, 20, "affect original or painting window");
		myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
		myLightButton->callback(cb_effectTarget);

		//add grad type choice 
	
		m_gradTypeChoice = new Fl_Choice(120, 40, 150, 25, "&Stroke Direction");
		m_gradTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_gradTypeChoice->menu(GradientTypeMenu);

		m_gradTypeChoice->callback(cb_gradientChoice);
		

		//button
		//------------Button---------------------------------------

	//---To install a button---------------------------
		blur = new Fl_Button(150, 850, 120, 20, "5x5 Gaussian Blur");
		blur->user_data((void*)(this));   // record self to be used by static callback functions
		blur->callback(cb_blur);


		deepFry = new Fl_Button(10, 850, 120, 20, "DEEP FRY");
		deepFry->user_data((void*)(this));   // record self to be used by static callback functions
		deepFry->callback(cb_fry);

		edges = new Fl_Button(10, 260, 120, 20, "findEdges");
		edges->user_data((void*)(this));   // record self to be used by static callback functions
		edges->callback(cb_edges);

		edges = new Fl_Button(10, 750, 120, 20, "IMPRESSIONIST");
		edges->user_data((void*)(this));   // record self to be used by static callback functions
		edges->callback(cb_paint);

		blur = new Fl_Button(140, 260, 120, 20, "Add Outline");
		blur->user_data((void*)(this));   // record self to be used by static callback functions
		blur->callback(cb_addEdges);


		
		threshold_slider = new Fl_Value_Slider(10, 230, 300, 20, "Threshold");
		threshold_slider->user_data((void*)(this));	// record self to be used by static callback functions
		threshold_slider->type(FL_HOR_NICE_SLIDER);
		threshold_slider->labelfont(FL_COURIER);
		threshold_slider->labelsize(12);
		threshold_slider->minimum(0);
		threshold_slider->maximum(1000);
		threshold_slider->step(1);
		threshold_slider->value(threshold);
		threshold_slider->align(FL_ALIGN_RIGHT);
		threshold_slider->callback(cb_threshold_slide);
		//threshold_slider->deactivate();


		threshold_slider = new Fl_Value_Slider(10, 600, 300, 20, "posterize/solarize Threshold");
		threshold_slider->user_data((void*)(this));	// record self to be used by static callback functions
		threshold_slider->type(FL_HOR_NICE_SLIDER);
		threshold_slider->labelfont(FL_COURIER);
		threshold_slider->labelsize(12);
		threshold_slider->minimum(0);
		threshold_slider->maximum(255);
		threshold_slider->step(1);
		threshold_slider->value(level);
		threshold_slider->align(FL_ALIGN_RIGHT);
		threshold_slider->callback(cb_posterize_slider);
		
		edges = new Fl_Button(10, 630, 120, 20, "posterize apply");
		edges->user_data((void*)(this));   // record self to be used by static callback functions
		edges->callback(cb_posterize);

		solarize = new Fl_Button(160, 630, 120, 20, "solarize apply");
		solarize->user_data((void*)(this));   // record self to be used by static callback functions
		solarize->callback(cb_solarize);

		swap = new Fl_Button(420, 10, 150, 25, "Paint view -> Original");
		swap->user_data((void*)(this));   // record self to be used by static callback functions
		swap->callback(cb_swap);

		swaptwo = new Fl_Button(420, 40, 150, 25, "Original -> Paint view");
		swaptwo->user_data((void*)(this));   // record self to be used by static callback functions
		swaptwo->callback(cb_swaptwo);


		

		threshold_slider = new Fl_Value_Slider(10, 300, 300, 20, "red");
		threshold_slider->user_data((void*)(this));	// record self to be used by static callback functions
		threshold_slider->type(FL_HOR_NICE_SLIDER);
		threshold_slider->labelfont(FL_COURIER);
		threshold_slider->labelsize(12);
		threshold_slider->minimum(0);
		threshold_slider->maximum(2);
		threshold_slider->step(0.01);
		threshold_slider->value(r);
		threshold_slider->align(FL_ALIGN_RIGHT);
		threshold_slider->callback(cb_red_slider);

		threshold_slider = new Fl_Value_Slider(10, 330, 300, 20, "green");
		threshold_slider->user_data((void*)(this));	// record self to be used by static callback functions
		threshold_slider->type(FL_HOR_NICE_SLIDER);
		threshold_slider->labelfont(FL_COURIER);
		threshold_slider->labelsize(12);
		threshold_slider->minimum(0);
		threshold_slider->maximum(2);
		threshold_slider->step(0.01);
		threshold_slider->value(g);
		threshold_slider->align(FL_ALIGN_RIGHT);
		threshold_slider->callback(cb_green_slider);

		threshold_slider = new Fl_Value_Slider(10, 360, 300, 20, "blue");
		threshold_slider->user_data((void*)(this));	// record self to be used by static callback functions
		threshold_slider->type(FL_HOR_NICE_SLIDER);
		threshold_slider->labelfont(FL_COURIER);
		threshold_slider->labelsize(12);
		threshold_slider->minimum(0);
		threshold_slider->maximum(2);
		threshold_slider->step(0.01);
		threshold_slider->value(b);
		threshold_slider->align(FL_ALIGN_RIGHT);
		threshold_slider->callback(cb_blue_slider);

		threshold_slider = new Fl_Value_Slider(10, 690, 300, 20, "radius (IMPRESSIONIST)");
		threshold_slider->user_data((void*)(this));	// record self to be used by static callback functions
		threshold_slider->type(FL_HOR_NICE_SLIDER);
		threshold_slider->labelfont(FL_COURIER);
		threshold_slider->labelsize(12);
		threshold_slider->minimum(1);
		threshold_slider->maximum(10);
		threshold_slider->step(1);
		threshold_slider->value(b);
		threshold_slider->align(FL_ALIGN_RIGHT);
		threshold_slider->callback(cb_radius_slider);

		threshold_slider = new Fl_Value_Slider(10, 720, 300, 20, "intensity (IMPRESSIONIST)");
		threshold_slider->user_data((void*)(this));	// record self to be used by static callback functions
		threshold_slider->type(FL_HOR_NICE_SLIDER);
		threshold_slider->labelfont(FL_COURIER);
		threshold_slider->labelsize(12);
		threshold_slider->minimum(1);
		threshold_slider->maximum(50);
		threshold_slider->step(1);
		threshold_slider->value(b);
		threshold_slider->align(FL_ALIGN_RIGHT);
		threshold_slider->callback(cb_intensity_slider);

		



    m_brushDialog->end();	

}

