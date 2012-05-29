/*
 * GrandOrgue - free pipe organ simulator
 *
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2012 GrandOrgue contributors (see AUTHORS)
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * MA 02111-1307, USA.
 */

#include "GOrguePath.h"
#include <wx/filename.h>

wxString GOCreateFilename(wxString path, wxString file)
{
	/* Translate directory seperator from ODF(\) to native format */
	wxString temp = file;
	temp.Replace(wxT("\\"), wxString(wxFileName::GetPathSeparator()));
	temp = path + wxFileName::GetPathSeparator() + temp;

	wxFileName path_name(temp);
	path_name.Normalize(wxPATH_NORM_DOTS);
	if (path_name.GetLongPath() != path_name.GetFullPath())
		wxLogWarning(_("Filename '%s' not compatible with case sensitive systems"), file.c_str());

	return temp;
}

void GOCreateDirectory(wxString path)
{
	if (wxFileName::DirExists(path))
		return;
	if(!wxFileName::Mkdir(path, 0777, wxPATH_MKDIR_FULL))
		wxLogError(_("Failed to create directory '%s"), path.c_str());
}

wxString GONormalizePath(wxString path)
{
	wxFileName name(path);
	name.MakeAbsolute();
	return name.GetLongPath();
}

wxString GOGetPath(wxString path)
{
	wxFileName name(GONormalizePath(path));
	return name.GetPath();
}