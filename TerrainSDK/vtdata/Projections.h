//
// Projections.h
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//
// Derived from public-domain USGS software.
//
/** \file Projections.h */

#ifndef PROJECTIONSH
#define PROJECTIONSH

//
// Earth's diameter: 12756 km
// approximate circumference: 40074 km
// each degree of latitude: 111.3 km
//
#define EARTH_RADIUS		6378000.0f		// in meters
#define METERS_PER_LATITUDE	111317.1f

// Some class names are just too long!
#define OCT OGRCoordinateTransformation

/**
 * Enumeration of the Datum types
 *
 * This list of Datums was originally from the USGS "ProjectionLib" library
 * and provides a more concise way to represent a Datum than the string
 * values used by OGRSpatialReference.
 */
enum DATUM { ADINDAN = 0, ARC1950, ARC1960, AUSTRALIAN_GEODETIC_1966,
			 AUSTRALIAN_GEODETIC_1984, CAMP_AREA_ASTRO, CAPE,
			 EUROPEAN_DATUM_1950, EUROPEAN_DATUM_1979, GEODETIC_DATUM_1949,
			 HONG_KONG_1963, HU_TZU_SHAN, INDIAN, NAD27, NAD83,
			 OLD_HAWAIIAN_MEAN, OMAN, ORDNANCE_SURVEY_1936, PUERTO_RICO,
			 PULKOVO_1942, PROVISIONAL_S_AMERICAN_1956, TOKYO, WGS_72, WGS_84,
			 UNKNOWN_DATUM = -1, NO_DATUM = -2, DEFAULT_DATUM = -3 };

// Do not change the order of this enumeration
enum LinearUnits
{
	LU_DEGREES,
	LU_METERS,
	LU_FEET_INT,	// International Foot
	LU_FEET_US,		// U.S. Survey Foot
	LU_UNKNOWN
};


#include "ogr_spatialref.h"
#include "MathTypes.h"

///////////////////////////

/**  The vtProjection class represents an earth projection, which defines a
 * coordinate system.  It is based on the class
 * <a href="http://gdal.velocet.ca/projects/opengis/ogrhtml/class_ogrspatialreference.html">OGRSpatialReference</a>
 * which represents a full OpenGIS Spatial Reference System.  The vtProjection
 * class extends OGRSpatialReference with several useful methods.
 */
class vtProjection : public OGRSpatialReference
{
public:
	vtProjection();

	// Assignment
	vtProjection &vtProjection::operator=(const vtProjection &ref);

	// Equality
	bool operator==(const vtProjection &ref);

	void	SetUTMZone(int iZone);
	int		GetUTMZone() const;
	void	SetDatum(DATUM datum);
	DATUM	GetDatum();
	LinearUnits	GetUnits();

	void	SetGeogCSFromDatum(DATUM eDatum);

	void	SetProjectionSimple(bool bUTM, int iUTMZone, DATUM eDatum);
	void	SetSpatialReference(OGRSpatialReference *pRef);

	const char *GetProjectionName() const;
	const char *GetProjectionNameShort() const;

	bool GetTextDescription(char *type, char *value);
	bool SetTextDescription(const char *type, const char *value);

	bool ReadProjFile(const char *filename);
	bool WriteProjFile(const char *filename);

	double GeodesicDistance(const DPoint2 &in, DPoint2 &out, bool bQuick = false);

protected:
	DATUM	m_Datum;
};

struct StatePlaneInfo
{
	char *name;
	int number;
	int usgs_code;
};

class Geodesic
{
public:
	void CalculateInverse();

	double	a;
	double	lam1, phi1;
	double	lam2, phi2;
	double	S;
	double	onef, f, f2, f4, f64;
};


//////////////////////////////
// Helper functions

const char *datumToString(DATUM d);
const char *datumToStringShort(DATUM d);

StatePlaneInfo *GetStatePlaneTable();
int GetNumStatePlanes();
void CreateSimilarGeographicProjection(const vtProjection &source, vtProjection &geo);
OCT *CreateConversionIgnoringDatum(const vtProjection *pSource, vtProjection *pTarget);

/**
 * Determine an approximate conversion from degrees of longitude to meters,
 * given a latitude in degrees.
 */
double EstimateDegreesToMeters(double latitude);

/**
 * Return the number of meters for a given type of linear units
 */
double GetMetersPerUnit(LinearUnits lu);

///////////////////////////

#endif	// PROJECTIONSH
