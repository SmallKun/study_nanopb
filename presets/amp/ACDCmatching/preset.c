#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "preset.pb.h"

// ********************************** IMPORTANT **********************************
// We found nanopb can't have too large float array inside *.pb.h, application
// will crash during initialization, we should use nanopb's pb_callback_t for
// large array/message instead
// *******************************************************************************
/* #define MAX_FLOAT_ARRAY_SIZE (2048) */
/* #define MAX_FLOAT_ARRAY_SIZE (512) */
/* #define MAX_FLOAT_ARRAY_SIZE (128) */

// ********************************** IMPORTANT **********************************
// If you encounter "stream full" errors during encoding, please increase these 
// buffer sizes!
// *******************************************************************************
#define ENCODE_DECODE_BUFFER_SIZE (30 * 1024) // 30 KB buffer
static uint8_t buffer_encode[ENCODE_DECODE_BUFFER_SIZE];
static uint8_t buffer_decode[ENCODE_DECODE_BUFFER_SIZE];

void hexDump(char *desc, void *addr, int len)
{
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}

void PrintPreset(const presets_CPresetAllData* all_data)
{
    printf("%s\n", __FUNCTION__);

    // ======== data.json ========
    printf("all_data->has_dataJson:%d\n", all_data->has_dataJson);
    if (all_data->has_dataJson)
    {
        const presets_CPresetDataJson* dataJson = &(all_data->dataJson);

        if (dataJson->has_sigPath)
        {
            printf("\t dataJson->sigPath.has_blocks:%d\n", dataJson->sigPath.has_blocks);
            if (dataJson->sigPath.has_blocks)
            {
                for (int i = 0; i < dataJson->sigPath.blocks.items_count; i++)
                {
                    const presets_CSigPath_CBlocks_CItem* item = &dataJson->sigPath.blocks.items[i];
                    printf("\t item[%d]\n", i);
                    if (item->has_id)
                        printf("\t item->id:\"%s\"\n", item->id);
                    if (item->has_isActive)
                        printf("\t item->isActive:%d\n", item->isActive);
                    if (item->has_name)
                        printf("\t item->name:\"%s\"\n", item->name);
                    if (item->has_selected)
                        printf("\t item->selected:\"%s\"\n", item->selected);
                    if (item->has_wavBitDepth)
                        printf("\t item->wavBitDepth:%d\n", item->wavBitDepth);
                    if (item->has_wavFileName)
                        printf("\t item->wavFileName:\"%s\"\n", item->wavFileName);
                    if (item->has_wavSampleRate)
                        printf("\t item->wavSampleRate:%d\n", item->wavSampleRate);
                    if (item->has_IsAudioRouting)
                        printf("\t item->IsAudioRouting:%d\n", item->IsAudioRouting);
                    for (int j = 0; j < item->params_count; j++)
                    {
                        const presets_CParam* param = &(item->params[j]);
                        if (param->has_id)
                            printf("\t\t param->id:%d\n", param->id);

                        // ********************************** IMPORTANT **********************************
                        // param->value will be printed in callback function cb_decode_one_float_value
                        // *******************************************************************************
                    #if 0
                        for (int k = 0; k < param->value_count; k++)
                        {
                            printf("\t\t\t value[%d]:%f\n", k, param->value[k]);
                        }
                    #endif
                    }
                }
            }
        }
    }
    // ===========================

    // ======== meta.json ========
    printf("all_data->has_metaJson:%d\n", all_data->has_metaJson);
    if (all_data->has_metaJson)
    {
        const presets_CPresetMetaJson* metaJson = &(all_data->metaJson);

        if (metaJson->has_category)
            printf("category:\"%s\"\n", metaJson->category);
        if (metaJson->has_description)
            printf("description:\"%s\"\n", metaJson->description);
        if (metaJson->has_displayName)
            printf("displayName:\"%s\"\n", metaJson->displayName);
        if (metaJson->has_id)
            printf("id:\"%s\"\n", metaJson->id);
        if (metaJson->has_version)
            printf("version:\"%s\"\n", metaJson->version);
        for (int i = 0; i < metaJson->features_count; i++)
        {
            printf("\t metaJson->features[%d]:%d\n", i, metaJson->features[i]);
        }
    }
    // ===========================

    // ======== template.json ========
    printf("all_data->has_templateJson:%d\n", all_data->has_templateJson);
    if (all_data->has_templateJson)
    {
        const presets_CPresetTemplateJson* templateJson = &(all_data->templateJson);
        if (templateJson->has_brand)
            printf("brand:\"%s\"\n", templateJson->brand);
        if (templateJson->has_case_material)
            printf("case_material:\"%s\"\n", templateJson->case_material);
        if (templateJson->has_corner)
            printf("corner:\"%s\"\n", templateJson->corner);
        if (templateJson->has_cover)
            printf("cover:\"%s\"\n", templateJson->cover);
        if (templateJson->has_handler)
            printf("handler:\"%s\"\n", templateJson->handler);
        if (templateJson->has_panel)
            printf("panel:\"%s\"\n", templateJson->panel);
        if (templateJson->has_templateId)
            printf("templateId:\"%s\"\n", templateJson->templateId);
        if (templateJson->has_elements)
        {
            for (int i = 0; i < templateJson->elements.items_count; i++)
            {
                printf("\t item[%d]\n", i);

                const presets_CPresetTemplateJson_CElements_CItem* item = &(templateJson->elements.items[i]);
                if (item->has_paramID)
                    printf("\t paramID:\"%s\"\n", item->paramID);
                if (item->has_position)
                    printf("\t position:\"%s\"\n", item->position);
                if (item->has_res)
                    printf("\t res:\"%s\"\n", item->res);
                if (item->has_type)
                    printf("\t type:\"%s\"\n", item->type);

                for (int j = 0; j < item->indexID_count; j++)
                {
                    printf("\t\t indexID[%d][0]:\"%s\"\n", j, &(item->indexID[j][0]));
                }
            }
        }
    }
    // ===========================
}

