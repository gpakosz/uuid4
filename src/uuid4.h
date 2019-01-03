// (‑●‑●)> dual licensed under the WTFPL v2 and MIT licenses
//   without any warranty.
//   by Gregory Pakosz (@gpakosz)
// https://github.com/gpakosz/uuid4

#ifndef UUID4_H
#define UUID4_H

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#include <stdbool.h>
#endif

#ifndef UUID4_FUNCSPEC
  #define UUID4_FUNCSPEC
#endif
#ifndef UUID4_PREFIX
  #define UUID4_PREFIX(x) uuid4_##x
#endif

#ifndef UUID4_STR_BUFFER_SIZE
  #define UUID4_STR_BUFFER_SIZE (int)sizeof("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx") // y is either 8, 9, a or b
#endif

typedef uint64_t UUID4_PREFIX(state_t);
#define UUID4_STATE_T UUID4_PREFIX(state_t)

typedef union
{
  uint8_t bytes[16];
  uint32_t dwords[4];
  uint64_t qwords[2];
} UUID4_PREFIX(t);
#define UUID4_T UUID4_PREFIX(t)

/**
 * Seeds the state of the PRNG used to generate version 4 UUIDs.
 *
 * @param a pointer to a variable holding the state.
 *
 * @return `true` on success, otherwise `false`.
 */
UUID4_FUNCSPEC
void UUID4_PREFIX(seed)(UUID4_STATE_T* seed);

/**
 * Generates a version 4 UUID, see https://tools.ietf.org/html/rfc4122.
 *
 * @param state the state of the PRNG used to generate version 4 UUIDs.
 * @param out the recipient for the UUID.
 */
UUID4_FUNCSPEC
void UUID4_PREFIX(gen)(UUID4_STATE_T* state, UUID4_T* out);

/**
 * Converts a UUID to a a `NUL` terminated string.
 *
 * @param out destination buffer
 * @param capacity destination buffer capacity, must be greater or equal to
 *   `UUID4_STR_BUFFER_SIZE`.
 *
 * @return `true` on success, otherwise `false`.
 */
UUID4_FUNCSPEC
bool UUID4_PREFIX(to_s)(const UUID4_T uuid, char* out, int capacity);

#ifdef __cplusplus
}
#endif

#endif // #ifndef UUID4_H
