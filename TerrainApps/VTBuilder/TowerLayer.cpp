//
// TowerLayer.cpp
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "wx/wxprec.h"
#include "Frame.h"
#include "TowerLayer.h"
#include "ScaledView.h"
#include "TowerDlg.h"

wxPen greenPen;
wxPen bluePen;
static bool g_bInitializedPens = false;

//////////////////////////////////////////////////////////////////////////

vtTowerLayer::vtTowerLayer() : vtLayer(LT_UTILITY)
{
	m_strFilename = "Untitled.utl";

	if (!g_bInitializedPens)
	{
		g_bInitializedPens = true;
		greenPen.SetColour(25,128,0);
		bluePen.SetColour(25,25,200);
	}
}

bool vtTowerLayer::GetExtent(DRECT &rect)
{
	if (IsEmpty())
		return false;

	GetExtents(rect);

	// expand by 2 meters
	rect.left -= 2.0f;
	rect.right += 2.0f;
	rect.bottom -= 2.0f;
	rect.top += 2.0f;

	return true;
}

#define BLENGTH 5

void vtTowerLayer::DrawLayer(wxDC* pDC, vtScaledView *pView)
{
	int npoints = GetSize();
	if (!npoints)
		return;

	pDC->SetPen(greenPen);
	pDC->SetBrush(*wxTRANSPARENT_BRUSH);
	bool bSel = false;

	m_size = pView->sdx(20);
	if (m_size > 5) m_size = 5;
	if (m_size < 1) m_size = 1;

	for (int i = 0; i < npoints; i++)
	{
		// draw each Tower
		vtTower *twr = GetAt(i);

		if (twr->IsSelected())
		{
			if (!bSel)
			{
				pDC->SetPen(bluePen);
				bSel = true;
			}
		}
		else
		{
			if (bSel)
			{
				pDC->SetPen(greenPen);
				bSel = false;
			}
		}
		DrawTower(pDC, pView, twr);
	}
}

#define MAX_SIDES	45
static wxPoint array[MAX_SIDES];

void vtTowerLayer::DrawTower(wxDC* pDC, vtScaledView *pView, vtTower *tower)
{
	DPoint2 corner[4];
	float fWidth, fDepth, fRotation;

	wxPoint origin;
	pView->screen(tower->GetLocation(), origin);

	pDC->DrawLine(origin.x-m_size, origin.y, origin.x+m_size+1, origin.y);
	pDC->DrawLine(origin.x, origin.y-m_size, origin.x, origin.y+m_size+1);

	if (tower->GetShape() == TSHAPE_POLY)
	{
		DLine2 &dl = tower->GetFootprint();
		int size = dl.GetSize();
		for (int j = 0; j < size && j < MAX_SIDES-1; j++)
			pView->screen(dl.GetAt(j), array[j]);
		pView->screen(dl.GetAt(0), array[j++]);

		pDC->DrawLines(j, array);
	}
	if (tower->GetShape() == TSHAPE_CIRCLE)
	{
		int size = pView->sdx(tower->GetRadius());
		pDC->DrawEllipse(origin.x-size, origin.y-size,
			size<<1, size<<1);
	}
	if (tower->GetShape() == TSHAPE_RECTANGLE)
	{
		tower->GetRectangle(fWidth, fDepth);
		tower->GetRotation(fRotation);
		if (fRotation == -1.0f) fRotation = 0.0f;
		DPoint2 pt(fWidth / 2.0, fDepth / 2.0);
		corner[0].Set(-pt.x, pt.y);
		corner[1].Set(pt.x, pt.y);
		corner[2].Set(pt.x, -pt.y);
		corner[3].Set(-pt.x, -pt.y);
		corner[0].Rotate(fRotation);
		corner[1].Rotate(fRotation);
		corner[2].Rotate(fRotation);
		corner[3].Rotate(fRotation);
		array[0] = origin + pView->screen_delta(corner[0]);
		array[1] = origin + pView->screen_delta(corner[1]);
		array[2] = origin + pView->screen_delta(corner[2]);
		array[3] = origin + pView->screen_delta(corner[3]);
		array[4] = array[0];
		pDC->DrawLines(5, array);
	}
}

bool vtTowerLayer::OnSave()
{
	wxString strExt = m_strFilename.AfterLast('.');

	if (!strExt.CmpNoCase("shp"))
		return WriteSHP(m_strFilename);
	if (!strExt.CmpNoCase("utl"))
		return WriteUTL(m_strFilename);
	return false;
}

