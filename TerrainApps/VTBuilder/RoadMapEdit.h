//
// RoadMapEdit.h
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef ROADMAPEDIT
#define ROADMAPEDIT

#include "vtdata/RoadMap.h"
#include "vtdata/Selectable.h"

class vtRoadLayer;
class vtScaledView;
class vtDLGFile;
class OGRLayer;
class OGRLineString;

enum VisualIntersectionType {
	VIT_UNKNOWN,	//uncontrolled
	VIT_NONE,		//uncontrolled
	VIT_ALLLIGHTS,	//controlled intersection with all lights
	VIT_ALLSTOPS,	//controlled intersection with all stop signs
	VIT_LIGHTS,		//controlled intersection with at least one, but not all, traffic light
	VIT_STOPSIGN,	//controlled intersection with at least one, but not all, stop sign
	VIT_SELECTED,
	VIT_TOTAL
};


class NodeEdit : public Node, public Selectable
{
public:
	NodeEdit();

	// compare one node to another
	bool operator==(NodeEdit &ref);

	//copies this node's properties to parameter node.
	void Copy(NodeEdit *node);
	//draws the node
	bool Draw(wxDC* pDC, vtScaledView *pView);
	//brings up a node dialog to edit road properties	
	bool EditProperties(vtRoadLayer *pLayer);

	//is target inside the extent
	bool WithinExtent(DRECT target);
	//is the node in "bound"
	bool InBounds(DRECT bound);

	//move the node
	void Translate(DPoint2 offset);
	//makes sure road endpoints match the node's position
	void EnforceLinkEndpoints();

	NodeEdit *GetNext() { return (NodeEdit *)m_pNext; }
	class LinkEdit *GetLink(int n);

	VisualIntersectionType GetVisual() { return m_iVisual; }
	void SetVisual(VisualIntersectionType v) { m_iVisual = v; }

	void DetermineVisualFromLinks();

	//use to find shortest path 
	int m_iPathIndex;	//index to the array of the priorty queue.  (yeah, not exactly pretty.)
	NodeEdit *m_pPrevPathNode;	//prev node in the shortest path
	LinkEdit *m_pPrevPathLink;	//road to take to the prev node.

protected:
	VisualIntersectionType m_iVisual;  //what to display the node as
};

class LinkEdit : public Link, public Selectable
{
public:
	LinkEdit();

	// compare one road to another
	bool operator==(LinkEdit &ref);

	// determine bounding box
	void ComputeExtent();
	//is target in the bounding box?
	bool WithinExtent(DRECT target);
	//is extent of the road in "bound"
	bool InBounds(DRECT bound);
	//if only part of road is in "bound"
	bool PartiallyInBounds(DRECT bound);

	//draw the road
	bool Draw(wxDC* pDC, vtScaledView *pView, bool bShowDirection = false,
		bool bShowWidth = false);
	// prepare to draw the road (estimate the left and right edges)
	void ComputeDisplayedLinkWidth(const DPoint2 &ToMeters);
	//edit the road - brings up a road dialog box
	bool EditProperties(vtRoadLayer *pLayer);

	NodeEdit *GetNode(int n) { return (NodeEdit *)m_pNode[n]; }
	LinkEdit *GetNext() { return (LinkEdit *)m_pNext; }

	DRECT	m_extent;		// bounding box in world coordinates
	int		m_iPriority;	// used to determine intersection behavior.  lower number => higher priority
	float	m_fLength;		// length of the road
	bool	m_bDrawPoints;	// draw each point in the road individually

	DLine2	m_Left, m_Right;
	bool	m_bSidesComputed;	// true when m_Left and m_Right are up-to-date
};

class RoadMapEdit : public vtRoadMap
{
public:
	RoadMapEdit();
	~RoadMapEdit();

	// overrides for virtual methods
	LinkEdit *GetFirstLink() { return (LinkEdit *)m_pFirstLink; }
	NodeEdit *GetFirstNode() { return (NodeEdit *)m_pFirstNode; }
	Node *NewNode() { return new NodeEdit; }
	Link *NewLink() { return new LinkEdit; }

	// Import from DLG
	void AddElementsFromDLG(vtDLGFile *pDlg);