#if 0 // float values generator
static const float firstFloat = 0.0020000000949949026;
static const float floatDiff = 0.001;
static float next_float_val(bool reset)
{
    static float next = firstFloat;
    if (reset)
    {
        next = firstFloat;
        return next;
    }

    next += floatDiff;

    return next;
}

static bool gen_float_val(float* ret)
{
    static uint32_t idx = 0;
    float next = 0;

    if (idx == 4096)
    {
        idx = 0;
        next = next_float_val(true);
        *ret = next;

        return false;
    }
    else
    {
        idx++;
        next = next_float_val(false);
        *ret = next;

        return true;
    }
}
#endif // float values generator

// args struct for pb_callback_t
typedef struct _cb_arg_add_float_t
{
    int32_t total;
    float default_val;
    bool (*cb_get_val)(float*);
} cb_arg_add_float_t;
/* static cb_arg_add_float_t cb_arg_type_1 = {1, 0.001, gen_float_val}; */
/* static cb_arg_add_float_t cb_arg_type_512 = {512, 0.005, gen_float_val}; */
/* static cb_arg_add_float_t cb_arg_type_2048 = {2048, 7.025, gen_float_val}; */
static float cb_arg_next_float_val = 0.33333;

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

/* Callback function for pb_callback_t
 * This callback function will be called once during the encoding.
 * It will write out any number of float entries into binary without consuming
 * unnecessary memory. This is accomplished by fetching the float value one at
 * a time and encoding them immediately.
 */
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

