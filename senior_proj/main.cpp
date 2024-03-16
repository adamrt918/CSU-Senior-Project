//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <../ltexture.hpp>
#include <../player.hpp>
#include <../choicePage.hpp>
#include <../render.hpp>
#include <vector>

/*Notes
    - The coordinates (0,0) in SDL is the top left of the screen, the y
      increases as the point moves down the screen, and decreases back to 0 if
      it moves up.
*/

/*TODO
    - I need to figure out how to get a class to handle the taskbar events and
      the main page events. It should be repeatable between pages but I keep
      messing up when I'm copy pasting.
    - I have the pages class, but now I need to load in all of the pages. I also
      have to decide how I will hold the textures whether that be in main or in
      the pages class. Pages class would make sense because then each page can
      hold its' own texture.
    - A function to calculate where text should go on a page and ensure that I
      can break up text if it is on a screen that is too small.
*/

using namespace std;

//Textures Per Page
const int TASKBAR_TEXTURES = 2;
const int PLAYER_TEXTURES = 3;
const int START_PAGE_TEXTURES = 1;
const int MAIN_MENU_TEXTURES = 4; // 1 texture for each clickable word
const int TUTORIAL_TEXTURES = 12; // textures for individual highlights and going back to the main menu
const int QUOTATION_PAGE_TEXTURES = 3;
const int CHOICE_PAGE_TEXTURES = 4;
const int POST_CHOICE_PAGE_TEXTURES = 3;
const int TEXT_PAGE_TEXTURES = 2;
const int OUTCOME_PAGE_TEXTURES = 2;
const int VERSE_PAGE_TEXTURES = 2;

/*Page Numbers*/
const int NULL_PAGE = -1;
const int START_PAGE = 0;
const int MAIN_MENU_PAGE = 1;
const int TUTORIAL_PAGE = 2;
const int SURVEY_PAGE = 3;
const int OUTCOME_PAGE = 4;
const int GAME_PAGE_1 = 10;
const int GAME_PAGE_2 = 20;
const int GAME_PAGE_3_1 = 31;
const int GAME_PAGE_3_2 = 32;
const int GAME_PAGE_3_3 = 33;
const int GAME_PAGE_4 = 40;
const int GAME_PAGE_5 = 50;
const int GAME_PAGE_6 = 60;
const int GAME_PAGE_7_1 = 71;
const int GAME_PAGE_7_2 = 72;
const int GAME_PAGE_7_3 = 73;
const int GAME_PAGE_8 = 80;
const int GAME_PAGE_9 = 90;
const int GAME_PAGE_10 = 100;
const int GAME_PAGE_11_1 = 111;
const int GAME_PAGE_11_2 = 112;
const int GAME_PAGE_11_3 = 113;
const int GAME_PAGE_12 = 120;
const int GAME_PAGE_13 = 130;
const int GAME_PAGE_14_1 = 141;
const int GAME_PAGE_14_2 = 142;
const int GAME_PAGE_14_3 = 143;
const int GAME_PAGE_15 = 150;
const int GAME_PAGE_16 = 160;

/* Words per page */
const string NEXT_PAGE = "Next Page";
const string TASKBAR_WORDS[TASKBAR_TEXTURES]{"Main Menu", "Exit to Desktop"};
string PLAYER_WORDS[PLAYER_TEXTURES]{"Health:   ", "Sanity:   ", "Reputation:   "};
const string MAIN_MENU_WORDS[MAIN_MENU_TEXTURES] = {"Begin", "Tutorial", "Survey", "Exit"};
const string TUTORIAL_WORDS[TUTORIAL_TEXTURES] = {"Tutorial", 
    "    The novel will measure three metrics throughout the chapter, health and sanity which affect the individual player, and reputation, which affects the games ending. The metrics are affected through user-made decisions. The page of the visual novel is turned by clicking the interactive text. The novel is only advanced when a decision is made or when the timer runs out. Once the game ends, the player can choose to return to the main menu or exit the game. Progress is not saved, but the game should only take about 20 minutes to complete. Once complete, please fill out the survey.",  
    "Health", 
    "    Losing all your health during a chapter will result in losing the ability to make the most heroic decision for the rest of the chapter, but restoring your health. Health restores at the beginning of a new chapter. Heroic decisions affect your health the most but have the least impact on your sanity.", 
    "Sanity", 
    "    Losing all of your sanity in a chapter will immediately train track your actions and prevent player choice, forcing the player to make cowardly decisions which impact reputation. Choices which are cowardly affect sanity the most but save your health. A new chapter will result in a restoration of sanity.", 
    "Reputation",
    "    Reputation will continue with you throughout the novel and will determine your game ending. To achieve the most favorable outcome, you must be willing to take risks and decide heroically. However, if you always choose the most heroic outcome, there is a chance that you will die. To make it to the end without dying, you must make decisions which are less heroic.",
    "Ending", 
    "    There are 3 endings. Play the game as a hero, as a human, or as a coward to see each ending." ,
    "Decisions",
    "    At various points throughout the novel, the player will need to make decisions by clicking on them with their mouse. It is not always clear what the right choice is in these decisions, as it is not always clear in life what decisions one should make. Often, decisions which are competent and correct in one situation are deluded and ineffective in another. Sometimes, there is no correct decision. Other times, decisions need to be made quickly. The decisions in this game are no different. It is meant to display the futility of choice in certain situations and the need for a higher power. Decisions affect health and/or sanity, and reputation."};
const string GAME_PAGE_1_WORDS[QUOTATION_PAGE_TEXTURES] = {"Chapter 1", 
    "To each there comes in their lifetime a special moment when they are figuratively tapped on the shoulder and offered the chance to do a very special thing, unique to them and fitted to their talents. What a tragedy if that moment finds them unprepared or unqualified for that which could have been their finest hour.",  
    "- Winston Churchill"};
const string GAME_PAGE_2_WORDS[CHOICE_PAGE_TEXTURES] = {"    \"What does it mean to be a man?\" My father asked me, a young 17-year-old boy preparing to embark upon the adventures only found on the precipice of manhood. ",
    "\"Military service.\"", 
    "\"There\'s no such thing.\"", 
    "\"I don\'t know.\""};
