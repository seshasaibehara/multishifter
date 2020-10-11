# About
`mulstishift` is a [casm](https://github.com/prisms-center/CASMcode) and [casm-utilities](https://github.com/goirijo/casm-utilities) powered utility to create gamma surfaces and twisted bilayers along arbitrary crystallographic planes.
For a tutorial on the features and workflow see the official [pages](https://goirijo.github.io/multishifter).

This work is a product of the [Van der Ven research group](https://labs.materials.ucsb.edu/vanderven/anton/) at the UCSB Materials department.

# Citing
If this software helped your research please cite this repository and the following paper in addition to the papers listed in the [casm](https://github.com/prisms-center/CASMcode) repository.

```
__CITATION GOES HERE__
```

```bibtex
__BIBTEX GOES HERE__
```

The [paper](link/to/paper) outlines how the algorithms of `multishifter` operate, and applies them to metallic systems.
If you like this repository, consider giving me a star!

# Prerequisites
`multishift` is written on top of [casm-utilities](https://github.com/goirijo/casm-utilities), which requires a c++ compiler with c++17 support (`g++-8` recommended).

# Installation
You can install `multishift` by compiling from a tarball or zipball, you can install it from the git repository, or you can install it as a [casm-utilities](https://github.com/goirijo/casm-utilities) plugin.

## Installing from tarball or zipball (recommended)
Head over to the [releases](https://github.com/goirijo/multishifter/releases) page and download the `tar.gz` or `zip` file of the latest version (*not* the "Source code" files, you want the attachment with the extension in the name).

Once you've downloaded it, unpack it and run

    ./configure
    make
    make install
    
The build involves compiling some relatively heavy libraries, so it may take a few minutes to finish. You can speed up the build running `make -j4`, which will parallize the compilation on 4 processors.
Don't forget to specify a compiler with c++17 support if it's no the default on your system!

## Installing from git repository
Installing from the repository requires that you already have the [casm-utilities](https://github.com/goirijo/casm-utilities) libraries installed.
Once it's installed on your system, you can install `multishifter` using

    bash bootstrap.sh
    ./configure
    make
    make install
    
The `bootstrap.sh` script introduces additional dependencies, as it uses autotools to create the `configure` file. In order for this to work you'll need to have the following installed:

- autoconf
- automake
- libtool
- autoconf-archive

## Installing as a casm-utilities plugin
Documentation on the [casm-utilities](https://github.com/goirijo/casm-utilities) repository explains how to install plugins.

# Acknowledgements
Initial development of this software package was possible thanks to the financial support from NSF DMREF program under grant DMR-1534264.
Subsequent development was made possible by additional grants.
The scientific work was supported by the National Science Foundation DMREF grant: DMR-1729166 “DMREF/GOALI: Integrated ComputationalFramework for Designing Dynamically Controlled Alloy-Oxide Heterostructures”.
Software development was supported by the National Science Foundation, Grant No. OAC-1642433.
Computational resources provided by the National Energy Research Scientific Computing Center (NERSC), supported by the Office of Science and US Department of Energy under Contract No. DE-AC02-05CH11231, are gratefully acknowledged, in addition to support from the Center for Scientific Computing from the CNSI, MRL, and NSF MRSEC (No. DMR-1720256).

