OFIChain Core
=============

Setup
---------------------
OFIChain Core is the original OFIChain client and it builds the backbone of the network. It downloads and, by default, stores the entire history of OFIChain transactions (which is currently more than 100 GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download OFIChain Core, visit [OFIChaincore.org](https://OFIChaincore.org/en/releases/).

Running
---------------------
The following are some helpful notes on how to run OFIChain on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/OFIChain-qt` (GUI) or
- `bin/OFIChaind` (headless)

### Windows

Unpack the files into a directory, and then run OFIChain-qt.exe.

### OS X

Drag OFIChain-Core to your applications folder, and then run OFIChain-Core.

### Need Help?

* See the documentation at the [OFIChain Wiki](https://en.OFIChain.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#OFIChain](http://webchat.freenode.net?channels=OFIChain) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=OFIChain).
* Ask for help on the [OFIChainTalk](https://OFIChaintalk.org/) forums, in the [Technical Support board](https://OFIChaintalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build OFIChain on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The OFIChain repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/OFIChain/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [OFIChainTalk](https://OFIChaintalk.org/) forums, in the [Development & Technical Discussion board](https://OFIChaintalk.org/index.php?board=6.0).
* Discuss project-specific development on #OFIChain-core-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=OFIChain-core-dev).
* Discuss general OFIChain development on #OFIChain-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=OFIChain-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.