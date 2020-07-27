#======================================================================
# GNU MAKE REQUIRED!
#
#		make clean
#		make
#======================================================================

UNAME := $(shell uname)
MACAPPEND=
AUTO_ARGUMENT=
ifeq ($(UNAME), Darwin)
	MACAPPEND=-mac
	CXX=clang++
	OS_VERSION := $(shell system_profiler SPSoftwareDataType | awk '/System Version/ { print $$4; } ')
else
	OS_VERSION := $(shell lsb_release -r  | cut -d: -f2)
	OS_VERSION := $(strip ${OS_VERSION})
	ifeq (${OS_VERSION}, 16.04)
		MACAPPEND=-16.04
		AUTO_ARGUMENT := -DUSE_AUTO_PTR
	endif
endif


SRCDIR := src
OBJDIR := obj${MACAPPEND}
DEPDIR := .d
TEST_SRC=tests

LIB_DIR=${SRCDIR}/faker

VPATH := ${SRCDIR}:${LIB_DIR}:${TEST_SRC}
CXXFLAGS := -Isrc -I/usr/local/include -I./src/includes -std=c++14 -g -Wno-unused-local-typedefs -Wno-deprecated-declarations ${AUTO_ARGUMENT}
LDFLAGS := -L./lib -lcppunit -lboost_filesystem -lstdc++

SRCS_NOSORT = $(shell find . -name "*.cpp" -print)
SRCS = $(sort ${SRCS_NOSORT})
SRCS_NODIR = $(notdir ${SRCS})

# $(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

LIB_NOSORT := $(wildcard ${LIB_DIR}/*.cpp)
LIB_SRC := $(sort ${LIB_NOSORT})
LIB_OBJ := $(patsubst ${LIB_DIR}/%.cpp,${OBJDIR}/%.o,${LIB_SRC})

LIBNAME=faker${MACAPPEND}
LIB=lib/libfaker${MACAPPEND}.a
LIB_ARGS= -cvrU
ifeq ($(UNAME), Darwin)
	LIB_ARGS= -cvr
endif

INSTALL_BASE=/usr/local

#======================================================================
# Top-level targets.
#======================================================================
.PHONY: all
all: directories ${LIB}

Makefile: ;

# Clean the contents of the subdirs.
.PHONY: clean
clean:
	rm -f ${DEPDIR}/* ${OBJDIR}/* ${LIB}

# Clean out the subdirs entirely.
.PHONY: reallyclean
reallyclean:
	rm -rf ${DEPDIR} ${OBJDIR}

.PHONY: echo
echo:
	@echo CXXFLAGS is ${CXXFLAGS}
	@echo LIB_OBJ is ${LIB_OBJ}
	@echo VPATH = ${VPATH}

#======================================================================
# Build the directories needed.
# You shouldn't need to invoke these directly.
#======================================================================
.PHONY: directories
directories: ${DEPDIR} ${OBJDIR} lib

${DEPDIR}:
	mkdir -p $@

${OBJDIR}:
	mkdir -p $@

lib:
	mkdir -p $@

#======================================================================
# How to make the .o files as. This is a little complicated but is
# derived from:
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
#======================================================================

${OBJDIR}/%.o : %.cpp
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

INCLUDELIST = $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS_NODIR))))
include ${INCLUDELIST}

#======================================================================
# Making the library.
#======================================================================
${LIB}: ${LIB_OBJ}
	ar ${LIB_ARGS} ${LIB} ${LIB_OBJ}
	ranlib ${LIB}

#======================================================================
# Documentation
#======================================================================
.PHONY: docs
docs:
	doxygen

#======================================================================
# Installation.
#======================================================================
.PHONY: install
install: ${LIB}
	mkdir -p ${INSTALL_BASE}/include/faker
	mkdir -p ${INSTALL_BASE}/faker
	mkdir -p ${INSTALL_BASE}/faker/docs
	mkdir -p ${INSTALL_BASE}/faker/locales
	cp ${LIB_DIR}/*.h ${LIB_DIR}/*.hpp ${INSTALL_BASE}/include/faker
	cp ${LIB} ${INSTALL_BASE}/lib/libfaker.a
	cp -R docs/html/ ${INSTALL_BASE}/faker/docs
	cp -R locales/ ${INSTALL_BASE}/faker

#======================================================================
# The unit tests.
#======================================================================
TEST_BIN=test-bin${MACAPPEND}
TEST_LIST= \
	${TEST_BIN}/TestCore \
	${TEST_BIN}/TestName \
	${TEST_BIN}/TestNumber \
	${TEST_BIN}/TestPhone

.PHONY: tests
tests: all ${TEST_BIN} ${TEST_LIST}

.PHONY: mock
mock: all ${TEST_BIN} ${TEST_MOCKS}

.PHONY: ${TEST_BIN}
${TEST_BIN}:
	mkdir -p ${TEST_BIN}

${TEST_BIN}/TestCore: ${OBJDIR}/TestCore.o ${OBJDIR}/main-test.o ${LIB}
	$(CXX) ${OBJDIR}/TestCore.o ${OBJDIR}/main-test.o -L. -l${LIBNAME} ${LDFLAGS_PROM} ${LDFLAGS} $(OUTPUT_OPTION)

${TEST_BIN}/TestName: ${OBJDIR}/TestName.o ${OBJDIR}/main-test.o ${LIB}
	$(CXX) ${OBJDIR}/TestName.o ${OBJDIR}/main-test.o -L. -l${LIBNAME} ${LDFLAGS_PROM} ${LDFLAGS} $(OUTPUT_OPTION)

${TEST_BIN}/TestNumber: ${OBJDIR}/TestNumber.o ${OBJDIR}/main-test.o ${LIB}
	$(CXX) ${OBJDIR}/TestNumber.o ${OBJDIR}/main-test.o -L. -l${LIBNAME} ${LDFLAGS_PROM} ${LDFLAGS} $(OUTPUT_OPTION)

${TEST_BIN}/TestPhone: ${OBJDIR}/TestPhone.o ${OBJDIR}/main-test.o ${LIB}
	$(CXX) ${OBJDIR}/TestPhone.o ${OBJDIR}/main-test.o -L. -l${LIBNAME} ${LDFLAGS_PROM} ${LDFLAGS} $(OUTPUT_OPTION)
