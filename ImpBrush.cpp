//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"
#include <iostream>
using namespace std;
// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[3];
	
	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );

	glColor3ubv( color );

	
	
	
	double alp = pDoc->getAlpha();
	GLubyte al = 255*alp;
	

	glColor4ub(color[0], color[1],color[2], al);
	//glColor4f(1.0f, 0.5f, 0.5f, 0.5f);
	//GLubyte alp = 0.4;
	//glColor4b(color[0], color[1], color[2], alp);


	//cout << color[1] << color[2] << color[3] << alp << endl;
	//cout <<alp<< endl;
}

bool ImpBrush::CheckBoundary(Point target) {

	cout << "target.x: " << target.x << endl;
	cout << "target.y: " << target.y << endl;
	cout << "m_pDoc->m_nPaintWidth " << m_pDoc->m_nPaintWidth << endl;
	cout << "m_nPaintHeight " << m_pDoc->m_nPaintHeight << endl;
	cout << "stroke dir: " << m_pDoc->strDir << endl;

	if (target.x > m_pDoc->m_nPaintWidth || target.x <  0 || target.y >  m_pDoc->m_nPaintHeight || target.y < 0) {
		cout << "FALSE" << endl;
		return false;
	}
	
	return true;
}