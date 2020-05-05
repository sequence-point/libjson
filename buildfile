./: {*/ -build/} doc{CHANGELOG LICENSE README.md} manifest

define doxyfile: file
doxyfile{*}: extension = ""
doxyfile{*}: backlink = true
doxyfile{*}: in.substitution = lax

./: doxyfile{Doxyfile}: in{Doxyfile} $src_root/manifest

# Don't install tests.
#
tests/: install = false
