/*
 * GrandOrgue - free pipe organ simulator
 *
 * MyOrgan 1.0.6 Codebase - Copyright 2006 Milan Digital Audio LLC
 * MyOrgan is a Trademark of Milan Digital Audio LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef GOGUIIMAGE_H
#define GOGUIIMAGE_H

#include <wx/wx.h>
#include "GOGUIControl.h"

class GOGUIImage : public GOGUIControl
{
protected:
	wxBitmap* m_Bitmap;
	unsigned m_TileOffsetX;
	unsigned m_TileOffsetY;

public:
	GOGUIImage(GOGUIPanel* panel);

	void Load(IniFileConfig& cfg, wxString group);

	void Draw(wxDC* dc);
};

#endif