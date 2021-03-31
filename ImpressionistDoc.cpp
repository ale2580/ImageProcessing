// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LineBrush.h"
#include "CircleBrush.h"
#include "ScatteredPoints.h"
#include "ScatteredLines.h"
#include "ScatteredCircles.h"
#include <iostream>
using namespace std;


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPoints( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLines( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircles( this, "Scattered Circles" );

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

	


}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}



//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	saved = new unsigned char[width * height * 3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}


//additional functions
	//change slider visibility
void ImpressionistDoc::activity(int type) {

	if (type == 1 || type==4) { 
		
		m_pUI->line_angle_slider->activate(); 
		m_pUI->line_width_slider->activate();
	
	}
	else { 
		
		m_pUI->line_angle_slider->deactivate(); 
		m_pUI->line_width_slider->deactivate();
	}
	
	
}

//stroke direction info
void ImpressionistDoc::strokeDirection(int type) {

	strDir = type;
	
}

//get linewidth
int ImpressionistDoc::getWidth() {

	return m_pUI->getWidth();

}

int ImpressionistDoc::getAngle() {

	return m_pUI->getAngle();
}

double ImpressionistDoc::getAlpha() {

	return m_pUI->getAlpha();
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetPaintingPixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nPaintWidth)
		x = m_nPaintWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nPaintHeight)
		y = m_nPaintHeight - 1;

	return (GLubyte*)(m_ucPainting + 3 * (y * m_nPaintWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetPaintingPixel(const Point p)
{
	return GetPaintingPixel(p.x, p.y);
}

//Point ImpressionistDoc::gradient(const Point source, const Point target)

Point ImpressionistDoc::gradient(const Point source)
{
	
	int Xgradient =0;
	int Ygradient =0;
	int pixelX=0;
	int pixelY = 0;
	
	

	int imgY[3][3] = {
		{1,2,1},
		{0,0,0},
		{-1,-2,-1}

	};

	int imgX[3][3] =
	{
		{ 1, 0, -1 },
		{ 2, 0, -2 },
		{ 1, 0, -1 }
	};
	for (int i = 0; i < 3; i++)

		{
			for (int j = 0; j < 3; j++){

				pixelX=source.x+i-1;

				 pixelY=source.y+j-1;

				GLubyte* pixelColor = GetOriginalPixel(pixelX, pixelY);
			 
			 Xgradient = Xgradient +  imgX[j][i] * (pixelColor[0] + pixelColor[1] + pixelColor[2]);
			
			 Ygradient = Ygradient + imgY[j][i] * (pixelColor[0] + pixelColor[1] + pixelColor[2]);
		}
	}
	return Point(Xgradient, Ygradient);
}

void ImpressionistDoc::DeepFry() {
	
	
	int width = m_nPaintWidth;
	int height = m_nPaintHeight;
	int sum = 0;
	GLubyte r = 0;
		GLubyte g = 0;
		GLubyte b = 0;
		int filterSize = 3;
	GLubyte* p;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < filterSize; k++) {
				//for (int l = 0; l < filterSize; l++) {

					//p = GetOriginalPixel(i+k, j+l);
					//p = GetPaintingPixel(i + k, j );
					if (m_pUI->target)
						p = GetOriginalPixel(i + k, j);
					else
						p = GetPaintingPixel(i + k, j);
					r = r + p[0];
					g = g + p[1];
					b = b + p[2];
					//b = 50;


				//}
			}
			r = r ;
			g = g ;
			b = b ;
			//GLuint a =p[0] << 16 + p[1] << 8 + p[2];
			//cout << a << endl;
			

			m_ucPainting[(j * width + i) * 3] = r;
			m_ucPainting[(j * width + i) * 3 + 1] = g;
			m_ucPainting[(j * width + i) * 3 + 2] = b;

			r = 0;
			g = 0;
			b = 0;
		
		}
	
	
	}

	
	m_pUI->m_paintView->redraw();
}


