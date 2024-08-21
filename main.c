#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int convert_arr_to_int(char arr[], int length) {
	int val = 0;

	for (int i = 0; i < length; i++) {
		if (arr[i] >= '0' && arr[i] <= '9') {
			val = val * 10 + (arr[i] - '0');
		}
		else {
			break;
		}
	}
	return val;
}

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

void decompress_file(char* input_filename, char* output_filename) {
	FILE* input_file = fopen(input_filename, "r");
	FILE* output_file = fopen(output_filename, "w");

	if (!input_file || !output_file) {
		perror("Error opening file...");
		return;
	}

	int current_char, next_char;
	unsigned char count[5] = {'N', 'N', 'N', 'N', 'N'};
	int amount;

	current_char = fgetc(input_file);
	while (current_char != EOF) {
		// reinit count
		for (int i = 0; i < sizeof(count); i++) {
			count[i] = 'N';
		}


		// reads all nums to learn what amount it is
		for (int i = 0; i < sizeof(count); i++) {
			next_char = fgetc(input_file);
			if (isalpha(next_char)) {
				break;
			}
			count[i] = next_char;
		};

		// reformats nums to int amount
		amount = convert_arr_to_int(count, sizeof(count));

		// decompress
		for (int i = 0; i < amount; i++) {
			fputc(current_char, output_file);
		}

		current_char = next_char;
	}

	fclose(input_file);
	fclose(output_file);
}

void menu() {
	int choice;
	char input_filename[20], output_filename[20];
	printf("1. Compress file.\n");
	printf("2. Decompress file.\n");
	printf("99. Quit.\n");
	
	scanf_s("%d", &choice);
	switch (choice) {
		case 1:
			printf("Type in input filename: ");
			scanf_s("%s", input_filename, (unsigned)_countof(input_filename));
			printf("Type in output filename: ");
			scanf_s("%s", &output_filename, (unsigned)_countof(output_filename));
			compress_file(input_filename, output_filename);
			break;

		case 2:
			printf("Type in input filename: ");
			scanf_s("%s", &input_filename, (unsigned)_countof(input_filename));
			printf("Type in output filename: ");
			scanf_s("%s", &output_filename, (unsigned)_countof(output_filename));
			decompress_file(input_filename, output_filename);
			break;

		case 99:
			printf("Ok, bye!");
			exit(0);

		default:
			printf("Invalid choice!\n");
			break;
	}
}

int main(void)
{
	// Invitation to dialog: compress or decompress and pick files
	printf("Hello! ");
	while (1) {
		printf("Pick an option:\n");
		menu();
	}

	return 0;
}