#include <stdio.h>
#include <gmp.h>
#include<stdlib.h>
#define BASE 10

int main(int argc, char **argv) {
    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    mpz_t hash_value;
    mpz_t hash_offset;
    mpz_init(hash_value);
    mpz_init(hash_offset);
    mpz_set_str(hash_offset, "69696969", BASE);
    mpz_set_str(hash_value, "0", BASE);

    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    for (int i = 0; buffer[i] != '\0'; i++) {
        char ch = buffer[i];
        if (ch >= 32 && ch <= 79) {
            ch += 47;
        } else if (ch >= 80 && ch <= 126) {
            ch -= 47;
        }
        mpz_mul_ui(hash_value, hash_value, BASE);
        mpz_add_ui(hash_value, hash_value, ch);
    }

    mpz_mod(hash_offset, hash_value, hash_offset);

    int i=0;

    for (;;) {
        mpz_add(hash_value, hash_value, hash_offset);
        mpz_mod_ui(hash_value, hash_value, 127);
        int out = mpz_get_ui(hash_value);
        if (out > 31 && out < 80) {
            out += 47;
	    printf("%c",out);
	    i++;
        } else if (out > 79 && out < 127) {
            out -= 47;
	    printf("%c",out);
	    i++;
        }
	if(i==30){
	break;
	}
        
    }
    printf("\n");
    free(buffer);
    mpz_clear(hash_value);
    mpz_clear(hash_offset);
    fclose(file);
    return 0;
}
