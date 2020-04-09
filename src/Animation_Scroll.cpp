#pragma once

#include "Animation_Scroll.h"

const vector<ScrollEntry>& ScrollAnimation::GetScroll(void) const 
{
	return scroll; 
}

void ScrollAnimation::SetScroll(const  vector<ScrollEntry>& p) 
{
	scroll = p; 
}

ScrollAnimation::ScrollAnimation(const string& _id, const vector<ScrollEntry>& _scroll) :Animation(_id), scroll(_scroll) 
{

}
