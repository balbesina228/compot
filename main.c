#include <stdio.h>
#include <stdlib.h>

void compress_file(char* input_filename, char* output_filename) {
	FILE* input_file = fopen(input_filename, "r");
	FILE* output_file = fopen(output_filename, "w");

	if (!input_file || !output_file) {
		perror("Error opening file...");
		return;
	}

	int current_char, next_char;
	unsigned char count;

	current_char = fgetc(input_file);
	while (current_char != EOF) {
		count = 1;

		// Counting byte repeats
		while ((next_char = fgetc(input_file)) == current_char && count < 255) {
			count++;
		}

		if (count > 1) {
			fprintf(output_file, "%c%d", current_char, count);
		} else {
			fputc(current_char, output_file);
		}
		current_char = next_char;
	}

	fclose(input_file);
	fclose(output_file);
}

int main(void)
{
	compress_file("input.txt", "output.txt");
	return 0;
}