string OUTCOME_PAGE_WORDS = "";
const string GAME_PAGE_3_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = { GAME_PAGE_2_WORDS[1], 
    "    I stated bluntly and confidently to my Dad\'s solemn face. No one could have understood how right I was, not even me. Dad signed his name on the dotted line while Mom sobbed into his shoulder and my little brother looked on from between the staircase balusters, eyes wide. No one in my immediate family had served - I would be the first of my known kindred to range this frontier. The recruiter and my father shook hands and made ceremonious eye contact. Then the recruiter turned to me. I excitedly grabbed the pen and signed my name on the other dotted line, being too young to sign for myself. The recruiter thanked me and my Dad, shaking hands with us one last time.",
    NEXT_PAGE};
const string GAME_PAGE_3_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_2_WORDS[2], 
    "    I stated rebelliously, spitting in the face of the Christian moral guidelines I had been raised with. I couldn\'t have understood how wrong I was. The recruiter looked at me questioningly, silently holding back his surprise. My father looked disappointingly upon me but signed the paper. The words cut my mother deeply, who could only sob harder. My brother took quiet notice from behind the staircase balusters. I brashly grabbed the pen and signed my name on the other dotted line, being too young to sign for myself.", 
    NEXT_PAGE };
const string GAME_PAGE_3_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_2_WORDS[3], 
    "    I stated timidly, unsure of what the future held for me. My father sighed deeply. My whole life he had attempted to impart to me the meaning of manhood - discipline, accountability, and love. It wasn\'t that he disproved of my decision. It was that he was ashamed of his own ability to impart this one important aspect of adulthood into the life of his young son. Now, I would embark upon this journey without his guidance. Dad reached out to hand the pen to me. I paused to reconsider my decision. \n    \"Sign here.\" The recruiter pointed. \n    I took the pen and signed my name, not because of my own strength, but because I did not want to upset my recruiter.",
    NEXT_PAGE};
const string GAME_PAGE_4_WORDS[TEXT_PAGE_TEXTURES] = {"    The recruiter futilely attempted to console my mother and walked out the front door, nodding towards my brother as he passed the staircase. Unbeknownst to me, I had entered my journey into manhood with the scribble of a pen.\n    As I drove through my neighborhood on the way to basic training, the families in my neighborhood lined up with signs and American flags in what I thought was support for my decision. Really, it was a small consolation to my family for whatever befell me during my time in service. Both of my parents shed tears, and with some hugging and vigorous handshaking, I left my family and journeyed into manhood. I belonged to my comrades now.\n    I had 3 weeks after graduating from basic training and airborne school to prepare for Ranger Selection. Fortunately, my good friend from high school was there, Ethan, so I was not completely alone. There was another guy which I had befriended during basic training, Cameron Meddock. We spent our evenings in pre-Ranger at the gym doing Ethan\'s torturous workout creations, reading, jamming \"Peanut Butter Jelly\" by Galantis on the way to the chow hall to crush our seventeenth piece of cornbread for the day, or sleeping 10 hours straight. Meddock and I used to butt heads over different army protocols. I tended to be on the rebellious side, while Meddock was a by-the-book straight edge. Ethan was just a chill surfer/snowboarder type from California, who could keep the peace. The three of us were inseparable. We graduated from Ranger Selection together. It was the last time I would ever see Meddock. Ethan and Meddock headed to Second Ranger Battalion out of Washington State. Then I headed to Hunter Army Airfield (HAAF) located in Savannah, Georgia, the home of First Ranger Battalion.",
    "How is Regiment?"};
const string GAME_PAGE_5_WORDS[TEXT_PAGE_TEXTURES] = {"    My phone rings and I am lifted out of a deep nap. I see the caller ID, Marsden. He\'s the senior private in my squad - That is, a private who has been on deployment, but still hasn\'t graduated Ranger School.\n"
    "    \"Where are you?!\" he half yells at me, half spits into his phone between labored panting.\n"
    "    I check the time, 0910. I was supposed to be at the company operations facility (COF) in my duty uniform by 0845. Uh oh, shouldn\'t have slept so long.\n"
    "    \"It doesn\'t matter. Just get here, NOW!!!\" He yells frantically into the phone before hanging up.\n"
    "    I throw on my uniform so fast that I forget my belt. I show up to the cage, all the privates in the squad are already dumping sweat. Puddles of it are slowly spreading out on the ground.\n"
    "    A sadistic, smiling, team leader looks at me and says, \"Nice of you to join us. Drop. Now.\"\n"
    "    I rapidly find a place to elevate my feet. Privates in Ranger Regiment aren\'t even allowed to do normal pushups. We must elevate our feet off the ground by placing them on some object. I start banging out decline pushups.",
    NEXT_PAGE};
const string GAME_PAGE_6_WORDS[CHOICE_PAGE_TEXTURES] = {"\"Where were you?\" the sergeant asks. ",
    "\"I couldn't find my belt, sergeant.\"",
    "\"I was sleeping and didn't set an alarm.\"",
    "\"I don't want to be a ranger anymore. I quit."};
const string GAME_PAGE_7_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_6_WORDS[1],
    "I half lie between repetitions.\n    I was dead asleep when Marsden's repeated calls broke through my phone's do not disturb rule.\n    \"So, you just didn't tell anyone and didn't answer your phone. Not only are you late, you're also out of uniform. Everyone, hang from the cage.\" I'm sure he knew I had been dead asleep.",
     NEXT_PAGE};
const string GAME_PAGE_7_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_6_WORDS[2],
    "    You say with utmost honesty, not mentioning your missing belt.\n    \"Well, at least you're honest.\" The sergeant said. \"Everyone else get up. <LAST NAME>, what is your least favorite exercise?\" he asks, smiling.\n    \"Burpees.\" You gasp, winded from the set of decline pushups.\n    \"Maybe too honest. Do burpees,\" He orders, not cutting you a break for your honesty, \"and then after that, hang from the cage.\"\n    You knock out your 25 burpees and jump up to begin your hang.",
    NEXT_PAGE};