void ImpressionistDoc::GaussianBlur() {
	//glDrawBuffer(GL_FRONT_AND_BACK);
	float gaussian[5][5] = {
		{0.003,0.0133,0.0219, 0.0133,0.0030},
		{0.0133, 0.0596, 0.0983, 0.0596, 0.0133},
		{0.0219, 0.0983, 0.1621, 0.0983, 0.0219},
		{0.0133, 0.0596, 0.0983, 0.0596, 0.0133},
		{0.0030, 0.0133, 0.0219, 0.0133, 0.0030}

	};
	
	int width = m_nPaintWidth;
	int height = m_nPaintHeight;
	int sum = 0;
	GLubyte r = 0;
	GLubyte g = 0;
	GLubyte b = 0;
	int filterSize = 5;
	GLubyte* p;
	cout << gaussian[2][2] << "width" << m_nPaintWidth << " " << m_nPaintHeight<< endl;
	
	for (int i = 2; i < width - 2; i++) {
		for (int j = 2; j < height - 2; j++) {
			for (int k = 0; k < filterSize; k++) {
				for (int l = 0; l < filterSize; l++) {
					if (m_pUI->target)
						p = GetOriginalPixel(i - 2 + k, j - 2 + l);
					else
						p = GetPaintingPixel(i - 2 + k, j - 2 + l);
					//p = GetPaintingPixel(i - 2 + k, j - 2 + l);
					r = r + gaussian[k][l]*p[0];
					g = g + gaussian[k][l] * p[1];
					b = b + gaussian[k][l] * p[2];

					//r = 200;
					//cout << gaussian[k][l] << endl;
					//cout << "test" << endl;
				}
			}
			
			//GLuint a =p[0] << 16 + p[1] << 8 + p[2];
			//cout << a << endl;
			//cout << r << endl
			
			m_ucPainting[(j * width + i) * 3] = r;
			m_ucPainting[(j * width + i) * 3 + 1] = g;
			m_ucPainting[(j * width + i) * 3 + 2] = b;
			

			r = 0;
			g = 0;
			b = 0;

		}
		//edgeCase
		
	}

	//m_ucPainting = m_ucBitmap;
	//cout << "end" << endl;
	m_pUI->m_paintView->redraw();
}


void ImpressionistDoc::edges() {

	int thld = 200;
	int maxC = 255; int minC = 0;
	thld = m_pUI->getThreshold();
	cout << "threshold" << thld << endl;
	//const int threshold = m_pDoc->m_pUI->getEdgeThreshold();
	int width = m_nWidth;
	int height = m_nHeight;
	// glPointSize(1);
	// glBegin(GL_POINTS);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			const Point a = Point(i, j);
			const Point b = Point(j, i);
			const Point c = gradient(a);
			// if(grad.x !=0 || grad.y != 0)
			// {
			// 	printf("hey");
			// bool check = sqrt(pow(c.x, 2) + pow(c.y, 2)) > thld;
			float check = sqrt(c.x * c.x + c.y * c.y);
			
			
			if (check > thld)
			{
				
				// glColor3d(color, color, color);
				// glVertex2d(i, j);
				m_ucPainting[(j * width + i) * 3] = maxC;
				m_ucPainting[(j * width + i) * 3 + 1] = maxC;
				m_ucPainting[(j * width + i) * 3 + 2] = maxC;
			}
			else
			{
				m_ucPainting[(j * width + i) * 3] = minC;
				m_ucPainting[(j * width + i) * 3 + 1] = minC;
				m_ucPainting[(j * width + i) * 3 + 2] = minC;
			}
			// }
		}
	}
	// glEnd();
	// glFlush();
	m_pUI->m_paintView->redraw();

}


void ImpressionistDoc::posterize() {

	int numberOfDivisions=4;
	int step = 255 / numberOfDivisions;
	GLubyte* interval = new GLubyte[numberOfDivisions+1];
	GLubyte* setColor = new GLubyte[numberOfDivisions+1];
	GLubyte* p;
	int width = m_nWidth;
	int height = m_nHeight;
	setColor[0] = 0;
	setColor[1] = 255;
	int level = 100;
	level = m_pUI->getlevel();
	for (int i = 0; i < numberOfDivisions+1; i++) {
	
		interval[i] = step*i;
		setColor[i] = step*i +step;
		cout << interval[i] << " " << setColor[i] << endl;
	}
	
	for (int i = 0; i < numberOfDivisions + 1; i++) {
	
		setColor[i] = (2/ numberOfDivisions) * (i+1);
		//setColor[i] = 2;
		cout << setColor[i] << endl;
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			
			if (m_pUI->target)
				p = GetOriginalPixel(i, j);
			else
				p = GetPaintingPixel(i, j);
			
			if (p[0] < level && level / 2 < p[0]) {
				m_ucPainting[(j * width + i) * 3] = 150;

			}
			else if (p[0] < level / 2) {
				m_ucPainting[(j * width + i) * 3 ] = 30;

			}
			else {
				m_ucPainting[(j * width + i) * 3] = 210;
				
			}

			if (p[1] < level && level/2 < p[1]) {
				m_ucPainting[(j * width + i) * 3+1] =150;

			}
			else if(p[1]<level/2) {
				m_ucPainting[(j * width + i) * 3+1] = 30;

			}
			else {
				m_ucPainting[(j * width + i) * 3 + 1] = 210;
			}

			if (p[2] < level && level / 2 < p[2]) {
				m_ucPainting[(j * width + i) * 3+2] = 150;

			}
			else if (p[2] < level / 2) {
				m_ucPainting[(j * width + i) * 3 + 2] = 30;

			}
			else {
				m_ucPainting[(j * width + i) * 3+2] = 210;

			}

/*
			for (int k = 0; k < numberOfDivisions; k++) {
				if (interval[k] <= p[0] && p[0] <= interval[k + 1]){
					//cout << interval[k] << "  " << interval[k + 1] << endl;
					//cout << k << endl;
					m_ucPainting[(j * width + i) * 3] = p[0]* setColor[k];
				}
				
				else {
					m_ucPainting[(j * width + i) * 3] =p[0];
				}
				
				if (interval[k] <= p[1] && p[1] <= interval[k + 1])
					m_ucPainting[(j * width + i) * 3+1] = p[1] * setColor[k];
				
				else {
					m_ucPainting[(j * width + i) * 3 + 1] = p[1];
					
				}
				
				if (interval[k] <= p[2] && p[2] <= interval[k + 1])
					m_ucPainting[(j * width + i) * 3+2] = p[2] * setColor[k];
				
				else {
					m_ucPainting[(j * width + i) * 3 + 2] = p[2];
					
				}
				
				
				
			}
*/
			
				
		}
		
		
	}

	m_pUI->m_paintView->redraw();
}

