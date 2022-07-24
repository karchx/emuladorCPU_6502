default_target: all
.PHONY : default_target

all:
	cmake -S . -B build \
	&& clear && cd build \
	&& make \
	&& ./M6502Test


clean:
	@rm -rf build

.PHONY : all