const string GAME_PAGE_7_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_6_WORDS[3],
    "    I state, wanting to get out of the impending physical destruction which awaits me. The anxiety of watching my comrades suffer because of my actions has broken me.\n"
    "    \"Well you should have done it before you ran here. Hang from the cage.\" the sadist smiled, knowing there was no one to save you from his wrath.\n",
    NEXT_PAGE};
const string GAME_PAGE_8_WORDS[TEXT_PAGE_TEXTURES] = {"    Ranger squads reside in the COF which is something resembling a WWE cage match. Lord knows that as a private, every day felt like it. When I went to work in the morning, I would enter Delta Company\'s COF, then enter my squad\'s cage. There was chain link surrounding the entire squad cage with all our gear, to include chain link on the ceiling. The only entrance is through the chain link door between the lockers. The cage is a literal prison when one is a private.\n"    
    "    When my team leader told me to hang from the cage, I jumped to grab the chain link ceiling surrounding me. It was a barbaric practice. The space between intersections of the chain link was not big enough to fit two fingers comfortably; however, one\'s hand would be too stretched out to fit every finger in its own space. One could painfully jam their pinky into the space with their ring finger, tearing skin and cutting off blood flow to both, or leave one finger\'s worth of strength out of the equation, lessening one\'s ability to hang on for long periods of time. With the sadist breathing fire down my neck, I wanted to hang on for as long as possible.\n"
    "    The protective paint on the chain link had worn off from the privates who had to hang on the cage before me, and the privates who had to hang on the cage before them, and so on. The bodyweight of the individual caused the raw metal chain link to tear skin like a sandpaper blade directly to the joints of one\'s fingers. Eventually, the chain link would saw deep enough to draw blood. One could not hold on much longer than a minute or so, but with a team leader breathing fire down my neck, I must have held onto the chain link for about fifteen minutes - an eternity in such a situation. Hazing cuts deeper than the skin, but not as deep as artillery shrapnel or a bullet.\n"
    "    I did not consider these incidents hazing, but training, and they occurred often during my years as a private. These incidents taught me valuable lessons. There was a shoot house on HAAF named after Bradley Crose, a fallen Ranger. For physical exercise in the morning, the squad would sometimes run about two miles to the shoot house with full kit, weapons, and night vision to practice close quarters battle (CQB). Unfortunately, this was 2015. I was new to Ranger Regiment, so the entire trip to Bradley Crose consisted of my team leader crushing the new guys of the squad.", 
    NEXT_PAGE};
