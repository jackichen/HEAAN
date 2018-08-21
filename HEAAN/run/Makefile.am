bin_PROGRAMS = HEAAN
HEAAN_CXXFLAGS = -fPIC -std=c++11
HEAAN_CPPFLAGS = -I${top_srcdir}/HEAAN/src
HEAAN_LDFLAGS = -pthread
HEAAN_SOURCES = run.cpp ${top_srcdir}/HEAAN/src/TestScheme.cpp ${top_srcdir}/HEAAN/src/TestScheme.h
HEAAN_LDADD = ${top_srcdir}/HEAAN/src/libHEAAN.la -lntl -lgmp
