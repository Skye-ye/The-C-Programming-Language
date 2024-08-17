#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1048576  // 1 MB buffer

void generate_random_text(char* buffer, size_t size) {
  const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 \n";
  for (size_t i = 0; i < size; i++) {
    int key = rand() % (int)(sizeof charset - 1);
    buffer[i] = charset[key];
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <output_file> <size_in_mb>\n", argv[0]);
    return 1;
  }

  const char* filename = argv[1];
  long long size_mb = atoll(argv[2]);
  long long size_bytes = size_mb * 1024 * 1024LL;

  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  char* buffer = malloc(BUFFER_SIZE);
  if (buffer == NULL) {
    perror("Memory allocation failed");
    fclose(file);
    return 1;
  }

  long long bytes_written = 0;
  int last_progress = -1;

  srand((unsigned int)time(NULL));  // Initialize random seed

  while (bytes_written < size_bytes) {
    size_t chunk_size = (size_bytes - bytes_written < BUFFER_SIZE)
                            ? (size_t)(size_bytes - bytes_written)
                            : BUFFER_SIZE;

    generate_random_text(buffer, chunk_size);

    size_t written = fwrite(buffer, 1, chunk_size, file);
    if (written != chunk_size) {
      perror("Error writing to file");
      fclose(file);
      free(buffer);
      return 1;
    }

    bytes_written += written;

    // Update progress
    int progress = (int)((bytes_written * 100LL) / size_bytes);
    if (progress > last_progress) {
      fprintf(stderr, "\rProgress: %d%%", progress);
      fflush(stderr);
      last_progress = progress;
    }
  }

  fprintf(stderr, "\nFile generation complete.\n");
  fclose(file);
  free(buffer);
  return 0;
}