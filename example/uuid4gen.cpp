#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4623)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
#endif

#include <iostream>
#include <cstdlib>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

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
  buffer[UUID4_STR_BUFFER_SIZE - 1] = 0;

  std::cout << buffer << std::endl;

  return EXIT_SUCCESS;
}
