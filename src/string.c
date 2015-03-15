#include "string.h"
#include "zft_memory.h"


BOOL is_empty(const char* string){
	char* stringptr = (char*)string;
	while(*stringptr){
		if(*stringptr != ' ' && *stringptr != '\n' && *stringptr != '\t' && *stringptr != '\n'){
			return FALSE;
		}
		stringptr++;
	}
	return TRUE;
}
size_t strlen(const char* string){
	size_t retval = 0;
	while(string[retval++]);
	return retval;
}

uint8_t strcmp(const char* string_a, const char* string_b){
	size_t i;
	for(i = 0; string_a[i] && string_b[i] && string_a[i] == string_b[i]; ++i);
	return string_b[i] - string_a[i];
}

char* strcpy(char* destination, const char* source){
	memcpy((void*)destination, (const void*)source, strlen(source));
	return destination;
}



char* reverse(char* string){
    size_t i, j;
    char buff;
    for (i = 0, j = strlen(string)-2; i < j; ++i, --j){
        buff = string[i];
        string[i] = string[j];
        string[j] = buff;
    }
    return string;
}


char* uint_to_string(uint64_t value, char* buffer, uint8_t base){
	size_t string_iterator = 0;
	char temp;
	do{
		temp = value % base;
		if(temp <= 9){
			temp += '0';
		}
		else{
			temp += 'a' - 10;
		}
		buffer[string_iterator++] = temp;
	} while ((value /= base) > 0);
	buffer[string_iterator] = '\0';
	return reverse(buffer);
}
char* int_to_string(int64_t value, char* buffer, uint8_t base){
	BOOL sign = (value < 0);
	size_t string_iterator;
	if(sign)
		value = -value;
	string_iterator = 0;
	char temp;
	do{
		temp = value % base;
		if(temp <= 9){
			temp += '0';
		}
		else{
			temp += 'a' - 10;
		}
		buffer[string_iterator++] = temp;
	} while ((value /= base) > 0);
	if(sign)
		buffer[string_iterator++] = '-';
	buffer[string_iterator] = '\0';
	return reverse(buffer);
}

/*char* sprintf(char* destination, const char* format, ...){
	const char** stack_ptr = &format;
	stack_ptr++;
	return vsprintf(destination, format, (void*)stack_ptr);
}*/
//TODO
//char* vsprintf(char* destination, const char* format, void* args){return destination, format, args, NULL;}