dpyctl
===========================

Purpose
-------

Source code for my
[Teensy-LC](https://www.pjrc.com/teensy/teensyLC.html)-powered pseudo-KVM-switch
which listens for commands from a host machine and controls the routing of IO
devices such as HDMI switches, keyboards, mice, etc. 

Setup 
-----

#### Dependencies

* [teensy_loader_cli](https://www.pjrc.com/teensy/loader_cli.html)
	- Arch Linux: 
		-  [`aur/teensy-loader-cli-git`](https://www.archlinux.org/packages/community/x86_64/arm-none-eabi-gcc/) 
			_(Recommended)_
		- [`aur/teensyduino`](https://aur.archlinux.org/packages/teensyduino/)
			_(Alternate)_

			**Note:** This package provides a binary named with dashes rather than
			underscores - you will need to modify the Makefile if you choose this
			package.

		- [`community/teensy-loader-cli`](https://www.archlinux.org/packages/community/x86_64/teensy-loader-cli/) 
			_(Not Recommended)_
		
			**Note:** This official package in the Arch `community` is outdated and
			*does not* support the Teensy-LC board. I haven't tested any other boards. 
			Use this at your own discretion.

* ARM EABI GCC compiler:
	- Arch Linux:
		[`arm-none-eabi-gcc`](https://www.archlinux.org/packages/community/x86_64/arm-none-eabi-gcc/)

* ARM EABI GCC binutils:
	- Arch Linux:
		[`arm-none-eabi-binutils`](https://www.archlinux.org/packages/community/x86_64/arm-none-eabi-binutils/)

* ARM EABI C Stdlib:
	- Arch Linux:
		[`arm-none-eabi-newlib`](https://www.archlinux.org/packages/community/any/arm-none-eabi-newlib/)


Make Targets
------------

- `make`: alias for `make hex`
- `make build`: compiles everything and produces a .elf
- `make hex`: converts the elf to an intel hex file
- `make upload`: uploads the hex file to a teensy board

Credits
-------

This project is based on the scaffolding provided by
[apmorton/teensy-template](https://github.com/apmorton/teensy-template), which
in turn is based on
[PaulStoffregen/cores](https://github.com/PaulStoffregen/cores).

License
-------

Copyright &copy; 2018 Maddison Hellstrom

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

