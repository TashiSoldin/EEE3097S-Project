/*
 * simple_buffer.c
 * Copyright  : Kyle Harper
 * License    : Follows same licensing as the lz4.c/lz4.h program at any given time.  Currently, BSD 2.
 * Description: Example program to demonstrate the basic usage of the compress/decompress functions within lz4.c/lz4.h.
 *              The functions you'll likely want are LZ4_compress_default and LZ4_decompress_safe.
 *              Both of these are documented in the lz4.h header file; I recommend reading them.
 */

/* Dependencies */
#include <stdio.h>   // For printf()
#include <string.h>  // For memcmp()
#include <stdlib.h>  // For exit()
#include "lz4.h"     // This is all that is required to expose the prototypes for basic compression and decompression.
#include <time.h>

/*
 * Simple show-error-and-bail function.
 */
void run_screaming(const char* message, const int code) {
  printf("%s \n", message);
  exit(code);
}


/*
 * main
 */
int main(void) {

  double time_spent = 0.0;
  clock_t begin = clock();
  /* Introduction */
  // Below we will have a Compression and Decompression section to demonstrate.
  // There are a few important notes before we start:
  //   1) The return codes of LZ4_ functions are important.
  //      Read lz4.h if you're unsure what a given code means.
  //   2) LZ4 uses char* pointers in all LZ4_ functions.
  //      This is baked into the API and not going to change, for consistency.
  //      If your program uses different pointer types,
  //      you may need to do some casting or set the right -Wno compiler flags to ignore those warnings (e.g.: -Wno-pointer-sign).

  /* Compression */
  // We'll store some text into a variable pointed to by *src to be compressed later.
  const char* const src = "The quick brown fox jumps over the lazy dog. Lets all be unique together until we realise we are all the same. Happiness can be found in the depths of chocolate pudding. The sudden rainstorm washed crocodiles into the ocean. It was her first experience training a rainbow unicorn. He shaved the peach to prove a point. They desperately needed another drummer since the current one only knew how to play bongos. He uses onomatopoeia as a weapon of mental destruction. Her scream silenced the rowdy teenagers. The trick to getting kids to eat anything is to put catchup on it. Don't piss in my garden and tell me you're trying to help my plants grow. Abstraction is often one floor above you. Art doesn't have to be intentional. Normal activities took extraordinary amounts of concentration at the high altitude. Edith could decide if she should paint her teeth or brush her nails. The elderly neighborhood became enraged over the coyotes who had been blamed for the poodle’s disappearance. He found a leprechaun in his walnut shell. That is an appealing treasure map that I can't read. Henry couldn't decide if he was an auto mechanic or a priest. People keep telling me orange but I still prefer pink. He went on a whiskey diet and immediately lost three days. The best part of marriage is animal crackers with peanut butter. I just wanted to tell you I could see the love you have for your child by the way you look at her. Trash covered the landscape like sprinkles do a birthday cake. If any cop asks you where you were, just say you were visiting Kansas. He was all business when he wore his clown suit. There were three sphered rocks congregating in a cubed room. The hawk didn’t understand why the ground squirrels didn’t want to be his friend. The manager of the fruit stand always sat and only sold vegetables. The view from the lighthouse excited even the most seasoned traveler. His mind was blown that there was nothing in space except space itself. The rain pelted the windshield as the darkness engulfed us. Beach-combing replaced wine tasting as his new obsession. The beach was crowded with snow leopards. Strawberries must be the one food that doesn't go well with this brand of paint. She used her own hair in the soup to give it more flavor. He felt that dining on the bridge brought romance to his relationship with his cat. In hopes of finding out the truth, he entered the one-room library. She was disgusted he couldn’t tell the difference between lemonade and limeade. Eating eggs on Thursday for choir practice was recommended. He didn’t want to go to the dentist, yet he went anyway. He took one look at what was under the table and noped the hell out of there. They wandered into a strange Tiki bar on the edge of the small beach town. Hit me with your pet shark! Malls are great places to shop; I can find everything I need under one roof. She had that tint of craziness in her soul that made her believe she could actually make a difference. Carol drank the blood as if she were a vampire. The group quickly understood that toxic waste was the most effective barrier to use against the zombies. He went back to the video to see what had been recorded and was shocked at what he saw. The bird had a belief that it was really a groundhog.";
  // The compression function needs to know how many bytes exist.  Since we're using a string, we can use strlen() + 1 (for \0).
  const int src_size = (int)(strlen(src) + 1);
  // LZ4 provides a function that will tell you the maximum size of compressed output based on input data via LZ4_compressBound().
  const int max_dst_size = LZ4_compressBound(src_size);
  // We will use that size for our destination boundary when allocating space.
  char* compressed_data = (char*)malloc((size_t)max_dst_size);
  if (compressed_data == NULL)
    run_screaming("Failed to allocate memory for *compressed_data.", 1);
  // That's all the information and preparation LZ4 needs to compress *src into* compressed_data.
  // Invoke LZ4_compress_default now with our size values and pointers to our memory locations.
  // Save the return value for error checking.
  const int compressed_data_size = LZ4_compress_default(src, compressed_data, src_size, max_dst_size);
  // Check return_value to determine what happened.
  if (compressed_data_size <= 0)
    run_screaming("A 0 or negative result from LZ4_compress_default() indicates a failure trying to compress the data. ", 1);
  if (compressed_data_size > 0)
    printf("We successfully compressed some data! Ratio: %.2f\n",
        (float) src_size/compressed_data_size);

  // Not only does a positive return_value mean success, the value returned == the number of bytes required.
  // You can use this to realloc() *compress_data to free up memory, if desired.  We'll do so just to demonstrate the concept.
  compressed_data = (char *)realloc(compressed_data, (size_t)compressed_data_size);
  if (compressed_data == NULL)
    run_screaming("Failed to re-alloc memory for compressed_data.  Sad :(", 1);

    printf("%s\n", compressed_data);
  /* Decompression */
  // Now that we've successfully compressed the information from *src to *compressed_data, let's do the opposite!
  // The decompression will need to know the compressed size, and an upper bound of the decompressed size.
  // In this example, we just re-use this information from previous section,
  // but in a real-world scenario, metadata must be transmitted to the decompression side.
  // Each implementation is in charge of this part. Oftentimes, it adds some header of its own.
  // Sometimes, the metadata can be extracted from the local context.

  // First, let's create a *new_src location of size src_size since we know that value.
  char* const regen_buffer = (char*)malloc(src_size);
  if (regen_buffer == NULL)
    run_screaming("Failed to allocate memory for *regen_buffer.", 1);
  // The LZ4_decompress_safe function needs to know where the compressed data is, how many bytes long it is,
  // where the regen_buffer memory location is, and how large regen_buffer (uncompressed) output will be.
  // Again, save the return_value.
  const int decompressed_size = LZ4_decompress_safe(compressed_data, regen_buffer, compressed_data_size, src_size);
  free(compressed_data);   /* no longer useful */
  if (decompressed_size < 0)
    run_screaming("A negative result from LZ4_decompress_safe indicates a failure trying to decompress the data.  See exit code (echo $?) for value returned.", decompressed_size);
  if (decompressed_size >= 0)
    printf("We successfully decompressed some data!\n");
  // Not only does a positive return value mean success,
  // value returned == number of bytes regenerated from compressed_data stream.
  if (decompressed_size != src_size)
    run_screaming("Decompressed data is different from original! \n", 1);

  /* Validation */
  // We should be able to compare our original *src with our *new_src and be byte-for-byte identical.
  if (memcmp(src, regen_buffer, src_size) != 0)
    run_screaming("Validation failed.  *src and *new_src are not identical.", 1);
  printf("Validation done. The string we ended up with is:\n%s\n", regen_buffer);


  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("The elapsed time is %f seconds", time_spent);

  return 0;
}
