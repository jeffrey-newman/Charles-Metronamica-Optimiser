 
cmake_minimum_required(VERSION 3.0)
PROJECT(Charles-Metro-Cal)
set (CMAKE_CXX_STANDARD 11)
#Variable for location of parallel-nsgaII-backend

FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem system program_options mpi serialization timer chrono date_time)
find_package(GDAL)
find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})
include_directories("${CMAKE_SOURCE_DIR}/pugixml-1.7/src/")
find_package(ImageMagick COMPONENTS Magick++ MagickWand MagickCore)

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
set(RASTER2IMAGE "Not specified" CACHE PATH "Path to the Raster2Image code")

set(MAC_FRAMEWORK_PATHS "FALSE" CACHE BOOL "Whether to use header paths in include statements for mac gdal framework")

if(MAC_FRAMEWORK_PATHS)
    add_definitions(-DWITH_MAC_FRAMEWORK)
ENDIF()

# Find where Magick++-config lives
find_program(MAGICK_CONFIG "Magick++-config")
# Ask about CXX and lib flags/locations
execute_process(COMMAND "${MAGICK_CONFIG}" "--cxxflags" OUTPUT_VARIABLE MAGICK_CXX_FLAGS)
execute_process(COMMAND "${MAGICK_CONFIG}" "--libs" OUTPUT_VARIABLE MAGICK_LD_FLAGS)
#message(STATUS "${MAGICK_CXX_FLAGS}")
#message(STATUS "${MAGICK_LD_FLAGS}")
# Remove trailing whitespace (CMAKE warns about this)
string(STRIP "${MAGICK_CXX_FLAGS}" MAGICK_CXX_FLAGS)
string(STRIP "${MAGICK_LD_FLAGS}" MAGICK_LD_FLAGS)


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
include_directories(${ImageMagick_Magick++_INCLUDE_DIR})
include_directories(${RASTER2IMAGE})

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


SET(MagickLibs
        ${ImageMagick_Magick++_LIBRARY}
        ${ImageMagick_MagickWand_LIBRARY}
        ${ImageMagick_MagickCore_LIBRARY}
        )

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
        "${PARALLEL-NSGAII}/Checkpoints/SignalCheckpoint.hpp"
        "${PARALLEL-NSGAII}/Checkpoints/SignalHandler.cpp"
        "${PARALLEL-NSGAII}/Checkpoints/SignalHandler.hpp"

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
#                 Test MetronamicaOF on one random DV string  Large Case Study   3 Obj                           #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Test_Metro_OF_Large_Src
        TestMetroOFLarge.cpp
        MetronamicaCalibrationObjectiveFunction.h
        Pathify.hpp
        )



add_executable(metro_lrgR_test ${Test_Metro_OF_Large_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility}  ${MCL_SOURCES}  ${PUGIXML-SRC})
target_link_libraries(metro_lrgR_test ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_lrgR_test ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_lrgR_test vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_lrgR_test PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")

##################################################################################################################
#                                                                                                                #
#                 Test MetronamicaOF on one random DV string  Small Case Study   3 Obj                           #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Test_Metro_OF_Small_Src
        TestMetroOFSmall.cpp
        MetronamicaCalibrationObjectiveFunction.h
        Pathify.hpp
        )



add_executable(metro_smR_test ${Test_Metro_OF_Small_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility}  ${MCL_SOURCES}  ${PUGIXML-SRC})
target_link_libraries(metro_smR_test ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_smR_test ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_smR_test vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_smR_test PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")

##################################################################################################################
#                                                                                                                #
#                 Parallel NSGA with Large case study    2 Obj                                                   #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Metro_calib_parallel_Lrg_2Obj_Src
        MainPar_LargCaseStudy_2Obj.cpp
        MetronamicaCalibrationObjectiveFunction.h
        Pathify.hpp
        GeoprojectManipBigCaseStudy.h
    )

