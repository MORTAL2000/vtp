//
// RawLayer.cpp
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//
// A 'raw' layer is just data, without any specific meaning.  This is the
// same as a traditional GIS file (e.g. ESRI Shapefile) without any
// attributes.  In fact, SHP and 'shapelib' are used as the format and
// basic functionality for this layer.
//

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "RawLayer.h"
#include "ScaledView.h"

////////////////////////////////////////////////////////////////////

vtRawLayer::vtRawLayer() : vtLayer(LT_RAW)
{
	m_strFilename = "Untitled.shp";
	m_nSHPType = SHPT_NULL;
}

vtRawLayer::~vtRawLayer()
{
}

bool vtRawLayer::GetExtent(DRECT &rect)
{
	int i, entities = NumEntities();

	if (!entities)
		return false;

	if (m_nSHPType == SHPT_POINT)
	{
		rect.SetRect(1E9, -1E9, -1E9, 1E9);
		for (i = 0; i < entities; i++)
			rect.GrowToContainPoint(m_Point2[i]);
	}
	if (m_nSHPType == SHPT_POINTZ)
	{
		rect.SetRect(1E9, -1E9, -1E9, 1E9);
		DPoint2 p;
		for (i = 0; i < entities; i++)
		{
			p.Set(m_Point3[i].x, m_Point3[i].y);
			rect.GrowToContainPoint(p);
		}
	}
	if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
	{
		rect.SetRect(1E9, -1E9, -1E9, 1E9);
		for (i = 0; i < entities; i++)
			rect.GrowToContainLine(*m_LinePoly[i]);
	}
	return true;
}

void vtRawLayer::DrawLayer(wxDC* pDC, vtScaledView *pView)
{
	// single pixel solid pen
	wxPen DefPen(wxColor(128,0,0), 1, wxSOLID);
	wxPen SelPen(wxColor(255,255,0), 1, wxSOLID);
	int pen = 0;

	pDC->SetLogicalFunction(wxCOPY);
	pDC->SetPen(DefPen);
	int i, j, size, size2;

	wxPoint p;
	int entities = NumEntities();
	if (m_nSHPType == SHPT_POINT)
	{
		for (i = 0; i < entities; i++)
		{
			if (m_Selected[i]) {
				if (pen == 0) { pDC->SetPen(SelPen); pen = 1; }
			}
			else {
				if (pen == 1) { pDC->SetPen(DefPen); pen = 0; }
			}
			pView->screen(m_Point2[i], p);
			pDC->DrawPoint(p);
			pDC->DrawPoint(p.x+1, p.y);
			pDC->DrawPoint(p.x, p.y+1);
			pDC->DrawPoint(p.x-1, p.y);
			pDC->DrawPoint(p.x, p.y-1);
		}
	}
	if (m_nSHPType == SHPT_POINTZ)
	{
		size = m_Point3.GetSize();
		for (i = 0; i < entities; i++)
		{
			if (m_Selected[i]) {
				if (pen == 0) { pDC->SetPen(SelPen); pen = 1; }
			}
			else {
				if (pen == 1) { pDC->SetPen(DefPen); pen = 0; }
			}
			pView->screen(DPoint2(m_Point3[i].x, m_Point3[i].y), p);
			pDC->DrawPoint(p);
			pDC->DrawPoint(p.x+1, p.y);
			pDC->DrawPoint(p.x, p.y+1);
			pDC->DrawPoint(p.x-1, p.y);
			pDC->DrawPoint(p.x, p.y-1);
		}
	}
	if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
	{
		size = m_LinePoly.GetSize();
		for (i = 0; i < entities; i++)
		{
			if (m_Selected[i]) {
				if (pen == 0) { pDC->SetPen(SelPen); pen = 1; }
			}
			else {
				if (pen == 1) { pDC->SetPen(DefPen); pen = 0; }
			}
			DLine2 *dl = m_LinePoly.GetAt(i);
			size2 = dl->GetSize();

			for (j = 0; j < size2 && j < SCREENBUF_SIZE-1; j++)
				pView->screen(dl->GetAt(j), g_screenbuf[j]);
			if (m_nSHPType == SHPT_POLYGON)
				pView->screen(dl->GetAt(0), g_screenbuf[j++]);

			pDC->DrawLines(j, g_screenbuf);
		}
	}
}

