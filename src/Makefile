#
# OMNeT++/OMNEST Makefile for uav
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = uav$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Iinet \
    -Iinet/applications \
    -Iinet/applications/contract \
    -Iinet/applications/ethernet \
    -Iinet/common \
    -Iinet/common/figures \
    -Iinet/common/geometry \
    -Iinet/common/geometry/base \
    -Iinet/common/geometry/common \
    -Iinet/common/geometry/object \
    -Iinet/common/queue \
    -Iinet/environment \
    -Iinet/environment/common \
    -Iinet/environment/contract \
    -Iinet/linklayer \
    -Iinet/linklayer/base \
    -Iinet/linklayer/contract \
    -Iinet/linklayer/dara \
    -Iinet/linklayer/irsa \
    -Iinet/linklayer/ld \
    -Iinet/linklayer/tdma \
    -Iinet/mobility \
    -Iinet/mobility/base \
    -Iinet/mobility/contract \
    -Iinet/mobility/single \
    -Iinet/mobility/static \
    -Iinet/node \
    -Iinet/physicallayer \
    -Iinet/physicallayer/contract \
    -Iinet/physicallayer/idealradio

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/inet/applications/ethernet/TrafGen.o \
    $O/inet/common/Compat.o \
    $O/inet/common/ModuleAccess.o \
    $O/inet/common/figures/TrailFigure.o \
    $O/inet/common/geometry/base/GeometricObjectBase.o \
    $O/inet/common/geometry/base/ShapeBase.o \
    $O/inet/common/geometry/common/Coord.o \
    $O/inet/common/geometry/common/EulerAngles.o \
    $O/inet/common/geometry/common/Rotation.o \
    $O/inet/common/geometry/object/LineSegment.o \
    $O/inet/common/queue/DropTailQueue.o \
    $O/inet/common/queue/PassiveQueueBase.o \
    $O/inet/common/queue/Sink.o \
    $O/inet/environment/common/Material.o \
    $O/inet/linklayer/base/ApMacBase.o \
    $O/inet/linklayer/base/HostMacBase.o \
    $O/inet/linklayer/dara/DaraMac.o \
    $O/inet/linklayer/ld/LdMac.o \
    $O/inet/linklayer/tdma/TdmaApMac.o \
    $O/inet/linklayer/tdma/TdmaHostMac.o \
    $O/inet/mobility/base/MobilityBase.o \
    $O/inet/mobility/base/MovingMobilityBase.o \
    $O/inet/mobility/contract/IMobility.o \
    $O/inet/mobility/single/ThreeWayRandomMobility.o \
    $O/inet/mobility/static/StationaryMobility.o \
    $O/inet/physicallayer/idealradio/IdealRadio.o \
    $O/inet/linklayer/dara/DaraReq_m.o \
    $O/inet/linklayer/tdma/TdmaAck_m.o \
    $O/inet/linklayer/tdma/TdmaReq_m.o

