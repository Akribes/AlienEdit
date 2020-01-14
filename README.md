# AlienEdit
AlienEdit is a command line text editor based on ncurses.
At this point, it is very limited, but it is possible to edit files.
In fact, I wrote this README using AlienEdit itself.

## Usage
To edit a file with AlienEdit, run `alienedit filename` in a terminal. You can
start typing straight away, or navigate with the arrow keys.

To use the menu at the bottom of the screen, press Escape. You can then choose
an option using the arrow keys and the Enter key. This way, you can save the
file, or exit the editor.

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
You can also install AlienEdit to another location. Running	
`make install PREFIX=/usr/local` will install AlienEdit into `/usr/local`.
