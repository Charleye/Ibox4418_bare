#ifndef _S5P4418_KEY_H_
#define _S5P4418_KEY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef enum {
    KEY_NAME_UP     = 0x01 << 0,
    KEY_NAME_DOWN   = 0x01 << 1
}key_name_t;

void key_init(void);
u32_t get_key_status(u32_t *key);
u32_t get_key_event(u32_t *keyup, u32_t *keydown);

#ifdef __cplusplus
}
#endif

#endif /* _S5P4418_KEY_H_ */
