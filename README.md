Elementum
=========

Elementum is an application framework built upon a number of common C++
libraries for cross-platform application development. The idea behind
Elementum is to create an intuitive object-oriented interface that spans
across all the common domains of building a networked, graphical application.

Overview
--------

The structure of Elementum is meant to be layer-component based. The core of
the model is a number of base elements that provide commonly needed abilities
to an application. More complex elements, such as UI abilities or Animation,
will be built on top of more base elements.

Getting Started
---------------

Ensure you have the necessary dependencies installed.

 * make
 * SDL2
 * OpenGL

In `chroma/chroma.cc`, ensure that the values set for SDL_GL_VERSION_MAJOR and
SDL_GL_VERSION_MINOR match the version of OpenGL you are using. (This should
be fixed soon.)

In a terminal, for each element:

1. Enter the directory of the element. (e.g. `$ cd lumina`)
2. Run `make`

Currently, the only examples are the code in *element*_test.cc, so look there
for basic usage of the element. Real examples should be added soon.

Components
----------

*\*Note: Elementum is a work in progress. This describes the ideal, which
might not be met yet.*

  * Aqua (Networking)

    Aqua deals with everything from inter-process communication, to
    communication within processes, to communication over a network, to
    streaming data within a single application. Basically, it is data flow. If
    data needs to get from one place to another, it goes through Aqua.

  * Terra (Data Storage)

    Terra is a library for putting data into and out of databases and files.

  * Ignis (Algorithms)

    Ignis does basic calculations and operations on data.

  * Aer (Program Flow)

    Aer contains a system for creating threads, jobs, callbacks, and
    publisher-subscriber systems. Anything that needs to respond to an event,
    wait, happen sometimes, or in parallel, Aer will do it.

  * Shadow (Mathematics)

    Shadow is the hidden dark side of Ignis. While Ignis deals mainly with
    vectors and lists, Shadow can handle matrices, vectors, polynomials, and
    more. It can be used for graphics, machine learning, data processing, and
    much more.

  * Lumina (User I/O)

    Lumina is a wrapper around SDL2, aiming for a more Object-oriented
    interface. It provides a way for users to interact with programs.

  * Chroma (Base Graphics)

    Chroma is a wrapper around OpenGL, again creating a more Object-Oriented
    interface.

  * Prisma (Graphics)

    Prisma is a graphical assets management system. It is built on top of
    Chroma, and is capable of loading 2d and 3d animated models and drawing
    them to the screen.

