/*
 *  utils/files.h
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * This source includes functions to work with files.
 */


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/*
 * create_directory - Recursively create directory. Argument dir is 
 * directory path. Function checks directory path and if directory 
 * doesnot exsists, function creates it. On success return value is
 * 1, otherwise function returns 0 if there is something wrong.
 */
int create_directory(char* dir);


/* 
 * copy_file - Copy file from source to destination. Argument src is path of 
 * source file which we want to copy and argument dst is destination path of 
 * new file. On success return walue is 1, otherwise function returns -1 if 
 * can not open source file and 0 if can not copy to destination file..
 */
int copy_file(char* src, char* dst);


/* 
 * remove_line - Remove exiting line from file. Function finds line 
 * and deletes it from file. First Argument file path and second 
 * argument str is keyword to find line which we want to delete. 
 */
void file_remove_line(char *fname, char *str);


/* file_add_line - Add line to file. First argument fname
 * is file path in which we want to append line and second
 * argument line is line to be added to file */
int file_add_line(char *fname, char *line);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif