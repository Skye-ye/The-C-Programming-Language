#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

double measure_time(char* program, char* input_file) {
  clock_t start, end;
  pid_t pid;
  int status;

  start = clock();
  pid = fork();

  if (pid == 0) {                       // Child process
    freopen("/dev/null", "w", stdout);  // Redirect stdout to /dev/null
    execl(program, program, input_file, NULL);
    perror("execl");
    exit(1);
  } else if (pid > 0) {  // Parent process
    waitpid(pid, &status, 0);
    end = clock();
  } else {
    perror("fork");
    exit(1);
  }

  return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  char* input_file = argv[1];
  double time_high_level, time_low_level;

  // Run low-level implementation first
  time_low_level = measure_time("./cat_low_level", input_file);
  time_high_level = measure_time("./cat_high_level", input_file);

  printf("Low-level implementation time: %.6f seconds\n", time_low_level);
  printf("High-level implementation time: %.6f seconds\n", time_high_level);

  double speedup = (time_high_level / time_low_level - 1) * 100;
  printf(
      "The low-level implementation is %.2f%% %s than the high-level "
      "implementation.\n",
      fabs(speedup), speedup > 0 ? "faster" : "slower");

  return 0;
}