# Message files
MSGFILES = \
    inet/linklayer/dara/DaraReq.msg \
    inet/linklayer/tdma/TdmaAck.msg \
    inet/linklayer/tdma/TdmaReq.msg

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f uav uav.exe libuav.so libuav.a libuav.dll libuav.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h
	$(Q)-rm -f inet/*_m.cc inet/*_m.h inet/*_sm.cc inet/*_sm.h
	$(Q)-rm -f inet/applications/*_m.cc inet/applications/*_m.h inet/applications/*_sm.cc inet/applications/*_sm.h
	$(Q)-rm -f inet/applications/contract/*_m.cc inet/applications/contract/*_m.h inet/applications/contract/*_sm.cc inet/applications/contract/*_sm.h
	$(Q)-rm -f inet/applications/ethernet/*_m.cc inet/applications/ethernet/*_m.h inet/applications/ethernet/*_sm.cc inet/applications/ethernet/*_sm.h
	$(Q)-rm -f inet/common/*_m.cc inet/common/*_m.h inet/common/*_sm.cc inet/common/*_sm.h
	$(Q)-rm -f inet/common/figures/*_m.cc inet/common/figures/*_m.h inet/common/figures/*_sm.cc inet/common/figures/*_sm.h
	$(Q)-rm -f inet/common/geometry/*_m.cc inet/common/geometry/*_m.h inet/common/geometry/*_sm.cc inet/common/geometry/*_sm.h
	$(Q)-rm -f inet/common/geometry/base/*_m.cc inet/common/geometry/base/*_m.h inet/common/geometry/base/*_sm.cc inet/common/geometry/base/*_sm.h
	$(Q)-rm -f inet/common/geometry/common/*_m.cc inet/common/geometry/common/*_m.h inet/common/geometry/common/*_sm.cc inet/common/geometry/common/*_sm.h
	$(Q)-rm -f inet/common/geometry/object/*_m.cc inet/common/geometry/object/*_m.h inet/common/geometry/object/*_sm.cc inet/common/geometry/object/*_sm.h
	$(Q)-rm -f inet/common/queue/*_m.cc inet/common/queue/*_m.h inet/common/queue/*_sm.cc inet/common/queue/*_sm.h
	$(Q)-rm -f inet/environment/*_m.cc inet/environment/*_m.h inet/environment/*_sm.cc inet/environment/*_sm.h
	$(Q)-rm -f inet/environment/common/*_m.cc inet/environment/common/*_m.h inet/environment/common/*_sm.cc inet/environment/common/*_sm.h
	$(Q)-rm -f inet/environment/contract/*_m.cc inet/environment/contract/*_m.h inet/environment/contract/*_sm.cc inet/environment/contract/*_sm.h
	$(Q)-rm -f inet/linklayer/*_m.cc inet/linklayer/*_m.h inet/linklayer/*_sm.cc inet/linklayer/*_sm.h
	$(Q)-rm -f inet/linklayer/base/*_m.cc inet/linklayer/base/*_m.h inet/linklayer/base/*_sm.cc inet/linklayer/base/*_sm.h
	$(Q)-rm -f inet/linklayer/contract/*_m.cc inet/linklayer/contract/*_m.h inet/linklayer/contract/*_sm.cc inet/linklayer/contract/*_sm.h
	$(Q)-rm -f inet/linklayer/dara/*_m.cc inet/linklayer/dara/*_m.h inet/linklayer/dara/*_sm.cc inet/linklayer/dara/*_sm.h
	$(Q)-rm -f inet/linklayer/irsa/*_m.cc inet/linklayer/irsa/*_m.h inet/linklayer/irsa/*_sm.cc inet/linklayer/irsa/*_sm.h
	$(Q)-rm -f inet/linklayer/ld/*_m.cc inet/linklayer/ld/*_m.h inet/linklayer/ld/*_sm.cc inet/linklayer/ld/*_sm.h
	$(Q)-rm -f inet/linklayer/tdma/*_m.cc inet/linklayer/tdma/*_m.h inet/linklayer/tdma/*_sm.cc inet/linklayer/tdma/*_sm.h
	$(Q)-rm -f inet/mobility/*_m.cc inet/mobility/*_m.h inet/mobility/*_sm.cc inet/mobility/*_sm.h
	$(Q)-rm -f inet/mobility/base/*_m.cc inet/mobility/base/*_m.h inet/mobility/base/*_sm.cc inet/mobility/base/*_sm.h
	$(Q)-rm -f inet/mobility/contract/*_m.cc inet/mobility/contract/*_m.h inet/mobility/contract/*_sm.cc inet/mobility/contract/*_sm.h
	$(Q)-rm -f inet/mobility/single/*_m.cc inet/mobility/single/*_m.h inet/mobility/single/*_sm.cc inet/mobility/single/*_sm.h
	$(Q)-rm -f inet/mobility/static/*_m.cc inet/mobility/static/*_m.h inet/mobility/static/*_sm.cc inet/mobility/static/*_sm.h
	$(Q)-rm -f inet/node/*_m.cc inet/node/*_m.h inet/node/*_sm.cc inet/node/*_sm.h
	$(Q)-rm -f inet/physicallayer/*_m.cc inet/physicallayer/*_m.h inet/physicallayer/*_sm.cc inet/physicallayer/*_sm.h
	$(Q)-rm -f inet/physicallayer/contract/*_m.cc inet/physicallayer/contract/*_m.h inet/physicallayer/contract/*_sm.cc inet/physicallayer/contract/*_sm.h
	$(Q)-rm -f inet/physicallayer/idealradio/*_m.cc inet/physicallayer/idealradio/*_m.h inet/physicallayer/idealradio/*_sm.cc inet/physicallayer/idealradio/*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc inet/*.cc inet/applications/*.cc inet/applications/contract/*.cc inet/applications/ethernet/*.cc inet/common/*.cc inet/common/figures/*.cc inet/common/geometry/*.cc inet/common/geometry/base/*.cc inet/common/geometry/common/*.cc inet/common/geometry/object/*.cc inet/common/queue/*.cc inet/environment/*.cc inet/environment/common/*.cc inet/environment/contract/*.cc inet/linklayer/*.cc inet/linklayer/base/*.cc inet/linklayer/contract/*.cc inet/linklayer/dara/*.cc inet/linklayer/irsa/*.cc inet/linklayer/ld/*.cc inet/linklayer/tdma/*.cc inet/mobility/*.cc inet/mobility/base/*.cc inet/mobility/contract/*.cc inet/mobility/single/*.cc inet/mobility/static/*.cc inet/node/*.cc inet/physicallayer/*.cc inet/physicallayer/contract/*.cc inet/physicallayer/idealradio/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/inet/applications/ethernet/TrafGen.o: inet/applications/ethernet/TrafGen.cc \
	inet/applications/ethernet/TrafGen.h \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/InitStages.h
$O/inet/common/Compat.o: inet/common/Compat.cc \
	inet/common/Compat.h
$O/inet/common/ModuleAccess.o: inet/common/ModuleAccess.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h
$O/inet/common/figures/TrailFigure.o: inet/common/figures/TrailFigure.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/InitStages.h \
	inet/common/figures/TrailFigure.h
$O/inet/common/geometry/base/GeometricObjectBase.o: inet/common/geometry/base/GeometricObjectBase.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/InitStages.h \
	inet/common/geometry/base/GeometricObjectBase.h
$O/inet/common/geometry/base/ShapeBase.o: inet/common/geometry/base/ShapeBase.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/geometry/base/GeometricObjectBase.h \
	inet/common/geometry/base/ShapeBase.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/object/LineSegment.h
$O/inet/common/geometry/common/Coord.o: inet/common/geometry/common/Coord.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/geometry/common/Coord.h
$O/inet/common/geometry/common/EulerAngles.o: inet/common/geometry/common/EulerAngles.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/geometry/common/EulerAngles.h
$O/inet/common/geometry/common/Rotation.o: inet/common/geometry/common/Rotation.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/common/geometry/common/Rotation.h
$O/inet/common/geometry/object/LineSegment.o: inet/common/geometry/object/LineSegment.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/geometry/base/GeometricObjectBase.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/object/LineSegment.h
$O/inet/common/queue/DropTailQueue.o: inet/common/queue/DropTailQueue.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/InitStages.h \
	inet/common/queue/DropTailQueue.h \
	inet/common/queue/IPassiveQueue.h \
	inet/common/queue/PassiveQueueBase.h
$O/inet/common/queue/PassiveQueueBase.o: inet/common/queue/PassiveQueueBase.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/InitStages.h \
	inet/common/queue/IPassiveQueue.h \
	inet/common/queue/PassiveQueueBase.h
$O/inet/common/queue/Sink.o: inet/common/queue/Sink.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/InitStages.h \
	inet/common/queue/Sink.h
$O/inet/environment/common/Material.o: inet/environment/common/Material.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/Units.h \
	inet/environment/common/Material.h \
	inet/environment/contract/IMaterial.h
$O/inet/linklayer/base/ApMacBase.o: inet/linklayer/base/ApMacBase.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/figures/TrailFigure.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/linklayer/base/ApMacBase.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/base/MovingMobilityBase.h \
	inet/mobility/contract/IMobility.h
$O/inet/linklayer/base/HostMacBase.o: inet/linklayer/base/HostMacBase.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/figures/TrailFigure.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/common/queue/DropTailQueue.h \
	inet/common/queue/IPassiveQueue.h \
	inet/common/queue/PassiveQueueBase.h \
	inet/linklayer/base/HostMacBase.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/base/MovingMobilityBase.h \
	inet/mobility/contract/IMobility.h
$O/inet/linklayer/dara/DaraMac.o: inet/linklayer/dara/DaraMac.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/PacketKinds.h \
	inet/common/figures/TrailFigure.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/common/queue/DropTailQueue.h \
	inet/common/queue/IPassiveQueue.h \
	inet/common/queue/PassiveQueueBase.h \
	inet/linklayer/base/HostMacBase.h \
	inet/linklayer/dara/DaraMac.h \
	inet/linklayer/dara/DaraReq_m.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/base/MovingMobilityBase.h \
	inet/mobility/contract/IMobility.h
$O/inet/linklayer/dara/DaraReq_m.o: inet/linklayer/dara/DaraReq_m.cc \
	inet/linklayer/dara/DaraReq_m.h
$O/inet/linklayer/ld/LdMac.o: inet/linklayer/ld/LdMac.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/figures/TrailFigure.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/common/queue/DropTailQueue.h \
	inet/common/queue/IPassiveQueue.h \
	inet/common/queue/PassiveQueueBase.h \
	inet/linklayer/base/HostMacBase.h \
	inet/linklayer/ld/LdMac.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/base/MovingMobilityBase.h \
	inet/mobility/contract/IMobility.h
$O/inet/linklayer/tdma/TdmaAck_m.o: inet/linklayer/tdma/TdmaAck_m.cc \
	inet/linklayer/tdma/TdmaAck_m.h
$O/inet/linklayer/tdma/TdmaApMac.o: inet/linklayer/tdma/TdmaApMac.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/PacketKinds.h \
	inet/common/figures/TrailFigure.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/linklayer/base/ApMacBase.h \
	inet/linklayer/tdma/TdmaAck_m.h \
	inet/linklayer/tdma/TdmaApMac.h \
	inet/linklayer/tdma/TdmaReq_m.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/base/MovingMobilityBase.h \
	inet/mobility/contract/IMobility.h
$O/inet/linklayer/tdma/TdmaHostMac.o: inet/linklayer/tdma/TdmaHostMac.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/PacketKinds.h \
	inet/common/figures/TrailFigure.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/common/queue/DropTailQueue.h \
	inet/common/queue/IPassiveQueue.h \
	inet/common/queue/PassiveQueueBase.h \
	inet/linklayer/base/HostMacBase.h \
	inet/linklayer/tdma/TdmaAck_m.h \
	inet/linklayer/tdma/TdmaHostMac.h \
	inet/linklayer/tdma/TdmaReq_m.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/base/MovingMobilityBase.h \
	inet/mobility/contract/IMobility.h \
	inet/physicallayer/idealradio/IdealRadio.h
$O/inet/linklayer/tdma/TdmaReq_m.o: inet/linklayer/tdma/TdmaReq_m.cc \
	inet/linklayer/tdma/TdmaReq_m.h
$O/inet/mobility/base/MobilityBase.o: inet/mobility/base/MobilityBase.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/IVisitor.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/Units.h \
	inet/common/geometry/base/GeometricObjectBase.h \
	inet/common/geometry/base/ShapeBase.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/common/geometry/common/Rotation.h \
	inet/common/geometry/object/LineSegment.h \
	inet/environment/common/Material.h \
	inet/environment/contract/IMaterial.h \
	inet/environment/contract/IMaterialRegistry.h \
	inet/environment/contract/IPhysicalEnvironment.h \
	inet/environment/contract/IPhysicalObject.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/contract/IMobility.h
$O/inet/mobility/base/MovingMobilityBase.o: inet/mobility/base/MovingMobilityBase.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/IVisitor.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/Units.h \
	inet/common/figures/TrailFigure.h \
	inet/common/geometry/base/GeometricObjectBase.h \
	inet/common/geometry/base/ShapeBase.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/common/geometry/common/Rotation.h \
	inet/common/geometry/object/LineSegment.h \
	inet/environment/common/Material.h \
	inet/environment/contract/IMaterial.h \
	inet/environment/contract/IMaterialRegistry.h \
	inet/environment/contract/IPhysicalEnvironment.h \
	inet/environment/contract/IPhysicalObject.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/base/MovingMobilityBase.h \
	inet/mobility/contract/IMobility.h
$O/inet/mobility/contract/IMobility.o: inet/mobility/contract/IMobility.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/mobility/contract/IMobility.h
$O/inet/mobility/single/ThreeWayRandomMobility.o: inet/mobility/single/ThreeWayRandomMobility.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/figures/TrailFigure.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/base/MovingMobilityBase.h \
	inet/mobility/contract/IMobility.h \
	inet/mobility/single/ThreeWayRandomMobility.h
$O/inet/mobility/static/StationaryMobility.o: inet/mobility/static/StationaryMobility.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/INETMath.h \
	inet/common/InitStages.h \
	inet/common/ModuleAccess.h \
	inet/common/geometry/common/Coord.h \
	inet/common/geometry/common/EulerAngles.h \
	inet/mobility/base/MobilityBase.h \
	inet/mobility/contract/IMobility.h \
	inet/mobility/static/StationaryMobility.h
$O/inet/physicallayer/idealradio/IdealRadio.o: inet/physicallayer/idealradio/IdealRadio.cc \
	inet/common/Compat.h \
	inet/common/INETDefs.h \
	inet/common/InitStages.h \
	inet/common/PacketKinds.h \
	inet/physicallayer/idealradio/IdealRadio.h

