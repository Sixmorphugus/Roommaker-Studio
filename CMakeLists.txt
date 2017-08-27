cmake_minimum_required(VERSION 3.6)

######################
# COMPILE PROPERTIES

# all of this is contained in the Roommaker_Studio project
project(Roommaker_Studio)

# Roommaker_Studio's files
file(GLOB Roommaker_Studio_INCLUDE_FOLDERS
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*"
)

file(GLOB Roommaker_Studio_SRC_FOLDERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
)

file(GLOB Roommaker_Studio_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp"
)

# make everything output to the same place (we do not have to copy sfml's libs to where Roommaker_Studio is if Roommaker_Studio already outputs next to them)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

######################
# COMPILE DEPENDENCIES

add_subdirectory(extlibs) # find all externals

# options for externals - use all sfml libs but network+audio
set(Roommaker_Studio_SFML_LIB sfml-main sfml-system sfml-window sfml-graphics)
set(Roommaker_Studio_SFML_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/SFML/include)

######################
# COMPILE DATA

# Roommaker_Studio (Core)
add_executable(Roommaker_Studio ${Roommaker_Studio_FILES})
include_directories(${Roommaker_Studio_INCLUDE_FOLDERS})

target_compile_definitions(Roommaker_Studio PRIVATE Roommaker_StudioDLL_Export) # tell Roommaker_Studio's header files that they are exporting functions, not importing them

# set flags for the engine to compile properly
if(MSVC)
	SET(CMAKE_CXX_FLAGS "/EHsc /bigobj")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

# Link libraries - include required files
target_link_libraries(Roommaker_Studio ${Roommaker_Studio_SFML_LIB})
include_directories(${Roommaker_Studio_SFML_INCLUDE})

# On any UNIX os, Roommaker_Studio needs libdl
if(UNIX)
	target_link_libraries(Roommaker_Studio dl)
endif()

######################
# POST-COMPILE

# update the version number upon each compilation
add_custom_command(
    TARGET Roommaker_Studio
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}" -DPROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}" -P "${CMAKE_CURRENT_LIST_DIR}/version.cmake"
)

# copy base to the binary dir
add_custom_command(TARGET Roommaker_Studio POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/base $<TARGET_FILE_DIR:Roommaker_Studio>/base
)
	
# copy OpenAL32.dll to the base dir

######################
# PRE-COMPILE

# get the initial git version number (sadly this repeats code)

# find git version number
execute_process(
  COMMAND git rev-list HEAD --count
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT GIT_VERSION)
	set(GIT_VERSION 0)
endif()

# build.h will therefore contain our build number accurately enough to use
configure_file (
  "${PROJECT_SOURCE_DIR}/build.h.in"
  "${PROJECT_BINARY_DIR}/build.h"
)

# ----

include_directories("${PROJECT_BINARY_DIR}") # reason for this is that build.h is created in the program's compilation folder

# fix msc's working directory
if(MSVC)
	file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user" 
	"<?xml version=\"1.0\" encoding=\"utf-8\"?>
	<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
	  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">
		<LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
		<DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
	  </PropertyGroup>
	  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">
		<LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
		<DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
	  </PropertyGroup>
	  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='RelWithDebInfo|Win32'\">
		<LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
		<DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
	  </PropertyGroup>
	  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">
		<LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
		<DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
	  </PropertyGroup>
	  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='MinSizeRel|Win32'\">
		<LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
		<DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
	  </PropertyGroup>
	  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">
		<LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
		<DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
	  </PropertyGroup>
	</Project>")
endif()