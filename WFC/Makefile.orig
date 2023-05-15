# =========================================================================
# Lance Moczygemba
# May 4, 2023
# LASA CS
# =========================================================================

prefix = /usr/local
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
INSTALL = /usr/bin/install -c
EXEEXT = 
WINDRES = 
NM = nm
srcdir = .
top_srcdir = ../../..
LIBS = -lz -framework Security -lpthread -liconv
LDFLAGS_GUI = 
CXX = g++ -std=gnu++11 -mmacosx-version-min=10.10
CXXFLAGS = 
CPPFLAGS = 
LDFLAGS = 
USE_DPI_AWARE_MANIFEST = 2
WX_LIB_FLAVOUR = 
TOOLKIT = OSX_COCOA
TOOLKIT_LOWERCASE = osx_cocoa
TOOLKIT_VERSION = 
TOOLCHAIN_FULLNAME = osx_cocoa-unicode-3.2
EXTRALIBS =   -framework IOKit -framework Carbon -framework Cocoa -framework QuartzCore -framework AudioToolbox -framework System -framework OpenGL  -lz -framework Security -lpthread -liconv  
EXTRALIBS_XML =  -lexpat
EXTRALIBS_GUI = -framework WebKit
WX_CPPFLAGS = -I${wx_top_builddir}/lib/wx/include/osx_cocoa-unicode-3.2 -I${top_srcdir}/include -D_FILE_OFFSET_BITS=64 
WX_CXXFLAGS = -Wall -Wundef -Wunused-parameter -Wno-ctor-dtor-privacy -Woverloaded-virtual -Wno-deprecated-declarations -g -O0 -fno-common  -fvisibility=hidden -fvisibility-inlines-hidden
WX_LDFLAGS =  -framework IOKit -framework Carbon -framework Cocoa -framework QuartzCore -framework AudioToolbox -framework System -framework OpenGL 
HOST_SUFFIX = 
SAMPLES_RPATH_FLAG = 
SAMPLES_CXXFLAGS =  -dynamic -fPIC -DPIC
wx_top_builddir = ../..

DESTDIR = 
WX_RELEASE = 3.2
WX_VERSION = $(WX_RELEASE).2
LIBDIRNAME = $(wx_top_builddir)/lib
IMAGE_CXXFLAGS = $(WX_CPPFLAGS) -D__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p) \
	$(__DEBUG_DEFINE_p) $(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) \
	$(__THREAD_DEFINE_p) -I$(srcdir) $(__DLLFLAG_p) -I$(srcdir)/../../samples \
	$(WX_CXXFLAGS) $(SAMPLES_CXXFLAGS) $(CPPFLAGS) $(CXXFLAGS)
IMAGE_OBJECTS =  \
	ImageExpansionDialog.o \
	WFC_WFC.o \
	$(__WFC___win32rc)

CXXC = $(CXX)
PORTNAME = $(TOOLKIT_LOWERCASE)$(TOOLKIT_VERSION)
WXUNICODEFLAG = u
EXTRALIBS_FOR_BASE = $(EXTRALIBS)
EXTRALIBS_FOR_GUI = $(EXTRALIBS_GUI)
__DLLFLAG_p = -DWXUSINGDLL
__DLLFLAG_p_1 = --define WXUSINGDLL
COND_PLATFORM_OS2_1___WFC___os2_emxbindcmd = $(NM) WFC$(EXEEXT) | if grep -q \
	pmwin.763 ; then emxbind -ep WFC$(EXEEXT) ; fi
__WFC_app_Contents_PkgInfo___depname \
	= WFC.app/Contents/PkgInfo
__WFC_bundle___depname = WFC_bundle
____WFC_BUNDLE_TGT_REF_DEP \
	= $(__WFC_app_Contents_PkgInfo___depname)
