#include "RectI.h"

RectI::RectI( int left_in,int right_in,int top_in,int bottom_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottom( bottom_in )
{
}

RectI::RectI( const Vei2& topLeft,const Vei2 & bottomRight )
	:
	RectI( topLeft.x,bottomRight.x,topLeft.y,bottomRight.y )
{
}

RectI::RectI( const Vei2& topLeft,int width,int height )
	:
	RectI( topLeft,topLeft + Vei2( width,height ) )
{
}

bool RectI::isOverlappingWith( const RectI& other ) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool RectI::isContainedBy( const RectI & other ) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

bool RectI::contains( const Vei2& point ) const
{
	return point.x >= left && point.x < right && point.y >= top && point.y < bottom;
}

RectI RectI::fromCenter( const Vei2 & center,int halfWidth,int halfHeight )
{
	const Vei2 half( halfWidth,halfHeight );
	return RectI( center - half,center + half );
}

RectI RectI::getExpanded( int offset ) const
{
	return RectI( left - offset,right + offset,top - offset,bottom + offset );
}

Vei2 RectI::getCenter() const
{
	return Vei2( (left + right) / 2,(top + bottom) / 2 );
}

int RectI::getWidth() const
{
	return right - left;
}

int RectI::getHeight() const
{
	return bottom - top;
}
