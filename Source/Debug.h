#pragma once

#ifdef _MSC_VER
	#define _DEBUGBREAK() __debugbreak()
#else
	#define _DEBUGBREAK()
#endif


#ifdef _DEBUG
	#define ASSERT(check) if(!(check)) { _DEBUGBREAK(); }
#else
	#define ASSERT(check) 
#endif
