//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "linebrush.h"
#include <iostream>
using namespace std;
extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
	//pDoc->m_pUI->line_angle_slider->activate();
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();


	xp = source.x;
	yp = source.y;
	glPointSize((float)size);

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();
	int half = size / 2;
	int lineWidth = pDoc->getWidth();
	int lw = lineWidth / 2;
	int ang = pDoc->getAngle();
	int strokeMode = pDoc->strDir;
	cout << strokeMode << endl;
	 glLineWidth(lineWidth);
	//int lineWidth = pDoc->
	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}
	
	//gradient MODE
	if (strokeMode == 2) {

		Point a = pDoc->gradient(source);
		double ang = 180* atan2(a.y, a.x)/M_PI;


		glPushMatrix();

		glTranslatef(target.x, target.y, 0);
		glRotatef(ang, 0, 0, 1);

		glTranslatef(-target.x, -target.y, 0);

		glBegin(GL_LINES);
		SetColor(source);


		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {
				glVertex2d(target.x - half, target.y);

				glVertex2d(target.x + half, target.y);
			}
		}
		else {
			glVertex2d(target.x - half, target.y);

			glVertex2d(target.x + half, target.y);

		}


		glEnd();
		glPopMatrix();
	}

	if (strokeMode == 1) {
		glPushMatrix();

		glTranslatef(target.x, target.y, 0);
		glRotatef(ang, 0, 0, 1);

		glTranslatef(-target.x, -target.y, 0);

		glBegin(GL_LINES);
		SetColor(source);


		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {
				glVertex2d(target.x - half, target.y);

				glVertex2d(target.x + half, target.y);
			}
		}
		else {
			glVertex2d(target.x - half, target.y);

			glVertex2d(target.x + half, target.y);

		}


		glEnd();
		glPopMatrix();
	}
	//brish direction mode
	if (strokeMode == 3) {

		
		double ang = 180*atan2(yp - source.y, xp - source.x)/M_PI;


		glPushMatrix();

		glTranslatef(target.x, target.y, 0);
		glRotatef(ang, 0, 0, 1);

		glTranslatef(-target.x, -target.y, 0);

		glBegin(GL_LINES);
		SetColor(source);


		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {
				glVertex2d(target.x - half, target.y);

				glVertex2d(target.x + half, target.y);
			}
		}
		else {
			glVertex2d(target.x - half, target.y);

			glVertex2d(target.x + half, target.y);

		}


		glEnd();
		glPopMatrix();

		xp = source.x;
		yp = source.y;
	}



}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void LineBrush::rmbegin(const Point source, const Point target)
{
	x = target.x;
	y = target.y;
}

void LineBrush::rmmove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int currentSize = dlg->getWidth();
	glLineWidth(2);
	cout << " test" << endl;
	
	glColor3f(1, 0, 0);
	//GLubyte a = 1;
	//glColor3s(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(x, y);
	glVertex2d(target.x, target.y);
	glEnd();
	glLineWidth(currentSize);
}

void LineBrush::rmend(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int angle = static_cast<int>((180*(atan2(target.y - y, target.x - x)))/M_PI);
	if (angle < 0) {
		angle = 360 + angle;
	
	}
	int size2 = sqrt((target.y - y) * (target.y - y) + (target.x - x) * (target.x - x));
	dlg->setAngle(angle);
	dlg->setSize(size2);
}