const string GAME_PAGE_9_WORDS[TEXT_PAGE_TEXTURES] = { "\"<LAST NAME>, what are you doing?\" My team leader barked as I walked in a mock patrol, breathing heavily from the most recent set of burpees.\n" 
    "    My night vision goggles were pointed straight at the ground, fogging up from the perspiration evaporating off my body, as I just tried to put one foot in front of the next.\n" 
    "    \"Walking, Corporal!\" I responded inadequately.\n" 
    "    After my team leader promptly ordered another set of burpees, my squad leader, Staff Sergeant Morton, looked at me and told me something I would never forget:\n\n" 
    "    \"You're never just walking, <LAST NAME>. We are Rangers, there's always something we need to be doing. You are scanning for the enemy. Every ten meters you're surveying the ground around you. You're thinking to yourself, 'Where do I take cover if I get shot at from the front? Where do I take cover if I get shot at from the left, right, or rear? Where do I go if I need to break contact or take cover from indirect fire?' If you're a leader, you're thinking, 'What should my men be doing? How can I help them?' You are NEVER just walking.\"\n\n"
    "    During the testing for my expert infantryman's badge (EIB), I did not give due respect to a ranking NCO who was failing me on a lane for the sake of semantics. In my eyes, this NCO was keeping me from achieving the same level of expertise as my peers for no reason – and I let him know as much. He destroyed me with physical training then grabbed my team leader to tell him what I did. My team leader at the time, Sergeant Davis, calmed the situation down. He told the NCO that he would punish me for my lack of respect and rude behavior, but also that I should pass the lane because I did not fail. The other NCO respected his opinion and his reasoning, passing me through the lane after a long and brutal session of physical exercise. Again, the session crossed the grey area into what many would consider hazing.\n" 
    "    That was not the end of my punishment.\n"
    "    \"<LAST NAME>, what you did was wrong, childish, and stupid. I want a 4-page paper written in 8 pt font, front and back, about what it means to be a man by tomorrow morning.\" Sergeant Davis ordered at 5pm that evening.\n",
    NEXT_PAGE
};
const string GAME_PAGE_10_WORDS[CHOICE_PAGE_TEXTURES] = {
    "    I spent the whole night typing in tiny font to finish this essay. The question my Dad had asked me was at the forefront of my mind. What have I been doing all this time? I'm going through my time in service, but do I have what it takes to be a man?\n" 
    "    The answer I settled on was:\n",
    "responsibility, accountability, discipline, and love.",
    "Manhood doesn't matter. Just how good of a person you are.",
    "Being a Christian and following the Christian tenants of love, mercy, and grace."
};
const string GAME_PAGE_11_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_10_WORDS[1],
	"    Sergeant Davis and I made purposeful eye contact, and I saw the pride he had from reading my paper. I reached out to shake his hand. He looked down at my hand, with a slight dampening of his demeanor.\n"
    "    \"I'm still your team leader, <LAST NAME>, not your buddy or your father. Drop.\"\n"
    "    I dropped and began knocking out my decline pushups. Why are these values the values which my father taught me?\n",
    NEXT_PAGE
};
const string GAME_PAGE_11_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_10_WORDS[2],
    "    As long as I follow my own moral code, I am in the right. As such, rank doesn't matter as long as I follow my own idea of right and wrong. The sergeant was treating me like I was inferior and I was right to stand up for myself.\n"
    "    \"<LAST NAME>, you missed the point on this one. I don't know what kind of childhood you had, but in my team you will be a man, respect authority, and be accountable for your actions, no matter what they are. Re-write the paper by tomorrow morning about respect and accountability.\" Sergeant Davis ordered.\n"
    "    Regardless, my actions were justified.",
    NEXT_PAGE
};
const string GAME_PAGE_11_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_10_WORDS[3],
    "    \"<LAST NAME>, we are Army Rangers. We close with to kill and destroy the enemy in cold blood with our bare hands if necessary. I don't know what kind of Bible you are reading, but when the Israelites stormed the walls of Jericho, they killed every man, woman, and child. So help me God you will be the best at killing. Hold squat.\" Sergeant Davis ordered.\n"
    "    He smoked me relentlessly to drive the point home... and drive the point home he did. Perhaps being a Christian was not only about these notably soft virtues, but also boldness, discipline, and savagery when the time calls? If God could allow such an awful thing as war, then surely He must provision a way for us to be made righteous within that anguish?\n",
    NEXT_PAGE
};
const string GAME_PAGE_12_WORDS[TEXT_PAGE_TEXTURES] = {
    "    Every hazing incident was also a fire hose of information being blasted into me by force. My first live fire exercise took place after just 6 months in the Ranger Battalion. Sergeant Davis was not my team leader at the time. I was 18 years old, handling live ammunition around other human beings. This is the first exercise in which I truly felt I was being trained for war. My job was to carry the stretcher, also known as a litter. During the night live fire portion of the exercise, the Alpha Team, led by Corporal Andrew Aimesbury, laid down a base of fire, while my section maneuvered on the targets. While waiting on the order to move, something peculiar happened. A white light beamed towards Aimesbury's team, and the shooting became more sporadic, soon stopping.\n" 
    "    I stood up and started moving towards Aimesbury's team, saying to my team leader, \"Something is wrong.\"\n" 
    "    Privates have no right to tell team leaders what to do, and I was immediately yanked to the ground.\n"
    "    \"Stay down unless I tell you to move.\" The team leader barked.\n",
    NEXT_PAGE
};
const string GAME_PAGE_13_WORDS[CHOICE_PAGE_TEXTURES] = {"Troubled, I thought about my next move.",
    "I stood back up and started sprinting towards the white light, completely disregarding a direct order.",
    "I remained laying on the ground, waiting to see what my team leader would do next.",
    "I took a knee and tried to convince the corporal that something was wrong."
};
const string GAME_PAGE_14_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_13_WORDS[1],
    "As I ran, I heard my team leader behind me, following suit. Up ahead, I heard people yelling for the litter bearer - me. I sprinted as fast as my legs would carry me. Tripping and smashing my night vision into my face, I still arrived in time to see Corporal Andrew Aimesbury in the throes of death. I performed my litter drill, removing the litter from the bag and extending it to carrying configuration fully under night vision. I placed the heat blanket on the stretcher and lined it up next to Aimesbury as he gasped for breath. My team leader looked on, unable to be angry at my decisiveness but concerned for his best friend who was dying.",
    NEXT_PAGE
};
const string GAME_PAGE_14_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_13_WORDS[2],
    "    \"Take a knee and pull security. If you ever do that again during a live fire I'll make sure you get kicked out of the Ranger battalion.\" Snapped my team leader.\n"
	"    The white light shone towards us and started waving erratically. Shouts could be heard bouncing through the trees.\n" 
	"    \"Let's go.\" The team leader stated.\n" 
	"    We ran through the trees, reaching the near lifeless body of Corporal Aimesbury.\n" 
	"    The team leader grabbed the litter off my back and performed the litter drill himself, telling me to get out of his way. My team leader treated me like dirt, unable to perform my duties under austere circumstances. But how was I supposed to know? I listened to him. He was wrong.",
    NEXT_PAGE
};
const string GAME_PAGE_14_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_13_WORDS[3],
    "    \"You don't get to make the calls around here, <LAST NAME>! It is a live fire, and it is training. Whatever trouble Aimesbury's team is having they will work through. The squad leader will give us a call and we will maneuver on the targets when Aimesbury is set.\" The team leader wisely responded.\n"
    "    Static came over radio, then a voice feverishly called for a stretcher bearer.\n"
    "    \"GO!\" The team leader screamed in my ear.\n"
    "    I ran towards the light as fast as I could, tripping and smashing my night vision into my face, but arriving as Aimesbury took his last breaths. I performed my litter drill under night vision, the team leader grabbed the heat blanket and opened it up once I had prepared the stretcher. I had known something was wrong. I should have acted sooner.\n",
    NEXT_PAGE
};
const string GAME_PAGE_15_WORDS[TEXT_PAGE_TEXTURES] = {
    "    \"Stay with me, Aims!!\" The squad leader yelled.\n"
    "    Corporal Aimesbury was gushing blood at a rate which was unimaginable to my young mind while the senior medic worked on stopping the bleeding. The squad medic worked on sticking an IV port to push fluids and narcotics, but Corporal Aimesbury kept convulsing and it was nearly impossible to stick a vein. Finally, I watched him take his last breath. On December 9th, 2015, Corproal Andrew Aimesbury was pronounced dead upon arrival to the hospital. I watched my mentors and some of the hardest men I ever knew break down and cry.\n"
    "    Wanting help to process what I had just witnessed, I reached out to a mentor I had in high school who was an ex-Ranger, explaining what had happened.\n"
    "    He responded, \"I'm sorry for your loss... But that is good training.\"\n",
    "What is the point of all this suffering?"
};
const string GAME_PAGE_16_WORDS[VERSE_PAGE_TEXTURES] = {
    "    In this you rejoice, though now for a little while, if necessary, you have been grieved by various trials, so that the tested genuineness of your faith - more precious than gold that perishes though it is tested by fire - may be found to result in praise and glory and honor at the revelation of Jesus Christ.\n"
    "    Though you have not seen him, you love him. Though you do not now see him, you believe in him and rejoice with joy that is inexpressible and filled with glory, obtaining the outcome of your faith, the salvation of your souls.",
    "-- 1 Peter 1: 6-9, ESV"
};


