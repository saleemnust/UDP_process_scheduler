    #include <stdio.h>
    #include <stdlib.h> // For exit() function
    int main() {
        int c[2];
        FILE *fptr;
        if ((fptr = fopen("text", "r")) == NULL) {
            printf("Error! opening file");
            // Program exits if file pointer returns NULL.
            exit(1);
        }
        // reads text until newline is encountered
        //fscanf(fptr, "%d[^\n]", c);
        fscanf(fptr, "%d", c);
        //int i = (int)c;

        //printf("Data from the file:\n%d\n", c);
        printf("%d\n", *c);
        fclose(fptr);
        return 0;
    }