bool vtRawLayer::ConvertProjection(vtProjection &proj)
{
	// Create conversion object
	OCT *trans = OGRCreateCoordinateTransformation(&m_proj, &proj);
	if (!trans)
		return false;		// inconvertible projections

	int i, j, pts;
	if (m_nSHPType == SHPT_POINT)
	{
		for (i = 0; i < m_Point2.GetSize(); i++)
			trans->Transform(1, &m_Point2[i].x, &m_Point2[i].y);
	}
	if (m_nSHPType == SHPT_POINTZ)
	{
		for (i = 0; i < m_Point2.GetSize(); i++)
			trans->Transform(1, &m_Point3[i].x, &m_Point3[i].y);
	}
	if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
	{
		for (i = 0; i < m_LinePoly.GetSize(); i++)
		{
			DLine2 *dline = m_LinePoly.GetAt(i);
			pts = dline->GetSize();
			for (j = 0; j < pts; j++)
			{
				trans->Transform(1, &((*dline)[i]).x, &((*dline)[i]).y);
			}
		}
	}
	delete trans;
	return true;
}

bool vtRawLayer::OnSave()
{
	SHPHandle hSHP = SHPCreate(m_strFilename, m_nSHPType);
	if (!hSHP)
		return false;

	int i, j, size;
	SHPObject *obj;
	if (m_nSHPType == SHPT_POINT)
	{
		size = m_Point2.GetSize();
		for (i = 0; i < size; i++)
		{
			// Save to SHP
			obj = SHPCreateSimpleObject(m_nSHPType, 1,
				&m_Point2[i].x, &m_Point2[i].y, NULL); 
			SHPWriteObject(hSHP, -1, obj);
			SHPDestroyObject(obj);
		}
	}
	if (m_nSHPType == SHPT_POINTZ)
	{
		size = m_Point3.GetSize();
		for (i = 0; i < size; i++)
		{
			// Save to SHP
			obj = SHPCreateSimpleObject(m_nSHPType, 1,
				&m_Point3[i].x, &m_Point3[i].y, &m_Point3[i].z); 
			SHPWriteObject(hSHP, -1, obj);
			SHPDestroyObject(obj);
		}
	}
	if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
	{
		size = m_LinePoly.GetSize();
		for (i = 0; i < size; i++)
		{
			DLine2 *dl = m_LinePoly.GetAt(i);
			// Save to SHP
			obj = SHPCreateSimpleObject(m_nSHPType, dl->GetSize(),
				&m_Point2[i].x, &m_Point2[i].y, NULL);
			SHPWriteObject(hSHP, -1, obj);
			SHPDestroyObject(obj);
		}
	}
	SHPClose(hSHP);

	if (m_fields.GetSize() > 0)
	{
		// Save DBF File also
		wxString dbfname = m_strFilename;
		dbfname.Truncate(dbfname.Len() - 4);
		dbfname += ".dbf";
		DBFHandle db = DBFCreate(dbfname);
		if (db == NULL)
		{
			wxMessageBox("Couldn't create DBF file.");
			return false;
		}

		Field *field;
		for (i = 0; i < m_fields.GetSize(); i++)
		{
			field = m_fields[i];

			DBFAddField(db, (const char *) field->m_name, field->m_type,
				field->m_width, field->m_decimals );
		}

		// Write DBF Attributes, one record per entity
		int entities = NumEntities();
		for (i = 0; i < entities; i++)
		{
			for (j = 0; j < m_fields.GetSize(); j++)
			{
				field = m_fields[j];
				switch (field->m_type)
				{
				case FTInteger:
					DBFWriteIntegerAttribute(db, i, j, field->m_int[i]);
					break;
				case FTDouble:
					DBFWriteDoubleAttribute(db, i, j, field->m_double[i]);
					break;
				case FTString:
					DBFWriteStringAttribute(db, i, j, (const char *) *(field->m_string[i]));
					break;
				}
			}
		}
		DBFClose(db);
	}

	// Try saving projection to PRJ
	wxString prjname = m_strFilename;
	prjname.Truncate(prjname.Len() - 4);
	prjname += ".prj";
	m_proj.WriteProjFile(prjname);

	return true;
}

