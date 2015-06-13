/*
 *  utils/files.c
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * This source includes functions to work with files.
 */


#include "stdinc.h"
#include "files.h"


/*
 * create_directory - Recursively create directory. Argument dir is 
 * directory path. Function checks directory path and if directory 
 * doesnot exsists, function creates it. On success return value is
 * 1, otherwise function returns 0 if there is something wrong.
 */
int create_directory(char* dir)
{
    /* Used variables */
    struct stat st = {0};
    char tmp[256];
    char *p = NULL;
    size_t len;

    /* Parse directory from path */
    snprintf(tmp, sizeof(tmp),"%s",dir);
    len = strlen(tmp);
    if(tmp[len - 1] == '/') tmp[len - 1] = 0;

    /* Start creation recursively */
    for(p = tmp + 1; *p; p++) 
    {
        if(*p == '/') 
        {
            *p = 0;
            if (stat(tmp, &st) == -1) 
            {
                if (mkdir(tmp, 0777) < 0) 
                    return 0;
            }

            *p = '/';
        }
    }

    /* Create final directory */
    if (stat(tmp, &st) == -1) 
    {
        if (mkdir(tmp, 0777) < 0)
            return 0;
    }

    return 1;
}


/* 
 * copy_file - Copy file from source to destination. Argument src is path of 
 * source file which we want to copy and argument dst is destination path of 
 * new file. On success return walue is 1, otherwise function returns -1 if 
 * can not open source file and 0 if can not copy to destination file..
 */
int copy_file(char* src, char* dst)
{
    /* Used variables */
    int input, output, flags, ret = 1;
    mode_t perms;
    ssize_t size;
    char buf[1024];
 
    /* Open input */
    input = open(src, O_RDONLY);
    if (input == -1) return -1;
 
    /* Set flags */
    flags = O_CREAT | O_WRONLY | O_TRUNC;
    perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    /* Open output */
    output = open(dst, flags, perms);
    if (output != -1) 
    {
        while ((size = read(input, buf, 1024)) > 0) 
        {
            if (write(output, buf, size) != size) 
            {
                ret = 0;
                break;
            }
        }

        if (size == -1) ret = 0;
        close(output);
    }
    close(input);
 
    return ret;
}


/* 
 * remove_line - Remove exiting line from file. Function finds line 
 * and deletes it from file. First Argument file path and second 
 * argument str is keyword to find line which we want to delete. 
 */
void file_remove_line(char *fname, char *str)
{
    FILE * fp;
    FILE * file;
    size_t len = 0;
    ssize_t read;
    char * line = NULL;

    /* Open templorary file */
    file = fopen("file.tmp", "a");
    if (file != NULL) 
    {
        /* Open exiting cache file */
        fp = fopen(fname, "r");
        if(fp != NULL)
        {
            /* Read from exiing cache file */
            while ((read = getline(&line, &len, fp)) != -1) 
            {
                /* Skip line if string exits on line */
                if(strstr(line, str) == NULL) 
                    fprintf(file, "%s", line);
            }

            /* Clean up memory */
            fclose(fp);
            if (line) free(line);
        }

        /* End up */
        fclose(file);
        remove(fname);
        rename("file.tmp", fname);
    }
}


/* file_add_line - Add line to file. First argument fname
 * is file path in which we want to append line and second
 * argument line is line to be added to file */
int file_add_line(char *fname, char *line) 
{
    /* Open file pointer */
    FILE *fp = fopen(fname, "a");
    if (fp == NULL) return -1;

    /* Write key in file */
    fprintf(fp, "%s\n", line);

    /* Close file pointer */
    fclose(fp);

    return 1;
}
/* create_file - create file. First argument fname
 * is file path in which we want to add line and second
 * argument line is line to be added to file */
int create_file(char *fname, char *line) 
{
    /* Open file pointer */
    FILE *fp = fopen(fname, "wb+");
    if (fp == NULL) return -1;

    /* Write key in file */
    fprintf(fp, "%s\n", line);

    /* Close file pointer */
    fclose(fp);

    return 1;
}