//Colors {r, g, b, alpha}
const SDL_Color BACKGROUND_COLOR = {0, 0, 0, SDL_ALPHA_OPAQUE}; //Background color black
const SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
const SDL_Color TAN = {210, 180, 140, SDL_ALPHA_OPAQUE};
const SDL_Color GREY = {128, 128, 128, SDL_ALPHA_OPAQUE};
const SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};
SDL_Color textColor = WHITE; //Text color white for initial use in the main loop.
SDL_Color* color = &textColor;

//Text sizes
const int HEADING_1 = 72;
const int HEADING_2 = 48;
const int HEADING_3 = 36;
const int QUOTATION = 18;
const int WRITING = 24;

//Textures and pages
const int MAX_TEXTURES = 20;
LTexture textures[MAX_TEXTURES];
LTexture TASKBAR[TASKBAR_TEXTURES];

//Player variables
LTexture PLAYER_STATS[PLAYER_TEXTURES];
Player gamer;
Player* player = &gamer;
int* gamerStatChange; //Holds Health/Sanity/Rep changes
const string GAMER_STAT[3] = {"health", "sanity", "reputation"};

//Mute button variables
LTexture MUTE_BUTTON;
SDL_Rect MUTE_BUTTON_SPRITES[2];
bool playMusic = true;
Mix_Music *gMusic = NULL; //Music for background

//Pages and Rendering
ChoicePage choicePage(player, textures);
Render render(textures);

//Monitor data
SDL_DisplayMode dimensions;
Window dms;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Renderer
SDL_Renderer* renderer;

//Event handler
SDL_Event e;

//Main loop flag
bool gaming = true;

//The current page variable so the game knows what to load.
int currentPage = -1;
int newPage = 100;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();
bool loadPlayerMedia(); //Load the player textures and fonts

//Calculates total height of all rendered words in a section
int totalHeight(int tNum);

//Frees media and shuts down SDL
void close();

//Event functions to determine what happens for different pages upon mouse events
void mainMenuEvents();
void taskBarEvents();
void quotationPageEvents(int nextPage);
void textPageEvents(int nextPage);
void postChoicePageEvents(int nextPage);
void muteButtonEvents();
void outcomeEvents(int nextPage);

//Rendering functions to determine what happens for different loaded text
//depending on page
void mainMenuRenderer();
void taskBarRenderer();
void playerBarRenderer();
void tutorialRenderer();
void quotationPageRenderer();
void postChoicePageRenderer();
void textPageRenderer();
void muteButtonRenderer(bool unMute);
void outcomePageRenderer();
void versePageRenderer();

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
		printf( "Failed to initialize!\n" );
    
    if (!loadMedia())
        cout << "Failed to load media!" << endl;

    // Play the MP3 file
    if (Mix_PlayMusic(gMusic, -1) == -1) {
        std::cerr << "Mix_PlayMusic Error: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(gMusic);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    /*GAME LOOP*/
    while( gaming )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
                gaming = false;
            
            //User wants to mute/unmute the music
            muteButtonEvents();

            //Handle events based on the page
            /*START SWITCH STATEMENT FOR EVENTS BASED ON PAGE*/
            switch (currentPage)
            {
                case START_PAGE:
                    break;
                case MAIN_MENU_PAGE:                        
                    mainMenuEvents();                    
                    break;
                case TUTORIAL_PAGE:
                    taskBarEvents();
                    break;
                case SURVEY_PAGE:
                    break;
                case GAME_PAGE_1:
                    taskBarEvents();
                    quotationPageEvents(GAME_PAGE_2);                    
                    break;
                case GAME_PAGE_2: // choice page
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case OUTCOME_PAGE:
                    taskBarEvents();
                    outcomeEvents(choicePage.getStorePage());
                    break;
                case GAME_PAGE_3_1:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_4);
                    break;
                case GAME_PAGE_3_2:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_4);
                    break;
                case GAME_PAGE_3_3:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_4);
                    break;
                case GAME_PAGE_4:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_5);
                    break;
                case GAME_PAGE_5:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_6);
                    break;
                case GAME_PAGE_6: // choice page
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case GAME_PAGE_7_1:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_8);
                    break;
                case GAME_PAGE_7_2:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_8);
                    break;                
                case GAME_PAGE_7_3:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_8);
                    break; 
                case GAME_PAGE_8:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_9);
                    break;    
                case GAME_PAGE_9:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_10);
                    break; 
                case GAME_PAGE_10: // choice page
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case GAME_PAGE_11_1:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_12);
                    break;
                case GAME_PAGE_11_2:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_12);
                    break;
                case GAME_PAGE_11_3:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_12);
                    break;
                case GAME_PAGE_12:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_13);
                    break; 
                case GAME_PAGE_13:// choice page
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case GAME_PAGE_14_1:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_15);
                    break;
                case GAME_PAGE_14_2:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_15);
                    break;
                case GAME_PAGE_14_3:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_15);
                    break;
                case GAME_PAGE_15:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_16);
                    break; 
                case GAME_PAGE_16: //STUBBED
                    taskBarEvents();
                    break;
                default:
                    taskBarEvents();
                    break;
            /*END EVENTS BASED ON PAGE SWITCH STATEMENT*/
            }
        }
        //Load new media whenever the page we are on does not match the new page we
        //are supposed to be on
        if (currentPage != newPage) 
        {
            if(!loadMedia())
                cout << "Failed to load media on page " << newPage << "!\n";
            if (!loadPlayerMedia())
                cout << "Failed to load player media on page " << newPage << "!\n";
            //Once the media is loaded, the player is on the new page.
            currentPage = newPage;
            cout << "current page: " << currentPage << endl;
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
        SDL_RenderClear(renderer);

        //Render current frame
        /*Begin switch for which frames to Render*/
        switch (currentPage)
        {
            case MAIN_MENU_PAGE:
                mainMenuRenderer();
                break;
            case TUTORIAL_PAGE:
                taskBarRenderer();
                tutorialRenderer();
                break;
            case SURVEY_PAGE:
                break;
            case GAME_PAGE_1:
                taskBarRenderer();
                playerBarRenderer();
                quotationPageRenderer();
                break;
            case GAME_PAGE_2:
                taskBarRenderer();
                playerBarRenderer();
                render.choicePageRenderer(choicePage.chooseInsane(), renderer, player);
                break;
            case OUTCOME_PAGE:
                taskBarRenderer();
                playerBarRenderer();
                outcomePageRenderer();
                break;
            case GAME_PAGE_3_1:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_3_2:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_3_3:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_6:
                taskBarRenderer();
                playerBarRenderer();
                render.choicePageRenderer(choicePage.chooseInsane(), renderer, player);
                break;
            case GAME_PAGE_7_1:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_7_2:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_7_3:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_10:
                taskBarRenderer();
                playerBarRenderer();
                render.choicePageRenderer(choicePage.chooseInsane(), renderer, player);
                break;
            case GAME_PAGE_11_1:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_11_2:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_11_3:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_13:
                taskBarRenderer();
                playerBarRenderer();
                render.choicePageRenderer(choicePage.chooseInsane(), renderer, player);
                break;
            case GAME_PAGE_14_1:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_14_2:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_14_3:
                taskBarRenderer();
                playerBarRenderer();
                postChoicePageRenderer();
                break;
            case GAME_PAGE_16:
                taskBarRenderer();
                playerBarRenderer();
                versePageRenderer();
                break;
            default: //Default is for regular text pages
                taskBarRenderer();
                playerBarRenderer();
                textPageRenderer();
                break;

        }
        /*End switch for rendering frames*/

        //Render the mute button on top of every frame
        muteButtonRenderer(playMusic);

        //Update screen
        SDL_RenderPresent(renderer);
    }
	/*END GAME LOOP*/
	close();
	return 0;
}

