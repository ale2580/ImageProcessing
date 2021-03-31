//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredlines.h"
#include <iostream>
using namespace std;
extern float frand();

ScatteredLines::ScatteredLines(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
	//pDoc->m_pUI->line_angle_slider->activate();
}

void ScatteredLines::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();


	xp = source.x;
	yp = source.y;
	glPointSize((float)size);

	BrushMove(source, target);
}

void ScatteredLines::BrushMove(const Point source, const Point target)
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
	int range = dlg->getSize();
	int randomY = 0;
	int randomX = 0;
	//int lineWidth = pDoc->
	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	//random gen
	int numLines = rand() % 2 + 3; //3 or 4 lines

	//gradient MODE
	if (strokeMode == 2) {

		int randomLength = rand() % (2 * half) - half;
		Point  colorsample = Point(0, 0);
		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {

				for (int i = 0; i < numLines; i++) {

					randomLength = rand() % (2 * half) - half;
					randomY = (rand() % range) - (range / 2);
					randomX = (rand() % range);
					cout << "RANDOM Y: " << randomY << endl;
					colorsample.x = target.x + randomLength;
					colorsample.y = target.y + randomY;
					Point a = Point(0, 0);
					a.x = target.x + randomLength;
					a.y = target.y + randomY;
					Point grad = pDoc->gradient(a);
					double ang = 180 * atan2(grad.y, grad.x) / M_PI;
					glPushMatrix();

					glTranslatef(target.x, target.y, 0);
					glRotatef(ang, 0, 0, 1);

					glTranslatef(-target.x, -target.y, 0);

					glBegin(GL_LINES);
					SetColor(source);
					SetColor(colorsample);
					glVertex2d(target.x + randomX + randomLength, target.y + randomY);

					glVertex2d(target.x - randomX + randomLength, target.y + randomY);

				}

			}
		}
		else {

			for (int i = 0; i < numLines; i++) {

				randomLength = rand() % (2 * half) - half;
				randomY = (rand() % range) - (range / 2);
				randomX = (rand() % range);
				cout << "RANDOM Y: " << randomY << endl;
				colorsample.x = target.x + randomLength;
				colorsample.y = target.y + randomY;
				Point a = Point(0, 0);
				a.x = target.x + randomLength;
				a.y = target.y + randomY;
				Point grad = pDoc->gradient(a);
				double ang = 180 * atan2(grad.y, grad.x) / M_PI;
				glPushMatrix();

				glTranslatef(target.x, target.y, 0);
				glRotatef(ang, 0, 0, 1);

				glTranslatef(-target.x, -target.y, 0);

				glBegin(GL_LINES);
				SetColor(source);
				SetColor(colorsample);
				glVertex2d(target.x + randomX + randomLength, target.y + randomY);

				glVertex2d(target.x - randomX + randomLength, target.y + randomY);

			}

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
		int randomLength = rand() % (2 * half) - half;
		Point  colorsample = Point(0, 0);
		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {

				for (int i = 0; i < numLines; i++) {
					randomLength = rand() % (2 * half) - half;
					randomY = (rand() % range) - (range / 2);
					randomX = (rand() % range);
					cout << "RANDOM Y: " << randomY << endl;
					colorsample.x = target.x + randomLength;
					colorsample.y = target.y + randomY;
					SetColor(colorsample);
					glVertex2d(target.x + randomX + randomLength, target.y + randomY);

					glVertex2d(target.x - randomX + randomLength, target.y + randomY);

				}

			}
		}
		else {

			for (int i = 0; i < numLines; i++) {
				randomLength = rand() % (2 * half) - half;
				randomY = (rand() % range) - (range / 2);
				randomX = (rand() % range);
				cout << "RANDOM Y: " << randomY << endl;
				colorsample.x = target.x + randomLength;
				colorsample.y = target.y + randomY;
				SetColor(colorsample);
				glVertex2d(target.x + randomX + randomLength, target.y + randomY);

				glVertex2d(target.x - randomX + randomLength, target.y + randomY);

			}

		}


		glEnd();
		glPopMatrix();
	}
	//brish direction mode
	if (strokeMode == 3) {





		int randomLength = rand() % (2 * half) - half;
		Point  colorsample = Point(0, 0);
		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {

				for (int i = 0; i < numLines; i++) {

					randomLength = rand() % (2 * half) - half;
					randomY = (rand() % range) - (range / 2);
					randomX = (rand() % range);
					cout << "RANDOM Y: " << randomY << endl;
					colorsample.x = target.x + randomLength;
					colorsample.y = target.y + randomY;
					Point a = Point(0, 0);
					a.x = target.x + randomLength;
					a.y = target.y + randomY;
				
					double ang = 180 * atan2(yp - source.y, xp - source.x) / M_PI;
					glPushMatrix();

					glTranslatef(target.x, target.y, 0);
					glRotatef(ang, 0, 0, 1);

					glTranslatef(-target.x, -target.y, 0);

					glBegin(GL_LINES);
					SetColor(source);
					SetColor(colorsample);
					glVertex2d(target.x + randomX + randomLength, target.y + randomY);

					glVertex2d(target.x - randomX + randomLength, target.y + randomY);

				}

			}
		}
		else {

			for (int i = 0; i < numLines; i++) {

				randomLength = rand() % (2 * half) - half;
				randomY = (rand() % range) - (range / 2);
				randomX = (rand() % range);
				cout << "RANDOM Y: " << randomY << endl;
				colorsample.x = target.x + randomLength;
				colorsample.y = target.y + randomY;
				Point a = Point(0, 0);
				a.x = target.x + randomLength;
				a.y = target.y + randomY;
				Point grad = pDoc->gradient(a);
				double ang = 180 * atan2(grad.y, grad.x) / M_PI;
				glPushMatrix();

				glTranslatef(target.x, target.y, 0);
				glRotatef(ang, 0, 0, 1);

				glTranslatef(-target.x, -target.y, 0);

				glBegin(GL_LINES);
				SetColor(source);
				SetColor(colorsample);
				glVertex2d(target.x + randomX + randomLength, target.y + randomY);

				glVertex2d(target.x - randomX + randomLength, target.y + randomY);

			}

		}


		glEnd();
		glPopMatrix();
		xp = source.x;
		yp = source.y;

	}
}

void ScatteredLines::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void ScatteredLines::rmbegin(const Point source, const Point target)
{
	x = target.x;
	y = target.y;
}

void ScatteredLines::rmmove(const Point source, const Point target)
{
	cout << " working" << endl;
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(x, y);
	glVertex2d(target.x, target.y);
	glEnd();
}

void ScatteredLines::rmend(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int angle = static_cast<int>((180 * (atan2(target.y - y, target.x - x))) / M_PI);
	if (angle < 0) {
		angle = 360 + angle;

	}
	int size2 = sqrt((target.y - y) * (target.y - y) + (target.x - x) * (target.x - x));
	dlg->setAngle(angle);
	dlg->setSize(size2);
}