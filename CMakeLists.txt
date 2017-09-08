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

foreach(source IN LISTS Roommaker_Studio_FILES)
	get_filename_component(source_path "${source}" PATH)
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" source_path "${source_path}")
    string(REPLACE "/" "\\" source_path "${source_path}")
    source_group("${source_path}" FILES "${source}")
endforeach()

######################
# COMPILE DEPENDENCIES

# make everything output to the same place (we do not have to copy sfml's libs to where Roommaker_Studio is if Roommaker_Studio already outputs next to them)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(extlibs) # find all externals

# options for externals - use all sfml libs but network+audio
set(Roommaker_Studio_SFML_LIB sfml-main sfml-system sfml-window sfml-graphics)
set(Roommaker_Studio_SFML_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/SFML/include)

set(Roommaker_Studio_WX_LIB core base adv propgrid aui)
set(Roommaker_Studio_WX_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/wxWidgets/include)

set(Roommaker_Studio_RAPIDJSON_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/rapidjson)

######################
# COMPILE DATA

# Roommaker_Studio (Core)
add_executable(Roommaker_Studio ${Roommaker_Studio_FILES})
include_directories(${Roommaker_Studio_INCLUDE_FOLDERS})

target_compile_definitions(Roommaker_Studio PRIVATE RMSDLL_Export) # tell Roommaker_Studio's header files that they are exporting functions, not importing them

# set flags for the engine to compile properly
if(MSVC)
	SET(CMAKE_CXX_FLAGS "/EHsc /bigobj")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

# Link libraries - include required files
target_link_libraries(Roommaker_Studio ${Roommaker_Studio_SFML_LIB})
target_link_libraries(Roommaker_Studio ${Roommaker_Studio_WX_LIB})

include_directories(${Roommaker_Studio_SFML_INCLUDE})
include_directories(${Roommaker_Studio_WX_INCLUDE})
include_directories(${Roommaker_Studio_RAPIDJSON_INCLUDE})

# On any UNIX os, Roommaker_Studio needs libdl, X11 and GTK2
if(UNIX)
	target_link_libraries(Roommaker_Studio dl)
	
	target_link_libraries(Roommaker_Studio X11)

	include_directories(${GTK2_INCLUDE_DIRS})
	target_link_libraries(Roommaker_Studio ${GTK2_LIBRARIES})
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

# cmake is so janky what the fuck
add_definitions(-DWXUSINGDLL)

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