PROJ=stopwatch

ifeq ($(OS),Windows_NT)
EXE:=.exe
endif
ifneq ("$(WSL_DISTRO_NAME)","")
        # if using Windows Subsystem for Linux, and yosys not found, try adding .exe
        ifeq (, $(shell which yosys))
                EXE:=.exe
        endif
endif

all: ${PROJ}.bit

%.json: %.v
	yosys$(EXE) -p "synth_ecp5 -json $@" $<

%_out.config: %.json had19_proto3.lpf
	nextpnr-ecp5$(EXE) --json $< --textcfg $@ --45k --package CABGA381 --speed 8 --lpf had19_proto3.lpf

%.bit: %_out.config
	ecppack$(EXE) $< $@

prog: ${PROJ}.bit
	dfu-util$(EXE) -d 1d50:614a,1d50:614b -a 0 -R -D $<

clean:
	rm -rf *.bit *.json *.config

.PRECIOUS: ${PROJ}.json ${PROJ}_out.config
