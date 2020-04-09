#pragma once
#ifndef VIEWDATA_H
#define VIEWDATA_H

struct  ViewData
{
	int x = 0;
	int y = 600;
	int width = 800;
	int height = 600;
};

typedef struct _Point
{
	int x = -1;
	int y = -1;
}Point;

#endif // !VIEWDATA_