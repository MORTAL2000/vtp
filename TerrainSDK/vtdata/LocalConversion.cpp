//
// LocalProjection.cpp
//
// This library has a concept of current conversion from earth to world
// coordinates which is represented by the vtLocalConversion class.
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "MathTypes.h"
#include "Projections.h"
#include "LocalConversion.h"

//
// The global current projection for the current terrain is stored here.
//
vtLocalConversion g_Conv;

////////////////////////////////////////////////////////////////////////////

vtLocalConversion::vtLocalConversion()
{
	m_EarthOrigin.Set(0, 0);
}

void vtLocalConversion::Setup(LinearUnits units, const DPoint2 &origin)
{
	m_units = units;

	m_EarthOrigin = origin;
	if (units == LU_DEGREES)
	{
		double fMetersPerLongitude = EstimateDegreesToMeters(origin.y);
		m_scale.x = fMetersPerLongitude;
		m_scale.y = METERS_PER_LATITUDE;
	}
	else
	{
		m_scale.x = m_scale.y = GetMetersPerUnit(units);
	}
}

void vtLocalConversion::SetOrigin(const DPoint2 &origin)
{
	m_EarthOrigin = origin;
}

void vtLocalConversion::convert_earth_to_local_xz(double ex, double ey,
												  float &x, float &z)
{
	x = (float) ((ex - m_EarthOrigin.x) * m_scale.x);
	z = (float) -((ey - m_EarthOrigin.y) * m_scale.y);
}

void vtLocalConversion::convert_local_xz_to_earth(float x, float z,
												  double &ex, double &ey)
{
	ex = m_EarthOrigin.x + (x / m_scale.x);
	ey = m_EarthOrigin.y + (-z / m_scale.y);
}

//
// Convert from the coordinate system of the virtual world (x,y,z) to actual
// earth coodinates (map coordinates, altitude in meters)
//
void vtLocalConversion::ConvertToEarth(const FPoint3 &world, DPoint3 &earth)
{
	convert_local_xz_to_earth(world.x, world.z, earth.x, earth.y);
	earth.z = world.y;
}

void vtLocalConversion::ConvertFromEarth(const DPoint3 &earth, FPoint3 &world)
{
	convert_earth_to_local_xz(earth.x, earth.y, world.x, world.z);
	world.y = (float) earth.z;
}

void vtLocalConversion::ConvertToEarth(float x, float z, DPoint2 &earth)
{
	convert_local_xz_to_earth(x, z, earth.x, earth.y);
}

void vtLocalConversion::ConvertFromEarth(const DPoint2 &earth, float &x, float &z)
{
	convert_earth_to_local_xz(earth.x, earth.y, x, z);
}

