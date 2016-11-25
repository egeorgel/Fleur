//
// Created by Edgar on 21/11/2016.
//

#include <gtest/gtest.h>
#include "Processing.h"

class Processing_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Processing_test() {}
};

/////////////////////
///     HTML      ///
/////////////////////

/// select html from "http://httpbin.org/html";
TEST_F(Processing_test, selecet_html_from_url) {
    const std::string input = "select html from \"http://httpbin.org/html\";";
    parser::Requete requete;
    parser::doParse(input, requete);

    Processing processing(requete);
    EXPECT_EQ( "<!DOCTYPE html>\n<html>\n  <head>\n  </head>\n  <body>\n      <h1>Herman Melville - Moby-Dick</h1>\n\n      <div>\n        <p>\n          Availing himself of the mild, summer-cool weather that now reigned in these latitudes, and in preparation for the peculiarly active pursuits shortly to be anticipated, Perth, the begrimed, blistered old blacksmith, had not removed his portable forge to the hold again, after concluding his contributory work for Ahab's leg, but still retained it on deck, fast lashed to ringbolts by the foremast; being now almost incessantly invoked by the headsmen, and harpooneers, and bowsmen to do some little job for them; altering, or repairing, or new shaping their various weapons and boat furniture. Often he would be surrounded by an eager circle, all waiting to be served; holding boat-spades, pike-heads, harpoons, and lances, and jealously watching his every sooty movement, as he toiled. Nevertheless, this old man's was a patient hammer wielded by a patient arm. No murmur, no impatience, no petulance did come from him. Silent, slow, and solemn; bowing over still further his chronically broken back, he toiled away, as if toil were life itself, and the heavy beating of his hammer the heavy beating of his heart. And so it was.\xE2\x80\x94Most miserable! A peculiar walk in this old man, a certain slight but painful appearing yawing in his gait, had at an early period of the voyage excited the curiosity of the mariners. And to the importunity of their persisted questionings he had finally given in; and so it came to pass that every one now knew the shameful story of his wretched fate. Belated, and not innocently, one bitter winter's midnight, on the road running between two country towns, the blacksmith half-stupidly felt the deadly numbness stealing over him, and sought refuge in a leaning, dilapidated barn. The issue was, the loss of the extremities of both feet. Out of this revelation, part by part, at last came out the four acts of the gladness, and the one long, and as yet uncatastrophied fifth act of the grief of his life's drama. He was an old man, who, at the age of nearly sixty, had postponedly encountered that thing in sorrow's technicals called ruin. He had been an artisan of famed excellence, and with plenty to do; owned a house and garden; embraced a youthful, daughter-like, loving wife, and three blithe, ruddy children; every Sunday went to a cheerful-looking church, planted in a grove. But one night, under cover of darkness, and further concealed in a most cunning disguisement, a desperate burglar slid into his happy home, and robbed them all of everything. And darker yet to tell, the blacksmith himself did ignorantly conduct this burglar into his family's heart. It was the Bottle Conjuror! Upon the opening of that fatal cork, forth flew the fiend, and shrivelled up his home. Now, for prudent, most wise, and economic reasons, the blacksmith's shop was in the basement of his dwelling, but with a separate entrance to it; so that always had the young and loving healthy wife listened with no unhappy nervousness, but with vigorous pleasure, to the stout ringing of her young-armed old husband's hammer; whose reverberations, muffled by passing through the floors and walls, came up to her, not unsweetly, in her nursery; and so, to stout Labor's iron lullaby, the blacksmith's infants were rocked to slumber. Oh, woe on woe! Oh, Death, why canst thou not sometimes be timely? Hadst thou taken this old blacksmith to thyself ere his full ruin came upon him, then had the young widow had a delicious grief, and her orphans a truly venerable, legendary sire to dream of in their after years; and all of them a care-killing competency.\n        </p>\n      </div>\n  </body>\n</html>"
    ,processing.build().front());
}

/// select html (h1) from "http://httpbin.org/html";
TEST_F(Processing_test, selecet_html__selectH1_from_url) {
    const std::string input = "select html (h1) from \"http://httpbin.org/html\";";
    parser::Requete requete;
    parser::doParse(input, requete);

    Processing processing(requete);
    EXPECT_EQ( "Herman Melville - Moby-Dick"
    ,processing.build().front());
}



/////////////////////
///     JSON      ///
/////////////////////

/// select html json "https://www.hutworks.net//test.php?json=ezd";
TEST_F(Processing_test, selecet_json_from_url) {
    const std::string input = "select json from \"https://www.hutworks.net//test.php?json=ezd\";";
    parser::Requete requete;
    parser::doParse(input, requete);

    Processing processing(requete);
    EXPECT_EQ("{\"test\":\"une chevre\",\"chat\":{\"fouine\":\"Fleur\"}}"
    ,processing.build().front());
}