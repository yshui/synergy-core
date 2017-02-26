/*
 * synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2017 yupi2 (Yachu Pachi)
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

#include <QString>
#include <QDir>
#include <QStandardPaths>

#if WIN32
#include <Windows.h>
#include <VersionHelpers.h>
#endif

QString g_GetConfigDirectory()
{
	QString dir =
		QStandardPaths::standardLocations(QStandardPaths::GenericConfigLocation)[0]
		+ QDir::separator() + "Synergy" + QDir::separator();

	if (!QDir(dir).mkpath("."))
		qFatal("failed to create/access directory %s", dir.toUtf8().constData());

	return dir;
}