bool vtTowerLayer::OnLoad()
{
	wxString strExt = m_strFilename.AfterLast('.');

	if (!strExt.CmpNoCase("shp"))
		return ReadSHP(m_strFilename);
	if (!strExt.CmpNoCase("utl"))
		return ReadUTL(m_strFilename);
	return false;
}

void vtTowerLayer::GetProjection(vtProjection &proj)
{
	proj = m_proj;
}

bool vtTowerLayer::ConvertProjection(vtProjection &proj)
{
	if (proj == m_proj)
		return true;

	// Create conversion object
	vtProjection Source;
	GetProjection(Source);
	OCT *trans = OGRCreateCoordinateTransformation(&Source, &proj);
	if (!trans)
		return false;		// inconvertible projections

	vtTower *tower;
	DPoint2 loc;
	int i;
	int count = GetSize();
	for (i = 0; i < count; i++)
	{
		tower = GetAt(i);
		loc = tower->GetLocation();
		trans->Transform(1, &loc.x, &loc.y);
		tower->SetLocation(loc);
	}

	delete trans;

	m_proj = proj;

	return false;
}

bool vtTowerLayer::AppendDataFrom(vtLayer *pL)
{
	// safety check
	if (pL->GetType() != LT_UTILITY)
		return false;

	vtTowerLayer *pFrom = (vtTowerLayer *)pL;

	int count = pFrom->GetSize();
	for (int i = 0; i < count; i++)
	{
		vtTower *tower = pFrom->GetAt(i);
		Append(tower);
	}
	return true;
}

void vtTowerLayer::Offset(DPoint2 p)
{

	int npoints = GetSize();
	if (!npoints)
		return;

	DPoint2 temp;
	for (int i = 0; i < npoints; i++)
	{
		vtTower *bld = GetAt(i);
		bld->Offset(p);
	}
}
//
// Helper: find the index of a field in a DBF file, given the name of the field.
// Returns -1 if not found.
//
int FindDBFieldT(DBFHandle db, const char *field_name)
{
	int count = DBFGetFieldCount(db);
	for (int i = 0; i < count; i++)
	{
		int pnWidth, pnDecimals;
		char pszFieldName[80];
		DBFFieldType fieldtype = DBFGetFieldInfo(db, i,
			pszFieldName, &pnWidth, &pnDecimals );
		if (!stricmp(field_name, pszFieldName))
			return i;
	}
	return -1;
}
//
// Locate the closest building that is no more than epsilon units in either
// dimension away from point.
//
// Return NULL if there is no building.
//
vtTower *vtTowerLayer::FindTower(DPoint2 &point, double epsilon)
{
	int count = GetSize();
	DPoint2 loc, diff;
	double dist2, closest = 1.0E10f, eps2 = epsilon * epsilon;

	vtTower *best_tower = NULL;

	for (int i = 0; i < count; i++)
	{
		vtTower *tower = GetAt(i);
		loc = tower->GetLocation();
		diff = loc - point;
		dist2 = diff.x*diff.x + diff.y*diff.y;
		if (dist2 < eps2)
		{
			if (dist2 < closest)
			{
				closest = dist2;
				best_tower = tower;
			}
		}
	}
	return best_tower;
}

//
// inverts Selected value of tower within error or utmCoord
//
/*bool vtTowerLayer::SelectTower(DPoint2 utmCoord, float error, DRECT &bound)
{
	NodeEdit* tower = SelectNode(utmCoord, error, true, false);
	if (node) {
		bound.left = bound.right = node->m_p.x;
		bound.top = bound.bottom = node->m_p.y;
		return true;
	} else
		return false;
}

//returns appropriate node at utmCoord within error
//toggle:	toggles the select value
//selectVal: what to assign the select value.
// toggle has precendence over selectVal.
NodeEdit* vtTowerLayer::SelectNode(DPoint2 point, float error, bool toggle, bool selectVal)
{
	NodeEdit* bestSoFar;
	float dist = (float)error;
	float result;
	bool found = false;

	//a backwards rectangle, to provide greater flexibility for finding the node
	DRECT target(point.x-error, point.y+error, point.x+error, point.y-error);
	for (NodeEdit* curNode = GetFirstNode(); curNode; curNode = curNode->GetNext())
	{
		if (curNode->WithinExtent(target))
		{
			result = curNode->DistanceToPoint(point);
			if (result < dist) {
				bestSoFar = curNode;
				dist = result;
				found = true;
			}
		}
	}

	if (found)
	{
		if (toggle)
			bestSoFar->ToggleSelect();
		else
			bestSoFar->Select(selectVal);
		return bestSoFar;
	}
	else
		return NULL;
}*/