add_executable(metro_cal_par_lrgR_2obj ${Metro_calib_parallel_Lrg_2Obj_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility} ${MCL_SOURCES}  ${PUGIXML-SRC})
target_link_libraries(metro_cal_par_lrgR_2obj ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_cal_par_lrgR_2obj ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_cal_par_lrgR_2obj vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_cal_par_lrgR_2obj PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")

##################################################################################################################
#                                                                                                                #
#                 Serial NSGA with Large case study   2 Obj                                                           #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Metro_calib_serial_Lrg_2Obj_Src
       MainSer_LargeCaseStudy_2Obj.cpp
        MetronamicaCalibrationObjectiveFunction.h
       Pathify.hpp
        GeoprojectManipBigCaseStudy.h
    )



add_executable(metro_cal_ser_lrgR_2obj ${Metro_calib_serial_Lrg_2Obj_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility}  ${MCL_SOURCES}  ${PUGIXML-SRC})
target_link_libraries(metro_cal_ser_lrgR_2obj ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_cal_ser_lrgR_2obj ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_cal_ser_lrgR_2obj vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_cal_ser_lrgR_2obj PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")





##################################################################################################################
#                                                                                                                #
#                 Parallel NSGA with Small case study     2 Obj                                                  #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Metro_calib_parallel_Small_2Obj_Src
        MainPar_SmallCaseStudy_2Obj.cpp
        MetronamicaCalibrationObjectiveFunction.h
        Pathify.hpp
        GeoprojectManipSmallCaseStudy.h)

add_executable(metro_cal_par_smR_2obj ${Metro_calib_parallel_Small_2Obj_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES} ${AHHZ_Raster_Utility}  ${PUGIXML-SRC})
target_link_libraries(metro_cal_par_smR_2obj ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_cal_par_smR_2obj ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_cal_par_smR_2obj vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_cal_par_smR_2obj PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")

##################################################################################################################
#                                                                                                                #
#                 Serial NSGA with Small case study         2 Obj                                                #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Metro_calib_serial_Small_2obj_Src
       MainSer_SmallCaseStudy_2Obj.cpp
        MetronamicaCalibrationObjectiveFunction.h
       Pathify.hpp
        GeoprojectManipSmallCaseStudy.h)



add_executable(metro_cal_ser_smR_2obj ${Metro_calib_serial_Small_2obj_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES} ${AHHZ_Raster_Utility}  ${PUGIXML-SRC})
target_link_libraries(metro_cal_ser_smR_2obj ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_cal_ser_smR_2obj ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_cal_ser_smR_2obj vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_cal_ser_smR_2obj PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")

##################################################################################################################
#                                                                                                                #
#                 Parallel NSGA with Large case study    3 Obj                                                   #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Metro_calib_parallel_Lrg_3obj_Src
        MainPar_LargeCaseStudy_3Obj.cpp
        MetronamicaCalibrationObjectiveFunction.h
        Pathify.hpp
        GeoprojectManipBigCaseStudy.h
        )

add_executable(metro_cal_par_lrgR_3obj ${Metro_calib_parallel_Lrg_3obj_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility} ${MCL_SOURCES}  ${PUGIXML-SRC})
target_link_libraries(metro_cal_par_lrgR_3obj ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_cal_par_lrgR_3obj ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_cal_par_lrgR_3obj vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_cal_par_lrgR_3obj PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")

##################################################################################################################
#                                                                                                                #
#                 Serial NSGA with Large case study   3 Obj                                                      #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Metro_calib_serial_Lrg_3obj_Src
        MainSer_LargeCaseStudy_3Obj.cpp
        MetronamicaCalibrationObjectiveFunction.h
        Pathify.hpp
        GeoprojectManipBigCaseStudy.h
        )



