Welcome to Finn's lab 3 unit test patch
=======================================

This patch includes:
- lists.cc
- catch.hpp (catch.hpp is the copyright of Phil Nash, see license at http://www.boost.org/LICENSE_1_0.txt)
- Makefile
- README.txt

The tests for part 2 of the lab are replaced with a new file lists.cc.
Main improvements:
- All tests run separately, so you can isolate them while debugging
- Run `./lists -h` for all the options available
- Pretty test output on failure
- Add your own tests using Catch - find the documentation at https://github.com/philsquared/Catch/blob/master/docs/tutorial.md
- Use node_manager to avoid having to remember to delete your lists in test (see the existing tests for what this looks like)

Have fun!
