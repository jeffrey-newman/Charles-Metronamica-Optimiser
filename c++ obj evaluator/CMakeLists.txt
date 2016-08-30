 
cmake_minimum_required(VERSION 3.0)
PROJECT(Charles-Metro-Cal)
set (CMAKE_CXX_STANDARD 11)
#Variable for location of parallel-nsgaII-backend

FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem system program_options mpi serialization timer chrono date_time)
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

# Define required for how hypervolume is calculated.
add_definitions(-DVARIANT=4)
# define which fks code to use.
add_definitions(-Dfast_fks)
add_definitions(-Dclump_fast)

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

# add path to FindPNGwriter.cmake, e.g. in the directory in cmake/
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

# find PNGwriter installation
#   optional: prefer static libraries over shared ones (but do not force them)
#set(PNGwriter_USE_STATIC_LIBS ON)

#   optional: specifiy (minimal) version / require to find it
#           (PNGwriter 0.5.6 REQUIRED)
find_package(PNGwriter)

if(PNGwriter_FOUND)
  # where to find the pngwriter.h header file (-I include for your compiler)
  include_directories(${PNGwriter_INCLUDE_DIRS})
  # additional compiler flags (e.g. -DNO_FREETYPE)
  add_definitions(${PNGwriter_DEFINITIONS})
  # libraries to link against (including dependencies)
#  set(LIBS ${LIBS} ${PNGwriter_LIBRARIES})
endif(PNGwriter_FOUND)

# add_executable(yourBinary ${SOURCES})
# ...
# target_link_libraries(yourBinary ${LIBS})



file(GLOB_RECURSE AHHZ_Raster
 "${AHHZ_RASTER_UTIL}/*.h"
 "${AHHZ_RASTER_UTIL}/*.hpp"
 "${AHHZ_RASTER_UTIL}/*.cpp" 
 "${AHHZ_RASTER_ITERATOR}/*.h" 
 "${AHHZ_RASTER_ITERATOR}/*.hpp" 
 "${AHHZ_RASTER_ITERATOR}/*.cpp"
 )

SET(AHHZ_Raster_Utility
    "${AHHZ_RASTER_UTIL}/blink/raster/Utility.cpp"
    "${AHHZ_RASTER_UTIL}/blink/raster/gdal_raster_lru.cpp"
    )

SET(prll-nsga-src
        "${PARALLEL-NSGAII}/Checkpoint.hpp"
        "${PARALLEL-NSGAII}/Comparator.hpp"
        "${PARALLEL-NSGAII}/Crossover.hpp"
        "${PARALLEL-NSGAII}/DebsCrowdingDistance.hpp"
        "${PARALLEL-NSGAII}/DebsNondominatedSorting.hpp"
        "${PARALLEL-NSGAII}/Evaluation.hpp"
        "${PARALLEL-NSGAII}/Individual.hpp"
        "${PARALLEL-NSGAII}/Merge.hpp"
        "${PARALLEL-NSGAII}/Mutation.hpp"
        "${PARALLEL-NSGAII}/NSGAII.hpp"
        "${PARALLEL-NSGAII}/ParallelEvaluator.hpp"
        "${PARALLEL-NSGAII}/Population.hpp"
        "${PARALLEL-NSGAII}/ProblemDefinitions.hpp"
        "${PARALLEL-NSGAII}/Selection.hpp"
        "${PARALLEL-NSGAII}/Types.hpp"

        "${PARALLEL-NSGAII}/Checkpoints/MaxGenCheckpoint.hpp"
        "${PARALLEL-NSGAII}/Checkpoints/SavePopCheckpoint.hpp"
        "${PARALLEL-NSGAII}/Checkpoints/SerialiseCheckpoint.hpp"
        "${PARALLEL-NSGAII}/Checkpoints/PlotFronts.hpp"
        "${PARALLEL-NSGAII}/Checkpoints/colours.hpp"
        "${PARALLEL-NSGAII}/Checkpoints/ResetMutationXoverFlags.hpp"
         "${PARALLEL-NSGAII}/Checkpoints/MailCheckpoint.hpp"
         "${PARALLEL-NSGAII}/Checkpoints/SaveFirstFrontCheckpoint.hpp"

        "${PARALLEL-NSGAII}/Serialization/SerializeBoostPath.hpp"
        "${PARALLEL-NSGAII}/Serialization/SerializeRng.hpp"

        "${PARALLEL-NSGAII}/Metrics/hv.c"
        "${PARALLEL-NSGAII}/Metrics/hv.h"
        "${PARALLEL-NSGAII}/Metrics/Hypervolume.hpp"
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
#                 Parallel NSGA with Large case study                                                            #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Metro_calib_parallel_Src
        MainPar.cpp
        MetronamicaOF2.hpp
        Pathify.hpp

    )

add_executable(metrocalpar ${Metro_calib_parallel_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility} ${MCL_SOURCES})
target_link_libraries(metrocalpar ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metrocalpar ${VTK_LIBRARIES})
    else()
        target_link_libraries(metrocalpar vtkHybrid vtkWidgets)
    endif()
ENDIF()


##################################################################################################################
#                                                                                                                #
#                 Serial NSGA with Large case study                                                              #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Metro_calib_serial_Src
       MainSer.cpp
       MetronamicaOF2.hpp
       Pathify.hpp
    )



add_executable(metrocalser ${Metro_calib_serial_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility}  ${MCL_SOURCES})
target_link_libraries(metrocalser ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metrocalser ${VTK_LIBRARIES})
    else()
        target_link_libraries(metrocalser vtkHybrid vtkWidgets)
    endif()
