//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredpoints.h"
#include <iostream>
using namespace std;

extern float frand();

ScatteredPoints::ScatteredPoints(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
	this->x = 0;
	this->y = 0;
}

void ScatteredPoints::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	this->x = target.x;
	this->y = target.y;

	glPointSize((float)size);

	BrushMove(source, target);
}

void ScatteredPoints::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int frameSize = pDoc->m_pUI->getSize();
	int num = frameSize * frameSize;
	glPointSize((float)1);

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	
		//left mouse stuff
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glBegin(GL_POINTS);
		SetColor(source);
		//int ran = (rand() % 6)-3; //rand int [-3,3]
		//cout << "Random displacement:" << ran << endl;
		int ran=0;
		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {
				SetColor(source);
				
				cout << frameSize << endl;
	
				Point a = Point(0, 0);
				for (int i = 0; i <frameSize; i+=2) {
					for (int j = 0; j < frameSize; j+=2) {
						ran = (rand() % 8) - 4; //rand int [-3,3]
						a.x = source.x - (frameSize / 2 )+ i+ ran;
						a.y= source.y - (frameSize / 2) + j + ran;
						SetColor(a);
						glVertex2d(target.x -frameSize/2 + i + ran, target.y -frameSize/2 + j+ran);

					}


					
					
				}
			}
		}
		else {
			SetColor(source);

			cout << frameSize << endl;

			Point a = Point(0, 0);
			for (int i = 0; i < frameSize; i += 2) {
				for (int j = 0; j < frameSize; j += 2) {
					ran = (rand() % 8) - 4; //rand int [-3,3]
					a.x = source.x - (frameSize / 2) + i + ran;
					a.y = source.y - (frameSize / 2) + j + ran;
					SetColor(a);
					glVertex2d(target.x - frameSize / 2 + i + ran, target.y - frameSize / 2 + j + ran);

				}
			}
		}
		glEnd();
	

}

void ScatteredPoints::BrushEnd(const Point source, const Point target)
{
	// do nothing so far

}

