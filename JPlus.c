#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>


typedef int comm;
typedef unsigned char BYTE;

void print(comm val);

int main(int argc, char **argv){
    uint64_t pc, global_var, index, size;
    uint64_t* slots;
    comm* code;


    FILE* file;
    uint32_t sz;
    comm j;
    BYTE while_cond;

    int mode = 0;
    if(argc <= 2){
        printf("Not enough arguments\n");
        return 1;
    }
    
    size = atoll(argv[2]);
    file = fopen(argv[1], "r");
    if(file==NULL){
        printf("Cannot open file %s\n", argv[0]);
        return 1;
    }

    /*allocate slot buffer*/
    slots = (uint64_t*)malloc(sizeof(uint64_t) * size);
    if(slots==NULL){
        printf("Cannot allocate memory\n");
        fclose(file);
        return 1;
    }

    /*get size of file*/
    sz = 0;
    for(mode = fgetc(file); mode != EOF; mode = fgetc(file)){
        ++sz;
    }
    rewind(file);

    /*allocate code buffer*/
    code = (comm*)malloc(sizeof(comm) * sz);
    if(code==NULL){
        printf("Cannot allocate memory\n");
        fclose(file);
        free(slots);
        return 1;
    }

    /*read and load code into buffer*/
    index = 0;
    for(mode = fgetc(file); mode != EOF; mode = fgetc(file)){
        code[index++] = mode;
    }

    /*close file*/
    fclose(file);

    /*reset slot buffer*/
    for(index = 0; index < size; ++index){
        slots[index] = 0;
    }
    
    pc = 0;
    global_var = 0;
    index = 0;
    while_cond = 1;
    mode = 0;

    while(while_cond){
        j = code[pc];
        if(mode == 3){
            if(j == '"')
                goto START_SWITCH;
            slots[index++] = j;
            goto END_OF_LOOP;
        }

START_SWITCH:

        switch(j){
            case '>':   ++index;                                        break;
            case '<':   --index;                                        break;
            case '+':   slots[index]++;                                 break;
            case '-':   slots[index]--;                                 break;
            case 'r':   global_var = slots[index];                      break;
            case 'w':   slots[index] = global_var;                      break;
            case 'j':   pc = slots[index];                              break;
            case 'c':   slots[index] = pc;                              break;
            case 'p':   print(slots[index]);                            break;
            case 'i':   slots[index] = getch();                         break;
            case '&':   slots[index] = index;                           break;
            case '*':   index = slots[index];                           break;
            case '?':   if(global_var)  pc = slots[index];              break;
            case ';':   while_cond = 0;                                 break;
            case '#':   if(mode != 1 && mode != 0){
                            printf("Syntax error: invalid\n");
                            while_cond = 0;
                            continue;
                        }
                        mode = !mode;
                        break;
            case 'x':   if(mode != 2 && mode != 0){
                            printf("Syntax error: invalid\n");
                            while_cond = 0;
                            continue;
                        }
                        mode = (mode == 2)?0:2;
                        break;
            case '"':   if(mode != 3 && mode != 0){
                            printf("Syntax error: invalid\n");
                            while_cond = 0;
                            continue;
                        }
                        mode = (mode == 3)?0:3;
                        slots[index] = 0;
                        break;
            case 'P':   for(j = index; slots[j] != 0; ++j)  putchar(slots[j]);                           
                        break;
            default:

                if(mode == 0){
                    if(j == '0')
                        index = 0;
                    break;
                }
                
                if(j >= '0' && j <= '9'){
                    if(mode == 1){
                        slots[index] *= 10;
                        slots[index] += (j - '0');
                    }
                    else if(mode == 2){
                        slots[index] <<= 4;
                        slots[index] += (j - '0');
                    }
                    else{   printf("Syntax error: invalid\n");   while_cond = 0;   continue;  }
                }
                else if(j >= 'A' && j <= 'F'){
                    if(mode == 2){
                        slots[index] <<= 4;
                        slots[index] += (j - 'A' + 10);
                    }
                    else{   printf("Syntax error: invalid\n");   while_cond = 0;   continue;    }
                }
        }
END_OF_LOOP:
        if(pc > sz)
            while_cond = 0;
        ++pc;
    }
    free(slots);
    free(code);
    
    return 0;
}


void print(comm val)
{
    putchar(val);
}

