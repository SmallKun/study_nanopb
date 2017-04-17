#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "simple.pb.h"

int main()
{
    /* This is the buffer where we will store our message. */
    uint8_t buffer_decode[128];
    size_t message_length;
    bool status;

    /* Decode from file. */
    {
        FILE *pFile = fopen("data.bin", "rb");
        if (pFile == NULL)
        {
            printf("Error opening file, data.bin!\n");
            return 1;
        }
        else
        {
            // Get file size
            fseek(pFile, 0, SEEK_END);   // non-portable
            message_length = ftell(pFile);
            rewind(pFile);

            // Read to buffer_decode
            fread(buffer_decode, sizeof(char), message_length, pFile);
            fclose(pFile);
        }

        // Ready to decode!
        SimpleMessage message = SimpleMessage_init_zero;

        pb_istream_t stream = pb_istream_from_buffer(buffer_decode, message_length);

        status = pb_decode(&stream, SimpleMessage_fields, &message);
        if (!status)
        {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }

        /* Print the data contained in the message. */
        if (message.has_num1)
            printf("num1:%d!\n", message.num1);
        if (message.has_num2)
            printf("num2:%d!\n", message.num2);
        if (message.has_num3)
            printf("num3:%d!\n", message.num3);
        if (message.has_num4)
            printf("num4:%d!\n", message.num4);
        /* if (message.has_name) */
            /* printf("Your string was \"%s\"!\n", message.name); */

        return 0;
    }
}
