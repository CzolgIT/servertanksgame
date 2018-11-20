#=============================================================================
# Copyright 2003-2009 Kitware, Inc.
#
# CMake - Cross Platform Makefile Generator
# Copyright 2000-2014 Kitware, Inc.
# Copyright 2000-2011 Insight Software Consortium
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# * Neither the names of Kitware, Inc., the Insight Software Consortium,
# nor the names of their contributors may be used to endorse or promote
# products derived from this software without specific prior written
# permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
# License text for the above reference.)

FIND_PATH(SDL2_NET_INCLUDE_DIR SDL_net.h
	HINTS
	${SDL2}
	$ENV{SDL2}
	$ENV{SDL2_NET}
	PATH_SUFFIXES include/SDL2 include SDL2
	i686-w64-mingw32/include/SDL2
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local/include/SDL2
	/usr/include/SDL2
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
)

# Lookup the 64 bit libs on x64
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(SDL2_NET_LIBRARY_TEMP
		NAMES SDL2_net
		HINTS
		${SDL2}
		$ENV{SDL2}
		$ENV{SDL2_NET}
		PATH_SUFFIXES lib64 lib
		lib/x64
		x86_64-w64-mingw32/lib
		PATHS
		/sw
		/opt/local
		/opt/csw
		/opt
	)
# On 32bit build find the 32bit libs
ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(SDL2_NET_LIBRARY_TEMP
		NAMES SDL2_net
		HINTS
		${SDL2}
		$ENV{SDL2}
		$ENV{SDL2_NET}
		PATH_SUFFIXES lib
		lib/x86
		i686-w64-mingw32/lib
		PATHS
		/sw
		/opt/local
		/opt/csw
		/opt
	)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)

SET(SDL2_NET_FOUND "NO")
	IF(SDL2_NET_LIBRARY_TEMP)
	# Set the final string here so the GUI reflects the final state.
	SET(SDL2_NET_LIBRARY ${SDL2_NET_LIBRARY_TEMP} CACHE STRING "Where the SDL2_net Library can be found")
	# Set the temp variable to INTERNAL so it is not seen in the CMake GUI
	SET(SDL2_NET_LIBRARY_TEMP "${SDL2_NET_LIBRARY_TEMP}" CACHE INTERNAL "")
	SET(SDL2_NET_FOUND "YES")
ENDIF(SDL2_NET_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_NET REQUIRED_VARS SDL2_NET_LIBRARY SDL2_NET_INCLUDE_DIR)

