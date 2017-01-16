#include "arch/unix/ArchFileUnix.h"

#include <string>

std::string
IArchFile::getConfigFilePath()
{
	return getConfigDirectory() + "synserver.conf";
}