void PreparePresetContent(presets_CPresetAllData* all_data)
{
    // ======== data.json ========
    all_data->has_dataJson = true;
    presets_CPresetDataJson* dataJson = &(all_data->dataJson);

    // Fill blocks fields
    dataJson->has_sigPath = true;
    dataJson->sigPath.has_blocks = true;
    dataJson->sigPath.blocks.items_count = 8;
    for (int i = 0; i < dataJson->sigPath.blocks.items_count; i++)
    {
        presets_CSigPath_CBlocks_CItem* item = &dataJson->sigPath.blocks.items[i];
        item->has_id = true;
        strncpy(item->id, "bias.toneMatching", strlen("bias.toneMatching"));
        item->has_isActive = true;
        item->isActive = true;
        item->has_name = true;
        strncpy(item->name, "Low cut high boost", strlen("Low cut high boost"));
        item->has_selected = true;
        strncpy(item->selected, "false", strlen("false"));

        item->params_count = 34;
        for (int j = 0; j < item->params_count; j++)
        {
            printf("@@@@@@@ param[%d,%d] @@\n", i, j);
            presets_CParam* param = &item->params[j];
            param->has_id = true;
            param->id = j;

            // ********************************** IMPORTANT **********************************
            // param->value will be encoded in callback function cb_encode_float_values
            // *******************************************************************************
        #if 0
            param->value.funcs.encode = &cb_encode_float_values;
            param->value.arg = &cb_arg_type_1;
            /* param->value.arg = &cb_arg_type_512; */
        #else
            param->value.funcs.encode = &cb_encode_one_float_value;
            param->value.arg = &cb_arg_next_float_val;
        #endif
        }
    }

    // special section for "bias.IRLoader", idx = 5
    presets_CSigPath_CBlocks_CItem* irLoader_item = &dataJson->sigPath.blocks.items[5];
    irLoader_item->has_wavBitDepth = true;
    irLoader_item->wavBitDepth = 24;
    irLoader_item->has_wavFileName = true;
    strncpy(irLoader_item->wavFileName, "55661234455590345", strlen("55661234455590345"));
    irLoader_item->has_wavSampleRate = true;
    irLoader_item->wavSampleRate = 44100;
    // "bias.IRLoader"'s params id 8 have 2048 values, so add additional 2047 params
    // Note : Since FW limitation, we only need the first 512 float been encoded into binary
    presets_CParam* irLoader_param_8 = &irLoader_item->params[8];
    irLoader_param_8->value.funcs.encode = &cb_encode_ir_loader_float_values;
    irLoader_param_8->value.arg = NULL;

    // special section for "bias.toneMatching", idx = 7
    presets_CSigPath_CBlocks_CItem* toneMatch_item = &dataJson->sigPath.blocks.items[7];
    toneMatch_item->has_IsAudioRouting = true;
    toneMatch_item->IsAudioRouting = false;
    // "bias.toneMatching"'s params id 0 have 2048 values, so add additional 2047 params
    // Note : Since FW limitation, we only need the first 512 float been encoded into binary
    presets_CParam* toneMatch_param_0 = &toneMatch_item->params[0];
    toneMatch_param_0->value.funcs.encode = &cb_encode_tone_match_float_values;
    toneMatch_param_0->value.arg = NULL;
    // ===========================

    // ======== meta.json ========
    all_data->has_metaJson = true;

    presets_CPresetMetaJson* metaJson = &(all_data->metaJson);
    metaJson->has_category = true;
    strncpy(metaJson->category, "Crunch", strlen("Crunch"));
    metaJson->has_description = true;
    strncpy(metaJson->description, "description for ac dc macthing", strlen("description for ac dc macthing"));
    metaJson->has_displayName = true;
    strncpy(metaJson->displayName, "AC DC matching", strlen("AC DC matching"));
    metaJson->has_id = true;
    strncpy(metaJson->id, "B6C43C9D-6A96-9A0D-35A2-9F46E77D34A3", strlen("B6C43C9D-6A96-9A0D-35A2-9F46E77D34A3"));
    metaJson->has_version = true;
    strncpy(metaJson->version, "1.4", strlen("1.4"));
    // ===========================

    // ======== template.json ========
    all_data->has_templateJson = true;

    presets_CPresetTemplateJson* templateJson = &(all_data->templateJson);

    templateJson->has_brand = true;
    strncpy(templateJson->brand, "Plexiglas", strlen("Plexiglas"));
    templateJson->has_case_material = true;
    strncpy(templateJson->case_material, "case_material_Plexiglas.png", strlen("case_material_Plexiglas.png"));
    templateJson->has_corner = true;
    strncpy(templateJson->corner, "corner_5153.png", strlen("corner_5153.png"));
    templateJson->has_cover = true;
    strncpy(templateJson->cover, "cover_Plexiglas.png", strlen("cover_Plexiglas.png"));
    templateJson->has_handler = true;
    strncpy(templateJson->handler, "handler_5153.png", strlen("handler_5153.png"));
    templateJson->has_panel = true;
    strncpy(templateJson->panel, "panel_Plexiglas.png", strlen("panel_Plexiglas.png"));
    templateJson->has_templateId = true;
    strncpy(templateJson->templateId, "", strlen(""));

    templateJson->has_elements = true;
    templateJson->elements.items_count = 6;
    for (int i = 0; i < templateJson->elements.items_count; i++)
    {
        presets_CPresetTemplateJson_CElements_CItem* item = &(templateJson->elements.items[i]);
        item->has_paramID = true;
        strncpy(item->paramID, "4", strlen("4"));
        item->has_position = true;
        strncpy(item->position, "52,170,173,173", strlen("52,170,173,173"));
        item->has_res = true;
        strncpy(item->res, "MarshallGolden", strlen("MarshallGolden"));
        item->has_type = true;
        strncpy(item->type, "knob", strlen("knob"));

        item->indexID_count = 1;
        for (int j = 0; j < item->indexID_count; j++)
        {
            strncpy(&(item->indexID[j][0]), "bias.glassypreamp", strlen("bias.glassypreamp"));
        }
    }
    // ===========================
}