ENDIF()



##################################################################################################################
#                                                                                                                #
#                 Test MetronamicaOF on one random DV string                                                     #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Metro_calib_test_Src
        TestMetroCalOF.cpp
        MetronamicaOF2.hpp
        Pathify.hpp
    )



add_executable(metrocaltest ${Metro_calib_test_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility}  ${MCL_SOURCES})
target_link_libraries(metrocaltest ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metrocaltest ${VTK_LIBRARIES})
    else()
        target_link_libraries(metrocaltest vtkHybrid vtkWidgets)
    endif()
ENDIF()


##################################################################################################################
#                                                                                                                #
#                 test Hypervolume Calculations wortking                                                         #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Hypervolume_test_Src
        HypervolumeCheck.cpp
        "${PARALLEL-NSGAII}/Metrics/hv.c"
        "${PARALLEL-NSGAII}/Metrics/hv.h"
        "${PARALLEL-NSGAII}/Metrics/Hypervolume.hpp"
    )



add_executable(testhypervol ${Hypervolume_test_Src})
target_link_libraries(testhypervol ${Boost_LIBRARIES} )


##################################################################################################################
#                                                                                                                #
#                 test MetronamicaOF on a complete population of solutions                                       #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Evaluation_test_Src
        EvaluationTester.cpp
        MetronamicaOF2.hpp
        Pathify.hpp
    )

add_executable(testevaluation ${Evaluation_test_Src} ${MCL_HEADERS} ${MCL_SOURCES} ${AHHZ_Raster_Utility} )
target_link_libraries(testevaluation ${Boost_LIBRARIES} ${GDAL_LIBRARY} ${PNGwriter_LIBRARIES})
IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(testevaluation ${VTK_LIBRARIES})
    else()
        target_link_libraries(testevaluation vtkHybrid vtkWidgets)
    endif()
ENDIF()


##################################################################################################################
#                                                                                                                #
#                 Read in a population, get the first front, and....                                             #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(GetFirstFront_Src
        GetFirstFront.cpp
        MetronamicaOF2.hpp
        Pathify.hpp
    )


add_executable(getfirstfront ${GetFirstFront_Src} ${MCL_HEADERS} ${MCL_SOURCES} ${AHHZ_Raster_Utility} )
target_link_libraries(getfirstfront ${Boost_LIBRARIES} ${GDAL_LIBRARY} ${PNGwriter_LIBRARIES})
IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(getfirstfront ${VTK_LIBRARIES})
    else()
        target_link_libraries(getfirstfront vtkHybrid vtkWidgets)
    endif()
ENDIF()


##################################################################################################################
#                                                                                                                #
#                 Parallel NSGA with Small case study                                                            #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Metro_calib_parallel_Small_Src
        MainPar_SmallCaseStudy.cpp
        MetronamicaOF2_SmallCaseStudy.hpp
        Pathify.hpp

    )

add_executable(metrocalpar_sm ${Metro_calib_parallel_Small_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES} ${AHHZ_Raster_Utility} )
target_link_libraries(metrocalpar_sm ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metrocalpar_sm ${VTK_LIBRARIES})
    else()
        target_link_libraries(metrocalpar_sm vtkHybrid vtkWidgets)
    endif()
ENDIF()


##################################################################################################################
#                                                                                                                #
#                 Serial NSGA with Small case study                                                              #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Metro_calib_serial_Small_Src
       MainSer_SmallCaseStudy.cpp
       MetronamicaOF2_SmallCaseStudy.hpp
       Pathify.hpp
    )



add_executable(metrocalser_sm ${Metro_calib_serial_Small_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES} ${AHHZ_Raster_Utility} )
target_link_libraries(metrocalser_sm ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metrocalser_sm ${VTK_LIBRARIES})
    else()
        target_link_libraries(metrocalser_sm vtkHybrid vtkWidgets)
    endif()
ENDIF()


##################################################################################################################
#                                                                                                                #
#                 test MetronamicaOF on a complete population of solutions, for SMALL case study                 #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Evaluation_test__Small_Src
        EvaluationTester_SmallCaseStudy.cpp
        MetronamicaOF2_SmallCaseStudy.hpp
        Pathify.hpp
    )

add_executable(testevaluation_sm ${Evaluation_test__Small_Src} ${MCL_HEADERS} ${MCL_SOURCES} ${AHHZ_Raster_Utility} )
target_link_libraries(testevaluation_sm ${Boost_LIBRARIES} ${GDAL_LIBRARY} ${PNGwriter_LIBRARIES})
IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(testevaluation_sm ${VTK_LIBRARIES})
    else()
        target_link_libraries(testevaluation_sm vtkHybrid vtkWidgets)
    endif()
ENDIF()


##################################################################################################################
#                                                                                                                #
#                 Read in a population, get the first front, and....                                             #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(GetFirstFront_Small_Src
        GetFirstFront_SmallCaseStudy.cpp
        MetronamicaOF2_SmallCaseStudy.hpp
        Pathify.hpp
    )


add_executable(getfirstfront_sm ${GetFirstFront_Small_Src} ${MCL_HEADERS} ${MCL_SOURCES} ${AHHZ_Raster_Utility} )
target_link_libraries(getfirstfront_sm ${Boost_LIBRARIES} ${GDAL_LIBRARY} ${PNGwriter_LIBRARIES})
IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(getfirstfront_sm ${VTK_LIBRARIES})
    else()
        target_link_libraries(getfirstfront_sm vtkHybrid vtkWidgets)
    endif()
ENDIF()
