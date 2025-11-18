#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX 100
#define DELIM "," // CSV delimiter

char *ifile, *ofile;
unsigned filter_age_max;
FILE *istream, *ostream;

const char USAGE[] =
    R"(Filters CSV rows, keeping only those with provided maximum age
%1$s max-age [input-file] [output-file]

Example: 
%1$s max-age 17 input.csv output.csv
%1$s max-age 10 input.csv (outputs to stdout)
%1$s max-age 54           (inputs from stdin, outputs to stdout)
)";

void filter_stream(FILE *istream, FILE *ostream) {
  char line[LINE_MAX];
  char *fgets_return;
  char *name, *age_str;
  size_t line_no = 0;

  while (
      // Read a line from `istream` and assign the return value to
      // `fgets_return`
      // YOUR CODE HERE
        (fgets_return = fgets(line, LINE_MAX, istream)) != NULL   // Læser linjer indtil LINE_MAX nås.
      // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     <- Indikerer afslutning på egen kodebid.
  ) {
    ++line_no;

    if (fgets_return && *fgets_return != '\n') {
      if (strlen(line) > 1) {
        // Assign `name` and `age_str` using `strtok`
        // YOUR CODE HERE

        name    = strtok(line, DELIM);      // Laver navne-tokens ud af tekst før kommaet (DELIM).
        age_str = strtok(NULL, DELIM);      // Laver alders-tokens af teksten efter komma.

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // Alternative to strtok:
        // sscanf(line, "%*[^,],%d", &age);

        if (!age_str) {
          // Error message
          // YOUR CODE HERE
              fprintf(stderr,               // Mangler aldersfeltet (!age_str)? -> Print fejlen
                  "Line %zu: missing age field (expected two columns)\n",
                  line_no);
          // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          continue;
        }
      }
    } else {
      // Error message
      // YOUR CODE HERE
            fprintf(stderr, "Line %zu: empty line\n", line_no); // Fejl ved tom linje eller kun \n.
      // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      continue;
    }

    // Age processing
    unsigned age;
    auto recognized_count = sscanf(age_str, "%u", &age);  // "%d" ændret til "%u", da unsigned forventer dette.
    if (recognized_count == 1) {
      if (age <= filter_age_max) {
        // Forward input line to `ostream`
        // YOUR CODE HERE
                fprintf(ostream, "%s,%s", name, age_str);   // Gyldig(e) linje(r) printes som CSV-linjer til output-filen.
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      }
    } else {
      // Error message
      // YOUR CODE HERE
            fprintf(stderr,                                 // Ugyldig alder? -> Print fejlmeddelelsen.
              "Line %zu: age is not a valid number: '%s'\n",
              line_no, age_str);
      // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }
  }
}

int main(int argc, char *argv[]) {
  switch (argc) {
  case 4:
    // max-age ifile ofile
    ofile = argv[3];
  case 3:
    // max-age ifile
    ifile = argv[2];
  case 2:
    // max-age
    if (!sscanf(argv[1], "%d", &filter_age_max)) {
      puts("First argument is not an age.");
      exit(EXIT_FAILURE);
    }
    break;
  default:
    printf(USAGE, argv[0]);
    return EXIT_SUCCESS;
  }

  if (ifile) {
    // Open `ifile` and assign it to `istream`
    // YOUR CODE HERE
      istream = fopen(ifile, "r");                     // Åbner filen i read-only ("r") og lægger indholdet i istream.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Exit program with an error message if file cannot be opened
    // YOUR CODE HERE
     if (!istream) {                                    // Tom stream (fil kunne ikke åbnes)? -> Print fejlmeddelelse.
        fprintf(stderr, "Could not open input file '%s'\n", ifile);
        return EXIT_FAILURE;
      }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  } else {
    // Set `istream` if no file provided
    // YOUR CODE HERE
      istream = stdin;              // Læser fra stdin, hvis der ingen input-fil er.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      
  }

  if (ofile) {
    // Open `ofile` and assign it to `ostream`
    // YOUR CODE HERE
      ostream = fopen(ofile, "w");
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Exit program with an error message if file cannot be opened
    // YOUR CODE HERE
     if (!ostream) {                          // Kan output-filen ikke åbnes? -> Print fejlmeddelelse.
        fprintf(stderr, "Could not open output file '%s'\n", ofile);
        if (istream && istream != stdin) {
          fclose(istream);
        }
        return EXIT_FAILURE;
      }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  } else {
    // Set `ostream` if no file provided
    // YOUR CODE HERE
          ostream = stdout;           // Ingen output-fil angivet? -> Skriv til stdout.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  }

  filter_stream(istream, ostream);
}