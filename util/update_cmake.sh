#!/bin/sh

set -e -u

update_cmake \
	CMakeLists.txt \
	SGEROIDS_FILES \
	include \
	src/sgeroids
