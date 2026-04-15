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

#ifndef WED_ARRESTERCABLE_H
#define WED_ARRESTERCABLE_H

#include "WED_GISChain.h"

struct	AptArresterCable_t;

class	WED_ArresterCable : public WED_GISChain {

DECLARE_PERSISTENT(WED_ArresterCable)

public:

	virtual	bool			IsClosed	(void	) const	{ return false; }

	// WED_Persistent
	virtual	bool 			ReadFrom(IOReader * reader);
	virtual	void 			WriteTo(IOWriter * writer);
	// WED_Thing
	virtual	void			AddExtraXML(WED_XMLElement * obj);

	virtual void		StartElement(
								WED_XMLReader * reader,
								const XML_Char *	name,
								const XML_Char **	atts);
	virtual	void		EndElement(void);
	virtual	void		PopHandler(void);

			void			Import(const AptArresterCable_t& x, void (* print_func)(void *, const char *, ...), void * ref);
			void			Export(		 AptArresterCable_t& x) const;

	virtual const char *	HumanReadableType(void) const { return "Arrester Cable"; }

protected:

	virtual	bool			IsJustPoints(void) const { return false; }

private:

	WED_PropStringText		cable_type;		// BAK-12, BAK-14, BAK-15
	WED_PropStringText		runway_id;		// e.g. RW05R
	WED_PropBoolText		always_raised;	// true = permanently raised, no instructor control in CommandCentral

};

#endif /* WED_ARRESTERCABLE_H */
