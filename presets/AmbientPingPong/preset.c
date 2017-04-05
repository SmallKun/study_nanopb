#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "preset.pb.h"

static uint8_t buffer_encode[2048];
static uint8_t buffer_decode[2048];

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

void PrintPreset(const presets_CPresetDataJson* decode_msg)
{
    printf("has_panelStyle:%d\n", decode_msg->has_panelStyle);
    printf("panelStyle:\"%s\"\n", decode_msg->panelStyle);
    printf("has_sigPath:%d\n", decode_msg->has_sigPath);
    printf("\t decode_msg->sigPath.has_metronome:%d\n", decode_msg->sigPath.has_metronome);
    printf("\t decode_msg->sigPath.metronome.has_bpm:%d\n", decode_msg->sigPath.metronome.has_bpm);
    printf("\t decode_msg->sigPath.metronome.bpm:%u\n", decode_msg->sigPath.metronome.bpm);
    printf("\t decode_msg->sigPath.metronome.has_isActive:%d\n", decode_msg->sigPath.metronome.has_isActive);
    printf("\t decode_msg->sigPath.metronome.isActive:%d\n", decode_msg->sigPath.metronome.isActive);

    printf("\t decode_msg->sigPath.has_noisegate:%d\n", decode_msg->sigPath.has_noisegate);
    printf("\t decode_msg->sigPath.noisegate.has_id:%d\n", decode_msg->sigPath.noisegate.has_id);
    printf("\t decode_msg->sigPath.noisegate.id:\"%s\"\n", decode_msg->sigPath.noisegate.id);
    printf("\t decode_msg->sigPath.noisegate.has_isActive:%d\n", decode_msg->sigPath.noisegate.has_isActive);
    printf("\t decode_msg->sigPath.noisegate.isActive:%d\n", decode_msg->sigPath.noisegate.isActive);
    printf("\t decode_msg->sigPath.noisegate.has_name:%d\n", decode_msg->sigPath.noisegate.has_name);
    printf("\t decode_msg->sigPath.noisegate.name:\"%s\"\n", decode_msg->sigPath.noisegate.name);
    printf("\t decode_msg->sigPath.noisegate.has_selected:%d\n", decode_msg->sigPath.noisegate.has_selected);
    printf("\t decode_msg->sigPath.noisegate.selected:\"%s\"\n", decode_msg->sigPath.noisegate.selected);
    for (int i = 0; i < decode_msg->sigPath.noisegate.params_count; i++)
    {
        const presets_CParam* param = &decode_msg->sigPath.noisegate.params[i];
        printf("\t\t param->has_id:%d\n", param->has_id);
        printf("\t\t param->id:%d\n", param->id);
        printf("\t\t param->has_value:%d\n", param->has_value);
        printf("\t\t param->value:%f\n", param->value);
    }

    printf("\t decode_msg->sigPath.has_blocks:%d\n", decode_msg->sigPath.has_blocks);
    printf("\t decode_msg->sigPath.blocks.items_count:%d\n", decode_msg->sigPath.blocks.items_count);
    for (int i = 0; i < decode_msg->sigPath.blocks.items_count; i++)
    {
        const presets_CSigPath_CBlocks_CItem* item = &decode_msg->sigPath.blocks.items[i];
        printf("\t item[%d]\n", i);
        printf("\t item->has_id:%d\n", item->has_id);
        printf("\t item->id:\"%s\"\n", item->id);
        printf("\t item->has_isActive:%d\n", item->has_isActive);
        printf("\t item->isActive:%d\n", item->isActive);
        printf("\t item->has_name:%d\n", item->has_name);
        printf("\t item->name:\"%s\"\n", item->name);
        printf("\t item->has_selected:%d\n", item->has_selected);
        printf("\t item->selected:\"%s\"\n", item->selected);
        for (int i = 0; i < item->params_count; i++)
        {
            const presets_CParam* param = &(item->params[i]);
            printf("\t\t param->has_id:%d\n", param->has_id);
            printf("\t\t param->id:%d\n", param->id);
            printf("\t\t param->has_value:%d\n", param->has_value);
            printf("\t\t param->value:%f\n", param->value);
        }
    }
}

void PreparePresetContent(presets_CPresetDataJson* encode_msg)
{
    encode_msg->has_panelStyle = true;
    strncpy(encode_msg->panelStyle, "HorizontalTypeHagibis", strlen("HorizontalTypeHagibis"));

    encode_msg->has_sigPath = true;

    // Fill metronome fields
    encode_msg->sigPath.has_metronome = true;
    encode_msg->sigPath.metronome.has_bpm = true;
    encode_msg->sigPath.metronome.bpm = 120;
    encode_msg->sigPath.metronome.has_isActive = true;
    encode_msg->sigPath.metronome.isActive = true;

    // Fill noisegate fields
    encode_msg->sigPath.has_noisegate = true;
    encode_msg->sigPath.noisegate.has_id = true;
    strncpy(encode_msg->sigPath.noisegate.id, "", strlen(""));
    encode_msg->sigPath.noisegate.has_isActive = true;
    encode_msg->sigPath.noisegate.isActive = true;
    encode_msg->sigPath.noisegate.has_name = true;
    strncpy(encode_msg->sigPath.noisegate.name, "Untitled", strlen("Untitled"));
    encode_msg->sigPath.noisegate.has_selected = true;
    strncpy(encode_msg->sigPath.noisegate.selected, "", strlen(""));
    encode_msg->sigPath.noisegate.params_count = 3;
    for (int i = 0; i < encode_msg->sigPath.noisegate.params_count; i++)
    {
        presets_CParam* param = &encode_msg->sigPath.noisegate.params[i];
        param->has_id = true;
        param->id = i;
        param->has_value = true;
        param->value = 0.30000001192092896;
    }

    // Fill blocks fields
    encode_msg->sigPath.has_blocks = true;
    encode_msg->sigPath.blocks.items_count = 5;
    for (int i = 0; i < encode_msg->sigPath.blocks.items_count; i++)
    {
        presets_CSigPath_CBlocks_CItem* item = &encode_msg->sigPath.blocks.items[i];
        item->has_id = true;
        strncpy(item->id, "bias.pingpongDelay", strlen("bias.pingpongDelay"));
        item->has_isActive = true;
        item->isActive = true;
        item->has_name = true;
        strncpy(item->name, "Untitled", strlen("Untitled"));
        item->has_selected = true;
        strncpy(item->selected, "false", strlen("false"));
        item->params_count = 15;
        for (int i = 0; i < item->params_count; i++)
        {
            presets_CParam* param = &item->params[i];
            param->has_id = true;
            param->id = i;
            param->has_value = true;
            param->value = 0.0020000000949949026;
        }
    }
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
        presets_CPresetDataJson encode_msg = presets_CPresetDataJson_init_zero;
        /* Fill in the message */
        PreparePresetContent(&encode_msg);

        /* Now we are ready to encode the message! */
        status = pb_encode(&stream, presets_CPresetDataJson_fields, &encode_msg);
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
        presets_CPresetDataJson decode_msg = presets_CPresetDataJson_init_zero;
        status = pb_decode(&stream, presets_CPresetDataJson_fields, &decode_msg);

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

