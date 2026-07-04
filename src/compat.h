#pragma once
#ifdef _WIN32
	#define strcasecmp _stricmp
	#define stat _stat
#endif