	// Import from SHP
	bool ApplyCFCC(LinkEdit *pR, const char *str);
	void AddElementsFromSHP(const char *filename, vtProjection &proj,
		void progress_callback(int) = NULL);

	// Import from SDTS via OGR
	void AddElementsFromOGR(class OGRDataSource *datasource,
		void progress_callback(int) = NULL);

	//cleaning functions-------------------------
	// merge nodes that are near each other
	int MergeRedundantNodes(bool bDegrees, void progress_callback(int) = NULL);
	// remove BAD roads
	int RemoveDegenerateLinks();
	// remove nodes and merge roads if 2 adjacent roads have the same properties and the node is uncontrolled.
	int RemoveUnnecessaryNodes();
	// fix road points so that the end nodes do not have same coordinates as their adjacent nodes.
	int CleanLinkPoints();
	// deletes roads that either:
	//		have the same start and end nodes and have less than 4 points
	//		have less than 2 points, regardless of start or end nodes.
	int DeleteDanglingLinks();
	// fix when two road meet at the same node along the same path
	int FixOverlappedLinks(bool bDegrees);
	// delete roads that are really close to another road, but go nowhere coming out of a node
	int FixExtraneousParallels();
	// split loops.  create an uncontrolled node in the middle.
	int SplitLoopingLinks();
	//----------------------------------------------

	// merge 2 selected nodes.
	bool Merge2Nodes();

	// draw the road network in window, given size of drawing area
	void Draw(wxDC* pDC, vtScaledView *pView, bool bNodes);

	// look at the road properties to guess what the intersections might be
	void GuessIntersectionTypes();

	// delete selected roads.
	DRECT* DeleteSelected(int &nBounds);

	// find which road is within a given distance of a given point
	LinkEdit *FindLink(DPoint2 point, float error);
	// inverts m_bSelect value of road within error of utmCoord
	bool SelectLink(DPoint2 point, float error, DRECT &bound);
	// if bval true, select roads within bound.  otherwise deselect roads
	int SelectLinks(DRECT bound, bool bval);
	
	// selects a road, as well as any adjacent roads that is an extension of that road.
	bool SelectAndExtendLink(DPoint2 point, float error, DRECT &bound);

	//selects all roads with given highway number
	bool SelectHwyNum(int num);

	// returns and selects (m_bSelect=true) road within error of utmCoord
	LinkEdit* GetLink(DPoint2 point, float error);

	//selects road if it is only partially in the box.
	bool CrossSelectLinks(DRECT bound, bool bval);
	//inverts selection values on all roads and nodes.
	void InvertSelection();

	//inverts m_bSelect value of node within error of utmCoord
	bool SelectNode(DPoint2 point, float error, DRECT &bound);
	//if bval true, select nodes within bound.  otherwise deselect nodes
	int SelectNodes(DRECT bound, bool bval);
	//returns and selects (m_bSelect=true) node within error of utmCoord
	NodeEdit* GetNode(DPoint2 point, float error);

	//return the number of selected nodes.
	int NumSelectedNodes();
	//return the number of selected roads
	int NumSelectedLinks();
	//deselect all (nodes and roads.
	DRECT *DeSelectAll(int &numRegions);

protected:
	void ApplyDLGAttributes(int road_type, int &lanes, SurfaceType &stype, int &priority);
	bool extract_road_attributes(const char *strEntity, int &lanes,
								  SurfaceType &stype, int &priority);

	bool attribute_filter_roads(DLGLine *pLine, int &lanes, SurfaceType &stype, int &priority);
	bool AppendFromOGRLayer(OGRLayer *pLayer);
	void AddLinkFromLineString(OGRLineString *pLineString);

	//delete one road.
	void DeleteSingleLink(LinkEdit *pLink);
	//replace a node
	void ReplaceNode(NodeEdit *pN, NodeEdit *pN2);

	//returns appropriate node/road at utmCoord within error
	//toggle:	toggles the select value
	//selectVal: what to assign the select value.
	// toggle has precendence over selectVal.
	NodeEdit *SelectNode(DPoint2 point, float error, bool toggle, bool selectVal);
	LinkEdit *SelectLink(DPoint2 point, float error, bool toggle, bool selectVal);
};

typedef NodeEdit *NodeEditPtr;

#endif