void ImpressionistDoc::solarize() {
	int width = m_nWidth;
	int height = m_nHeight;
	int level = m_pUI->getlevel();
	GLubyte* p;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (m_pUI->target)
				p = GetOriginalPixel(i, j);
			else
				p = GetPaintingPixel(i, j);

			if (p[0] > level)
				m_ucPainting[(j * width + i) * 3] = 255 - p[0];
			else
				m_ucPainting[(j * width + i) * 3] = p[0];
			
			if (p[1] > level)
				m_ucPainting[(j * width + i) * 3+1] = 255 - p[1];
			else
				m_ucPainting[(j * width + i) * 3+1] = p[1];
			
			if (p[2] > level)
				m_ucPainting[(j * width + i) * 3+2] = 255 - p[2];
			else
				m_ucPainting[(j * width + i) * 3+2] = p[2];
		
		}
	
	
	}

	m_pUI->m_paintView->redraw();

}

void ImpressionistDoc::cartoon() {


	//saveContent();
	int threshold = 200;
	threshold = m_pUI->getThreshold();
	cout << "threshold" << threshold << endl;
	//const int threshold = m_pDoc->m_pUI->getEdgeThreshold();
	int width = m_nWidth;
	int height = m_nHeight;
	GLubyte* p;
	float r =m_pUI->getRed();
	float g = m_pUI->getGreen();
	float b = m_pUI->getBlue();
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			
			
			
		//original image editing
			
			p = GetOriginalPixel(i,j);

			if(p[0]*r <=255)
				m_ucPainting[(j * width + i) * 3] = p[0] *r;
			if (p[1] * g <= 255)
				m_ucPainting[(j * width + i) * 3 + 1] = p[1]*g;
			if (p[2] * b <= 255)
				m_ucPainting[(j * width + i) * 3 + 2] =p[2]*b;
			
			
			
		}
	}
	// glEnd();
	// glFlush();
	
	m_pUI->m_paintView->redraw();


}

void ImpressionistDoc::saveContent() {
	int width = m_nWidth;
	int height = m_nHeight;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

				saved[(j * width + i) * 3] = m_ucPainting[(j * width + i) * 3];
			
				saved[(j * width + i) * 3 + 1] = m_ucPainting[(j * width + i) * 3 + 1];
				saved[(j * width + i) * 3+2] =m_ucPainting[(j * width + i) * 3 + 2] ;
		
		
		}
	
	}

}