bool init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
        return false;
    }

    //Get Monitor dimension
    dms.initWindow();

    //Create window
    gWindow = SDL_CreateWindow( "A Solemn Evolution", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dms.w(), dms.h(), SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Add window size to the choice page
    choicePage.setW(dms.w());
    choicePage.setH(dms.h());

    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Initialize renderer color to black
    SDL_SetRenderDrawColor( renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255 );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }

    //Initialize SDL_mixer
    if (!Mix_Init(MIX_INIT_MP3)){
        cerr << "Mix_Init Error: " << SDL_GetError() << endl;
        return false;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

	return true;
}

bool loadMedia()
{
    //Load the Taskbar textures
    for (int i = 0; i < TASKBAR_TEXTURES; i++){
        TASKBAR[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
        if (TASKBAR[i].gFont == NULL)
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            return false;
        }
        //Load in the textures for rendering
        if (!TASKBAR[i].loadFromRenderedText(renderer, TASKBAR_WORDS[i], GREY))
        {
            printf( "Failed to render text texture!\n" );
            return false;
        }
    }

    //Load music
	gMusic = Mix_LoadMUS( "resources/back_music.mp3" );
	if( gMusic == NULL )
	{
		printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
    
    //Load the mute/unmute button
    if (!MUTE_BUTTON.loadFromFile("resources/mute_buttons.png", renderer)){
        cout << "Failed to load mute button texture!" << endl;
        return false;
    }
    //Clip the picture of the mute buttons I want to use
    else {
        MUTE_BUTTON_SPRITES[0].x = 0;
        MUTE_BUTTON_SPRITES[0].y = 0;
        MUTE_BUTTON_SPRITES[0].w = MUTE_BUTTON.getWidth() / 4;
        MUTE_BUTTON_SPRITES[0].h = MUTE_BUTTON.getHeight();
        MUTE_BUTTON_SPRITES[1].x = (MUTE_BUTTON.getWidth() / 4) * 3;
        MUTE_BUTTON_SPRITES[1].y = 0;
        MUTE_BUTTON_SPRITES[1].w = MUTE_BUTTON.getWidth() / 4;
        MUTE_BUTTON_SPRITES[1].h = MUTE_BUTTON.getHeight();
    }


    //This is for loading the different page textures
    switch (newPage)
    {
        case START_PAGE:
            break;
        case MAIN_MENU_PAGE:
            for (int i = 0; i < MAIN_MENU_TEXTURES; i++){
                //Open the font
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", 72);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, MAIN_MENU_WORDS[i], textColor))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }  
            }
            break;
        case TUTORIAL_PAGE:
            for (int i = 0; i < TUTORIAL_TEXTURES; i++){
                //Open the font
                if (i == 0)
                    textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
                else if (i % 2 == 1)
                    textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                else if (i % 2 == 0)
                    textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, TUTORIAL_WORDS[i], textColor, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;  
        case SURVEY_PAGE:
            break;
        case GAME_PAGE_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_1_WORDS[0], TAN, dms.w() / 3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < QUOTATION_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", QUOTATION);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_1_WORDS[i], TAN, dms.w() / 3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_2:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load choice page 2" << endl;
            break;
        case OUTCOME_PAGE:
            OUTCOME_PAGE_WORDS = "";
            gamerStatChange = choicePage.getStatChange();
            for (int i = 0; i < 3; i++) {
                if (gamerStatChange[i] > 0)
                    OUTCOME_PAGE_WORDS.append("You gained " + to_string(gamerStatChange[i]) + ' ' + GAMER_STAT[i] + ".\n");
                else if (gamerStatChange[i] < 0)
                    OUTCOME_PAGE_WORDS.append("You lost " + to_string(gamerStatChange[i]) + ' ' + GAMER_STAT[i] + ".\n");
                else
                    OUTCOME_PAGE_WORDS.append("No change in " + GAMER_STAT[i] + ".\n");
            }
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, OUTCOME_PAGE_WORDS, TAN, dms.w() / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[1].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[1].loadFromRenderedText(renderer, "Continue", TAN, dms.w() / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            break;
        case GAME_PAGE_3_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_3_1_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_3_1_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_3_2:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_3_2_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_3_2_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_3_3:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_3_3_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_3_3_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_4:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_4_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_5:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_5_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_6:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load choice page 6" << endl;
            break;
        case GAME_PAGE_7_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_7_1_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_7_1_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_7_2:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_7_2_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_7_2_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_7_3:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_7_3_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_7_3_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }        
            break;
        case GAME_PAGE_8:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_8_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_9:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_9_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_10:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load choice page 10" << endl;
            break;
        case GAME_PAGE_11_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_11_1_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                cout << "word 0" << endl;
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_11_1_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_11_2:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_11_2_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_11_2_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;        
        case GAME_PAGE_11_3:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_11_3_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_11_3_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }        
            break;
        case GAME_PAGE_12:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_12_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_13:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load choice page" << currentPage << endl;
            break;
        case GAME_PAGE_14_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_14_1_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                cout << "word 0" << endl;
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_14_1_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_14_2:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_14_2_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                cout << "word 0" << endl;
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_14_2_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_14_3:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_14_3_WORDS[0], GREY, dms.w() / 2.5))
            {
                printf( "Failed to render text texture!\n" );
                cout << "word 0" << endl;
                return false;
            }
            for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_14_3_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_15:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_15_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_16:
            for (int i = 0; i < VERSE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", QUOTATION);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_16_WORDS[i], TAN, dms.w() / 3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
    } // End Switch
	return true;
}