bool vtRawLayer::OnLoad()
{
	// Open the SHP File & Get Info from SHP:
	SHPHandle hSHP = SHPOpen(m_strFilename, "rb");
	if (hSHP == NULL)
		return false;

	// Get number of entities (nElem) and type of data (nShapeType)
	int		nElem;
	int		nShapeType;
    double	adfMinBound[4], adfMaxBound[4];
	FPoint2 point;
	SHPGetInfo(hSHP, &nElem, &nShapeType, adfMinBound, adfMaxBound);

	//  Check shape type, we only support a few types
	switch (nShapeType)
	{
	case SHPT_POINT:
	case SHPT_POINTZ:
	case SHPT_ARC:
	case SHPT_POLYGON:
		m_nSHPType = nShapeType;
		break;
	default:
		SHPClose(hSHP);
		return false;
	}

	// Try loading DBF File as well
	wxString dbfname = m_strFilename;
	dbfname.Truncate(dbfname.Len() - 4);
	dbfname += ".dbf";
	DBFFieldType fieldtype;
	DBFHandle db = DBFOpen(dbfname, "rb");
	int iField, iFields;
	if (db != NULL)
	{
		// Check for field of poly id, current default field in dbf is Id
		iFields = DBFGetFieldCount(db);
		int pnWidth, pnDecimals;
		char szFieldName[80];

		for (iField = 0; iField < iFields; iField++)
		{
			fieldtype = DBFGetFieldInfo(db, iField, szFieldName,
				&pnWidth, &pnDecimals);
			AddField(szFieldName, fieldtype, pnWidth);
		}
	}

	// Initialize arrays
	switch (m_nSHPType)
	{
	case SHPT_POINT:
		m_Point2.SetSize(nElem);
		break;
	case SHPT_POINTZ:
		m_Point3.SetSize(nElem);
		break;
	case SHPT_ARC:
	case SHPT_POLYGON:
		m_LinePoly.SetSize(nElem);
		break;
	}

	// Read Data from SHP into memory
	for (int i = 0; i < nElem; i++)
	{
		// Get the i-th Shape in the SHP file
		SHPObject	*psShape;
		psShape = SHPReadObject(hSHP, i);

		DPoint2 p2;
		DPoint3 p3;
		DLine2 *new_poly;
		switch (m_nSHPType)
		{
		case SHPT_POINT:
			p2.x = *psShape->padfX;
			p2.y = *psShape->padfY;
			m_Point2.SetAt(i, p2);
			break;
		case SHPT_POINTZ:
			p3.x = *psShape->padfX;
			p3.y = *psShape->padfY;
			p3.z = *psShape->padfZ;
			m_Point3.SetAt(i, p3);
			break;
		case SHPT_ARC:
		case SHPT_POLYGON:
			new_poly = new DLine2();
			new_poly->SetSize(psShape->nVertices);
			m_LinePoly.SetAt(i, new_poly);

			// Store each coordinate
			for (int j = 0; j < psShape->nVertices; j++)
			{
				p2.x = psShape->padfX[j];
				p2.y = psShape->padfY[j];
				new_poly->SetAt(j, p2);
			}
			break;
		}
		SHPDestroyObject(psShape);

		// Read corresponding attributes (DBF record fields)
		if (db != NULL)
		{
			int rec = AddRecord();
			for (iField = 0; iField < iFields; iField++)
			{
				Field *field = m_fields[iField];
				switch (field->m_type)
				{
				case FTString:
					SetValue(rec, iField, DBFReadStringAttribute(db, rec, iField));
					break;
				case FTInteger:
					SetValue(rec, iField, DBFReadIntegerAttribute(db, rec, iField));
					break;
				case FTDouble:
					SetValue(rec, iField, DBFReadDoubleAttribute(db, rec, iField));
					break;
				}
			}
		}
	}

	// Try loading projection from PRJ
	m_proj.ReadProjFile(m_strFilename);

	SHPClose(hSHP);
	if (db != NULL)
		DBFClose(db);
	return true;
}

