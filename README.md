# elementum
An experimental framework for 3D cross-platform games

This is my Game Engine / Framework.
There are many like it (Maybe??) But this one is mine.

But seriously... This probably isn't a solution to your problem-
If you're looking for a game engine, I suggest you look at Unity
or Unreal, or Ogre, or even Blender for that matter- But not here.

Here you will find the scraps from me trying to learn the quirks
of what it takes to make a 3D game engine. It's not currently
functional--Still needs a lot of work.

Anyway... What is Elementum?

Elementum is (primarily) based off of the classic elements

(Fire, Water, Earth, and Air) (Ignis, Aqua, Terra, Aer)

I am a sucker for all things elemental, and have long wanted to
write some code with an elemental structure. Since code is
naturally made up of elements which build on each other, I thought
it would be cool to create some primal elements that could be
used to make larger more complex programs.

I tried to match the elements up with the parts of a program/game
that seemed to fit the best- In contemplating this, one idea I
came up with is the 3 states of Data.

Data at Rest
Data in Motion
Data in Use

It's not a perfect match, but I figured it was good enough

Earth/Terra ~ Solid  ~ Structure  ~ Rest    ---- Databases, FileSystems
Water/Aqua  ~ Liquid ~ Flow       ~ Motion  ---- Streams, Data Transfer, Networking
Fire/Ignis  ~ Plasma ~ Transform  ~ Use     ---- Algorithms, Data Transforms

So- The last might be kind of a stretch, since there's only 3 forms of data--
but

Air/Aer     ~ Gas    ~ Atmosphere ~ Control ---- Pub/Sub, Conc. Jobs, Patterns, etc.


^ So far the plans for this framework are very low-scale. It has some
networking stuff, but it will probably stay LAN/Small server. You won't notice
anything about distributed systems etc.

The 4 basic elements are meant to be aids in managing data, but they're not enough
to make a game. That's where a couple more base elements come in

Light/Lumina - I/O - User Input/Output   (Keyboard, Mouse, Window) (Wrapped around SDL2 - But OO)
Color/Chroma - Graphics - (Wrapped around OpenGL, But OO)

Also, I added Shadow which is a Mathematics library for graphics/physics

On top of Chroma (Which is basically OO OpenGL), I have Prisma (3D renderer) which
takes care of Model Loading/Unloading, scene generation, etc.

There will certainly be more elements to come, but that's where I'm at now... :)