bool loadPlayerMedia(){
    for (int i = 0; i < PLAYER_TEXTURES; i++)
    {
        PLAYER_STATS[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
        if (PLAYER_STATS[i].gFont == NULL)
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            return false;
        }
        switch (i){
            case 0:
                PLAYER_WORDS[i].replace(8, 9, to_string(gamer.getHealth()));
                break;
            case 1:
                PLAYER_WORDS[i].replace(8, 9, to_string(gamer.getSanity()));
                break;
            case 2:
                PLAYER_WORDS[i].replace(12, 13, to_string(gamer.getRep()));
                break;
        }
        
        if (!PLAYER_STATS[i].loadFromRenderedText(renderer, PLAYER_WORDS[i], WHITE))
        {
            printf( "Failed to render text texture!\n" );
            return false;
        }
    }
    return true;
}

int totalHeight(int tNum){
    int height = 0;
    for (int i = 0; i < tNum; i++)
        height += textures[i].getHeight();
    return height;
}

void close()
{
	//Free loaded textures, images, and font
    for (int i = 0; i < 20; i++){
        textures[i].free();
        TTF_CloseFont( textures[i].gFont );
        if (i < TASKBAR_TEXTURES)
            TASKBAR[i].free();
        if (i < PLAYER_TEXTURES)
            PLAYER_STATS[i].free();
    }

    //Free the music
	Mix_FreeMusic( gMusic );
	gMusic = NULL;



	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL subsystems
    Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void taskBarEvents(){
    for (int i = 0; i < TASKBAR_TEXTURES; i++)
    {
        if (TASKBAR[i].isMouseOver(TASKBAR[i].getRect()))
        {   textColor = RED;
            {
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    switch (i){
                        case 0: 
                            newPage = MAIN_MENU_PAGE;
                            gamer.setHealth(10);
                            gamer.setRep(10);
                            gamer.setSanity(20);
                            break;
                        case 1:
                            gaming = false;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        else
            textColor = GREY;
        TASKBAR[i].loadFromRenderedText(renderer, TASKBAR_WORDS[i], textColor);
    }
}

void mainMenuEvents()
{
    for (int i = 0; i < MAIN_MENU_TEXTURES; i++)
    {
        if (textures[i].isMouseOver(textures[i].getRect()))
        {   textColor = RED;
            textures[i].loadFromRenderedText(renderer, MAIN_MENU_WORDS[i], textColor);
            {
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    switch (i){
                        case 0: 
                            newPage = GAME_PAGE_1;
                            break;
                        case 1:
                            newPage = TUTORIAL_PAGE;
                            break;
                        case 2: 
                            cout << "Here is the survey link: " << endl;
                            break;
                        case 3:
                            gaming = false;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        else
            textColor = WHITE;
            textures[i].loadFromRenderedText(renderer, MAIN_MENU_WORDS[i], textColor);
    }
}

void quotationPageEvents(int nextPage) {
    switch (currentPage){
        case GAME_PAGE_1:
            if (textures[2].isMouseOver(textures[2].getRect())){
                textColor = GREY;
                textures[2].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", QUOTATION + 2);                        
                if(e.type == SDL_MOUSEBUTTONDOWN)
                    newPage = nextPage;
            }
            else
            {
                textColor = TAN;
                textures[2].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", QUOTATION);
            }
            textures[2].loadFromRenderedText(renderer, GAME_PAGE_1_WORDS[2], textColor, dms.w()/3);
            break;
        default:
            break;
    }
}

void textPageEvents(int nextPage){
    if (textures[TEXT_PAGE_TEXTURES - 1].isMouseOver(textures[TEXT_PAGE_TEXTURES - 1].getRect())){
        textColor = GREY;
        textures[TEXT_PAGE_TEXTURES - 1].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
        if(e.type == SDL_MOUSEBUTTONDOWN)
            newPage = nextPage;
    }
    else{
        textColor = TAN;
        textures[TEXT_PAGE_TEXTURES - 1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
    }
    //Ensure that there is a non-null value in the texture being rendered.
    //Return NEXT PAGE if not
    if (textures[TEXT_PAGE_TEXTURES - 1].loadFromRenderedText(renderer, textures[TEXT_PAGE_TEXTURES - 1].getWord(), textColor, dms.w()/1.3))
        return;
    else 
        textures[TEXT_PAGE_TEXTURES - 1].loadFromRenderedText(renderer, NEXT_PAGE, textColor, dms.w()/1.3);  
}

void postChoicePageEvents(int nextPage){
    if (textures[POST_CHOICE_PAGE_TEXTURES - 1].isMouseOver(textures[POST_CHOICE_PAGE_TEXTURES - 1].getRect())){
        textColor = GREY;
        textures[POST_CHOICE_PAGE_TEXTURES - 1].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
        if(e.type == SDL_MOUSEBUTTONDOWN)
            newPage = nextPage;
    }
    else{
        textColor = TAN;
        textures[POST_CHOICE_PAGE_TEXTURES - 1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
    }
    textures[POST_CHOICE_PAGE_TEXTURES - 1].loadFromRenderedText(renderer, NEXT_PAGE, textColor, dms.w()/1.3);  
}

void muteButtonEvents(){
    if (MUTE_BUTTON.isMouseOver(MUTE_BUTTON.getRect()))
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (!playMusic){
                playMusic = true;
                Mix_VolumeMusic(128);
            }
            else {
                playMusic = false;
                Mix_VolumeMusic(0);
            }
    

}

void outcomeEvents(int nextPage){
    if (textures[OUTCOME_PAGE_TEXTURES - 1].isMouseOver(textures[OUTCOME_PAGE_TEXTURES - 1].getRect())){
        textColor = GREY;
        textures[OUTCOME_PAGE_TEXTURES - 1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
        if(e.type == SDL_MOUSEBUTTONDOWN){
            newPage = nextPage;
            choicePage.setStorePage(NULL_PAGE);
        }
    }
    else{
        textColor = WHITE;
        textures[OUTCOME_PAGE_TEXTURES - 1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
    }
    //Ensure that there is a non-null value in the texture being rendered.
    //Return NEXT PAGE if not
    if (textures[OUTCOME_PAGE_TEXTURES - 1].loadFromRenderedText(renderer, textures[OUTCOME_PAGE_TEXTURES - 1].getWord(), textColor, dms.w()/1.3))
        return;
    textures[OUTCOME_PAGE_TEXTURES - 1].loadFromRenderedText(renderer, "Continue", textColor, dms.w()/1.3);  
}

void mainMenuRenderer(){
for (int i = 0; i < MAIN_MENU_TEXTURES; i++)
    textures[i].render((dms.w() * (i + .5) / MAIN_MENU_TEXTURES + 1) - textures[i].getWidth() / 2, ( dms.h() - textures[i].getHeight() ) / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

void taskBarRenderer(){
for (int i = 0; i < TASKBAR_TEXTURES; i++)
    TASKBAR[i].render((dms.w() * (1 + i) / 3) - (TASKBAR[i].getWidth() / 2), (TASKBAR[i].getHeight() / 2), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

void tutorialRenderer(){
    for (int i = 0; i < TUTORIAL_TEXTURES; i++){
        if (i == 0)
            textures[i].render((dms.w() / 2) - textures[i].getWidth() / 2, (dms.h() / 8) - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        else if (i % 2 == 1)
            textures[i].render((dms.w() / 2) - textures[i].getWidth() / 2, (dms.h() / 8) + totalHeight(i) + 10 * i , NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        else
            textures[i].render((dms.w() / 2) - textures[i].getWidth() / 2, (dms.h() / 8) + totalHeight(i) + 10 * i, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void quotationPageRenderer(){
    textures[0].render(dms.w() / 2 - textures[0].getWidth() / 2, dms.h() / 3 - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        for (int i = 1; i < QUOTATION_PAGE_TEXTURES; i++)
            textures[i].render(dms.w() / 2 - textures[i].getWidth() / 2, dms.h() / 2 - textures[i].getHeight() + totalHeight(i) + 20, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

void playerBarRenderer(){
    for (int i = 0; i < PLAYER_TEXTURES; i++)
        PLAYER_STATS[i].render((dms.w() * (1 + i) / 4 - PLAYER_STATS[i].getWidth() / 2), dms.h() / 8 - PLAYER_STATS[i].getHeight() * 4, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

void postChoicePageRenderer(){
    textures[0].render(dms.w() / 2 - textures[0].getWidth() / 2, dms.h() / 3 - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
        textures[i].render(dms.w() / 2 - textures[i].getWidth() / 2, dms.h() / 2 - textures[i].getHeight() + totalHeight(i) + (i * 20), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void textPageRenderer(){

    for (int i = 0; i < TEXT_PAGE_TEXTURES; i++){
        //Formulas for text position based on texture dimensions and screen dimensions
        int x = dms.w() / 2 - textures[i].getWidth() / 2;
        int y = dms.h() / 2 - textures[i].getHeight() / 2 + totalHeight(i) + (i * 20);

        //Validation to keep text on screen
        if (x > (dms.w() - textures[i].getWidth()))
            x = dms.w() - textures[i].getWidth();
        if (y > (dms.h() - textures[i].getHeight()))
            y = dms.h() - textures[i].getHeight();
        // cout << "page: " << currentPage << endl;
        // cout << "Texture[" << i << "].getWidth() = " << textures[i].getWidth() << endl;
        // cout << "Texture[" << i << "].getHeight() = " << textures[i].getHeight() << endl;
        // cout << "dms.w() = " << dms.w() << endl;
        // cout << "dms.h() = " << dms.h() << endl;
        // cout << " x = " << x << endl;
        // cout << " y = " << y << endl;
        textures[i].render(x, y, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void muteButtonRenderer(bool unMute){
    MUTE_BUTTON.render(0,0, &MUTE_BUTTON_SPRITES[unMute], 0, NULL, SDL_FLIP_NONE, renderer);
}

void outcomePageRenderer(){
    textures[0].render(dms.w() / 2 - textures[0].getWidth() / 15, dms.h() / 2 - textures[0].getHeight() / 2 + totalHeight(0), NULL, 0, NULL, SDL_FLIP_NONE, renderer);    
    textures[1].render(dms.w() / 2 - textures[1].getWidth() / 2, dms.h() / 2 - textures[1].getHeight() / 2 + totalHeight(1) + 20, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

void versePageRenderer(){
    for (int i = 0; i < VERSE_PAGE_TEXTURES; i++)
        textures[i].render(dms.w() / 2 - textures[i].getWidth() / 2, dms.h() / 2 - textures[i].getHeight() + totalHeight(i) + 20, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}


