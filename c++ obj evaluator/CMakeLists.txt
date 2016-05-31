 
cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
#Variable for location of parallel-nsgaII-backend

FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem system program_options mpi serialization timer chrono)
find_package(GDAL)
find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})

SET(USE_VTK CACHE BOOL "Set to on to use vtk visualisation")
IF (USE_VTK)
        find_package(VTK REQUIRED)
                IF(VTK_FOUND)
                include(${VTK_USE_FILE})
                add_definitions(-DWITH_VTK)
                ENDIF()
ENDIF()


set(AHHZ_RASTER_UTIL "Not Specified" CACHE PATH "Path to Alex Hagen-Zanker's Raster Utility Include direction (select above blink)")
set(AHHZ_RASTER_ITERATOR "Not Specified" CACHE PATH "Path to Alex Hagen-Zanker's Raster Iterator Include direction (select folder above blink)")
set(PARALLEL-NSGAII "Not Specified" CACHE PATH "Path to Jeff's parallel NSGAII code")
set(MCL "Not Specified" CACHE PATH "Path to MCL code")
set(MAC_FRAMEWORK_PATHS "FALSE" CACHE BOOL "Whether to use header paths in include statements for mac gdal framework")

if(MAC_FRAMEWORK_PATHS)
    add_definitions(-DWITH_MAC_FRAMEWORK)
ENDIF()

include_directories(${GDAL_INCLUDE_DIR} )
include_directories(${Boost_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES(${AHHZ_RASTER_UTIL} )
INCLUDE_DIRECTORIES(${AHHZ_RASTER_ITERATOR})
INCLUDE_DIRECTORIES(${PARALLEL-NSGAII})
INCLUDE_DIRECTORIES(${MCL})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_definitions(-DCLANG)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-DGNU)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  add_definitions(-DINTEL)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_definitions(-DMSVC)
endif()

SET(Metro_calib_parallel_Src
        MainPar.cpp
        MetronamicaOF.cpp
        MetronamicaOF.hpp

)

SET(Metro_calib_serial_Src
        MainSer.cpp
        MetronamicaOF.cpp
        MetronamicaOF.hpp

)


file(GLOB_RECURSE AHHZ_Raster
 "${AHHZ_RASTER_UTIL}/*.h"
 "${AHHZ_RASTER_UTIL}/*.hpp"
 "${AHHZ_RASTER_UTIL}/*.cpp" 
 "${AHHZ_RASTER_ITERATOR}/*.h" 
 "${AHHZ_RASTER_ITERATOR}/*.hpp" 
 "${AHHZ_RASTER_ITERATOR}/*.cpp"
 )

SET(prll-nsga-src
        "${PARALLEL-NSGAII}/Crossover.hpp"
        "${PARALLEL-NSGAII}/Individual.hpp"
        "${PARALLEL-NSGAII}/Mutation.hpp"
        "${PARALLEL-NSGAII}/parallel_nsgaII_backend.cpp"
        "${PARALLEL-NSGAII}/parallel_nsgaII_backend.hpp"
        "${PARALLEL-NSGAII}/parallel_nsgaII_backendPriv.hpp"
        "${PARALLEL-NSGAII}/Population.hpp"
        "${PARALLEL-NSGAII}/Types.hpp"
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
        "${MCL}/ReadFuzzyTables.h"
        "${MCL}/dt.h"
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
        )

add_executable(metrocalpar ${Metro_calib_parallel_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES})
target_link_libraries(metrocalpar ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} )

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metrocalpar ${VTK_LIBRARIES})
    else()
        target_link_libraries(metrocalpar vtkHybrid vtkWidgets)
    endif()
ENDIF()



add_executable(metrocalser ${Metro_calib_serial_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES})
target_link_libraries(metrocalser ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} )

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metrocalser ${VTK_LIBRARIES})
    else()
        target_link_libraries(metrocalser vtkHybrid vtkWidgets)
    endif()
ENDIF()
