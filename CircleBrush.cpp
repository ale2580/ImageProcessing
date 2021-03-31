//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circlebrush.h"
#include <iostream>
using namespace std;

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
	this->x = 0;
	this->y = 0;
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	this->x = target.x;
	this->y = target.y;

	glPointSize((float)size);

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	static const int circle_points = 3;
	static const float angle = 2.0f * 3.1415f / circle_points;
	int radius = pDoc->m_pUI->getSize() / 2;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	
	
		//left mouse stuff
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		
		SetColor(source);
		//glMatrixMode(GL_MODELVIEW);

		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {
				glBegin(GL_POLYGON);
				double angle1 = 0.0;

				//cout << "SIZE" << pDoc->m_pUI->getSize() << endl;

				int i;
				for (i = 0; i < circle_points; i++)
				{
					glVertex2d(target.x + radius * cos(angle1), target.y + radius * sin(angle1));
					angle1 += angle;
					//cout << "size*cosangle" << 180 * pDoc->m_nSize * cos(angle1) / M_PI << endl;
				}
				glEnd();
			}
		}
		else {
			

			glBegin(GL_POLYGON);
			double angle1 = 0.0;
			
			//scout << "SIZE" << pDoc->m_pUI->getSize() << endl;
			
			int i;
			for (i = 0; i < circle_points; i++)
			{
				glVertex2d(target.x + radius * cos(angle1),target.y+ radius * sin(angle1));
				angle1 += angle;
				//cout << "size*cosangle" << 180*pDoc->m_nSize * cos(angle1)/M_PI << endl;
			}
			glEnd();
			

		}
		
	

}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far

}