add_executable(metro_cal_ser_lrgR_3obj ${Metro_calib_serial_Lrg_3obj_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${AHHZ_Raster_Utility}  ${MCL_SOURCES}  ${PUGIXML-SRC})
target_link_libraries(metro_cal_ser_lrgR_3obj ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_cal_ser_lrgR_3obj ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_cal_ser_lrgR_3obj vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_cal_ser_lrgR_3obj PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")





##################################################################################################################
#                                                                                                                #
#                 Parallel NSGA with Small case study     3 Obj                                                  #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################

SET(Metro_calib_parallel_Small_3obj_Src
        MainPar_SmallCaseStudy_3Obj.cpp
        MetronamicaCalibrationObjectiveFunction.h
        Pathify.hpp

        GeoprojectManipSmallCaseStudy.h)

add_executable(metro_cal_par_smR_3obj ${Metro_calib_parallel_Small_3obj_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES} ${AHHZ_Raster_Utility}  ${PUGIXML-SRC})
target_link_libraries(metro_cal_par_smR_3obj ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_cal_par_smR_3obj ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_cal_par_smR_3obj vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_cal_par_smR_3obj PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")

##################################################################################################################
#                                                                                                                #
#                 Serial NSGA with Small case study         3 Obj                                                #
#                                                                                                                #
#                                                                                                                #
##################################################################################################################


SET(Metro_calib_serial_Small__3obbj_Src
        MainSer_SmallCaseStudy_3Obj.cpp
        MetronamicaCalibrationObjectiveFunction.h
        Pathify.hpp
        GeoprojectManipSmallCaseStudy.h)



add_executable(metro_cal_ser_smR_3obj ${Metro_calib_serial_Small__3obbj_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES} ${AHHZ_Raster_Utility}  ${PUGIXML-SRC})
target_link_libraries(metro_cal_ser_smR_3obj ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES} ${MagickLibs})

IF(USE_VTK)
    if(VTK_LIBRARIES)
        target_link_libraries(metro_cal_ser_smR_3obj ${VTK_LIBRARIES})
    else()
        target_link_libraries(metro_cal_ser_smR_3obj vtkHybrid vtkWidgets)
    endif()
ENDIF()
target_compile_definitions(metro_cal_ser_smR_3obj PUBLIC "-DMAGICKCORE_QUANTUM_DEPTH=16" PUBLIC "-DMAGICKCORE_HDRI_ENABLE=0")

#
###################################################################################################################
##                                                                                                                #
##                 test MetronamicaOF on a complete population of solutions, for SMALL case study                 #
##                                                                                                                #
##                                                                                                                #
###################################################################################################################
#
#SET(Evaluation_test__Small_Src
#        EvaluationTester_SmallCaseStudy.cpp
#        MetronamicaOF2_RandstadSmallCaseStudy_2Obj.hpp
#        Pathify.hpp
#        GeoprojectManipSmallCaseStudy.h)
#
#add_executable(testevaluation_sm ${Evaluation_test__Small_Src} ${MCL_HEADERS} ${MCL_SOURCES} ${AHHZ_Raster_Utility}  ${PUGIXML-SRC})
#target_link_libraries(testevaluation_sm ${Boost_LIBRARIES} ${GDAL_LIBRARY} ${PNGwriter_LIBRARIES})
#IF(USE_VTK)
#    if(VTK_LIBRARIES)
#        target_link_libraries(testevaluation_sm ${VTK_LIBRARIES})
#    else()
#        target_link_libraries(testevaluation_sm vtkHybrid vtkWidgets)
#    endif()
#ENDIF()
#
#
###################################################################################################################
##                                                                                                                #
##                 Read in a population, get the first front, and....                                             #
##                                                                                                                #
##                                                                                                                #
###################################################################################################################
#
#
#SET(GetFirstFront_Small_Src
#        GetFirstFront_SmallCaseStudy.cpp
#        MetronamicaOF2_RandstadSmallCaseStudy_2Obj.hpp
#        Pathify.hpp
#        GeoprojectManipSmallCaseStudy.h)
#
#
#add_executable(getfirstfront_sm ${GetFirstFront_Small_Src} ${MCL_HEADERS} ${MCL_SOURCES} ${AHHZ_Raster_Utility}  ${PUGIXML-SRC})
#target_link_libraries(getfirstfront_sm ${Boost_LIBRARIES} ${GDAL_LIBRARY} ${PNGwriter_LIBRARIES})
#IF(USE_VTK)
#    if(VTK_LIBRARIES)
#        target_link_libraries(getfirstfront_sm ${VTK_LIBRARIES})
#    else()
#        target_link_libraries(getfirstfront_sm vtkHybrid vtkWidgets)
#    endif()
#ENDIF()
#
###################################################################################################################
##                                                                                                                #
##                 Parallel NSGA with Small case study    with both obj to minimise (negative FKS)                #
##                                                                                                                #
##                                                                                                                #
###################################################################################################################
#
#SET(Metro_calib_parallel_Small_2min_Src
#        MainPar_SmallCase_BothMin.cpp
#        MetroOF2_SmallCase_BothMin.hpp
#        Pathify.hpp
#
#        GeoprojectManipSmallCaseStudy.h)
#
#add_executable(metrocalpar_sm_2min ${Metro_calib_parallel_Small_2min_Src} ${prll-nsga-src} ${MCL_HEADERS} ${AHHZ_Raster} ${MCL_SOURCES} ${AHHZ_Raster_Utility}  ${PUGIXML-SRC})
#target_link_libraries(metrocalpar_sm_2min ${GDAL_LIBRARY} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PNGwriter_LIBRARIES})
#
#IF(USE_VTK)
#    if(VTK_LIBRARIES)
#        target_link_libraries(metrocalpar_sm_2min ${VTK_LIBRARIES})
#    else()
#        target_link_libraries(metrocalpar_sm_2min vtkHybrid vtkWidgets)
#    endif()
#ENDIF()
#
#
#
#

#
#
###################################################################################################################
##                                                                                                                #
##                 test Hypervolume Calculations wortking                                                         #
##                                                                                                                #
##                                                                                                                #
###################################################################################################################
#
#
#SET(Hypervolume_test_Src
#        HypervolumeCheck.cpp
#        "${PARALLEL-NSGAII}/Metrics/hv.c"
#        "${PARALLEL-NSGAII}/Metrics/hv.h"
#        "${PARALLEL-NSGAII}/Metrics/Hypervolume.hpp"
#        )
#
#
#
#add_executable(testhypervol ${Hypervolume_test_Src})
#target_link_libraries(testhypervol ${Boost_LIBRARIES} )
#
#
###################################################################################################################
##                                                                                                                #
##                 test MetronamicaOF on a complete population of solutions                                       #
##                                                                                                                #
##                                                                                                                #
###################################################################################################################
#
#SET(Evaluation_test_Src
#        EvaluationTester.cpp
#        MetronamicaOF2.hpp
#        Pathify.hpp
#        )
#
#add_executable(testevaluation ${Evaluation_test_Src} ${MCL_HEADERS} ${MCL_SOURCES} ${AHHZ_Raster_Utility}   ${PUGIXML-SRC})
#target_link_libraries(testevaluation ${Boost_LIBRARIES} ${GDAL_LIBRARY} ${PNGwriter_LIBRARIES})
#IF(USE_VTK)
#    if(VTK_LIBRARIES)
#        target_link_libraries(testevaluation ${VTK_LIBRARIES})
#    else()
#        target_link_libraries(testevaluation vtkHybrid vtkWidgets)
#    endif()
#ENDIF()
#
#
###################################################################################################################
##                                                                                                                #
##                 Read in a population, get the first front, and....                                             #
##                                                                                                                #
##                                                                                                                #
###################################################################################################################
#
#
#SET(GetFirstFront_Src
#        GetFirstFront.cpp
#        MetronamicaOF2.hpp
#        Pathify.hpp
#        )
#
#
#add_executable(getfirstfront ${GetFirstFront_Src} ${MCL_HEADERS} ${MCL_SOURCES} ${AHHZ_Raster_Utility}  ${PUGIXML-SRC})
#target_link_libraries(getfirstfront ${Boost_LIBRARIES} ${GDAL_LIBRARY} ${PNGwriter_LIBRARIES})
#IF(USE_VTK)
#    if(VTK_LIBRARIES)
#        target_link_libraries(getfirstfront ${VTK_LIBRARIES})
#    else()
#        target_link_libraries(getfirstfront vtkHybrid vtkWidgets)
#    endif()
#ENDIF()
