AC_INIT([FBP_optics], [0.1], [phyjpb@leeds.ac.uk], [FBP_optics], [http://mpi.leeds.ac.uk/])
AC_PREREQ([2.68])
AM_INIT_AUTOMAKE([1.11 -Wall no-define])
AC_CONFIG_HEADERS([config.h])

AM_PATH_GSL(1.13,[],AC_MSG_ERROR(could not find required version of GSL))

[CIMG_LIBS="-L/usr/X11R6/lib -lpthread -lX11"] 
[OPENMP_CFLAGS="-fopenmp"]
[OPENMP_LIBS="-fopenmp"]

AC_SUBST([CIMG_LIBS])
AC_SUBST([OPENMP_LIBS])
AC_SUBST([OPENMP_CFLAGS])

AC_PROG_CXX
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
