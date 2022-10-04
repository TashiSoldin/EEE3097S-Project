#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{

    double time_spent = 0.0;
    clock_t begin = clock();


    char str[4000] = "He appeared to be confusingly perplexed. The chic gangster liked to start the day with a pink scarf. The fifty mannequin heads floating in the pool kind of freaked them out. A quiet house is nice until you are ordered to stay in it for months. The stench from the feedlot permeated the car despite having the air conditioning on recycled air. Wisdom is easily acquired when hiding under the bed with a saucepan on your head. He was disappointed when he found the beach to be so sandy and the sun so sunny. That is an appealing treasure map that I can't read. He would only survive if he kept the fire going and he could hear thunder in the distance. She lived on Monkey Jungle Road and that seemed to explain all of her strangeness. At that moment I was the most fearsome weasel in the entire swamp. Abstraction is often one floor above you. It turns out you don't need all that stuff you insisted you did. She wondered what his eyes were saying beneath his mirrored sunglasses. After exploring the abandoned building, he started to believe in ghosts. She found it strange that people use their cellphones to actually talk to one another. He strives to keep the best lawn in the neighborhood. Honestly, I didn't care much for the first season, so I didn't bother with the second. Jeanne wished she has chosen the red button. Potato wedges probably are not best for relationships. It's never comforting to know that your fate depends on something as unpredictable as the popping of corn. There's probably enough glass in my cupboard to build an undersea aquarium. The hand sanitizer was actually clear glue. Nobody loves a pig wearing lipstick. The changing of down comforters to cotton bedspreads always meant the squirrels had returned. He kept telling himself that one day it would all somehow make sense. A suit of armor provides excellent sun protection on hot days. When motorists sped in and out of traffic, all she could think of was those in need of a transplant. Combines are no longer just for farms. He ended up burning his fingers poking someone else's fire. He said he was not there yesterday; however, many people saw him there. He walked into the basement with the horror movie from the night before playing in his head. He decided to live his life by the big beats manifesto. The trick to getting kids to eat anything is to put catchup on it. He found a leprechaun in his walnut shell. The beauty of the African sunset disguised the danger lurking nearby. You're good at English when you know the difference between a man eating chicken and a man-eating chicken. Being unacquainted with the chief raccoon was harming his prospects for promotion. 8% of 25 is the same as 25% of 8 and one of them is much easier to do in your head. Trash covered the landscape like sprinkles do a birthday cake.";
    int length = sizeof(str);
   
    char encrypted[length];
    for(int i = 0; i < length; i++)
        encrypted[i] = str[i] + 5; //the key for encryption is 3 that is added to ASCII value

    printf("\nEncrypted string: %s\n", encrypted);

    char decrypted[length];
    for(int j = 0; j < length; j++)
        decrypted[j] = encrypted[j] - 5; //the key for encryption is 3 that is subtracted to ASCII value

    printf("\nDecrypted string: %s\n", decrypted);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);

   return 0;
}
