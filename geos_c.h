/************************************************************************
 *
 * $Id: geos_c.h.in,v 1.11.2.3 2006/03/27 09:05:19 strk Exp $
 *
 * C-Wrapper for GEOS library
 *
 * Copyright (C) 2005 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 * Author: Sandro Santilli <strk@refractions.net>
 *
 ***********************************************************************
 *
 * GENERAL NOTES:
 *
 *	- Remember to call initGEOS() before any use of this library's
 *	  functions, and call finishGEOS() when done.
 *
 *	- Currently you have to explicitly GEOSGeom_destroy() all
 *	  GEOSGeom objects to avoid memory leaks, and to free()
 *	  all returned char * (unless const). This might change
 *	  before first release to ensure greater API stability.
 *
 ***********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 *
 * Version
 *
 ***********************************************************************/

#define GEOS_VERSION_MAJOR 2
#define GEOS_VERSION_MINOR 2
#define GEOS_VERSION_PATCH 2
#define GEOS_FIRST_INTERFACE GEOS_VERSION_MAJOR 
#define GEOS_LAST_INTERFACE (GEOS_VERSION_MAJOR+GEOS_VERSION_MINOR)
#define GEOS_VERSION "2.2.2"
#define GEOS_JTS_PORT "1.4.1"

#define GEOS_CAPI_VERSION_MAJOR 1
#define GEOS_CAPI_VERSION_MINOR 1
#define GEOS_CAPI_VERSION_PATCH 0
#define GEOS_CAPI_FIRST_INTERFACE GEOS_CAPI_VERSION_MAJOR 
#define GEOS_CAPI_LAST_INTERFACE (GEOS_CAPI_VERSION_MAJOR+GEOS_CAPI_VERSION_MINOR)
#define GEOS_CAPI_VERSION "2.2.2-CAPI-1.1.0"

 
/************************************************************************
 *
 * (Abstract) type definitions
 *
 ***********************************************************************/

typedef void (*GEOSMessageHandler)(const char *fmt, ...);
typedef struct GEOSGeom_t *GEOSGeom;
typedef struct GEOSCoordSeq_t *GEOSCoordSeq;

/* Supported geometry types */
enum GEOSGeomTypeId {
	GEOS_POINT,
	GEOS_LINESTRING,
	GEOS_LINEARRING,
	GEOS_POLYGON,
	GEOS_MULTIPOINT,
	GEOS_MULTILINESTRING,
	GEOS_MULTIPOLYGON,
	GEOS_GEOMETRYCOLLECTION
};


/************************************************************************
 *
 * Initialization, cleanup, version
 *
 ***********************************************************************/

#if defined(_MSC_VER)
#  define GEOS_DLL     __declspec(dllexport)
#else
#  define GEOS_DLL
#endif

extern void GEOS_DLL initGEOS(GEOSMessageHandler notice_function,
	GEOSMessageHandler error_function);
extern void GEOS_DLL finishGEOS(void);
extern const char GEOS_DLL *GEOSversion();


/************************************************************************
 *
 * Geometry Input and Output functions, return NULL on exception.
 *
 ***********************************************************************/

extern GEOSGeom GEOS_DLL GEOSGeomFromWKT(const char *wkt);
extern char GEOS_DLL *GEOSGeomToWKT(const GEOSGeom g);

/*
 * Specify whether output WKB should be 2d or 3d.
 * Return previously set number of dimensions.
 */
extern int GEOS_DLL GEOS_setWKBOutputDims(int newDims);

extern GEOSGeom GEOS_DLL GEOSGeomFromWKB_buf(const unsigned char *wkb, size_t size);
extern unsigned char GEOS_DLL *GEOSGeomToWKB_buf(const GEOSGeom g, size_t *size);

/************************************************************************
 *
 * Coordinate Sequence functions
 *
 ***********************************************************************/

/*
 * Create a Coordinate sequence with ``size'' coordinates
 * of ``dims'' dimensions.
 * Return NULL on exception.
 */
extern GEOSCoordSeq GEOS_DLL GEOSCoordSeq_create(unsigned int size, unsigned int dims);

/*
 * Clone a Coordinate Sequence.
 * Return NULL on exception.
 */
extern GEOSCoordSeq GEOS_DLL GEOSCoordSeq_clone(GEOSCoordSeq s);

/*
 * Destroy a Coordinate Sequence.
 */
extern void GEOS_DLL GEOSCoordSeq_destroy(GEOSCoordSeq s);

