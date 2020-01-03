# AlienEdit
AlienEdit is a command line text editor based on ncurses.
At this point, it is very limited, but it is possible to edit files.
In fact, I wrote this README using AlienEdit itself.

## Running it
You'll need Git, make a C++ compiler and ncurses for this to build AlienEdit.
```sh
git clone https://github.com/The947thTokay/AlienEdit.git
cd AlienEdit
make
```
Then, to edit `/path/to/file`, run
```sh
./alienedit /path/to/file
```
Once AlienEdit is a bit more usable, I'll start releasing binaries through
GitHub releases.
