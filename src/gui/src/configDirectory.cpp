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
