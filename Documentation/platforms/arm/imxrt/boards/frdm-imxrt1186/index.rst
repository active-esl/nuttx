==================
NXP FRDM-IMXRT1186
==================

The ``frdm-imxrt1186:nsh`` configuration is an initial Cortex-M33 NSH port for
the MIMXRT1186 in the 12 x 12 mm, 196-pin BGA package.  The RAM-load image
places executable sections in the ITCM alias at ``0x0ffe0000`` and writable
sections, stack, and heap in the OCRAM alias at ``0x20480000``.

Supported features
==================

* Cortex-M33 ARMv8-M build
* SysTick
* LPUART1 console on GPIO_AON_08 (TX) and GPIO_AON_09 (RX)
* RT118x CCM register definitions for all clock roots and peripheral gates
* RT118x PLL, oscillator, PMU, and GPC register definitions
* Clock-root mux/divider, source-frequency, PLL/PFD-frequency, and LPCG APIs
* ELE transfer of AON, MEGA, and WAKEUP TRDC ownership to the Cortex-M33
* PMU PLL-LDO and SYS_PLL3 initialization, with the Cortex-M33 at 240 MHz
* NSH

This board is distinct from the MIMXRT1180-EVK, which uses MIMXRT1189 silicon
in a 289-pin package.  Board pinmux definitions are not interchangeable.

Early startup keeps the Cortex-M33 and LPUART1 on the always-available 24 MHz
RC oscillator.  NuttX then confirms that ELE responds, transfers the AON,
MEGA, and WAKEUP TRDC resources to the Cortex-M33, enables the PLL LDO, and
initializes the fixed 480 MHz SYS_PLL3.  The Cortex-M33 root uses SYS_PLL3
divided by two (240 MHz); LPUART1 uses SYS_PLL3 divided by two and then by ten,
retaining its 24 MHz input.  If any ownership or PLL-lock step fails, the roots
remain on RC24M and startup stops rather than running the scheduler with
incorrect timing.  The failure and completed-stage masks are available in
``g_imxrt118x_clock_error`` and ``g_imxrt118x_clock_status`` for debugger
diagnosis.

The port does not yet contain a ROM-bootable FlexSPI image.  On
FRDM-IMXRT1186, the on-board 16 MiB QSPI NOR is connected to FlexSPI2 and
appears in the Cortex-M33 non-secure AHB window at ``0x04000000``.
Applications that run for 24 hours or longer must also provide the periodic
ELE active-timer ping required by the RT1180 security reference manual.
