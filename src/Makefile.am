AUTOMAKE_OPTIONS = foreign

SUBDIRS = traderflow

bin_PROGRAMS = utah
utah_SOURCES = \
	Config.cc \
	Server.cc \
	Main.cc 


utah_CPPFLAGS = -I$(top_srcdir) \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(UFO_CPPFLAGS) \
		$(AIR_CPPFLAGS)


utah_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(UFO_LIBADD) \
	$(AIR_LIBADD)


utah_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = Config.hh \
		Log.hh \
		Server.hh


EXTRA_DIST = env.sh utah.cfg log.cfg

utahdir = $(bindir)
utah_DATA = $(EXTRA_DIST)
