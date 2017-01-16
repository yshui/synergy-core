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

#include "arch/unix/ArchFileUnix.h"

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <cstring>

//
// ArchFileUnix
//

ArchFileUnix::ArchFileUnix()
{
	// do nothing
}

ArchFileUnix::~ArchFileUnix()
{
	// do nothing
}

const char*
ArchFileUnix::getBasename(const char* pathname)
{
	if (pathname == NULL) {
		return NULL;
	}

	const char* basename = strrchr(pathname, '/');
	if (basename != NULL) {
		return basename + 1;
	}
	else {
		return pathname;
	}
}

std::string
ArchFileUnix::getInstalledDirectory()
{
#if WINAPI_XWINDOWS
	return "/usr/bin/";
#else
	return "/Applications/Synergy.app/Contents/MacOS/";
#endif
}

std::string
ArchFileUnix::getLogDirectory()
{
	return "/var/log/";
}

std::string
ArchFileUnix::getConfigDirectory()
{
	if (!m_configDirectory.empty())
		return m_configDirectory;
	return SYNCONF_DIR;
}

void
ArchFileUnix::setConfigDirectory(const String& s)
{
	m_configDirectory = s;
}
