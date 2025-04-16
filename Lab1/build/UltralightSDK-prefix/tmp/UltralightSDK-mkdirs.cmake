# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/SDK")
  file(MAKE_DIRECTORY "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/SDK")
endif()
file(MAKE_DIRECTORY
  "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/UltralightSDK-prefix/src/UltralightSDK-build"
  "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/UltralightSDK-prefix"
  "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/UltralightSDK-prefix/tmp"
  "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/UltralightSDK-prefix/src/UltralightSDK-stamp"
  "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/UltralightSDK-prefix/src"
  "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/UltralightSDK-prefix/src/UltralightSDK-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/UltralightSDK-prefix/src/UltralightSDK-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Administrator/Projects/C++/KHAI_Cpp_LabWorks_Ovs/Lab1/build/UltralightSDK-prefix/src/UltralightSDK-stamp${cfgdir}") # cfgdir has leading slash
endif()
