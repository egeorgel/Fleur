//
// Created by Edgar on 02/01/2017.
//
#include <gtest/gtest.h>
#include <utils/sha1.h>
#include "processing/Processing.h"

class Processing_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Processing_test() {}
};


TEST_F(Processing_test, test_1) {

    std::string requettes(  "select html from \"http://httpbin.org/html\";"
                            "select html (h1) from \"http://httpbin.org/html\";"
                            "use twitter;"
                            "(CBJimEZofmww7RQ4fvitrNHnj, M9NBXFAQLJC6j5lTcQ1QL0QMAm4L8nyCKGwNcARP5BGlrJaNLA, 2711422854-wV9d3fCBnyx7oTDFlRn9F4oCM4CysAaR97TeaKn, qq9z0Bv5ZigB810CnRnF8rgrdx7cen9TS1CJTKlMngYRm);"
                            "get * from . limit 2;"
                            "use wikipedia;"
                            "search c++ from wikipedia limit 2;"
                            "get (header) c++ from wikipedia;"
                            "get (txt) c++ from wikipedia;");

    fleur::Processing processing(requettes);
    std::vector<std::string> results = processing.build();

    ASSERT_EQ(results.size(), 8);
    ASSERT_EQ(results[0], "<!DOCTYPE html>\n<html>\n  <head>\n  </head>\n  <body>\n      <h1>Herman Melville - Moby-Dick</h1>\n\n      <div>\n        <p>\n          Availing himself of the mild, summer-cool weather that now reigned in these latitudes, and in preparation for the peculiarly active pursuits shortly to be anticipated, Perth, the begrimed, blistered old blacksmith, had not removed his portable forge to the hold again, after concluding his contributory work for Ahab's leg, but still retained it on deck, fast lashed to ringbolts by the foremast; being now almost incessantly invoked by the headsmen, and harpooneers, and bowsmen to do some little job for them; altering, or repairing, or new shaping their various weapons and boat furniture. Often he would be surrounded by an eager circle, all waiting to be served; holding boat-spades, pike-heads, harpoons, and lances, and jealously watching his every sooty movement, as he toiled. Nevertheless, this old man's was a patient hammer wielded by a patient arm. No murmur, no impatience, no petulance did come from him. Silent, slow, and solemn; bowing over still further his chronically broken back, he toiled away, as if toil were life itself, and the heavy beating of his hammer the heavy beating of his heart. And so it was.\xE2\x80\x94Most miserable! A peculiar walk in this old man, a certain slight but painful appearing yawing in his gait, had at an early period of the voyage excited the curiosity of the mariners. And to the importunity of their persisted questionings he had finally given in; and so it came to pass that every one now knew the shameful story of his wretched fate. Belated, and not innocently, one bitter winter's midnight, on the road running between two country towns, the blacksmith half-stupidly felt the deadly numbness stealing over him, and sought refuge in a leaning, dilapidated barn. The issue was, the loss of the extremities of both feet. Out of this revelation, part by part, at last came out the four acts of the gladness, and the one long, and as yet uncatastrophied fifth act of the grief of his life's drama. He was an old man, who, at the age of nearly sixty, had postponedly encountered that thing in sorrow's technicals called ruin. He had been an artisan of famed excellence, and with plenty to do; owned a house and garden; embraced a youthful, daughter-like, loving wife, and three blithe, ruddy children; every Sunday went to a cheerful-looking church, planted in a grove. But one night, under cover of darkness, and further concealed in a most cunning disguisement, a desperate burglar slid into his happy home, and robbed them all of everything. And darker yet to tell, the blacksmith himself did ignorantly conduct this burglar into his family's heart. It was the Bottle Conjuror! Upon the opening of that fatal cork, forth flew the fiend, and shrivelled up his home. Now, for prudent, most wise, and economic reasons, the blacksmith's shop was in the basement of his dwelling, but with a separate entrance to it; so that always had the young and loving healthy wife listened with no unhappy nervousness, but with vigorous pleasure, to the stout ringing of her young-armed old husband's hammer; whose reverberations, muffled by passing through the floors and walls, came up to her, not unsweetly, in her nursery; and so, to stout Labor's iron lullaby, the blacksmith's infants were rocked to slumber. Oh, woe on woe! Oh, Death, why canst thou not sometimes be timely? Hadst thou taken this old blacksmith to thyself ere his full ruin came upon him, then had the young widow had a delicious grief, and her orphans a truly venerable, legendary sire to dream of in their after years; and all of them a care-killing competency.\n        </p>\n      </div>\n  </body>\n</html>");
    ASSERT_EQ(results[1], "Herman Melville - Moby-Dick");
    ASSERT_EQ(results[2], "Id = 814785277025779712 | tweet = Considering the development speed, when would I want to use Java instead of Python? by Garry Taylor https://t.co/NihLaoR6Eu");
    ASSERT_EQ(results[3], "Id = 800073993445253120 | tweet = Just reached #InboxZero with @PolymailApp, the amazing new app for #email! \xF0\x9F\x92\x8C https://t.co/N2GisOhz9x https://t.co/AamdsExKaa");
    ASSERT_EQ(results[4], " *** Wikipedia Title *** \\nC++\\n *** Wikipedia Content *** \\nC++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.");
    ASSERT_EQ(results[5], " *** Wikipedia Title *** \\nC++11\\n *** Wikipedia Content *** \\nC++11 is a version of the standard for the programming language C++. It was approved by International Organization for Standardization (ISO) on 12 August 2011, replacing C++03, superseded by C++14 on 18 August 2014 and later, by C++17, which is still under development.");
    ASSERT_EQ(results[6], " *** Wikipedia Title *** \\nC++\\n *** Wikipedia Content *** \\nC++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.");
    std::string sha = sha1(results[7]);
    ASSERT_EQ(sha, "cf268ba885a8b1291a7ce7140ec8fbf36c05f186");
}

TEST_F(Processing_test, test_2) {

    std::string requettes(   "select html from \"http://httpbin.org/html\";"
                             "select html (h1) from \"http://httpbin.org/html\";"

                             "use twitter;"
                             "(CBJimEZofmww7RQ4fvitrNHnj, M9NBXFAQLJC6j5lTcQ1QL0QMAm4L8nyCKGwNcARP5BGlrJaNLA, 2711422854-wV9d3fCBnyx7oTDFlRn9F4oCM4CysAaR97TeaKn, qq9z0Bv5ZigB810CnRnF8rgrdx7cen9TS1CJTKlMngYRm);"
                             "get * from . limit 2;"
                             "get tweets from ProductHunt limit 2;"

                             "select html (h1.title) from \"http://reactivex.io\";"
                             "select * from \"http://httpbin.org/post\" post (name=denis, age=69);"

                             "search football from twitter limit 3;"
    );

    fleur::Processing processing(requettes);
    std::vector<std::string> results = processing.build();

    for (auto result : results) {
        std::cout << result << std::endl;
    }

}