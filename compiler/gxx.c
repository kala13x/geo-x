/*
 *  compiler/gx.h
 * 
 *  Copyleft (C) 2015  Geo-X Team
 *
 * Main source file of იქ-C compilator. 
 */


/* Util includes */
#include "../utils/stdinc.h"
#include "../utils/strops.h"
#include "../utils/errex.h"
#include "../utils/slog.h"
#include "../utils/files.h"

/* Local includes */
#include "mdefs.h"
#include "parser.h"
#include "info.h"


/* Files */
typedef struct {
    char input[PATH_MAX];
    char output[PATH_MAX];
} UserInputX;


/* 
 * init_uix - Initialize user input struct variables.
 * Argument uix is pointer of UserInputX structure.
 */
void init_uix(UserInputX *uix)
{
    bzero(uix->input, sizeof(uix->input));
    bzero(uix->output, sizeof(uix->output));
    strcpy(uix->output, "შედეგი");

}


/* 
 * parse_arguments - Parse arguments from user input.
 * Argument uix is pointer of UserInputX structure.
 */
static int parse_arguments(int argc, char *argv[], UserInputX *uix)
{
    int c;
    while ( (c = getopt(argc, argv, "i:o:h1")) != -1) {
        switch (c) {
        case 'i':
            strcpy(uix->input, optarg);
            break;
        case 'o':
            strcpy(uix->output, optarg);
            break;
        case 'h':
        default:
            usage(argv[0]);
            return -1;
        }
    }

    return 0;
}


/* Main function of compiler */
int main(int argc, char *argv[]) 
{
    /* Used variables */
    FILE * fp;
    char out[MAXMSG];
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    struct stat st;
    int ocreated = 0;

    /* Used variables */
    UserInputX uix;

    /* Greet users */
    greet("იქ->C კომპილატორი");

    /* Initialize user input vars */
    init_uix(&uix);

    /* Check valid args */
    if (argv[1] == NULL) 
    {
        slog(0, SLOG_ERROR, "მიუთითეთ დასაკომპილირებელი ფაილი.");
        usage(argv[0]);
        return 0;
    }

    /* Parse Commandline Arguments */
    if (parse_arguments(argc, argv, &uix)) return 0;

    /* Check if input file exists */
    if (stat(uix.input, &st) == -1)
        exit_prog(1, "ფაილი '%s' ვერ მოიძებნა", uix.input);
    
    /* Open input file for reading */
    fp = fopen(uix.input, "r");
    if (fp == NULL) exit_prog(1, "ვერ მოხერხდა '%s' ფაილის გახსნა", uix.input);

    /* Create new output file */
    while (!ocreated) 
    {
        /* Check if output file exists */
        if (stat(uix.output, &st) != -1) 
        {
            slog(0, SLOG_WARN, "ფაილი '%s' უკვე არსებობს", uix.output);
            sprintf(uix.output, "%s1", uix.output);
        }
        else ocreated = 1;
    }

    /* Loop in file line by line */
    while ((read = getline(&line, &len, fp)) != -1)
    {           
        /* Parse line */
        bzero(out, sizeof(out));
        sscanf(line, "%512[^\n]\n", line);
        strcpy(out, line);
        file_add_line(uix.output, parse_basic_types(out));
    }

    /* Cleanup */
    if (line) free(line);
    fclose(fp);

    return 0;
}
