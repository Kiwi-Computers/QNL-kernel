# What is QNL?

QNL is the kernel and low-level foundation of the Kiwi Computer operating system. QNL is an acronym for Q is Not Linux. QNL is a Linux-derived kernel combining the Linux kernel with Kiwi-specific modifications, hardware optimizations, and a curated configuration designed for Kiwi hardware. QNL is built around the LLVM/Clang toolchain (via cbuild) and is designed to work closely with Kiwi's Unix-like userland and system technologies.

QNL is intentionally hardware-specific. Rather than attempting to support every computer and configuration, QNL focuses on providing a tightly integrated foundation for supported Kiwi hardware.

The name follows the tradition of GNU and XNU: QNL acknowledges its Linux heritage while distinguishing itself from conventional Linux systems.

Linux is the foundation. QNL is what we build from it.

# Philosophy

We don't need Linux to be everything. We need it to be good at being QNL.

QNL is not intended to run on every computer, support every configuration, or accommodate every use case. It is designed to run exceptionally well on the hardware it was built for.

The goal is simple:

A UNIX-like/UNIX-based foundation that feels coherent, integrated, and purpose-built—not a collection of software held together by convention.

# Goals

Some goals we have for QNL are as follows:
- Hybrid architecture — combine Linux's proven kernel foundation with a Mach-inspired architecture for selected system services.
- Hardware integration — provide tightly integrated support for Kiwi hardware (curently RK3588) rather than general-purpose compatibility.
- Object-oriented driver system — develop a modular, object-oriented driver framework inspired by Apple’s DriverKit, providing structured interfaces for hardware drivers while improving isolation, extensibility, and maintainability.
- Modularity — move appropriate components out of the core kernel where practical, improving isolation and maintainability.
- Kiwi-native services — provide first-class kernel interfaces for Kiwi technologies and hardware.
- LLVM/Clang toolchain — use LLVM and Clang as the primary development and build toolchain wherever practical.
- Unix-like foundation — preserve the familiar principles and interfaces of Unix while creating a distinctly Kiwi system.
- Evolution, not reinvention — build upon proven technology while gradually replacing or restructuring components where doing so provides a meaningful advantage.

# Building

QNL is built using the **open-source cbuild and cports tooling provided by Chimera Linux**.

The QNL development environment uses **LLVM and Clang** as its primary compiler toolchain.

To build QNL, install the required Chimera Linux cbuild/cports tooling, configure the appropriate QNL target (aarch64), and build using Clang.

# Licensing

QNL incorporates Linux kernel code and therefore remains subject to the applicable GPLv2 requirements. QNL does not attempt to change or circumvent the licenses of its upstream components.

Kiwi-specific code and technology are developed separately where appropriate.

QNL is Linux-derived by necessity, Kiwi-designed by choice.

#

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/102648de-77b3-4821-98df-0d2a01a7e8e1" />


© 2026 Kiwi Computer. All Rights Reserved.
