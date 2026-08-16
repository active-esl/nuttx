==================
NXP FRDM-IMXRT1186
==================

The ``frdm-imxrt1186:nsh`` configuration is an initial Cortex-M33 NSH port for
the MIMXRT1186 in the 12 x 12 mm, 196-pin BGA package.  The RAM-load image
places executable sections in secure ITCM at ``0x0ffe0000`` and writable
sections, stack, and heap in secure OCRAM at ``0x20480000``.

Supported features
==================

* Cortex-M33 ARMv8-M build
* SysTick
* LPUART1 console on GPIO_AON_08 (TX) and GPIO_AON_09 (RX)
* RT118x CCM register definitions for all clock roots and peripheral gates
* RT118x PLL, oscillator, PMU, and GPC register definitions
* Clock-root mux/divider, source-frequency, PLL/PFD-frequency, and LPCG APIs
* NSH

This board is distinct from the MIMXRT1180-EVK, which uses MIMXRT1189 silicon
in a 289-pin package.  Board pinmux definitions are not interchangeable.

The debugger-load configuration keeps the Cortex-M33 and LPUART1 on the
always-available 24 MHz RC oscillator.  The clock driver can report and select
all documented PLL-derived root inputs when the relevant PLL is already
running.  It does not initialize or retune PLLs during early boot because
NuttX does not yet own the required ELE/TRDC and PMU policy.  The port also
does not yet contain a ROM-bootable FlexSPI image.
