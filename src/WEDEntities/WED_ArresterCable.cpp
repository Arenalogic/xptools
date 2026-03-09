/*
 * Copyright (c) 2026, ACT Project.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "WED_ArresterCable.h"
#include "IODefs.h"
#include "AptDefs.h"
#include "WED_XMLWriter.h"

DEFINE_PERSISTENT(WED_ArresterCable)

WED_ArresterCable::WED_ArresterCable(WED_Archive * a, int i) : WED_GISChain(a,i),
	cable_type(this,PROP_Name("Cable Type", XML_Name("arrester_cable","cable_type")), "BAK-12"),
	runway_id (this,PROP_Name("Runway ID",  XML_Name("arrester_cable","runway_id")),  "")
{
}

WED_ArresterCable::~WED_ArresterCable()
{
}

void WED_ArresterCable::CopyFrom(const WED_ArresterCable * rhs)
{
	WED_GISChain::CopyFrom(rhs);
	StateChanged();
	cable_type.value = rhs->cable_type.value;
	runway_id.value  = rhs->runway_id.value;
}

bool WED_ArresterCable::ReadFrom(IOReader * reader)
{
	bool r = WED_GISChain::ReadFrom(reader);
	cable_type.ReadFrom(reader);
	runway_id.ReadFrom(reader);
	return r;
}

void WED_ArresterCable::WriteTo(IOWriter * writer)
{
	WED_GISChain::WriteTo(writer);
	cable_type.WriteTo(writer);
	runway_id.WriteTo(writer);
}

void	WED_ArresterCable::AddExtraXML(WED_XMLElement * obj)
{
	WED_XMLElement * xml = obj->add_sub_element("arrester_cable");
	xml->add_attr_c_str("cable_type", cable_type.value.c_str());
	xml->add_attr_c_str("runway_id",  runway_id.value.c_str());
}

void	WED_ArresterCable::StartElement(
							WED_XMLReader * reader,
							const XML_Char *	name,
							const XML_Char **	atts)
{
	if(strcmp(name,"arrester_cable")==0)
	{
		const XML_Char * ct = get_att("cable_type",atts);
		if(ct) cable_type.value = ct;

		const XML_Char * ri = get_att("runway_id",atts);
		if(ri) runway_id.value = ri;
	}
	else
		WED_GISChain::StartElement(reader,name,atts);
}

void	WED_ArresterCable::EndElement(void) { }

void	WED_ArresterCable::PopHandler(void) { }

void	WED_ArresterCable::Import(const AptArresterCable_t& x, void (* print_func)(void *, const char *, ...), void * ref)
{
	cable_type.value = x.cable_type;
	runway_id.value  = x.runway_id;
}

void	WED_ArresterCable::Export(AptArresterCable_t& x) const
{
	x.cable_type = cable_type.value;
	x.runway_id  = runway_id.value;
}