COND_MONOLITHIC_0___WXLIB_CORE_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_CORE_p = $(COND_MONOLITHIC_0___WXLIB_CORE_p)
COND_MONOLITHIC_0___WXLIB_BASE_p = \
	-lwx_base$(WXBASEPORT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_BASE_p = $(COND_MONOLITHIC_0___WXLIB_BASE_p)
COND_MONOLITHIC_1___WXLIB_MONO_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__LIB_TIFF_p \
	= \
	-lwxtiff$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__LIB_JPEG_p \
	= \
	-lwxjpeg$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__LIB_PNG_p \
	= \
	-lwxpng$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
COND_wxUSE_REGEX_builtin___LIB_REGEX_p = \
	-lwxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__LIB_REGEX_p = $(COND_wxUSE_REGEX_builtin___LIB_REGEX_p)

### Targets: ###
all: WFC$(EXEEXT) $(__WFC_bundle___depname) data
	./WFC$(EXEEXT)

run: WFC$(EXEEXT)
	./WFC$(EXEEXT)

install: 

uninstall: 

install-strip: install

clean: 
	rm -rf ./.deps ./.pch
	rm -f ./*.o
	rm -f WFC$(EXEEXT)
	rm -rf WFC.app

WFC$(EXEEXT): $(IMAGE_OBJECTS) $(__WFC___win32rc)
	$(CXX) -o $@ $(IMAGE_OBJECTS)    -L$(LIBDIRNAME)  $(LDFLAGS_GUI) $(SAMPLES_RPATH_FLAG) $(LDFLAGS)  $(WX_LDFLAGS) $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_SCINTILLA_IF_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p)  $(EXTRALIBS_FOR_GUI) $(__LIB_ZLIB_p) $(__LIB_REGEX_p) $(__LIB_EXPAT_p) $(EXTRALIBS_FOR_BASE) $(LIBS)
	$(__WFC___os2_emxbindcmd)

WFC.app/Contents/PkgInfo: WFC$(EXEEXT) $(top_srcdir)/src/osx/carbon/Info.plist.in $(top_srcdir)/src/osx/carbon/wxmac.icns 
	mkdir -p WFC.app/Contents
	mkdir -p WFC.app/Contents/MacOS
	mkdir -p WFC.app/Contents/Resources
	
	
	sed -e "s/\$${MACOSX_BUNDLE_GUI_IDENTIFIER}/org.wxwidgets.WFC/" \
	-e "s/\$${MACOSX_BUNDLE_EXECUTABLE_NAME}/WFC/" \
	-e "s/\$${MACOSX_BUNDLE_BUNDLE_NAME}/WFC/" \
	-e "s/\$${MACOSX_BUNDLE_COPYRIGHT}/Copyright 2002-2023 wxWidgets/" \
	-e "s/\$${MACOSX_BUNDLE_BUNDLE_VERSION}/$(WX_VERSION)/" \
	-e "s/\$${MACOSX_BUNDLE_INFO_STRING}/WFC version $(WX_VERSION), (c) 2002-2023 wxWidgets/" \
	-e "s/\$${MACOSX_BUNDLE_LONG_VERSION_STRING}/$(WX_VERSION), (c) 2002-2023 wxWidgets/" \
	-e "s/\$${MACOSX_BUNDLE_SHORT_VERSION_STRING}/$(WX_RELEASE)/" \
	$(top_srcdir)/src/osx/carbon/Info.plist.in >WFC.app/Contents/Info.plist
	
	
	/bin/echo "APPL????" >WFC.app/Contents/PkgInfo
	
	
	ln -f WFC$(EXEEXT) WFC.app/Contents/MacOS/WFC
	
	
	cp -f $(top_srcdir)/src/osx/carbon/wxmac.icns WFC.app/Contents/Resources/wxmac.icns

WFC_bundle: $(____WFC_BUNDLE_TGT_REF_DEP)

data: 

ImageExpansionDialog.o: $(srcdir)/ImageExpansionDialog.cpp
	$(CXXC) -c -o $@ $(IMAGE_CXXFLAGS) $(srcdir)/ImageExpansionDialog.cpp
	echo $(CXXC)" -c -o "$@" "$(IMAGE_CXXFLAGS)" "$(srcdir)/ImageExpansionDialog.cpp

WFC_WFC.o: $(srcdir)/WFC.cpp
	$(CXXC) -c -o $@ $(IMAGE_CXXFLAGS) $(srcdir)/WFC.cpp
	echo $(CXXC)" -c -o "$@" "$(IMAGE_CXXFLAGS)" "$(srcdir)/WFC.cpp

WFC_WFC_rc.o: $(srcdir)/WFC.rc
	$(WINDRES) -i$< -o$@    --define __WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p_1) $(__DEBUG_DEFINE_p_1)  $(__EXCEPTIONS_DEFINE_p_1) $(__RTTI_DEFINE_p_1) $(__THREAD_DEFINE_p_1)  --include-dir $(srcdir) $(__DLLFLAG_p_1) $(__WIN32_DPI_MANIFEST_p) --include-dir $(srcdir)/../../samples $(__RCDEFDIR_p) --include-dir $(top_srcdir)/include