int main()
{
    /* This is the buffer where we will store our message. */
    size_t message_length;
    bool status;

    /* Encode our message */
    {
        /* Create a stream that will write to our buffer. */
        memset(buffer_encode, 0, sizeof(buffer_encode));
        pb_ostream_t stream = pb_ostream_from_buffer(buffer_encode, sizeof(buffer_encode));

        /* Allocate space on the stack to store the message data.
         *
         * Nanopb generates simple struct definitions for all the messages.
         * - check out the contents of preset.pb.h!
         * It is a good idea to always initialize your structures
         * so that you do not have garbage data from RAM in there.
         */
        presets_CPresetAllData encode_msg = presets_CPresetAllData_init_zero;
        /* Fill in the message */
        PreparePresetContent(&encode_msg);

        /* Now we are ready to encode the message! */
        status = pb_encode(&stream, presets_CPresetAllData_fields, &encode_msg);
        /* Then just check for any errors.. */
        if (!status)
        {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }

        // Get encoding length
        message_length = stream.bytes_written;
        printf("message_length:%ld\n", message_length);

        // print buffer_encode[] content
        hexDump("buffer_encode[]", buffer_encode, message_length);
    }

    /* Now we could transmit the encode_msg over network, store it in a file or
     * wrap it to a pigeon's leg.
     */

    /* But because we are lazy, we will just decode it immediately. */
    {
        /* Allocate space for the message. */
        memset(buffer_decode, 0, sizeof(buffer_decode));
        memcpy(&buffer_decode, &buffer_encode, message_length);

        /* Create a stream that reads from the buffer. */
        pb_istream_t stream = pb_istream_from_buffer(buffer_decode, message_length);

        /* Now we are ready to decode the decode_msg. */
        presets_CPresetAllData decode_msg = presets_CPresetAllData_init_zero;

        /* Give a pointer to our callback function, which will handle the
         * float values as they arrive. */
        // ------------------------------------------------------
        printf("set default decoder cb(s)\n");
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                decode_msg.dataJson.sigPath.blocks.items[i].params[j].value.funcs.decode = &cb_decode_one_float_value;
            }
        }
        printf("set default decoder cb(s) done\n");
        printf("set ir_loader and tone_match decoder cb(s)\n");
        decode_msg.dataJson.sigPath.blocks.items[5].params[8].value.funcs.decode = &cb_decode_ir_loader_one_float_value;
        decode_msg.dataJson.sigPath.blocks.items[7].params[0].value.funcs.decode = &cb_decode_tone_match_one_float_value;
        printf("set ir_loader and tone_match decoder cb(s) done\n");
        // ------------------------------------------------------

        status = pb_decode(&stream, presets_CPresetAllData_fields, &decode_msg);
        /* Check for errors... */
        if (!status)
        {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }

        /* Print the data contained in the decode_msg. */
        PrintPreset(&decode_msg);
    }

    return 0;
}