/*
 * Set ordinate values in a Coordinate Sequence.
 * Return 0 on exception.
 */
extern int GEOS_DLL GEOSCoordSeq_setX(GEOSCoordSeq s,
	unsigned int idx, double val);
extern int GEOS_DLL GEOSCoordSeq_setY(GEOSCoordSeq s,
	unsigned int idx, double val);
extern int GEOS_DLL GEOSCoordSeq_setZ(GEOSCoordSeq s,
	unsigned int idx, double val);
extern int GEOS_DLL GEOSCoordSeq_setOrdinate(GEOSCoordSeq s,
	unsigned int idx, unsigned int dim, double val);

/*
 * Get ordinate values from a Coordinate Sequence.
 * Return 0 on exception.
 */
extern int GEOS_DLL GEOSCoordSeq_getX(const GEOSCoordSeq s,
	unsigned int idx, double *val);
extern int GEOS_DLL GEOSCoordSeq_getY(const GEOSCoordSeq s,
	unsigned int idx, double *val);
extern int GEOS_DLL GEOSCoordSeq_getZ(const GEOSCoordSeq s,
	unsigned int idx, double *val);
extern int GEOS_DLL GEOSCoordSeq_getOrdinate(const GEOSCoordSeq s,
	unsigned int idx, unsigned int dim, double *val);

/*
 * Get size and dimensions info from a Coordinate Sequence.
 * Return 0 on exception.
 */
extern int GEOS_DLL GEOSCoordSeq_getSize(const GEOSCoordSeq s,
	unsigned int *size);
extern int GEOS_DLL GEOSCoordSeq_getDimensions(const GEOSCoordSeq s,
	unsigned int *dims);


/************************************************************************
 *
 * Geometry Constructors.
 * GEOSCoordSeq arguments will become ownership of the returned object.
 * All functions return NULL on exception.
 *
 ***********************************************************************/

extern GEOSGeom GEOS_DLL GEOSGeom_createPoint(GEOSCoordSeq s);
extern GEOSGeom GEOS_DLL GEOSGeom_createLinearRing(GEOSCoordSeq s);
extern GEOSGeom GEOS_DLL GEOSGeom_createLineString(GEOSCoordSeq s);

/*
 * Second argument is an array of GEOSGeom objects.
 * The caller remains owner of the array, but pointed-to
 * objects become ownership of the returned GEOSGeom.
 */
extern GEOSGeom GEOS_DLL GEOSGeom_createPolygon(GEOSGeom shell,
	GEOSGeom *holes, unsigned int nholes);
extern GEOSGeom GEOS_DLL GEOSGeom_createCollection(int type,
	GEOSGeom *geoms, unsigned int ngeoms);

extern GEOSGeom GEOS_DLL GEOSGeom_clone(const GEOSGeom g);

/************************************************************************
 *
 * Memory management
 *
 ***********************************************************************/

extern void GEOS_DLL GEOSGeom_destroy(GEOSGeom g);


/************************************************************************
 *
 * Topology operations - return NULL on exception.
 *
 ***********************************************************************/

extern GEOSGeom GEOS_DLL GEOSEnvelope(const GEOSGeom g1);
extern GEOSGeom GEOS_DLL GEOSIntersection(const GEOSGeom g1, const GEOSGeom g2);
extern GEOSGeom GEOS_DLL GEOSBuffer(const GEOSGeom g1,
	double width, int quadsegs);
extern GEOSGeom GEOS_DLL GEOSConvexHull(const GEOSGeom g1);
extern GEOSGeom GEOS_DLL GEOSDifference(const GEOSGeom g1, const GEOSGeom g2);
extern GEOSGeom GEOS_DLL GEOSSymDifference(const GEOSGeom g1,
	const GEOSGeom g2);
extern GEOSGeom GEOS_DLL GEOSBoundary(const GEOSGeom g1);
extern GEOSGeom GEOS_DLL GEOSUnion(const GEOSGeom g1, const GEOSGeom g2);
extern GEOSGeom GEOS_DLL GEOSPointOnSurface(const GEOSGeom g1);
extern GEOSGeom GEOS_DLL GEOSGetCentroid(const GEOSGeom g);
extern char GEOS_DLL *GEOSRelate(const GEOSGeom g1, const GEOSGeom g2);
extern GEOSGeom GEOS_DLL GEOSPolygonize(const GEOSGeom geoms[],
	unsigned int ngeoms);
