# FRDM-IMXRT1186 BSP status

<!-- SPDX-License-Identifier: Apache-2.0 -->

This table distinguishes implementation present on a named branch from
FRDM-IMXRT1186 hardware proof.  The Apache pull request remains focused on
the Cortex-M33 NSH and clock slice; FlexSPI2 XIP and Ethernet are fork-only
follow-ons until their remaining hardware gates pass.

| Area | Implemented | Tested on FRDM-IMXRT1186 | Remaining / notes |
|---|---|---|---|
| CM33 board bring-up / NSH | `ARCH_CHIP_MIMXRT1186`, ARMv8-M board target, reset entry clears inherited `MSPLIM`/`PSPLIM`, and LPUART1 console at 115200 | **PASS:** LinkServer RAM load, `nsh>`, `help`, `uname -a` | PR is a WIP debugger-load path, not a POR-boot claim |
| Clock tree / CCM | RT118x CCM roots/LPCGs, source/PLL/PFD queries, PMU PLL LDO, fixed 480 MHz SYS_PLL3, M33 at 240 MHz, LPUART at 24 MHz | **PASS:** status `0x7f`, error `0`; live PLL and root registers match the programmed tree | SYS_PLL1/2, ARM/audio PLLs and the complete peripheral clock tree remain |
| ELE / TRDC | ELE MU commands transfer AON, MEGA and WAKEUP TRDC ownership; clock startup fails closed | **PASS** as part of the clock smoke | Full TRDC DAC/MRC/MBC policy and the 24-hour ELE active-timer ping remain |
| SysTick / timers | SysTick uses the 240 MHz processor clock; GPT1/LPIT1 addresses and IRQs are defined | **PASS:** `uptime` advances at approximately one second per second | GPT/LPIT board configuration and hardware exercise remain |
| Memory map | ITCM, DTCM, OCRAM and peripheral maps; RAM image links code at ITCM alias `0x0ffe0000` and writable state at OCRAM alias `0x20480000` | **PASS:** ITCM/OCRAM image loads and runs | DTCM is defined but unused and unproven |
| Pinmux / GPIO | LPUART1 GPIO_AON_08/09 pinmux; Ethernet branch adds FRDM RGMII/MDIO pinmux | UART **PASS**; Ethernet MDIO/link **PASS** on its fork branch | Generic RT118x GPIO read/write remains stubbed |
| LEDs / button | Correct FRDM mapping is known: red GPIO2_IO09, green GPIO2_IO11, blue GPIO3_IO07, SW4 GPIO4_IO12 | **Not tested** | No FRDM LED/button driver or pinmux implementation; earlier EVK-named evidence is not FRDM proof |
| FlexSPI2 / XIP image | Fork branch `f7b87ebd279` adds W25Q128 FCB, RT1180 container and `nsh-xip`; flash at `0x04000000`, text at `0x0400b000` | **Build/layout/checkpatch PASS**; LinkServer target discovery passes | **No erase/program, XIP execution or POR `nsh>` proof**; latest attach failed with `Ee(42)` |
| Boot / J60 SDP | XIP documentation identifies J60 `100` for SDP/J63 and `001` for QSPI/POR | **Not proven** | Program in physical SDP mode, restore `001`, power-cycle and capture NSH without `gdb load` |
| Ethernet MDIO / PHY | Fork branch implements FRDM ENETC1/switch path and YT8531 PHYs at MDIO 5/4 | **PASS:** IDs `4f51:e91a`; port 0 link 1 Gbit full duplex; port 2 down with no cable | Fork-only until packet-path gates pass |
| Ethernet packet path | ENETC1 rings, cache handling, switch/IERB/VLAN setup, `eth0`, procfs and honest 10 ms polling | **PASS:** ENETC/switch enable, rings, `eth0` RUNNING with static `10.0.0.2/24` | MSI-X/MSGINTR remains; polling is bring-up quality |
| DHCP / ping | DHCP client is enabled at Ethernet tip `8568631133d`; ICMP/ping is included | DHCP **not proven**; static ping **FAILS** with ARP timeout `-110` | Prove DHCP, ARP, TX/RX and bidirectional local ping; do not claim working IP networking yet |
| USB and other peripherals | Limited address/IRQ groundwork only | **Not tested** | No board support/proof for USB, SPI, I2C, CAN, PWM, ADC, SAI, watchdog or general GPIO |
| Dual-core CM7 | None | **Not tested** | CM7 startup, image loading, IPC/shared memory and dual-core boot are deferred |
| Upstream CI / Make board build | Fork pre-upstream workflow aligned closer to Apache (`active-esl/nuttx#8`, apache/nuttx#14601); board has `src/CMakeLists.txt` and `src/Makefile` (tip `f3458c6739f`) | CMake/Ninja `frdm-imxrt1186:nsh` **PASS** on fork (e.g. tip `d4ba1324ff6`); local GNU Make in Apache CI container **PASS** (`libboard.a`, nuttx text 100488 / data 892 / bss 6688) | Prove green Make/`cibuild` on `active-esl/nuttx` self-hosted gate before any Apache push; sibling RT1180 board Makefile still TBD if that board is retained |
| Upstream PR posture | Apache PR tip `246b5eb5541` is FRDM-only CM33 NSH + clocks; draft `[WIP]` | Host build/checkpatch at tip; FRDM hardware proof at `d4ba1324ff6` | XIP and Ethernet stay fork-only until their hardware gates pass; no EVK/RT1189 claim |
| Scope / non-goals | Work is focused on CM33 NSH, clocks and later Ethernet | RT1186 peripheral count is sufficient for the MVP | RT1189 EVK parity, CM7, MCUBoot, private ELE identity/PSA, Hosted Mender and fuse/AHAB work are not this PR's blockers |
