#include "callbacks.h"

/* cb_arg_add_float_t cb_arg_type_1 = {1, 0.001, gen_float_val}; */
/* cb_arg_add_float_t cb_arg_type_512 = {512, 0.005, gen_float_val}; */
/* cb_arg_add_float_t cb_arg_type_2048 = {2048, 7.025, gen_float_val}; */
float cb_arg_next_float_val = 0.33333;

/* Callback function for pb_callback_t
 * This callback function will be called once for each float value while
 * decoding. The float value will be printed out immediately, so that
 * no memory has to be allocated for them.
 */
bool cb_decode_one_float_value(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    // for extracting 'repeated float value'

    float val = 0.0;

    if (!pb_decode_fixed32(stream, &val))
    {
        printf("pb_decode_fixed32 failed\n");
        return false;
    }

    printf("\t\t\t general_one_float:[%f]\n", val);

    return true;
}

bool cb_decode_ir_loader_one_float_value(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    // for extracting 'repeated float value'

    float val = 0.0;

    if (!pb_decode_fixed32(stream, &val))
    {
        printf("pb_decode_fixed32 failed\n");
        return false;
    }

    printf("\t\t\t ir_loader:[%f]\n", val);

    return true;
}

bool cb_decode_tone_match_one_float_value(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    // for extracting 'repeated float value'

    float val = 0.0;

    if (!pb_decode_fixed32(stream, &val))
    {
        printf("pb_decode_fixed32 failed\n");
        return false;
    }

    printf("\t\t\t tone_match:[%f]\n", val);

    return true;
}

bool cb_encode_float_values(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
    // for adding 'repeated float value'

    float next_val = 0.0;
    cb_arg_add_float_t *p_arg = (cb_arg_add_float_t*) *arg;

    /* printf("p_arg->total:%d\n", p_arg->total); */
    for (int i = 0; i < p_arg->total; i++)
    {
        // Update new value
    #if 1
        if (p_arg->cb_get_val)
        {
            bool success = false;
            success = p_arg->cb_get_val(&next_val);
        }
    #else
        next_val = p_arg->default_val;
    #endif
        /* printf("\t cb_encoding[%d]:%f\n", i, next_val); */

        /* This encodes the header for the field, based on the constant info
         * from pb_field_t. */
        if (!pb_encode_tag(stream, PB_WT_32BIT, field->tag))
        {
            printf("pb_encode_tag failed\n");
            return false;
        }

        /* This encodes the data for the field. */
        if (!pb_encode_fixed32(stream, &next_val))
        {
            printf("pb_encode_fixed32 failed\n");
            return false;
        }
    }

    return true;
}

bool cb_encode_one_float_value(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
    // for adding 'optional float value'

    if (NULL == *arg)
    {
        printf("cb_encode_one_float_value no arg error!\n");
        return false;
    }

    float *val = (float*) *arg;
    float next_val = *val;
    printf("\t cb_encode_one_float_value:%f\n", next_val);

    /* This encodes the header for the field, based on the constant info
     * from pb_field_t. */
    if (!pb_encode_tag(stream, PB_WT_32BIT, field->tag))
    {
        printf("pb_encode_tag failed\n");
        return false;
    }

    /* This encodes the data for the field. */
    if (!pb_encode_fixed32(stream, &next_val))
    {
        printf("pb_encode_fixed32 failed\n");
        return false;
    }

    return true;
}

bool cb_encode_ir_loader_float_values(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
    // for adding 'repeated float value'

    float next_val = -1.6570091247558594e-05;

    for (int i = 0; i < 2048; i++)
    {
        if (!pb_encode_tag(stream, PB_WT_32BIT, field->tag))
        {
            printf("pb_encode_tag failed\n");
            return false;
        }

        if (!pb_encode_fixed32(stream, &next_val))
        {
            printf("pb_encode_fixed32 failed\n");
            return false;
        }
    }

    return true;
}

bool cb_encode_tone_match_float_values(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
    // for adding 'repeated float value'

    float next_val = 7.163822010625154e-05;

    for (int i = 0; i < 2048; i++)
    {
        if (!pb_encode_tag(stream, PB_WT_32BIT, field->tag))
        {
            printf("pb_encode_tag failed\n");
            return false;
        }

        if (!pb_encode_fixed32(stream, &next_val))
        {
            printf("pb_encode_fixed32 failed\n");
            return false;
        }
    }

    return true;
}

