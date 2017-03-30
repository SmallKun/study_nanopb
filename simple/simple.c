#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "simple.pb.h"

int main()
{
    /* This is the buffer where we will store our message. */
    uint8_t buffer[128];
    size_t message_length;
    bool status;
    char* name_default = "abcdefghij";
    
    /* Encode our message */
    {
        /* Allocate space on the stack to store the message data.
         *
         * Nanopb generates simple struct definitions for all the messages.
         * - check out the contents of simple.pb.h!
         * It is a good idea to always initialize your structures
         * so that you do not have garbage data from RAM in there.
         */
        SimpleMessage message = SimpleMessage_init_zero;
        
        /* Create a stream that will write to our buffer. */
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
        
        /* Fill in the lucky number */
        message.lucky_number = 13;
        printf("strlen(name_default): %ld, \"%s\"\n", strlen(name_default), name_default);
        strncpy(message.name, name_default, strlen(name_default));
        printf("strlen(message.name): %ld, \"%s\"\n", strlen(message.name), message.name);
        
        /* Now we are ready to encode the message! */
        status = pb_encode(&stream, SimpleMessage_fields, &message);
        message_length = stream.bytes_written;
        
        /* Then just check for any errors.. */
        if (!status)
        {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }

        // print buffer[] content
        printf("message_length:%ld\n", message_length);
        for (int i = 0; i < message_length; i++)
        {
            if (i%4 == 3)
                printf("0x%02x \n", buffer[i]);
            else
                printf("0x%02x ", buffer[i]);
        }
        printf("\n");
    }
    
    /* Now we could transmit the message over network, store it in a file or
     * wrap it to a pigeon's leg.
     */

    /* But because we are lazy, we will just decode it immediately. */
    
    {
        /* Allocate space for the decoded message. */
        SimpleMessage message = SimpleMessage_init_zero;
        
        /* Create a stream that reads from the buffer. */
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        
        /* Now we are ready to decode the message. */
        status = pb_decode(&stream, SimpleMessage_fields, &message);
        
        /* Check for errors... */
        if (!status)
        {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
        
        /* Print the data contained in the message. */
        printf("Your lucky number was %d!\n", message.lucky_number);
        printf("Your string was %s!\n", message.name);
    }
    
    return 0;
}