bool vtTowerLayer::EditTowerProperties()
{
	int count = 0;
	vtTower *tower_selected;

	int size = GetSize();
	for (int i = 0; i < size; i++)
	{
		vtTower *tower = GetAt(i);
		if (tower->IsSelected())
		{
			count++;
			tower_selected = tower;
		}
	}
	if (count != 1)
		return false;

	// for now, assume they will change something (pessimistic)
	SetModified(true);

	TowerDLG dlg(NULL, -1, "Tansmission Tower Properties", wxDefaultPosition);
		dlg.Setup(tower_selected);
	return (dlg.ShowModal() == wxID_OK);
}

void vtTowerLayer::InvertSelection()
{
	int i, size = GetSize();
	for (i = 0; i < size; i++)
	{
		vtTower *str = GetAt(i);
		str->Select(!str->IsSelected());
	}
}



void vtTowerLayer::AddElementsFromSHP(const char *filename, vtProjection &proj)
{
	//Open the SHP File & Get Info from SHP:
	SHPHandle hSHP = SHPOpen(filename, "rb");
	if (hSHP == NULL)
		return;

	//  Get number of polys (m_iNumPolys) and type of data (nShapeType)
	int		nElem;
	int		nShapeType;
    double	adfMinBound[4], adfMaxBound[4];
	SHPGetInfo(hSHP, &nElem, &nShapeType, adfMinBound, adfMaxBound);

	//  Check Shape Type, Building outlines should be Poly data
	if (nShapeType == SHPT_POINT)
		AddElementsFromSHPPoints(hSHP, nElem);
	else if (nShapeType == SHPT_POLYGON)
		AddElementsFromSHPPolygons(filename, hSHP, nElem);

	m_proj = proj;	// Set projection

	SHPClose(hSHP);
}

void vtTowerLayer::AddElementsFromSHPPoints(SHPHandle hSHP, int nElem)
{
	// Initialize arrays
	SetMaxSize(nElem);

	// Read Points from SHP
	int i;
	SHPObject *psShape;
	for (i = 0; i < nElem; i++)
	{
		// Get the i-th Point in the SHP file
		psShape = SHPReadObject(hSHP, i);

		vtTower *new_tower = new vtTower();
		new_tower->SetShape(TSHAPE_RECTANGLE);
		new_tower->SetLocation(DPoint2(psShape->padfX[0], psShape->padfY[0]));
		//new_tower->SetStories(1);
		AddTower(new_tower);

		SHPDestroyObject(psShape);
	}
}

void vtTowerLayer::AddElementsFromSHPPolygons(const char *filename,
												 SHPHandle hSHP, int nElem)
{
	// Open DBF File & Get DBF Info:
	DBFHandle db = DBFOpen(filename, "rb");
	if (db == NULL)
		return;

	// Check for field with number of stories
	int stories_field = FindDBFieldT(db, "Stories");

	// Initialize arrays
	SetMaxSize(nElem);

	// Read Polys from SHP
	int i;
	SHPObject *psShape;
	for (i = 0; i < nElem; i++)
	{
		// Get the i-th Poly in the SHP file
		psShape = SHPReadObject(hSHP, i);

		// Store each SHP Poly as Building Footprint

		// The SHP appears to repeat the first point as the last, so ignore
		// the last point.
		int num_points = psShape->nVertices-1;

		vtTower *new_tower = new vtTower();
		new_tower->SetShape(TSHAPE_POLY);

		DLine2 foot;
		foot.SetSize(num_points);

		int j, k;
		for (j = 0; j < num_points; j++)
		{
			// The SHP polygons appear to be clockwise - but the vtBuilding
			//  convention is counter-clockwise, so reverse the order.
			k = num_points-1-j;

			foot.SetAt(j, DPoint2(psShape->padfX[k], psShape->padfY[k]));
		}
		new_tower->SetFootprint(foot);
		new_tower->SetCenterFromPoly();

		//int num_stories = 1;
		/*if (stories_field != -1)
		{
			// attempt to get number of stories from the DBF
			num_stories = DBFReadIntegerAttribute(db, i, stories_field);
			if (num_stories < 1)
				num_stories = 1;
		}*/
	//	new_tower->SetArms(num_arms);

		AddTower(new_tower);

		SHPDestroyObject(psShape);
	}
	DBFClose(db);
}

bool vtTowerLayer::AddNewTower(const DPoint2 &p)
{
	vtTower *new_tower = new vtTower();
	new_tower->SetLocation(p);
	new_tower->SetShape(TSHAPE_POLY);
	AddTower(new_tower);

		TowerDLG dlg(NULL, -1, "Tansmission Tower Properties", wxDefaultPosition);
		dlg.Setup(new_tower);
	return (dlg.ShowModal() == wxID_OK);


}

