#include <inttypes.h>

/* Error handling */

/*
 * All the functions return a pointer to the renode_error_t structure in case of an error.
 * Its memory has to be freed in case it's handled. NULL returned indicates success.
 */

#define NO_ERROR NULL

typedef enum {
    ERR_CONNECTION_FAILED,
    ERR_FATAL,
    ERR_NOT_CONNECTED,
    ERR_PERIPHERAL_INIT_FAILED,
    ERR_TIMEOUT,
    ERR_COMMAND_FAILED,
    ERR_NO_ERROR = -1,
} renode_error_code;

typedef struct {
    renode_error_code code;
    int flags;
    char *message;
    void *data;
} renode_error_t;

/* General */

// Pointers to these structs must be obtained in `X_get` functions (`connect` for renode_t)
// so that they can be later used in their related functions.
// Internals of these structs aren't part of the API.
typedef struct renode renode_t;

renode_error_t *renode_connect(const char *port, renode_t **renode);
renode_error_t *renode_disconnect(renode_t **renode);

void renode_free_error(renode_error_t *error);

/* Time control */

typedef enum {
    TU_MICROSECONDS =       1,
    TU_MILLISECONDS =    1000,
    TU_SECONDS      = 1000000,
} renode_time_unit_t;

renode_error_t *renode_run_for(renode_t *renode, renode_time_unit_t unit, uint64_t value);
renode_error_t *renode_get_current_time(renode_t *renode_instance, renode_time_unit_t unit, uint64_t *current_time);