extern GEOSGeom GEOS_DLL GEOSLineMerge(const GEOSGeom g);

/************************************************************************
 *
 *  Binary predicates - return 2 on exception, 1 on true, 0 on false
 *
 ***********************************************************************/

extern char GEOS_DLL GEOSRelatePattern(const GEOSGeom g1, const GEOSGeom g2,
	const char *pat);
extern char GEOS_DLL GEOSDisjoint(const GEOSGeom g1, const GEOSGeom g2);
extern char GEOS_DLL GEOSTouches(const GEOSGeom g1, const GEOSGeom g2);
extern char GEOS_DLL GEOSIntersects(const GEOSGeom g1, const GEOSGeom g2);
extern char GEOS_DLL GEOSCrosses(const GEOSGeom g1, const GEOSGeom g2);
extern char GEOS_DLL GEOSWithin(const GEOSGeom g1, const GEOSGeom g2);
extern char GEOS_DLL GEOSContains(const GEOSGeom g1, const GEOSGeom g2);
extern char GEOS_DLL GEOSOverlaps(const GEOSGeom g1, const GEOSGeom g2);
extern char GEOS_DLL GEOSEquals(const GEOSGeom g1, const GEOSGeom g2);


/************************************************************************
 *
 *  Unary predicate - return 2 on exception, 1 on true, 0 on false
 *
 ***********************************************************************/

extern char GEOS_DLL GEOSisEmpty(const GEOSGeom g1);
extern char GEOS_DLL GEOSisValid(const GEOSGeom g1);
extern char GEOS_DLL GEOSisSimple(const GEOSGeom g1);
extern char GEOS_DLL GEOSisRing(const GEOSGeom g1);
extern char GEOS_DLL GEOSHasZ(const GEOSGeom g1);


/************************************************************************
 *
 *  Geometry info
 *
 ***********************************************************************/

/* Return NULL on exception. Return must be freed by caller. */
extern char GEOS_DLL *GEOSGeomType(const GEOSGeom g1);

/* Return -1 on exception */
extern int GEOS_DLL GEOSGeomTypeId(const GEOSGeom g1);

/* Return 0 on exception */
extern int GEOS_DLL GEOSGetSRID(const GEOSGeom g1);

extern void GEOS_DLL GEOSSetSRID(GEOSGeom g, int SRID);

/* Return -1 on exception */
extern int GEOS_DLL GEOSGetNumGeometries(const GEOSGeom g1);

/*
 * Return NULL on exception, Geometry must be a Collection.
 * Returned object is a pointer to internal storage:
 * it must NOT be destroyed directly.
 */
extern const GEOSGeom GEOS_DLL GEOSGetGeometryN(const GEOSGeom g, int n);

/* Return -1 on exception */
extern int GEOS_DLL GEOSGetNumInteriorRings(const GEOSGeom g1);

/*
 * Return NULL on exception, Geometry must be a Polygon.
 * Returned object is a pointer to internal storage:
 * it must NOT be destroyed directly.
 */
extern const GEOSGeom GEOS_DLL GEOSGetInteriorRingN(const GEOSGeom g, int n);

/*
 * Return NULL on exception, Geometry must be a Polygon.
 * Returned object is a pointer to internal storage:
 * it must NOT be destroyed directly.
 */
extern const GEOSGeom GEOS_DLL GEOSGetExteriorRing(const GEOSGeom g);

/* Return -1 on exception */
extern int GEOS_DLL GEOSGetNumCoordinates(const GEOSGeom g1);

/*
 * Return NULL on exception.
 * Geometry must be a LineString, LinearRing or Point.
 */
extern const GEOSCoordSeq GEOS_DLL GEOSGeom_getCoordSeq(const GEOSGeom g);

/*
 * Return 0 on exception (or empty geometry)
 */
extern int GEOS_DLL GEOSGeom_getDimensions(const GEOSGeom g);

/************************************************************************
 *
 *  Misc functions 
 *
 ***********************************************************************/

/* Return 0 on exception, 1 otherwise */
extern int GEOS_DLL GEOSArea(const GEOSGeom g1, double *area);
extern int GEOS_DLL GEOSLength(const GEOSGeom g1, double *length);
extern int GEOS_DLL GEOSDistance(const GEOSGeom g1, const GEOSGeom g2,
	double *dist);

#ifdef __cplusplus
} // extern "C"
#endif
