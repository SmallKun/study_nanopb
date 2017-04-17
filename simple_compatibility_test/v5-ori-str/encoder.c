#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "simple.pb.h"

int main()
{
    uint8_t buffer_encode[128];
    size_t message_length;
    bool status;

    /* Encode our message */
    {
        SimpleMessage message = SimpleMessage_init_zero;
        pb_ostream_t stream = pb_ostream_from_buffer(buffer_encode, sizeof(buffer_encode));

        /* Fill */
        message.has_num1 = true;
        message.num1 = 14;
        message.has_num2 = true;
        message.num2 = 15;
        message.has_num3 = true;
        message.num3 = 16;
        message.has_name1 = true;
        strncpy(message.name1, "the_name1", strlen("the_name1"));

        status = pb_encode(&stream, SimpleMessage_fields, &message);
        message_length = stream.bytes_written;
        if (!status)
        {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }

        // print buffer_encode[] content
        printf("message_length:%ld\n", message_length);
        for (int i = 0; i < message_length; i++)
        {
            if (i%4 == 3)
                printf("0x%02x \n", buffer_encode[i]);
            else
                printf("0x%02x ", buffer_encode[i]);
        }
        printf("\n");
    }

    // Write to file
    FILE *pFile = fopen("data.bin", "wb");
    if (pFile == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    else
    {
        fwrite(buffer_encode, sizeof(char), message_length, pFile);
        fclose(pFile);
    }

    return 0;
}

