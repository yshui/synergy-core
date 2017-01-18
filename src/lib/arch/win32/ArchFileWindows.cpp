/*
 * synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2002 Chris Schoeneman
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "arch/win32/ArchFileWindows.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shlobj.h>
#include <tchar.h>
#include <string.h>
#include <VersionHelpers.h>

//
// ArchFileWindows
//

ArchFileWindows::ArchFileWindows()
{
	// do nothing
}

ArchFileWindows::~ArchFileWindows()
{
	// do nothing
}

const char*
ArchFileWindows::getBasename(const char* pathname)
{
	if (pathname == NULL) {
		return NULL;
	}

	// check for last slash
	const char* basename = strrchr(pathname, '/');
	if (basename != NULL) {
		++basename;
	}
	else {
		basename = pathname;
	}

	// check for last backslash
	const char* basename2 = strrchr(pathname, '\\');
	if (basename2 != NULL && basename2 > basename) {
		basename = basename2 + 1;
	}

	return basename;
}

std::string
ArchFileWindows::getInstalledDirectory()
{
	char fileNameBuffer[MAX_PATH];
	GetModuleFileName(NULL, fileNameBuffer, MAX_PATH);
	std::string fileName(fileNameBuffer);
	size_t lastSlash = fileName.find_last_of("\\");
	fileName = fileName.substr(0, lastSlash);

	return fileName;
}

std::string
ArchFileWindows::getLogDirectory()
{
	return getConfigDirectory();
}

std::string
ArchFileWindows::getConfigDirectory()
{
	if (!m_configDirectory.empty())
		return m_configDirectory;

	char buffer[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL,
		SHGFP_TYPE_CURRENT, buffer);

	if (result != S_OK)
	{
		// this is problematic and shouldn't happen
		return "C:\\";
	}

	return std::string(buffer) + '\\';
}

void
ArchFileWindows::setConfigDirectory(const String& s)
{
	m_configDirectory = s;
}
