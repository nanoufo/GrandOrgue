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

#ifndef GOGUIBUTTON_H
#define GOGUIBUTTON_H

#include <wx/wx.h>
#include "GOGUIControl.h"

class GOrgueButton;

class GOGUIButton : public GOGUIControl
{
protected:
	bool m_IsPiston;
	GOrgueButton* m_Button;
	int m_ShortcutKey;
	wxRect m_MouseRect;
	unsigned m_Radius;
	wxBitmap* m_OnBitmap;
	wxBitmap* m_OffBitmap;
	unsigned m_FontSize;
	wxString m_FontName;
	wxColor m_TextColor;
	wxString m_Text;
	wxRect m_TextRect;
	unsigned m_TextWidth;
	unsigned m_DispCol;
	unsigned m_DispRow;
	unsigned m_TileOffsetX;
	unsigned m_TileOffsetY;

public:
	GOGUIButton(GOGUIPanel* panel, GOrgueButton* control, bool is_piston = false, unsigned x_pos = 1, unsigned y_pos = 1);

	void Load(IniFileConfig& cfg, wxString group);

	void HandleKey(int key);
	void HandleMousePress(int x, int y, bool right, GOGUIMouseState& state);
	void Draw(wxDC* dc);
};

#endif