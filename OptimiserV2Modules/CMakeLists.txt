 
cmake_minimum_required(VERSION 3.0)
PROJECT(Charles-Metro-Cal-v2)
set (CMAKE_CXX_STANDARD 11)
#Variable for location of parallel-nsgaII-backend

FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem system program_options mpi serialization timer chrono date_time)
find_package(GDAL)
include_directories("${CMAKE_SOURCE_DIR}/pugixml-1.7/src/")

set(AHHZ_RASTER_UTIL "Not Specified" CACHE PATH "Path to Alex Hagen-Zanker's Raster Utility Include direction (select above blink)")
set(AHHZ_RASTER_ITERATOR "Not Specified" CACHE PATH "Path to Alex Hagen-Zanker's Raster Iterator Include direction (select folder above blink)")
set(GEONAMICA_OPTIMISATION_FRAMEWORK "Not Specified" CACHE PATH "Path to Jeff's Geonamica optimiser framework code")
set(MCL "Not Specified" CACHE PATH "Path to MCL code")
set(PARALLEL-NSGAII "Not Specified" CACHE PATH "Path to Jeff's Parallel NSGAII code")

set(MAC_FRAMEWORK_PATHS "FALSE" CACHE BOOL "Whether to use header paths in include statements for mac gdal framework")

if(MAC_FRAMEWORK_PATHS)
    add_definitions(-DWITH_MAC_FRAMEWORK)
ENDIF()


include_directories(${GDAL_INCLUDE_DIR} )
include_directories(${Boost_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES(${AHHZ_RASTER_UTIL} )
INCLUDE_DIRECTORIES(${AHHZ_RASTER_ITERATOR})
INCLUDE_DIRECTORIES(${MCL})
INCLUDE_DIRECTORIES(${GEONAMICA_OPTIMISATION_FRAMEWORK})
INCLUDE_DIRECTORIES(${PARALLEL-NSGAII})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_definitions(-DCLANG)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-DGNU)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  add_definitions(-DINTEL)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_definitions(-DMSVC)
endif()

add_definitions(-Dfast_fks)
add_definitions(-Dclump_fast)

SET(PUGIXML-SRC
        "./pugixml-1.7/src/pugiconfig.hpp"
        "./pugixml-1.7/src/pugixml.hpp"
        "./pugixml-1.7/src/pugixml.cpp"
        )

file(GLOB_RECURSE AHHZ_Raster
 "${AHHZ_RASTER_UTIL}/*.h"
 "${AHHZ_RASTER_UTIL}/*.hpp"
 "${AHHZ_RASTER_UTIL}/*.cpp" 
 "${AHHZ_RASTER_ITERATOR}/*.h" 
 "${AHHZ_RASTER_ITERATOR}/*.hpp" 
 "${AHHZ_RASTER_ITERATOR}/*.cpp"
 )


SET (MCL_HEADERS
        "${MCL}/MapComparison_0_4.h"
                "${MCL}/Map_Matrix.h"
                "${MCL}/ReadInMap.h"
                "${MCL}/Types.h"
                "${MCL}/RasterComparisonModule/KappaSimulation.h"
                "${MCL}/RasterComparisonModule/Kappa.h"
        "${MCL}/Neighbourhood.h"
        "${MCL}/FuzzyKappaSimulation.h"
        "${MCL}/FuzzyKappaSimulationImproved.hpp"
        "${MCL}/FuzzyKappaSimulationImprovedFast.hpp"
        "${MCL}/ReadFuzzyTables.h"
        "${MCL}/dt.h"
        "${MCL}/Clumpiness.h"
        "${MCL}/ClumpinessFast.h"
        )

SET (MCL_SOURCES
        "${MCL}/MapComparison_0_4.cpp"
        "${MCL}/Map_Matrix.cpp"
                "${MCL}/Map_Matrix_Impl.cpp"
#	   		ReadInMap.cpp
                "${MCL}/ReadInMap_Impl.cpp"
                "${MCL}/RasterComparisonModule/KappaSimulation.cpp"
                "${MCL}/RasterComparisonModule/Kappa.cpp"
        "${MCL}/Neighbourhood.cpp"
        "${MCL}/Neighbourhood_Impl.cpp"
        "${MCL}/FuzzyKappaSimulation.cpp"
        "${MCL}/FuzzyKappaSimulationImproved.cpp"
        "${MCL}/FuzzyKappaSimulationImprovedFast.cpp"
        "${MCL}/Clumpiness.cpp"
        "${MCL}/ClumpinessFast.cpp"
        )

link_directories(${Boost_LIBRARY_DIRS})


##################################################################################################################
#                                                                                                                #
#                 Madrid Evaluator 2Obj Module                                                                   #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Calibration_Obj_Module
        CalibrationMetricModule.cpp
        CalibrationMetricModule.hpp
        "${GEONAMICA_OPTIMISATION_FRAMEWORK}/Modules/EvaluatorModules/EvaluatorModuleAPI.hpp"
        ${MCL_HEADERS}
        ${AHHZ_Raster}
        ${MCL_SOURCES}
        )



add_library(calibrationobjmodule SHARED ${Calibration_Obj_Module})
target_link_libraries(calibrationobjmodule ${GDAL_LIBRARY} ${Boost_LIBRARIES})

##################################################################################################################
#                                                                                                                #
#                 Madrid Set DVs Module                                                                          #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Madrid_DV_Module
        MadridDVsModule.cpp
        MadridDVsModule.hpp
        "${GEONAMICA_OPTIMISATION_FRAMEWORK}/Modules/DVModules/DVModuleAPI.hpp"
        ${PUGIXML-SRC}
        )



add_library(madriddvmodule SHARED ${Madrid_DV_Module})
target_link_libraries(madriddvmodule ${Boost_LIBRARIES})

