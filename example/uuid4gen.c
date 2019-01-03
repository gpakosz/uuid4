#include <stdlib.h>
#include <stdio.h>

#include <uuid4.h>

int main()
{
  UUID4_STATE_T state;
  UUID4_T uuid;

  uuid4_seed(&state);
  uuid4_gen(&state, &uuid);

  char buffer[UUID4_STR_BUFFER_SIZE];
  if (!uuid4_to_s(uuid, buffer, sizeof(buffer)))
    exit(EXIT_FAILURE);

  printf("%s\n", buffer);

  return EXIT_SUCCESS;
}
