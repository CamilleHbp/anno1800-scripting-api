# Project Overview

## Anno 1800 API

### Code Generator

The code generator uses `yaml` files to generate code used in the `Injected` and `Monocle` projects, such as the `Telegraph` class, various structures, etc.

### Injected

This code will be injected through a DLL side-loaded in Anno 1800. It injects code at some offset

### Monocle

This is the main program. Monocle will get the Anno 1800's process and load a fake DLL. It will then inject the code from the [Injected](#injected) program into Anno 1800 through that DLL.

Communication between user programs and Anno1800 will be made using the auto-generated Telegraph class.

## User applications

### GoodMinMax

This program manages resources on all the user's islands and automatically set trade routes as needed.

### ProductionViewer

### ResourceExporter

## TestMonocle

This basic program will get help you test if Telegraph is able to communicate with the Anno1800's process.