void ImpressionistDoc::painter() {
	
	
	int radius = m_pUI->getRadius();
	int intensity = m_pUI->getIntensity();
	int width = m_nWidth;
	int height = m_nHeight;
	int* nIntensityCount = new int[intensity+1];
	int* nSumR = new int[intensity + 1];
	int* nSumG= new int[intensity + 1];
	int* nSumB = new int[intensity + 1];
	//GLubyte i = 0;

	
	GLubyte* p;
	for (int i = radius; i<width-radius; i++)
	{
		for (int j = radius; j<height-radius; j++)

		{
			for (int i = 0; i < intensity + 1; i++) {

				nIntensityCount[i] = 0;
				nSumR[i] = 0;
				nSumG[i] = 0;
				nSumB[i] = 0;

			}
			
			// Find intensities of nearest nRadius pixels in four direction.
			for (int k= -radius; k <= radius; k++)
			{
				for (int l = -radius; l <= radius; l++)
				{
					
					//p = GetPaintingPixel(i+k,j+l);

					if (m_pUI->target)
						p = GetOriginalPixel(i+k, j+l);
					else
						p = GetPaintingPixel(i+k, j+l);

					int nR = p[0];
					int nG = p[1];
					int nB = p[2];

					// Find intensity of RGB value and apply intensity level.
					int nCurIntensity = (((nR + nG + nB) / 3.0) * intensity) / 255;
					if (nCurIntensity > 255)
						nCurIntensity = 255;
					/**/
					
					int i = nCurIntensity;
					nIntensityCount[i]++;
					//cout << "curr int" << nIntensityCount[i] << endl;
					nSumR[i] = nSumR[i] + nR;
					nSumG[i] = nSumG[i] + nG;
					nSumB[i] = nSumB[i] + nB;
					//cout << nSumR[i] << endl;
				}
			}

			int nCurMax = 0;
			int nMaxIndex = 0;
			for (int nI = 0; nI < intensity + 1; nI++)
			{
				if (nIntensityCount[nI] > nCurMax)
				{
					nCurMax = nIntensityCount[nI];
					nMaxIndex = nI;
				}
			}

			

			
				m_ucPainting[(j * width + i) * 3] = nSumR[nMaxIndex] / nCurMax;
			
				m_ucPainting[(j * width + i) * 3 + 1] = nSumG[nMaxIndex] / nCurMax;
			
				m_ucPainting[(j * width + i) * 3 + 2] = nSumB[nMaxIndex] / nCurMax;

		}
	}
	m_pUI->m_paintView->redraw();

}

void ImpressionistDoc::addEdges() {

	
	int thld = 200;
	int maxC = 255; int minC = 0;
	thld = m_pUI->getThreshold();
	cout << "threshold" << thld << endl;
	//const int threshold = m_pDoc->m_pUI->getEdgeThreshold();
	int width = m_nWidth;
	int height = m_nHeight;
	// glPointSize(1);
	// glBegin(GL_POINTS);
	for (int i = 0; i <width; i++){
		for (int j = 0; j< height; j++){
			const Point a = Point(i, j);
			const Point b = Point(j, i);
			const Point c = gradient(a);
			// if(grad.x !=0 || grad.y != 0)
			// {
			// 	printf("hey");
			// bool check = sqrt(pow(c.x, 2) + pow(c.y, 2)) > thld;
			float check = sqrt(c.x * c.x + c.y * c.y);

			GLubyte* pixel = GetPaintingPixel(i,j);
			if (check > thld)
			{

				// glColor3d(color, color, color);
				// glVertex2d(i, j);
				m_ucPainting[(j * width + i) * 3] = 255;
				m_ucPainting[(j * width + i) * 3 + 1] = 255;
				m_ucPainting[(j * width + i) * 3 + 2] = 255;
			}
			else
			{
				m_ucPainting[(j * width + i) * 3] = pixel[0];
				m_ucPainting[(j * width + i) * 3 + 1] = pixel[1];
				m_ucPainting[(j * width + i) * 3 + 2] = pixel[2];
			}
			// }
		}
	}
	// glEnd();
	// glFlush();
	m_pUI->m_paintView->redraw();


}

void ImpressionistDoc::swap() {
	int size = m_nPaintWidth * m_nPaintHeight * 3;
	//saved = new unsigned char[m_nPaintWidth * m_nPaintHeight * 3];
	
		
		for (int i = 0; i < size; i++) {
		
			m_ucBitmap[i] = m_ucPainting[i];
		}
		m_pUI->m_origView->redraw();
}

void ImpressionistDoc::swaptwo() {
	int size = m_nPaintWidth * m_nPaintHeight * 3;
	//saved = new unsigned char[m_nPaintWidth * m_nPaintHeight * 3];


	for (int i = 0; i < size; i++) {

		 m_ucPainting[i] = m_ucBitmap[i];
	}
	m_pUI->m_paintView->redraw();
}

void ImpressionistDoc::noiseTime() {
	
	int width = m_nWidth;
	int height = m_nHeight;

	//make it black
	for (int i = 5; i < width-5; i++) {
		for (int j = 5; j < height-5; j++) {
			
			m_ucPainting[(j * width + i) * 3] =0;
			m_ucPainting[(j * width + i) * 3 + 1] = 0;
			m_ucPainting[(j * width + i) * 3 + 2] = 0;
			
		}
	}
	int z = 0;
	for (int i = 8; i < width-8; i++) {
	
		for (int j = 8; j<height-8; j++) {
			GLubyte* pixel = GetOriginalPixel(i, j);
			int z = cos( 2*i)*cos( 2*j);
			cout << z << endl;
			m_ucPainting[((j+z) * width + (i+z)) * 3] = pixel[0];
			m_ucPainting[((j+z) * width + (i + z)) * 3 + 1] = pixel[1];
			m_ucPainting[((j + z) * width + (i + z)) * 3 + 2] = pixel[2];
			
			
		}
	}
	m_pUI->m_origView->redraw();
}