bool vtRawLayer::AppendDataFrom(vtLayer *pL)
{
	// safety check
	if (pL->GetType() != LT_RAW)
		return false;

	vtRawLayer *pFrom = (vtRawLayer *)pL;

	// compatibility check
	if (pFrom->m_type != m_type)
		return false;

	// copy entities
	int i;
	int num = pFrom->NumEntities();
	for (i = 0; i < num; i++)
	{
		switch (m_type)
		{
		case SHPT_POINT:
			m_Point2.Append(pFrom->m_Point2[i]);
			break;
		case SHPT_POINTZ:
			m_Point3.Append(pFrom->m_Point3[i]);
			break;
		case SHPT_ARC:
		case SHPT_POLYGON:
			m_LinePoly.Append(pFrom->m_LinePoly[i]);	// steal pointer
			break;
		}
	}
	// empty the source layer
	switch (m_type)
	{
	case SHPT_POINT:  pFrom->m_Point2.SetSize(0); break;
	case SHPT_POINTZ: pFrom->m_Point3.SetSize(0); break;
	case SHPT_ARC:
	case SHPT_POLYGON: pFrom->m_LinePoly.SetSize(0); break;
	}
	return true;
}

void vtRawLayer::GetProjection(vtProjection &proj)
{
	proj = m_proj;
}

void vtRawLayer::SetProjection(vtProjection &proj)
{
	m_proj = proj;
}

void vtRawLayer::Offset(const DPoint2 &p)
{
	int i, entities = NumEntities();
	if (m_nSHPType == SHPT_POINT)
	{
		for (i = 0; i < entities; i++)
			m_Point2[i] += p;
	}
	if (m_nSHPType == SHPT_POINTZ)
	{
		for (i = 0; i < entities; i++)
			m_Point3[i] += DPoint3(p.x, p.y, 0);
	}
	if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
	{
		for (i = 0; i < entities; i++)
			m_LinePoly[i]->Add(p);
	}
}

void vtRawLayer::GetPropertyText(wxString &strIn)
{
	wxString str;

	str.Printf("Entity type: %s\n", SHPTypeName(m_nSHPType));
	strIn += str;

	str.Printf("Entities: %d\n", NumEntities());
	strIn += str;

	int entities = NumEntities();
	if (m_nSHPType == SHPT_POINTZ && entities > 0)
	{
		float fmin = 1E9, fmax = -1E9;

		for (int i = 0; i < entities; i++)
		{
			if (m_Point3[i].z > fmax) fmax = m_Point3[i].z;
			if (m_Point3[i].z < fmin) fmin = m_Point3[i].z;
		}

		str.Printf("Minimum Height: %.2f\n", fmin);
		strIn += str;

		str.Printf("Maximum Height: %.2f\n", fmax);
		strIn += str;
	}
}

int vtRawLayer::NumEntities()
{
	if (m_nSHPType == SHPT_POINT)
		return m_Point2.GetSize();
	else if (m_nSHPType == SHPT_POINTZ)
		return m_Point3.GetSize();
	else if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
		return m_LinePoly.GetSize();
	else
		return -1;
}

int vtRawLayer::GetEntityType()
{
	return m_nSHPType;
}

void vtRawLayer::SetEntityType(int type)
{
	m_nSHPType = type;
}

int vtRawLayer::AddPoint(const DPoint2 &p)
{
	int rec = -1;
	if (m_nSHPType == SHPT_POINT)
	{
		m_Point2.Append(p);
		AddRecord();
		SetModified(true);
	}
	return rec;
}

int vtRawLayer::AddPoint(const DPoint3 &p)
{
	int rec = -1;
	if (m_nSHPType == SHPT_POINTZ)
	{
		rec = m_Point3.Append(p);
		AddRecord();
		SetModified(true);
	}
	return rec;
}

void vtRawLayer::GetPoint(int num, DPoint3 &p)
{
	if (m_nSHPType == SHPT_POINTZ)
	{
		p = m_Point3.GetAt(num);
	}
}


/////////////////////////////////////////////////////////////////////////////
// Selection of Entities

void vtRawLayer::Select(int iEnt, bool set)
{
	m_Selected[iEnt] = set;
}

bool vtRawLayer::IsSelected(int iEnt)
{
	return m_Selected[iEnt];
}

int vtRawLayer::NumSelected()
{
	int count = 0;
	int size = m_Selected.GetSize();
	for (int i = 0; i < size; i++)
		if (m_Selected[i])
			count++;
	return count;
}

