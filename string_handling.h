#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

int compare_text(char *text_1, char *text_2);
char *compare_extension(char *text_1, char *text_2);
int file_exist(char *nomeArquivo, char *mode);
char *concat_string(char *string_1, char *string_2, char *extension);
void remove_extension(char *texto);

#endif // STRING_H_INCLUDED
