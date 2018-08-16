#pragma once

#include "Vei2.h"

class RectI
{
public:
	RectI() = default;
	RectI( int left_in,int right_in,int top_in,int bottom_in );
	RectI( const Vei2& topLeft,const Vei2& bottomRight );
	RectI( const Vei2& topLeft,int width,int height );
	bool isOverlappingWith( const RectI& other ) const;
	bool isContainedBy( const RectI& other ) const;
	bool contains( const Vei2& point ) const;
	static RectI fromCenter( const Vei2& center,int halfWidth,int halfHeight );
	RectI getExpanded( int offset ) const;
	Vei2 getCenter() const;
	int getWidth() const;
	int getHeight() const;

public:
	int left;
	int right;
	int top;
	int bottom;
};