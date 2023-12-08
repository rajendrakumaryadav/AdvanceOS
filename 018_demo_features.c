#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

int globalVar = 0;
static int staticVar = 0;

void func() {
  int automaticVar = 0;
  volatile int volatileVar = 0;

  printf("Before longjmp:\n");
  printf("  globalVar: %d\n", globalVar);
  printf("  staticVar: %d\n", staticVar);
  printf("  automaticVar: %d\n", automaticVar);
  printf("  volatileVar: %d\n", volatileVar);

  longjmp(env, 1);

  printf("After longjmp (which should never be reached):\n");
  printf("  globalVar: %d\n", globalVar);
  printf("  staticVar: %d\n", staticVar);
  printf("  automaticVar: %d\n", automaticVar);
  printf("  volatileVar: %d\n", volatileVar);
}

int main() {
  int ret = setjmp(env);
  int automaticVar; // Declare automaticVar within main()
  volatile int volatileVar; // Declare volatileVar within main()

  if (ret == 0) {
    func();
  } else {
    printf("After setjmp:\n");
    printf("  globalVar: %d\n", globalVar);
    printf("  staticVar: %d\n", staticVar);
    printf("  automaticVar: %d (undefined)\n", automaticVar);
    printf("  volatileVar: %d\n", volatileVar);
  }

  return 0;
}
