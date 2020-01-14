# AlienEdit
AlienEdit is a command line text editor based on ncurses.
At this point, it is very limited, but it is possible to edit files.
In fact, I wrote this README using AlienEdit itself.

## Installing it
Once AlienEdit is a bit more usable, I'll start releasing binaries through
GitHub releases.

## Building it
You'll need Git, make a C++ compiler and ncurses for this to build AlienEdit.
```sh
git clone https://github.com/Akribes/AlienEdit.git
cd AlienEdit
make
make install
```
Then, to edit `/path/to/file`, run
```sh
alienedit /path/to/file
```
You can also install AlienEdit to another location. Running	
`make install PREFIX=/usr/local` will install AlienEdit into `/usr/local`.
