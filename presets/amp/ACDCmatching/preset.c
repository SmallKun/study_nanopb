#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "preset.pb.h"

static uint8_t buffer_encode[30720]; // 30KB buffer
static uint8_t buffer_decode[30720]; // 30KB buffer

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
    printf("PrintPreset\n");
#if 0
    // ======== data.json ========
    printf("all_data->has_dataJson:%d\n", all_data->has_dataJson);
    if (all_data->has_dataJson)
    {
        const presets_CPresetDataJson* dataJson = &(all_data->dataJson);

        if (dataJson->has_panelStyle)
            printf("panelStyle:\"%s\"\n", dataJson->panelStyle);
        if (dataJson->has_sigPath)
        {
            printf("\t dataJson->sigPath.has_metronome:%d\n", dataJson->sigPath.has_metronome);
            if (dataJson->sigPath.has_metronome)
            {
                if (dataJson->sigPath.metronome.has_bpm)
                    printf("\t dataJson->sigPath.metronome.bpm:%u\n", dataJson->sigPath.metronome.bpm);
                if (dataJson->sigPath.metronome.has_isActive)
                    printf("\t dataJson->sigPath.metronome.isActive:%d\n", dataJson->sigPath.metronome.isActive);
            }

            printf("\t dataJson->sigPath.has_noisegate:%d\n", dataJson->sigPath.has_noisegate);
            if (dataJson->sigPath.has_noisegate)
            {
                if (dataJson->sigPath.noisegate.has_id)
                    printf("\t dataJson->sigPath.noisegate.id:\"%s\"\n", dataJson->sigPath.noisegate.id);
                if (dataJson->sigPath.noisegate.has_isActive)
                    printf("\t dataJson->sigPath.noisegate.isActive:%d\n", dataJson->sigPath.noisegate.isActive);
                if (dataJson->sigPath.noisegate.has_name)
                    printf("\t dataJson->sigPath.noisegate.name:\"%s\"\n", dataJson->sigPath.noisegate.name);
                if (dataJson->sigPath.noisegate.has_selected)
                    printf("\t dataJson->sigPath.noisegate.selected:\"%s\"\n", dataJson->sigPath.noisegate.selected);
                for (int i = 0; i < dataJson->sigPath.noisegate.params_count; i++)
                {
                    const presets_CParam* param = &dataJson->sigPath.noisegate.params[i];
                    if (param->has_id)
                        printf("\t\t param->id:%d\n", param->id);
                    if (param->has_value)
                        printf("\t\t param->value:%f\n", param->value);
                }
            }

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
                    for (int i = 0; i < item->params_count; i++)
                    {
                        const presets_CParam* param = &(item->params[i]);
                        if (param->has_id)
                            printf("\t\t param->id:%d\n", param->id);
                        if (param->has_value)
                            printf("\t\t param->value:%f\n", param->value);
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
        if (templateJson->has_Box)
            printf("Box:\"%s\"\n", templateJson->Box);
        if (templateJson->has_Control)
            printf("Control:\"%s\"\n", templateJson->Control);
        if (templateJson->has_Texture)
            printf("Texture:\"%s\"\n", templateJson->Texture);
        if (templateJson->has_fontFamily)
            printf("fontFamily:\"%s\"\n", templateJson->fontFamily);
        if (templateJson->has_panelStyle)
            printf("panelStyle:\"%s\"\n", templateJson->panelStyle);
        if (templateJson->has_showsKnobs)
            printf("showsKnobs:%d\n", templateJson->showsKnobs);
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
#endif
}

void PreparePresetContent(presets_CPresetAllData* all_data)
{
    // ======== data.json ========
#if 1
    all_data->has_dataJson = false;
#else
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
        for (int i = 0; i < item->params_count; i++)
        {
            presets_CParam* param = &item->params[i];
            param->has_id = true;
            param->id = i;
            param->value_count = 1;
            param->value[0] = 0.0020000000949949026;
        }
    }

    // special section for "bias.IRLoader", idx = 5
    presets_CSigPath_CBlocks_CItem* irLoader_item = &dataJson->sigPath.blocks.items[5];
    irLoader_item->has_wavBitDepth = true;
    irLoader_item->wavBitDepth = 24;
    irLoader_item->has_wavFileName = true;
    strncpy(irLoader_item->wavFileName, "bias.toneMatching", strlen("bias.toneMatching"));
    irLoader_item->has_wavSampleRate = true;
    irLoader_item->wavSampleRate = 44100;
    // "bias.IRLoader"'s params id 8 have 2048 values, so add additional 2047 params
    presets_CParam* irLoader_param_8 = &irLoader_item->params[8];
    irLoader_param_8->value_count = 2048;
    for (int i = 0; i < 2047; i++)
    {
        irLoader_param_8->value[i] = -1.6570091247558594e-05;
    }

    // special section for "bias.toneMatching", idx = 7
    presets_CSigPath_CBlocks_CItem* toneMatch_item = &dataJson->sigPath.blocks.items[7];
    toneMatch_item->has_IsAudioRouting = true;
    toneMatch_item->IsAudioRouting = false;
    // "bias.toneMatching"'s params id 0 have 2048 values, so add additional 2047 params
    presets_CParam* toneMatch_param_0 = &toneMatch_item->params[0];
    toneMatch_param_0->value_count = 2048;
    for (int i = 0; i < 2047; i++)
    {
        toneMatch_param_0->value[i] = 7.163822010625154e-05;
    }
#endif
    // ===========================

    // ======== meta.json ========
#if 1
    all_data->has_metaJson = false;
#else
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
#endif
    // ===========================

    // ======== template.json ========
#if 1
    all_data->has_templateJson = false;
#else
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
#endif
    // ===========================
}

int main()
{
    /* This is the buffer where we will store our message. */
    size_t message_length;
    bool status;

    message_length = 0;
    status = false;
    memset(buffer_decode, 0, sizeof(buffer_decode));
    memset(buffer_encode, 0, sizeof(buffer_encode));
#if 1
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
    #if 1
        #if 1
        presets_CPresetAllData encode_msg = presets_CPresetAllData_init_zero;
        /* presets_CPresetAllData encode_msg = presets_CPresetAllData_init_default; */
        /* presets_CPresetAllData encode_msg; */

        #else
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
        #endif
    #endif
    }
#endif

    /* Now we could transmit the encode_msg over network, store it in a file or
     * wrap it to a pigeon's leg.
     */

#if 0
    /* But because we are lazy, we will just decode it immediately. */
    {
        /* Allocate space for the message. */
        memset(buffer_decode, 0, sizeof(buffer_decode));
        memcpy(&buffer_decode, &buffer_encode, message_length);

        /* Create a stream that reads from the buffer. */
        pb_istream_t stream = pb_istream_from_buffer(buffer_decode, message_length);

        /* Now we are ready to decode the decode_msg. */
        presets_CPresetAllData decode_msg = presets_CPresetAllData_init_zero;
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
#endif

    return 0;
}