void vtRawLayer::DeselectAll()
{
	for (int i = 0; i < m_Selected.GetSize(); i++)
		m_Selected[i] = false;
}

void vtRawLayer::InvertSelection()
{
	for (int i = 0; i < m_Selected.GetSize(); i++)
		m_Selected[i] = !m_Selected[i];
}

int vtRawLayer::DoBoxSelect(const DRECT &rect, SelectionType st)
{
	int affected = 0;
	int entities = NumEntities();

	bool bIn;
	bool bWas;
	for (int i = 0; i < entities; i++)
	{
		bWas = m_Selected[i];
		if (st == ST_NORMAL)
			Select(i, false);

		if (m_nSHPType == SHPT_POINT)
			bIn = rect.ContainsPoint(m_Point2[i]);

		if (m_nSHPType == SHPT_POINTZ)
			bIn = rect.ContainsPoint(DPoint2(m_Point3[i].x, m_Point3[i].y));

		if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
			bIn = rect.ContainsLine(*m_LinePoly[i]);

		if (!bIn)
			continue;

		switch (st)
		{
		case ST_NORMAL:
			Select(i, true);
			affected++;
			break;
		case ST_ADD:
			Select(i, true);
			if (!bWas) affected++;
			break;
		case ST_SUBTRACT:
			Select(i, false);
			if (bWas) affected++;
			break;
		case ST_TOGGLE:
			Select(i, !bWas);
			affected++;
			break;
		}
	}
	return affected;
}

int vtRawLayer::SelectByCondition(int iField, int iCondition,
								  const char *szValue)
{
	int i, ival, itest;
	double dval, dtest;
	int entities = NumEntities(), selected = 0;
	int con = iCondition;
	vtString *sp;
	bool result;

	if (iField < 0)
	{
		dval = atof(szValue);
		for (i = 0; i < entities; i++)
		{
			// special field numbers are used to refer to the spatial components
			if (m_nSHPType == SHPT_POINT)
			{
				if (iField == -1) dtest = m_Point2[i].x;
				if (iField == -2) dtest = m_Point2[i].y;
				if (iField == -3) return -1;
			}
			else if (m_nSHPType == SHPT_POINTZ)
			{
				if (iField == -1) dtest = m_Point3[i].x;
				if (iField == -2) dtest = m_Point3[i].y;
				if (iField == -3) dtest = m_Point3[i].z;
			}
			else
				return -1;	// TODO: support non-point types
			if (con == 0) result = (dtest == dval);
			if (con == 1) result = (dtest > dval);
			if (con == 2) result = (dtest < dval);
			if (con == 3) result = (dtest >= dval);
			if (con == 4) result = (dtest <= dval);
			if (con == 5) result = (dtest != dval);
			if (result)
			{
				Select(i);
				selected++;
			}
		}
		return selected;
	}
	Field *field = m_fields[iField];
	switch (field->m_type)
	{
	case FTString:
		for (i = 0; i < entities; i++)
		{
			sp = field->m_string[i];
			if (con == 0) result = (sp->Compare(szValue) == 0);
			if (con == 1) result = (sp->Compare(szValue) > 0);
			if (con == 2) result = (sp->Compare(szValue) < 0);
			if (con == 3) result = (sp->Compare(szValue) >= 0);
			if (con == 4) result = (sp->Compare(szValue) <= 0);
			if (con == 5) result = (sp->Compare(szValue) != 0);
			if (result)
			{
				Select(i);
				selected++;
			}
		}
		break;
	case FTInteger:
		ival = atoi(szValue);
		for (i = 0; i < entities; i++)
		{
			itest = field->m_int[i];
			if (con == 0) result = (itest == ival);
			if (con == 1) result = (itest > ival);
			if (con == 2) result = (itest < ival);
			if (con == 3) result = (itest >= ival);
			if (con == 4) result = (itest <= ival);
			if (con == 5) result = (itest != ival);
			if (result)
			{
				Select(i);
				selected++;
			}
		}
		break;
	case FTDouble:
		dval = atof(szValue);
		for (i = 0; i < entities; i++)
		{
			dtest = field->m_double[i];
			if (con == 0) result = (dtest == dval);
			if (con == 1) result = (dtest > dval);
			if (con == 2) result = (dtest < dval);
			if (con == 3) result = (dtest >= dval);
			if (con == 4) result = (dtest <= dval);
			if (con == 5) result = (dtest != dval);
			if (result)
			{
				Select(i);
				selected++;
			}
		}
		break;
	}
	return selected;
}

