# What is QNL?

QNL is the kernel and low-level foundation of the Kiwi Computer operating system. QNL is an acronym for Q is Not Linux. QNL is a Linux-derived kernel combining the Linux kernel with Kiwi-specific modifications, hardware optimizations, and a curated configuration designed for Kiwi hardware. QNL is built around the LLVM/Clang toolchain (via cbuild) and is designed to work closely with Kiwi's Unix-like userland and system technologies.

QNL is intentionally hardware-specific. Rather than attempting to support every computer and configuration, QNL focuses on providing a tightly integrated foundation for supported Kiwi hardware.

The name follows the tradition of GNU and XNU: QNL acknowledges its Linux heritage while distinguishing itself from conventional Linux systems.

Linux is the foundation. QNL is what we build from it.

# Philosophy

We don't need Linux to be everything. We need it to be good at being QNL.

QNL is not intended to run on every computer, support every configuration, or accommodate every use case. It is designed to run exceptionally well on the hardware it was built for.

The goal is simple:

A UNIX-like foundation that feels coherent, integrated, and purpose-built—not a collection of software held together by convention.

# Licensing

QNL incorporates Linux kernel code and therefore remains subject to the applicable GPLv2 requirements. QNL does not attempt to change or circumvent the licenses of its upstream components.

Kiwi-specific code and technology are developed separately where appropriate.

QNL is Linux-derived by necessity, Kiwi-designed by choice.
