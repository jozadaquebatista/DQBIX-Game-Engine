#include "collisiondetection.h"

bool collisiondetection::box(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int x1Min = x1;
	int y1Min = y1;
	int x1Max = x1 + w1;
	int y1Max = y1 + h1;
	
	int x2Min = x2;
	int y2Min = y2;
	int x2Max = x2 + w2;
	int y2Max = y2 + h2;
	
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	return true;
}

bool collisiondetection::circle(int x1, int y1, int r1, int x2, int y2, int r2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) < (r1 + r2);
}

std::string collisiondetection::side(point pos, point sz, point delta, point opos, point osz)
{
	return _side(pos.x, pos.y, sz.x, sz.y, delta.x, delta.y, opos.x, opos.y, osz.x, osz.y);
}

std::string collisiondetection::_side(int x, int y, int w, int h, int dx, int dy, int ox, int oy, int ow, int oh)
{
	if (dx == 0 && dy == 0)
	{
		return "none";
	}
	if (dx < 0)
	{
		if (x >= ox + ow)
		{
			if (x + dx < ox + ow)
			{
				if (y + dy < oy + oh && oy < y + dy + h)
				{
					return "left";
				}
			}
		}
	}
	else if (dx > 0)
	{
		if (ox > x + w)
		{
			if (ox < x + w + dx)
			{
				if (y + dy < oy + oh && oy < y + dy + h)
				{
					return "right";
				}
			}
		}
	}

	if (dy < 0)
	{
		if (y >= oy + oh)
		{
			if (y + dy < oy + oh)
			{
				if (x < ox + ow && ox < x + w)
				{
					return "top";
				}
			}
		}
	}
	else if (dy > 0)
	{
		if (oy >= y + h)
		{
			if (oy < y + h + dy)
			{
				if (x < ox + ow && ox < x + w)
				{
					return "bottom";
				}
			}
		}
	}
	return "none";
}
