# name of the program (Minix service)

PROG=proj

.PATH: ${.CURDIR}/src
.PATH: ${.CURDIR}/src/devices/kbc
.PATH: ${.CURDIR}/src/devices/timer
.PATH: ${.CURDIR}/src/devices/video
.PATH: ${.CURDIR}/src/utils
.PATH: ${.CURDIR}/src/game

SRCS = proj.c kbc.c mouse.c timer.c video_gr.c utils.c cursor.c


# additional compilation flags

CPPFLAGS += -pedantic


# list of library dependencies (for Lab 2, only LCF library)

DPADD += ${LIBLCF}
LDADD += -llcf


# include LCOM's makefile that does all the "heavy lifting"

.include <minix.lcom.mk>
