==================
NXP FRDM-IMXRT1186
==================

This board support package targets the Cortex-M33 in the MIMXRT1186
12 x 12 mm, 196-pin BGA package.  It supports debugger-loaded images and
Boot ROM execute-in-place (XIP) images for the on-board QSPI NOR flash.

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
* NETC switch Ethernet through the ENETC1 management station interface
* YT8531 RGMII PHY discovery, delay configuration, and link negotiation
* DHCP client and ICMP networking
* FlexSPI2 NOR Boot ROM container and XIP from the on-board W25Q128 flash
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

Configurations
==============

``nsh``
  Minimal debugger-loaded NSH image.

``netnsh``
  Debugger-loaded networking image.  Executable sections are placed in secure
  ITCM at ``0x0ffe0000`` and writable sections, stack, heap, and NETC DMA
  storage are placed in secure OCRAM beginning at ``0x20480000``.

``netnsh-xip``
  Networking image packaged for Boot ROM startup from the on-board 16 MiB
  W25Q128 QSPI NOR connected to FlexSPI2.  The raw ``nuttx.bin`` starts at
  flash offset zero and contains the FlexSPI configuration block, image
  container, and executable image.  Code executes from ``0x14000000`` while
  writable data remains in OCRAM.

Ethernet
========

The board exposes two external YT8531 RGMII PHYs on NETC switch ports 0 and 2.
The driver uses internal switch port 4 and ENETC1 SI0 as the Cortex-M33 data
path.  The default configuration selects the first external port with an
active link.  Port 0 uses PHY address 5 and port 2 uses PHY address 4.

The Port MAC ``PMx_IF_MODE.IFMODE`` RGMII value is 4.  This is intentionally
different from the ``BLK_CTRL_WAKEUPMIX.NETC_LINKn_CFG.MII_PROTOCOL`` RGMII
value of 2; these fields must not share an enum.

The NETC DMA rings require 128-byte descriptor alignment and 32-byte buffer
alignment.  ENETC1 management SI0 reserves ring 0 for management traffic; the
port-masquerade transmit path uses ring 1.  Port 4 is a pseudo MAC and must not
be accessed through the external Ethernet MAC register layout.

The PHY may still be negotiating when the one-shot NSH network initialization
runs after a cold power-on reset.  If ``eth0`` remains down, run::

  ifup eth0

The interface then uses DHCP.  This startup ordering limitation does not affect
the NETC data path after link-up.

Building
========

Configure and build the debugger-loaded networking image with::

  tools/configure.sh frdm-imxrt1186:netnsh
  make

Configure and build the Boot ROM XIP image with::

  tools/configure.sh frdm-imxrt1186:netnsh-xip
  make

The XIP configuration produces ``nuttx.bin`` for programming at FlexSPI2 flash
offset zero, as well as ``nuttx.hex``.

Applications that run for 24 hours or longer must provide the periodic ELE
active-timer ping required by the RT1180 security reference manual.
