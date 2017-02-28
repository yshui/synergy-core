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

#pragma once

#include "common/IInterface.h"
#include <string>
#include "base/String.h"

//! Interface for architecture dependent file system operations
/*!
This interface defines the file system operations required by
synergy.  Each architecture must implement this interface.
*/
class IArchFile : public IInterface {
public:
	//! @name manipulators
	//@{

	//! Extract base name
	/*!
	Find the base name in the given \c pathname.
	*/
	virtual const char*	getBasename(const char* pathname) = 0;

	//! Get installed directory
	/*!
	Returns the directory in which Synergy is installed.
	*/
	virtual std::string	getInstalledDirectory() = 0;

	//! Get log directory
	/*!
	Returns the log file directory.
	*/
	virtual std::string	getLogDirectory() = 0;

	//! Get's the Synergy config directory
	/*!
	Returns the Synergy config directory.
	Windows XP: 'C:\All Users\Synergy\'
	Windows Vista and higher: 'C:\ProgramData\Synergy\'
	Unixes: '/etc/Synergy/'
	OSX: '/Library/Application Support/Synergy/' ???
	*/
	virtual std::string	getConfigDirectory() = 0;

	//! Get's the Synergy server's config file path
	std::string getConfigFilePath();

	//@}
	//! Set the user's profile directory
	/*
	Returns the user's profile directory.
	*/
	virtual void		setConfigDirectory(const String& s) = 0;
};
