
//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef SCATTEREDLINES_H
#define SCATTEREDLINES_H

#include "ImpBrush.h"

class ScatteredLines : public ImpBrush
{
public:
	int x; int y;
	int xp; int yp;
	ScatteredLines(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void rmbegin(const Point source, const Point target) override;
	void rmmove(const Point source, const Point target) override;
	void rmend(const Point source, const Point target) override;
	char* BrushName(void);
};

#endif
