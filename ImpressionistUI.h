//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_gradTypeChoice;


	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			line_width_slider;
	Fl_Slider*			line_angle_slider;
	Fl_Slider*			line_alpha_slider;
	Fl_Slider*			threshold_slider;
	Fl_Slider* red;
	Fl_Button*          m_ClearCanvasButton;
	Fl_Button*			blur;
	Fl_Button*			deepFry;
	Fl_Button*			edges;
	Fl_Button* solarize;
	Fl_Button* swap;
	Fl_Button* swaptwo;

	//Fl_Int_Input* myInput;

	Fl_Light_Button* myLightButton;
	bool myBool;
	bool target;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);
	void				rmb();

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);
	void				setAngle(int angle);

	int					getWidth();
	int					getAngle();
	double getAlpha();
	int getThreshold();
	int getlevel();
	float getRed();
	float getGreen();
	float getBlue();

	int getRadius();
	int getIntensity();



private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int     m_nWidth;
	int		m_nAngle;
	double	m_nAlpha;
	int threshold;	
	int level;
	float r;
	float g;
	float b;
	//outline color set
	int or ;
	int og;
	int ob;

	int radius;
	int intensity;
	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		GradientTypeMenu[4];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void	cb_widthSlides(Fl_Widget* o, void* v);
	static void	cb_angleSlides(Fl_Widget* o, void* v);
	static void	cb_alphaSlides(Fl_Widget* o, void* v);
	static void cb_myLightButton(Fl_Widget* o, void* v);
	static void cb_gradientChoice(Fl_Widget* o, void* v);
	static void cb_blur(Fl_Widget* o, void* v);
	static void cb_fry(Fl_Widget* o, void* v);
	static void cb_threshold_slide(Fl_Widget* o, void* v);
	static void cb_edges(Fl_Widget* o, void* v);
	static void cb_posterize_slider(Fl_Widget* o, void* v);
	static void cb_posterize(Fl_Widget* o, void* v);
	static void cb_solarize(Fl_Widget* o, void* v);
	static void cb_red_slider(Fl_Widget* o, void* v);
	static void cb_green_slider(Fl_Widget* o, void* v);
	static void cb_blue_slider(Fl_Widget* o, void* v);
	static void cb_radius_slider(Fl_Widget* o, void* v);
	static void cb_intensity_slider(Fl_Widget* o, void* v);
	static void cb_paint(Fl_Widget* o, void* v);
	static void cb_addEdges(Fl_Widget* o, void* v);
	static void cb_effectTarget(Fl_Widget* o, void* v);
	static void cb_swap(Fl_Widget* o, void* v);
	//static void cb_myInput(Fl_Widget* o, void* v);
	static void cb_swaptwo(Fl_Widget* o, void* v);
};

#endif
