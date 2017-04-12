#ifndef _CALLBACKS_H_
#define _CALLBACKS_H_

#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>

// args struct for pb_callback_t
typedef struct _cb_arg_add_float_t
{
    int32_t total;
    float default_val;
    bool (*cb_get_val)(float*);
} cb_arg_add_float_t;
/* extern cb_arg_add_float_t cb_arg_type_1; */
/* extern cb_arg_add_float_t cb_arg_type_512; */
/* extern cb_arg_add_float_t cb_arg_type_2048; */
extern float cb_arg_next_float_val;

/* Decoding callback function for pb_callback_t
 *
 * This callback function will be called once for each float value while
 * decoding. The float value will be printed out immediately, so that
 * no memory has to be allocated for them.
 */
extern bool cb_decode_one_float_value(pb_istream_t *stream, const pb_field_t *field, void **arg);
extern bool cb_decode_ir_loader_one_float_value(pb_istream_t *stream, const pb_field_t *field, void **arg);
extern bool cb_decode_tone_match_one_float_value(pb_istream_t *stream, const pb_field_t *field, void **arg);

/* Encoding callback function for pb_callback_t
 *
 * This callback function will be called once during the encoding.
 * It will write out any number of float entries into binary without consuming
 * unnecessary memory. This is accomplished by fetching the float value one at
 * a time and encoding them immediately.
 */
extern bool cb_encode_float_values(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);
extern bool cb_encode_one_float_value(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);
extern bool cb_encode_ir_loader_float_values(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);
extern bool cb_encode_tone_match_float_values(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);

#endif // _CALLBACKS_H_