void vtRawLayer::DeleteSelected()
{
	int i, entities = NumEntities();

	int target = 0;
	int newtotal = entities;
	for (i = 0; i < entities; i++)
	{
		if (!m_Selected[i])
		{
			if (target != i)
			{
				CopyEntity(i, target);
				m_Selected[target] = false;
			}
			target++;
		}
		else
			newtotal--;
	}
	if (m_nSHPType == SHPT_POINT)
		m_Point2.SetSize(newtotal);
	if (m_nSHPType == SHPT_POINTZ)
		m_Point3.SetSize(newtotal);
	if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
		m_LinePoly.SetSize(newtotal);
}

void vtRawLayer::CopyEntity(int from, int to)
{
	// copy geometry
	if (m_nSHPType == SHPT_POINT)
	{
		m_Point2[to] = m_Point2[from];
	}
	if (m_nSHPType == SHPT_POINTZ)
	{
		m_Point3[to] = m_Point3[from];
	}
	if (m_nSHPType == SHPT_ARC || m_nSHPType == SHPT_POLYGON)
	{
		m_LinePoly[to] = m_LinePoly[from];
	}
	// copy record
	for (int i = 0; i < m_fields.GetSize(); i++)
	{
		m_fields[i]->CopyValue(from, to);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Data Fields

int vtRawLayer::AddField(const char *name, DBFFieldType ftype, int string_length)
{
	Field *f = new Field(name, ftype);
	if (ftype == FTInteger)
	{
		f->m_width = 11;
		f->m_decimals = 0;
	}
	if (ftype == FTDouble)
	{
		f->m_width = 12;
		f->m_decimals = 12;
	}
	if (ftype == FTString)
	{
		f->m_width = string_length;
		f->m_decimals = 0;
	}
	return m_fields.Append(f);
}

int vtRawLayer::AddRecord()
{
	int recs;
	for (int i = 0; i < m_fields.GetSize(); i++)
	{
		recs = m_fields[i]->AddRecord();
	}
	m_Selected.Append(false);
	return recs;
}

void vtRawLayer::SetValue(int record, int field, const char *value)
{
	m_fields[field]->SetValue(record, value);
}

void vtRawLayer::SetValue(int record, int field, int value)
{
	m_fields[field]->SetValue(record, value);
}

void vtRawLayer::SetValue(int record, int field, double value)
{
	m_fields[field]->SetValue(record, value);
}

void vtRawLayer::GetValueAsString(int iRecord, int iField, vtString &str)
{
	Field *field = m_fields[iField];
	switch (field->m_type)
	{
	case FTString:
		str = *(field->m_string[iRecord]);
		break;
	case FTInteger:
		str.Format("%d", field->m_int[iRecord]);
		break;
	case FTDouble:
		str.Format("%lf", field->m_double[iRecord]);
		break;
	}
}

/////////////////////////////////////////////////

int Field::AddRecord()
{
	switch (m_type)
	{
	case FTInteger: return	m_int.Append(0); break;
	case FTDouble: return m_double.Append(0.0); break;
	case FTString: return m_string.Append(new vtString); break;
	}
	return -1;
}

void Field::SetValue(int record, const char *value)
{
	if (m_type != FTString)
		return;
	m_string[record] = new vtString(value);
}

void Field::SetValue(int record, int value)
{
	if (m_type == FTInteger)
		m_int[record] = value;
	else if (m_type == FTDouble)
		m_double[record] = value;
}

void Field::SetValue(int record, double value)
{
	if (m_type == FTInteger)
		m_int[record] = (int) value;
	else if (m_type == FTDouble)
		m_double[record] = value;
}

void Field::CopyValue(int FromRecord, int ToRecord)
{
	if (m_type == FTInteger)
		m_int[ToRecord] = m_int[FromRecord];
	if (m_type == FTDouble)
		m_double[ToRecord] = m_double[FromRecord];

	// when dealing with strings, copy by value not reference, to
	// avoid memory tracking issues
	if (m_type == FTString)
		*m_string[ToRecord] = *m_string[FromRecord];
}

