
//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include "ImpBrush.h"

class LineBrush : public ImpBrush
{
public:
	int x; int y;
	int xp; int yp;
	LineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void rmbegin(const Point source, const Point target) override;
	void rmmove(const Point source, const Point target) override;
	void rmend(const Point source, const Point target) override;
	char* BrushName(void);
};

#endif