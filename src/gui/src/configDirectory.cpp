#include <QString>
#include <QDir>
#include <QStandardPaths>

#if WIN32
#include <Windows.h>
#include <VersionHelpers.h>
#endif

QString g_GetConfigDirectory()
{
	QString dir;

	// NOTE: AppConfigLocation does .config/Synergy/Synergy on unixes.
	// That's why GenericConfigLocation is used.
	//dir =
	//	QStandardPaths::standardLocations(QStandardPaths::GenericConfigLocation)[0]
	//	.append(QDir::separator())
	//	.append("Synergy");

#if WIN32
	if (IsWindowsVistaOrGreater())
		dir = "C:\\ProgramData\\Synergy\\";
	else
		dir = "C:\\All Users\\Synergy\\";
#else
	dir = SYNCONF_DIR;
#endif

	if (!QDir(dir).mkpath("."))
		qFatal("failed to open/access directory %s", dir.toLatin1());

	return dir;
}
