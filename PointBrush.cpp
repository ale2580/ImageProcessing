//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "pointbrush.h"
#include <iostream>
using namespace std;

extern float frand();

PointBrush::PointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
	this->x = 0;
	this->y = 0;
}

void PointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();

	this->x = target.x;
	this->y = target.y;

	glPointSize( (float)size );

	BrushMove( source, target );

}

void PointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	if (pDoc->rmb) { //right mouse stuff
		
		
	}
	else {
		//left mouse stuff
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glBegin(GL_POINTS);
		SetColor(source);

		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {
				glVertex2d(target.x, target.y);
			}
		}
		else {
			glVertex2d(target.x, target.y);
			//cout << "MYBOOL FALSE" << endl;

		}
		glEnd();
	}
	
}

void PointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
	ImpressionistDoc* pDoc = GetDocument();
	//pDoc->GaussianBlur();
	
	
}

