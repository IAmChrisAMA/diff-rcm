# diff-rcm
### The totally original program no one has ever thought of before.

v1.0 GM | Well, that's all the time I've got.

Written by: Chris Nutter (building foundation), William McCarthy (initial struct), Rasputin (inspiration)


For the most part it's pretty fairly accurate. Side-by-side, brief, and identical are _**flawless**_. ;)

However normal, context, and unified are off. 

They work in outputting differences but normal doesn't have line numbers.

Context and unified work like normal but at least make awareness to the file date.

Enjoy. Thanks again. Love you, Mom & Dad. - C


Usage: diff-rcm [OPTION]... FILES
Compare FILES line by line.

Mandatory arguments to long options are mandatory for short options too.

	    --normal		        output a lineline diff (the default)
	-q, --brief		        report only when files differ
	-s, --report-identical-files    report when two files are the same
	-c, -C NUM, --context[=NUM]     output NUM (default 3) lines of copied context
	-u, -U NUM, --unified[=NUM]     output NUM (default 3) lines of unified context
	-y, --side-by-side	        output in two columns

	-i, --ignore-case	        ignore case differences in file contents

	    --help		        display this help and exit
	-v, --version		        output version information and exit

Report bugs to: cdnutter@gmail.com

diff-rcm homepage: <https://www.github.com/cdnutter/diff/>


 
