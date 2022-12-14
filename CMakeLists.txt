cmake_minimum_required (VERSION 3.8)

project (ArkanoidGame CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")

set(EXECUTABLE_NAME "ArkanoidGame")

if (NOT DEFINED ${TDENGINE2_LIBRARY_NAME})
	set(TDENGINE2_LIBRARY_NAME "TDEngine2")
endif ()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# attach TDEngine2
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/TDEngine2/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/bin")


configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")


set(HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/include/Components.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/Utilities.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/CGameLevelsCollection.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/components/CPaddle.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/components/CBrick.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/components/CBall.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/components/CGameInfo.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/components/CDamageable.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/components/CGravitable.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/components/Bonuses.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/components/CLevelSettings.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CPaddleControlSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CBallUpdateSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CDamageablesUpdateSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CCollectingSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CGravityUpdateSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/BonusCollectSystems.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CStickyBallsProcessSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CPowerUpSpawnSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CProjectilesPoolSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CGameUIUpdateSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/systems/CPaddlePositionerSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/editor/CLevelsEditorWindow.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/CCustomEngineListener.h")

set(SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/source/CCustomEngineListener.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/Components.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/Utilities.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/CGameLevelsCollection.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/components/CPaddle.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/components/CBrick.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/components/CBall.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/components/CGameInfo.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/components/CDamageable.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/components/CGravitable.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/components/Bonuses.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/components/CLevelSettings.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CPaddleControlSystem.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CBallUpdateSystem.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CDamageablesUpdateSystem.cpp"	
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CStickyBallsProcessSystem.cpp"	
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CGravityUpdateSystem.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/BonusCollectSystems.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CPowerUpSpawnSystem.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CProjectilesPoolSystem.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CGameUIUpdateSystem.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/systems/CPaddlePositionerSystem.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/editor/CLevelsEditorWindow.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

source_group("includes" FILES ${HEADERS})
source_group("sources" FILES ${SOURCES})


if (MSVC) 	#cl.exe compiler's options

	#Debug compiler's options
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /std:c++14 /MDd /W3 /GS /Zc:inline /Od /ZI  /Zc:wchar_t")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /RTC1 /Gd /Oy- /EHsc /nologo /diagnostics:classic /errorReport:prompt /sdl /permissive- /analyze-  /wd4250")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D _DEBUG")

	#Release compiler's options
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /std:c++14 /permissive- /GS /GL /analyze- /W3 /Gy /Zc:wchar_t /O2 /sdl /Zc:inline  /wd4250")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /fp:precise /D _WINDLL /D _MBCS /errorReport:prompt /WX- /Zc:forScope /Gd /Oy- /Oi /MD /EHsc /nologo /diagnostics:classic")

endif(MSVC)


if (UNIX)
	message(STATUS "UNIX system has detected...")

	include(CheckCXXCompilerFlag)

	CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX14)

	if(COMPILER_SUPPORTS_CXX14)		
		set(CMAKE_CXX_STANDARD 14)
		set(CMAKE_CXX_STANDARD_REQUIRED ON)
	else()
		message(ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
	endif()
endif (UNIX)


add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

# dependencies of TDEngine2
target_include_directories(${EXECUTABLE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/TDEngine2/deps/glew-2.1.0/include")
target_include_directories(${EXECUTABLE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/TDEngine2/deps/Wrench/source")
target_include_directories(${EXECUTABLE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/TDEngine2/deps/Box2D/")
target_include_directories(${EXECUTABLE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/TDEngine2/deps/optick/include")

if (UNIX)
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
endif ()

target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${TDENGINE2_LIBRARY_NAME})


# Copy .project into executable's directory
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	"${CMAKE_CURRENT_SOURCE_DIR}/${EXECUTABLE_NAME}.project"
	"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")