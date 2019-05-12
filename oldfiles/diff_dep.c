int main(int argc, const char* argv[]) {

  //if (argc != 3 && (*argv)[0] == '-') { fprintf(stderr, "Usage: ./diff file1 file2\n"); exit(ARGC_ERROR); }
  //if (argc < 3)                       { fprintf(stderr, "Usage: ./diff file1 file2\n"); exit(ARGC_ERROR); }
  //if (argc == 3)                      { loadfiles(argv); normal(argv); return 0; }

  init(--argc, ++argv);
  loadfiles(files[0], files[1]);
  if (!showcontext && !showunified && !showsidebyside && !showleftcolumn) { normal(files[0], files[1]); }

  // while (*++argv)
  //   switch ((*argv)[1]) {
  //     default:  break;
  //     case 'v': version(); return 0;         // 100%  implemented (unless I want to enhance)
  //     case 't': todo(); return 0;            // Only for me. To be deprecated later.
  //     case 'q': loadfiles(argv); quiet(argv); break;       // 100% implemented
  //     case 'y': loadfiles(argv); sideside(argv); break;    // 50%   implemented
  //     case 'i': printf("i done\n"); break;
  //     case 'c': printf("c done\n"); break;
  //     case 'u': printf("u done\n"); break;
  //     case 's': loadfiles(argv); loud(argv); break;
  //   }

  return 0;
}
