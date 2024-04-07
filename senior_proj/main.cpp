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
#include <../timer.hpp>

/*Notes
    - The coordinates (0,0) in SDL is the top left of the screen, the y
      increases as the point moves down the screen, and decreases back to 0 if
      it moves up.
*/

/*TODO  
    - Taskbar events don't work on choice page
        - Hitting main menu on choice page resets stats
*/

using namespace std;

//Textures Per Page
const int START_PAGE_TEXTURES = 2;
const int TASKBAR_TEXTURES = 2;
const int PLAYER_TEXTURES = 3;
const int MAIN_MENU_TEXTURES = 4; // 1 texture for each clickable word
const int TUTORIAL_TEXTURES = 12; // textures for individual highlights and going back to the main menu
const int QUOTATION_PAGE_TEXTURES = 3;
const int CHOICE_PAGE_TEXTURES = 4;
const int POST_CHOICE_PAGE_TEXTURES = 3;
const int TEXT_PAGE_TEXTURES = 2;
const int OUTCOME_PAGE_TEXTURES = 2;
const int VERSE_PAGE_TEXTURES = 2;
const int END_CHAPTER_PAGE_TEXTURES = 2;

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
const int GAME_PAGE_17 = 170;
const int GAME_PAGE_18 = 180;
const int GAME_PAGE_19 = 190;
const int GAME_PAGE_20 = 200;
const int GAME_PAGE_21 = 210;
const int GAME_PAGE_22 = 220;
const int GAME_PAGE_23_1 = 231;
const int GAME_PAGE_23_2 = 232;
const int GAME_PAGE_23_3 = 233;
const int GAME_PAGE_24 = 240;
const int GAME_PAGE_25 = 250;
const int GAME_PAGE_26_1 = 261;
const int GAME_PAGE_26_2 = 262;
const int GAME_PAGE_26_3 = 263;
const int GAME_PAGE_27 = 270;
const int GAME_PAGE_28 = 280;
const int GAME_PAGE_29_1 = 291;
const int GAME_PAGE_29_2 = 292;
const int GAME_PAGE_29_3 = 293;
const int GAME_PAGE_30 = 300;
const int GAME_PAGE_31 = 310;
const int GAME_PAGE_32_1 = 321;
const int GAME_PAGE_32_2 = 322;
const int GAME_PAGE_32_3 = 323;
const int GAME_PAGE_33 = 330;
const int GAME_PAGE_34 = 340;
const int GAME_PAGE_35 = 350;
const int GAME_PAGE_36 = 360;
const int GAME_PAGE_37 = 370;
const int GAME_PAGE_38_HERO = 381;
const int GAME_PAGE_38_AVERAGE = 382;
const int GAME_PAGE_38_COWARD = 383;
const int GAME_PAGE_38_4_AVERAGE = 384;
const int GAME_PAGE_39 = 390;
const int GAME_PAGE_40 = 400;
const int GAME_PAGE_41 = 410;


/* Words per page */
const string NEXT_PAGE = "Next Page";
const string START_PAGE_WORDS = "Click Here to Begin";
const string TASKBAR_WORDS[TASKBAR_TEXTURES]{"Main Menu", "Exit to Desktop"};
string PLAYER_WORDS[PLAYER_TEXTURES]{"Health:   ", "Sanity:   ", "Reputation:   "};
const string MAIN_MENU_WORDS[MAIN_MENU_TEXTURES] = {"Begin", "Tutorial", "Survey", "Exit"};
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
    "    You say with utmost honesty, not mentioning your missing belt.\n    \"Well, at least you're honest.\" The sergeant said. \"Everyone else get up. Thiemann, what is your least favorite exercise?\" he asks, smiling.\n    \"Burpees.\" You gasp, winded from the set of decline pushups.\n    \"Maybe too honest. Do burpees,\" He orders, not cutting you a break for your honesty, \"and then after that, hang from the cage.\"\n    You knock out your 25 burpees and jump up to begin your hang.",
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
const string GAME_PAGE_9_WORDS[TEXT_PAGE_TEXTURES] = { "\"Thiemann, what are you doing?\" My team leader barked as I walked in a mock patrol, breathing heavily from the most recent set of burpees.\n" 
    "    My night vision goggles were pointed straight at the ground, fogging up from the perspiration evaporating off my body, as I just tried to put one foot in front of the next.\n" 
    "    \"Walking, Corporal!\" I responded inadequately.\n" 
    "    After my team leader promptly ordered another set of burpees, my squad leader, Staff Sergeant Morton, looked at me and told me something I would never forget:\n\n" 
    "    \"You're never just walking, Thiemann. We are Rangers, there's always something we need to be doing. You are scanning for the enemy. Every ten meters you're surveying the ground around you. You're thinking to yourself, 'Where do I take cover if I get shot at from the front? Where do I take cover if I get shot at from the left, right, or rear? Where do I go if I need to break contact or take cover from indirect fire?' If you're a leader, you're thinking, 'What should my men be doing? How can I help them?' You are NEVER just walking.\"\n\n"
    "    During the testing for my expert infantryman's badge (EIB), I did not give due respect to a ranking NCO who was failing me on a lane for the sake of semantics. In my eyes, this NCO was keeping me from achieving the same level of expertise as my peers for no reason - and I let him know as much. He destroyed me with physical training then grabbed my team leader to tell him what I did. My team leader at the time, Sergeant Davis, calmed the situation down. He told the NCO that he would punish me for my lack of respect and rude behavior, but also that I should pass the lane because I did not fail. The other NCO respected his opinion and his reasoning, passing me through the lane after a long and brutal session of physical exercise. Again, the session crossed the grey area into what many would consider hazing.\n" 
    "    That was not the end of my punishment.\n"
    "    \"Thiemann, what you did was wrong, childish, and stupid. I want a 4-page paper written in 8 pt font, front and back, about what it means to be a man by tomorrow morning.\" Sergeant Davis ordered at 5pm that evening.\n",
    NEXT_PAGE};
const string GAME_PAGE_10_WORDS[CHOICE_PAGE_TEXTURES] = {
    "    I spent the whole night typing in tiny font to finish this essay. The question my Dad had asked me was at the forefront of my mind. What have I been doing all this time? I'm going through my time in service, but do I have what it takes to be a man?\n" 
    "    The answer I settled on was:\n",
    "responsibility, accountability, discipline, and love.",
    "Manhood doesn't matter. Just how good of a person you are.",
    "Being a Christian and following the Christian tenants of love, mercy, and grace."};
const string GAME_PAGE_11_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_10_WORDS[1],
	"    Sergeant Davis and I made purposeful eye contact, and I saw the pride he had from reading my paper. I reached out to shake his hand. He looked down at my hand, with a slight dampening of his demeanor.\n"
    "    \"I'm still your team leader, Thiemann, not your buddy or your father. Drop.\"\n"
    "    I dropped and began knocking out my decline pushups. Why are these values the values which my father taught me?\n",
    NEXT_PAGE};
const string GAME_PAGE_11_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_10_WORDS[2],
    "    As long as I follow my own moral code, I am in the right. As such, rank doesn't matter as long as I follow my own idea of right and wrong. The sergeant was treating me like I was inferior and I was right to stand up for myself.\n"
    "    \"Thiemann, you missed the point on this one. I don't know what kind of childhood you had, but in my team you will be a man, respect authority, and be accountable for your actions, no matter what they are. Re-write the paper by tomorrow morning about respect and accountability.\" Sergeant Davis ordered.\n"
    "    Regardless, my actions were justified.",
    NEXT_PAGE};
const string GAME_PAGE_11_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_10_WORDS[3],
    "    \"Thiemann, we are Army Rangers. We close with to kill and destroy the enemy in cold blood with our bare hands if necessary. I don't know what kind of Bible you are reading, but when the Israelites stormed the walls of Jericho, they killed every man, woman, and child. So help me God you will be the best at killing. Hold squat.\" Sergeant Davis ordered.\n"
    "    He smoked me relentlessly to drive the point home... and drive the point home he did. Perhaps being a Christian was not only about these notably soft virtues, but also boldness, discipline, and savagery when the time calls? If God could allow such an awful thing as war, then surely He must provision a way for us to be made righteous within that anguish?\n",
    NEXT_PAGE};
const string GAME_PAGE_12_WORDS[TEXT_PAGE_TEXTURES] = {
    "    Every hazing incident was also a fire hose of information being blasted into me by force. My first live fire exercise took place after just 6 months in the Ranger Battalion. Sergeant Davis was not my team leader at the time. I was 18 years old, handling live ammunition around other human beings. This is the first exercise in which I truly felt I was being trained for war. My job was to carry the stretcher, also known as a litter. During the night live fire portion of the exercise, the Alpha Team, led by Corporal Andrew Aimesbury, laid down a base of fire, while my section maneuvered on the targets. While waiting on the order to move, something peculiar happened. A white light beamed towards Aimesbury's team, and the shooting became more sporadic, soon stopping.\n" 
    "    I stood up and started moving towards Aimesbury's team, saying to my team leader, \"Something is wrong.\"\n" 
    "    Privates have no right to tell team leaders what to do, and I was immediately yanked to the ground.\n"
    "    \"Stay down unless I tell you to move.\" The team leader barked.\n",
    NEXT_PAGE};
const string GAME_PAGE_13_WORDS[CHOICE_PAGE_TEXTURES] = {"Troubled, I thought about my next move.",
    "I stood back up and started sprinting towards the white light, completely disregarding a direct order.",
    "I remained laying on the ground, waiting to see what my team leader would do next.",
    "I took a knee and tried to convince the corporal that something was wrong."};
const string GAME_PAGE_14_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_13_WORDS[1],
    "As I ran, I heard my team leader behind me, following suit. Up ahead, I heard people yelling for the litter bearer - me. I sprinted as fast as my legs would carry me. Tripping and smashing my night vision into my face, I still arrived in time to see Corporal Andrew Aimesbury in the throes of death. I performed my litter drill, removing the litter from the bag and extending it to carrying configuration fully under night vision. I placed the heat blanket on the stretcher and lined it up next to Aimesbury as he gasped for breath. My team leader looked on, unable to be angry at my decisiveness but concerned for his best friend who was dying.",
    NEXT_PAGE};
const string GAME_PAGE_14_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_13_WORDS[2],
    "    \"Take a knee and pull security. If you ever do that again during a live fire I'll make sure you get kicked out of the Ranger battalion.\" Snapped my team leader.\n"
	"    The white light shone towards us and started waving erratically. Shouts could be heard bouncing through the trees.\n" 
	"    \"Let's go.\" The team leader stated.\n" 
	"    We ran through the trees, reaching the near lifeless body of Corporal Aimesbury.\n" 
	"    The team leader grabbed the litter off my back and performed the litter drill himself, telling me to get out of his way. My team leader treated me like dirt, unable to perform my duties under austere circumstances. But how was I supposed to know? I listened to him. He was wrong.",
    NEXT_PAGE};
const string GAME_PAGE_14_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_13_WORDS[3],
    "    \"You don't get to make the calls around here, Thiemann! It is a live fire, and it is training. Whatever trouble Aimesbury's team is having they will work through. The squad leader will give us a call and we will maneuver on the targets when Aimesbury is set.\" The team leader wisely responded.\n"
    "    Static came over radio, then a voice feverishly called for a stretcher bearer.\n"
    "    \"GO!\" The team leader screamed in my ear.\n"
    "    I ran towards the light as fast as I could, tripping and smashing my night vision into my face, but arriving as Aimesbury took his last breaths. I performed my litter drill under night vision, the team leader grabbed the heat blanket and opened it up once I had prepared the stretcher. I had known something was wrong. I should have acted sooner.\n",
    NEXT_PAGE};
const string GAME_PAGE_15_WORDS[TEXT_PAGE_TEXTURES] = {
    "    \"Stay with me, Aims!!\" The squad leader yelled.\n"
    "    Corporal Aimesbury was gushing blood at a rate which was unimaginable to my young mind while the senior medic worked on stopping the bleeding. The squad medic worked on sticking an IV port to push fluids and narcotics, but Corporal Aimesbury kept convulsing and it was nearly impossible to stick a vein. Finally, I watched him take his last breath. On December 9th, 2015, Corproal Andrew Aimesbury was pronounced dead upon arrival to the hospital. I watched my mentors and some of the hardest men I ever knew break down and cry.\n"
    "    Wanting help to process what I had just witnessed, I reached out to a mentor I had in high school who was an ex-Ranger, explaining what had happened.\n"
    "    He responded, \"I'm sorry for your loss... But that is good training.\"\n",
    "What is the point of all this suffering?"};
const string GAME_PAGE_16_WORDS[VERSE_PAGE_TEXTURES] = {
    "    In this you rejoice, though now for a little while, if necessary, you have been grieved by various trials, so that the tested genuineness of your faith - more precious than gold that perishes though it is tested by fire - may be found to result in praise and glory and honor at the revelation of Jesus Christ.\n"
    "    Though you have not seen him, you love him. Though you do not now see him, you believe in him and rejoice with joy that is inexpressible and filled with glory, obtaining the outcome of your faith, the salvation of your souls.",
    "-- 1 Peter 1: 6-9, ESV"};
const string END_CHAPTER_PAGE_WORDS[CHOICE_PAGE_TEXTURES] = {"You have finished the chapter, how will you continue?", 
    "Roll for health restoration", 
    "Roll for sanity restoration",
    "Roll for reputation increase"        };
const string GAME_PAGE_18_WORDS[QUOTATION_PAGE_TEXTURES] = {
    "Chapter 2: Afghanistan",
    "\"I offer neither pay, nor quarters, nor food; I offer only hunger, thirst, forced marches, battles and death. Let him who loves his country with his heart and not merely with his lips, follow me.\"\n", 
    "- Giuseppe Garibaldi"};
const string GAME_PAGE_19_WORDS[TEXT_PAGE_TEXTURES] = {
    "    \"Get off the bird and load the buses. We're taking you straight to the ready room, jam your magazines and prep your kit, you're going out tonight.\"\n" 
    "    Not 1 minute before the door had opened and a man left us with those words, the battalion had landed in Afghanistan. The battalion sergeant major and commander jumped off the C-130 with the man. It was my first deployment. I breathed deeply to keep my adrenaline from dumping before it was needed.\n"
    "    \"Is this normal?\" I asked my senior private.\n"
    "    \"No.\" He replied, eyes wide.\n"
    "    My adrenaline dumped. We rushed off the plane and jumped onto buses which were waiting on the runway. The gates were all up in preparation for our movement and we rushed straight through Bagram Airfield to Camp Alpha, the walled off special operations camp in the corner of the base. We quickly disembarked and I followed the crowd up a set of stairs to the ready room. My team leader for the deployment, Corporal Fausey, was on his third Afghanistan deployment at 22 years of age. He had partaken in the events which led to the awarding of Sergeant Anderson's valorous silver star. He was waving me to our team's corner of the ready room. \"Paranoid\" by Black Sabbath blasted through the room as team leaders gave orders and individuals loaded their magazines with the appropriate ammo.\n",
    NEXT_PAGE};
const string GAME_PAGE_20_WORDS[TEXT_PAGE_TEXTURES] = {
    "    As I arrived to my locker Corporal Fausey gave me the order, \"Pack 400 rounds armor piercing, 200 rounds armor piercing incendiary, then load your magazines. You have 4 minutes.\"\n"
    "    He turned back towards his own kit and locked a 200 rd. Drum of 7.62 armor piercing link into his MK48 machine gun. Every 100 rounds of linked 7.62mm ammunition weighs about 7 pounds. This meant for my first mission, I would have 42 pounds of ammunition, my body armor, helmet, my own combat loadout for the M4, a large thermal optic to spot targets, and my own food and water. When we weighed in for the helicopter, I had 110 total pounds of gear on.\n" 
    "    We loaded the Chinook helicopters, still not knowing what the mission was. The loadmaster briefed us in flight, using imagery from a drone to show us the objective.\n"
    "    \"Two professors from the college of Kabul have been kidnapped by the Taliban - Kevin King, an American - and Timothy Weeks, an Australian. Our mission is to get them back. The Taliban are currently moving with the two hostages through the desert by trucks. Our mission is to knock out the trucks, kill the Taliban, and rescue the hostages.\" Our platoon leader briefed.\n"
    "    Easy enough, I guess. He went through the positions of each of the squads and the other platoons once we hit the ground. The adrenaline was pumping and dudes had their game face on. I was too weighed down by my gear to want anything except to get to our firing position to lay down and take my backpack off. Instead, halfway to the target, the helicopters made a sharp bank and turned around. We had been called off the target by the Secretary of Defense, Ash Carter. He had opted to call in a more elite unit, SEAL Team 6, to perform the hostage rescue. This was probably a good idea, as I was still 18 years old and had never trained for a hostage rescue. By the time SEAL Team 6 arrived and executed the mission, it was a dry hole. The hostages had been snuck out of the target compound and were lost. There was no worse way to start a deployment.\n",
    NEXT_PAGE};
const string GAME_PAGE_21_WORDS[TEXT_PAGE_TEXTURES] = {
    "    Sometime later we got the call for our next mission, the second part in a legendary trilogy of missions known as operation \"Green Sword.\" The first piece of the mission had been executed by Bravo Company months earlier, and the operation was about dismantling a weapons smuggling ring led by Taliban and ISIL-K Insurgents. Their previous operation had yielded excellent results, with leaders of the smuggling ring being confirmed killed in an airstrike. For our piece, we were to kill or capture a lieutenant who was holed up on the mountainous border of Pakistan and Afghanistan in Paktiya Province. We wanted to get intelligence from the target, not airstrike him. So, we had to hike 16 kilometers through the mountains of Afghanistan to get to his house. Our Company Commander briefed us that the whole area was hostile, and even unarmed military aged males or non-compliant females could be considered combatants. On the way up, we received interim communications (ICOM) chatter from the Taliban which told us they were going to attempt to ambush us. Though brave, the Taliban were in grave danger after dusk in that valley.\n" 
    "    A vehicle approached us with its' headlights on. Under night vision, we had seen it approaching far before they would be able to see us, and the company took cover under the outcropping of a cliff. In a small ditch we laid trying to maintain the relative secrecy of 150 Rangers and partner forces. For such a considerable footprint, we managed to remain hidden. Once a weapon was positively identified inside the vehicle, 2 Apache helicopters performed gun runs, killing the men who wished to ambush us. Just in case, suppressed rifles opened fire for a short period as well.\n"
    "    \"Merica...\" Our platoon sergeant keyed through the radio, which I could only hear quietly through Corporal Fausey's headset.",
    NEXT_PAGE};
const string GAME_PAGE_22_WORDS[CHOICE_PAGE_TEXTURES] = {
    "In training, nothing had been overtly dangerous - other than the live rounds - which is to be expected during combat; however, I needed to traverse steep and slippery shale slopes up mountains to gain a position over the target compound. One misstep, and I would have tumbled thousands of feet to my death. The most senior members walked upright, straight up the mountain just like an Afghan goat would. Some members crawled. I decided to...",
    "scramble up the mountain on my hands and knees, clawing at any foothold or handhold to try not to fall with all of my heavy gear.\n",
    "look to my team leader and say, \"I can't make it. Take my bag of rounds, I'll wait for you at the release point.\"\n",
    "follow the example of the Afghan goat and feign confidence walking up the mountain.\n"};
const string GAME_PAGE_23_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = {
    GAME_PAGE_22_WORDS[1],
    "    I only fell a little bit, but it only cut up my hands and knees on the shale. I'm sure someone will make fun of me for it later but I got to my position.\n",
    NEXT_PAGE};
const string GAME_PAGE_23_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {
    GAME_PAGE_22_WORDS[2],
    "    Corporal Fausey looked at me sideways, initially thinking that I was joking. He grabbed my bag and shook his head, muttering expletives under his breath before telling the rest of the platoon about my course of action. The platoon sergeant came and ordered me up the mountain, and he half dragged me there since I would not comply. It was dangerous. Any normal person would have done the same in my shoes.\n",
    NEXT_PAGE};
const string GAME_PAGE_23_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {
    GAME_PAGE_22_WORDS[3],
    "    I took each step with terrifying anxiety. Finally, a piece of shale broke lose and I tumbled down the mountain, unable to slow my descent. Luckily, a tree was there to break my fall. I might have a concussion from the fall and made a ton of noise right outside the target compound. Also, I broke the $40,000 thermal optic mounted on my rifle. That was stupid. I began to fade out of consciousness but came back to a bright light shining in my eyes. Whether it was heaven or my night vision, I wasn't sure.\n",
    NEXT_PAGE};
const string GAME_PAGE_24_WORDS[TEXT_PAGE_TEXTURES] = {
    "    Somehow, no one else fell.\n"
    "    We set up overwatching the compound and watched the raid unfold. The assault point man moved towards the breach when a man stepped out of the house, AK-47 blazing into the night. He was promptly dispatched by the point man. An explosion detonated inside the compound and blew out the wall. The night had gone from smooth and controlled to unadulterated chaos.\n" 
    "    A young teenager stepped from the house, perhaps only 14, and shouted before detonating a suicide vest with no one nearby. Inside the house a dead woman was found near the impromptu explosion, along with miscellaneous Taliban paraphernalia. The assault team searched the house, grabbing cellphones and hard drives. The man which the team leader had killed was our target, and it was time to leave. As rapid as the operation had begun, it ended, and the night was back to being controlled, smooth, and serene. I slid from my overwatch position down the mountain with 110 pounds of gear.\n" 
    "    For the movement to extract, I was near the point man in the front of the formation. I watched the point man's infrared illuminator wave back and forth over the terrain, briefly stopping on a tent which sat on top of a spur directly above us. During this brief rest, I thought I saw 4 pixels in my night vision, like the top of someone's head, bob over the threshold of the tent entrance. I wasn't sure. The point man's laser kept scanning before I could find out. I stopped and took a knee, illuminating the tent with my own IR laser.\n",
    NEXT_PAGE};
const string GAME_PAGE_25_WORDS[CHOICE_PAGE_TEXTURES] = {
    "    \"Thiemann, keep up.\" Corporal Fausey hissed, thinking I was too tired and trying to take a break.\n"
    "    I readied my rifle, flipped my weapon to fire, and took a deep breath as I pulled the slack out of the trigger. Should I shoot through the tent? Would I be justified? I didn't have enough time to decide.\n",
    "    I squeeze the trigger. I am an Army Ranger, and I will not put my platoon in danger.\n",
    "    Disregard the orders of my team leader, place my weapon on fire but wait for the situation to develop.\n",
    "    It's my first real mission. I should just listen to my team leader and not lag behind. "};
const string GAME_PAGE_26_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = {
    GAME_PAGE_25_WORDS[1],
    "    The thump of my suppressed rifle bullets hitting the thick blankets which fashioned the tent penetrate the silence of the movement. The voice of a man cries out, and the squad next to me assaults up the spur towards the tent with automatic weapons and rifles, finishing off whatever I had started.\n" 
	"    \"Good kill, Thiemann.\" Corporal Fausey patted me on the back.\n" 
	"    But what if he was innocent?",
    NEXT_PAGE};
const string GAME_PAGE_26_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {
    GAME_PAGE_25_WORDS[2],
    "    A man came around the corner of the tent. Corporal Fausey saw my IR laser illuminate the man's chest. On the last ounce of strength to break the trigger, I stopped and let off. He was unarmed. An interpreter was brought up and he yelled at the man to go back inside.\n" 
    "    \"You shoot next time, Thiemann.\" Corporal Fausey instructed.\n"
    "    \"Roger, Corporal.\" I acknowledged, not needing an explanation.\n"
    "    He could have thrown a grenade or detonated an IED. Though the man ultimately lived that night, the risk was too high. He could have killed me or one of my friends.\n",
    NEXT_PAGE};
const string GAME_PAGE_26_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {
    GAME_PAGE_25_WORDS[3],
    "    \"I thought I saw something, corporal.\" I explained, not wanting to seem like I was tired.\n"
    "    Just then, there was commotion as men readied their rifles and yelled up towards the tent. The interpreter came and told the man to go back to sleep.\n"
    "    \"Thiemann, if you know something, which contradicts my orders, you should never second guess yourself.\" Corporal Fausey stated.\n"
    "    I would surely pay for this when I got back to base. How could I have put the platoon in danger because I was too scared to disobey orders? I anxiously walked, knowing what physical tortures awaited me when the mission ended. My mindset continued to put the team in danger as I could not focus on the mission.\n",
    NEXT_PAGE};
const string GAME_PAGE_27_WORDS[TEXT_PAGE_TEXTURES] = {
    "    As we continued the walk down the draw on the side of the mountain, into the valley, the leaders of the formation put up the hand sign for halt and get down. Wshhh, wshhh, wshhh...BOOM! BOOM! BOOM! The other side of the draw we were on was hit by the 40mm BOFORS cannon of the AC-130 circling overhead. Body parts went flying over the spur into our patrol. \n"
    "    \"Two guys were prepping frags to throw over here.\" Corporal Fausey relayed to me, intently listening to the radio.\n"
    "    As we continued movement, we heard more explosions from the AC-130, but too far off for us to stop the movement.",
    NEXT_PAGE};
const string GAME_PAGE_28_WORDS[CHOICE_PAGE_TEXTURES] = {
    "    We reached the bottom of the mountain and exited our draw into the valley below. The point man lased the ground. Two members of the Taliban lay splayed open, shredded apart by the gunship. We walked between the two bodies, stepping on the various fluids which soaked into the ground. I deliberately looked at each of those bodies, stopping to closely examine the seemingly indignant contortion of their bodies.\n",
    "    I will remember this forever.\n",
    "    It sucks to suck, bud.\n",
    "    Father, forgive them.\n"};
const string GAME_PAGE_29_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_28_WORDS[1],
    "I have come to terms with what I have seen. Though I will remember the bodies of these men which tried to kill me, I need not fear them any longer. Remembering this image is a spiritual form of respect to my enemies, despite the physical state of their being. I put two rounds in one body just to be sure he's dead. He groans, then explodes seconds later. Fortunately, the groaning man's mangled body shielded us mostly from the blast, but some debris hits me. We're alright, but a little shaken. Corporal Fausey shoots the other \"dead\" insurgent just to be sure.",
    NEXT_PAGE};
const string GAME_PAGE_29_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_28_WORDS[2],
    "The desecrated bodies of my enemies are worthless. They are evil, and I am good. Disregarding their humanity, I put a round in each of their heads to make sure they are dead. Even for Rangers, this is a callous act.",
    NEXT_PAGE};
const string GAME_PAGE_29_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_28_WORDS[3],
    "    Pretending to pull security, I knelt near the bodies just to say a prayer for their souls. Lord, if there is any way one can come to you after death, I pray that these men would - PING! A metallic pinging noise spikes my hair on end. The noise was familiar to me, but for the moment it remained yet unknown. My body screamed for me to move, but my mind held me in a milliseconds brief pause while it recalled memories to discern the noise.\n" 
    "    \"GRENADE!!!\" Corporal Fausey screamed.\n"
    "    It clicked in my mind. It was the sound of a spoon leaving the body of a fragmentation grenade. I got up and took two giant leaps before diving away, cutting myself on the shale. Fortunately, no one was injured and I was able to brush myself off and keep moving.\n",
    NEXT_PAGE};
const string GAME_PAGE_30_WORDS[TEXT_PAGE_TEXTURES] = {
    "    The last 8 kilometers to extract was uneventful, and a brutal slog. I am not proud to admit I found myself looking straight down at my feet, attempting to step on an IED to rid myself of the weight of my 110 pounds of gear forever. I was not successful, and we returned to base dehydrated and aching.\n"
    "    No missions I did after were any more eventful than this first one, though some not less. I felt as if I never fired my weapon in combat during my time in service with the US Military, though the platoon killed roughly 20 members of the Taliban in direct fire over the course of the deployment. After we returned, Corporal Fausey, a war hero in my eyes, fell into an intense bout of drinking and drug use. Despite this, he was honorably separated from the Army. Last I heard he had found sobriety at home and reprieve in running long distances. Though combat was a unique experience in many ways, it felt all too much like training. I was too proud for training.\n\n"
    "    Nonetheless, it would be another year of training and Ranger School before I got to deploy to Afghanistan the second time, where our mission was to train the Afghan special operations forces - not go out and kill the Taliban. It was time for me to get out of the military. The war was winding down, and I had missed my shot. 2nd Ranger Battalion, with my friends Ethan and Cameron Meddock, relieved 1st Ranger Battalion at the end of 2018, and I headed home without having the chance to see them.  I would stop chasing the elusive dragon of manhood through combat.\n",
    NEXT_PAGE};
const string GAME_PAGE_31_WORDS[CHOICE_PAGE_TEXTURES] = {
    "    Sitting in my barracks room, two days before leaving the military on January 17, 2019, I learned that Sergeant Cameron Meddock, was killed in action.\n",
    "    Why?",
    "    That could have been me.",
    "    Its always the good ones."};
const string GAME_PAGE_32_1_WORDS[POST_CHOICE_PAGE_TEXTURES] = { GAME_PAGE_31_WORDS[1],
    "    Who wouldn't ask why in this situation? God put us on this Earth, and I had every right to ask that question. The least of my worries were that Cameron was my good friend from basic training and RASP. He had married his fiancé just 3 months before the deployment, and she was already pregnant with their first child. Three months of marriage, and already widowed with their unborn daughter. She would carry the baby to term and raise it to know her father through numerous meetings with the 2nd Ranger Battalion, and the men who fought alongside Cameron that faithful night. It was fitting he would have had a daughter first. A daughter to go along with his Texas chivalry would have been the perfect complement to his personality.\n" 
    "    I went to the gym to try and shake my depression. It didn't work, but I crushed myself to the point of exhaustion. I drifted into a workout induced coma.\n", 
    NEXT_PAGE};
const string GAME_PAGE_32_2_WORDS[POST_CHOICE_PAGE_TEXTURES] = { GAME_PAGE_31_WORDS[2],
    "    It certainly could have been me, if I had just gotten married and my wife had our first child on the way. Only then could it have been 1/16th as sad as it was. But it wasn't me, and I didn't have a wife or a child on the way. It was a selfish thought. Cameron's brand-new wife, after only 3 months of marriage, had been widowed with their unborn daughter. She would carry the baby to term and raise it to know her father through numerous meetings with the 2nd Ranger Battalion, and the men who fought alongside Cameron that faithful night. It was fitting he would have had a daughter first. A daughter to go along with his Texas chivalry would have been the perfect complement to his personality.\n"
	"    I knocked out a set of pushups to ease the pain, but it didn't work. I grabbed a beer instead. It was going to be a long night.\n",
    NEXT_PAGE};
const string GAME_PAGE_32_3_WORDS[POST_CHOICE_PAGE_TEXTURES] = {GAME_PAGE_31_WORDS[3],
    "    Cameron was a good friend to me in RASP. Despite our differences, he was the one who would always uphold Christian virtue alongside the army standards. Not to mention, his moral code was impeccable. That was a man I wanted to emulate. Not only that, but he had married the love of his life just 3 months earlier and she was pregnant with their first child, a daughter. Cameron's widow would carry the baby to term and raise it to know her father through numerous meetings with the 2nd Ranger Battalion, and the men who fought alongside Cameron that faithful night. It was fitting he would have had a daughter first. A daughter to go along with his Texas chivalry would have been the perfect complement to his personality.\n" 
	"    I tried to sweat off my sadness in the gym. It didn't work, but I crushed myself anyways. When I got back I sat, unable to even fix my protein shake. Screw this. I grabbed a beer for the Airborne Ranger in the Sky.\n",
    NEXT_PAGE};
const string GAME_PAGE_33_WORDS[TEXT_PAGE_TEXTURES] = {
    "    Meddock made the second Ranger I had known that was killed in just a 1-year span. The first was another one of the best men I have ever known, Sergeant First Class Christopher Celiz, who was killed in action, leaving behind his wife and daughter. War simply took men of irreplaceable caliber from my life and added nothing - or so I believed. SFC Celiz was posthumously awarded the Medal of Honor, whatever consolation that was to his family or us who knew him.\n",
    "    Rangers Lead the Way"};
const string GAME_PAGE_34_WORDS[VERSE_PAGE_TEXTURES] = {
    "    \"'Absolute futility,' says the Teacher. 'Absolute futility. Everything is futile.' -- There is no remembrance of those who came before; and of those who will come after there will also be no remembrance by those who follow them.\"\n",
    " - Ecclesiastes 1: 2, 11 CSB"};
const string GAME_PAGE_36_WORDS[QUOTATION_PAGE_TEXTURES] = {"Epilogue",
    "    The desire for safety goes against every great and noble enterprise.\n\n",
    "- Tacitus"};
const string GAME_PAGE_37_WORDS[TEXT_PAGE_TEXTURES] = {
    "    The years drew on. My Christian walk became less new and more normal. As a single man living in absolute abundance, I couldn't help but to feel as if my life was not being used for its' correct purpose. Growing up, all I had ever wanted to do was be in the military. While in the military, all I ever wanted to do was get out. Now, I just found myself working an IT job – something neither I nor my family could have seen coming. It paid the bills and then some, but there was no point. My college degree in computing, though at a Baptist university, had little purpose outside of my classes related to the Bible. It was not the path I was meant to follow in life, and I was sure of it. Through fervent prayer and discernment that comes only through divine revelation, I concluded the experiences I have, and the expertise in soldiering could be put to good use elsewhere. Not only could it be put to good use, it was not Christian for me to leave those skills unused to follow a path along white picket fences and suburban households in the United States.\n" 
    "    Before following my call, questions nagged at the back of my mind. Did I ever really learn what it means to be a man? How would my Father feel to have poured his life's work into me just for me to go off and die in another war without having children? Could I overcome the insecurities of my youth to do good under austere circumstances? Would my character withstand the trials of combat without the discipline of the U.S. Military? I thought back to the decisions which I had made in my previous life.\n",
    "Was I a hero?"};
const string GAME_PAGE_38_HERO_WORDS[TEXT_PAGE_TEXTURES] = {
    "    My choices were morally upstanding. I have few regrets about anything I did. Those choices would made my Father proud, and certainly I was that much more of a man for it. Perhaps I was too much of an idealist though, not coping fully with the cynical realities with which humans are faced on this Earth. I would go on to fight in Ukraine, and many friends and family members would weep over my casket. I would certainly see them again in Heaven, but heroes don't get to live forever. My comrades would stand next to my casket and bury me with full military honors, dress uniforms, a 21-gun salute, and all the usual ceremonial proceedings. They may as well have been wearing Halloween costumes and dancing in a school play for all my parents cared. My parents would receive the folded flag of a foreign country in place of a daughter-in-law and grandchildren. They would have a nice medal, “Order of Bohdan Khemelnytsky” in place of their son. They would get a funeral instead of a wedding, a memorial placard with my name on Khreschatyk Street instead of decades spent with their son. Yet, against all hope, there was still the faith which remained in their hearts knowing I did what was right, and the promises of Christ to carry them to the end.\n",
        NEXT_PAGE};
const string GAME_PAGE_38_AVERAGE_WORDS[TEXT_PAGE_TEXTURES] = {
    "    My choices did not make me a hero. I was scared. My mind was cynical. I often went against the teachings of my father and the Bible. Nonetheless, my choices were rooted in reality and often prevented myself or others from needing to be heroes, which was a blessing. I was no hero, and I don't think I'll ever know what it takes to be one. God allows war on this Earth, so I know he has made provision for the despicable choices one must make in so doing. Executing a life sentence on a human for being in the wrong place at the wrong time may have saved my comrades, but it didn't feel good after the war ended and I thought about the life that individual might be living. Corporal Fausey's words stuck with me, and in Ukraine, I killed an unarmed man for non-compliance – shooting him in the back as he tried to run from our element. He might have called for artillery on us. Or he just might have been scared.\n" 
    "    I got married and had kids, but the forlorn choices I made due to temporal circumstances always left a rift between me and other humans, even my wife, children and my immediate family. They were very proud of what I had accomplished, yet thankful that I was not too morally upstanding. They considered me a hero, but I know who the heroes really are: Corporal Andrew Aimesbury, Sergeant First Class Christopher Celiz, Corporal Fausey, Olecksii Chubashev, Gregorii Tsekhmistrenko, and Daniel Swift, just to name a few.\n",
    NEXT_PAGE
    };
const string GAME_PAGE_38_4_AVERAGE_WORDS[TEXT_PAGE_TEXTURES] = {
    "    I stood at Gregorii's funeral in Kyiv, Ukraine. The longest I've ever had to stand at parade rest was while I listened to the shrieks of my best friend's mother as she stroked her son's putrefied face for the last time. Out of the corner of my unmoving gaze, his grandmother collapsed under the weight of seeing her dead grandson lying in a casket. Behind me, one of the best men to have ever walked this Earth lay still at room-temperature, his eyes shut forever. I stood at parade rest as a guard to his casket, a paltry offering for the man that he was when he was alive. In exchange for the radiant life of their son, I would instead stand in a military uniform which may as well have been a Halloween costume. They would get a funeral instead of grandchildren. They would get a folded flag instead of a daughter-in-law. Rather than joyous memories of Greg's future, they would be haunted ceaselessly by the memories of his past. These were the cynical realities of war. Though painful, I could always rely on the one who carried me through my darkest hours and allowed me to experience joy once again. And it was painful, but it was possible. My children grew up to know the character of such men, just as my father had taught me.\n",
    NEXT_PAGE};
const string GAME_PAGE_38_COWARD_WORDS[TEXT_PAGE_TEXTURES] = {
    "    My choices were mine to make, and many people would have done the same in my situation. I tried not to take sides and just stand up for myself. I don't need to prove myself to anyone, and my goal was just to get through alive. Perhaps the white picket fence life is for me, despite the calling I feel on my life. I'm sure I can show my children what it means to be a man, even though I don't try at it very hard. My lost friends were from another life, they wouldn't know who I have become. Though my relationship with my family suffered somewhat, I have many good friends and live a happy life. I don't need to go anywhere to prove anything. If the world doesn't do anything crazy, my life will continue in an abundance of material wealth and my focus can remain on my immediate family. The wars in Ukraine and Israel are far away and don't affect me. The closest I get to war these days is watching politics on the news. That's enough anxiety for me.\n",
    NEXT_PAGE};
const string GAME_PAGE_40_WORDS[POST_CHOICE_PAGE_TEXTURES] = {"Written, Developed, and Produced by Adam Thiemann", "In memory of fallen comrades", NEXT_PAGE};
const string GAME_PAGE_41_WORDS[TEXT_PAGE_TEXTURES] = {"Thank you for playing my game! please return to the main menu and take the survey.", "Return to main menu"};

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

//Timer variables
Timer timer;

//Choice Pages
ChoicePage choicePage(player, textures);

//Monitor data
SDL_DisplayMode dimensions;
Window dms;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Renderer + render class
SDL_Renderer* renderer;
Render render(textures, &dms);


//Event handler
SDL_Event e;

//Main loop flag
bool gaming = true;

//The current page variable so the game knows what to load.
int currentPage = -1;
int newPage = START_PAGE;
int chapterHolder = 0;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();
bool loadPlayerMedia(); //Load the player textures and fonts

//Frees media and shuts down SDL
void close();

//Event functions to determine what happens for different pages upon mouse
//events
void startPageEvents();
void mainMenuEvents();
void taskBarEvents();
void quotationPageEvents(int nextPage);
void textPageEvents(int nextPage);
void postChoicePageEvents(int nextPage);
void muteButtonEvents();
void outcomeEvents(int nextPage);
void versePageEvents();

int main( int argc, char* args[] ){
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
        /*EVENTS LOOP*/
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
                gaming = false;
            
            //User wants to mute/unmute the music
            muteButtonEvents();

            /*EVENTS SWITCH*/
            switch (currentPage)
            {
                case START_PAGE:
                    startPageEvents();
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
                    //Display normal outcome if not dead, or else restart the chapter.
                    if (!gamer.checkDeath())
                        outcomeEvents(choicePage.getStorePage());
                    else 
                        outcomeEvents(chapterHolder);
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
                case GAME_PAGE_16: //Verse Page
                    versePageEvents();
                    taskBarEvents();
                    break;
                case GAME_PAGE_17: // choice page end chptr
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case GAME_PAGE_18:
                    taskBarEvents();
                    quotationPageEvents(GAME_PAGE_19);                    
                    break;
                case GAME_PAGE_19:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_20);
                    break;
                case GAME_PAGE_20:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_21);
                    break;
                case GAME_PAGE_21:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_22);
                    break;
                case GAME_PAGE_22: //choice page
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case GAME_PAGE_23_1:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_24);
                    break;
                case GAME_PAGE_23_2:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_24);
                    break;
                case GAME_PAGE_23_3:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_24);
                    break;
                case GAME_PAGE_24:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_25);
                    break;
                case GAME_PAGE_25: //Choice Page Timer
                    taskBarEvents();
                    //Events in Render due to need to prevent event polling
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer, timer.isOut());
                    break;
                case GAME_PAGE_26_1:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_27);
                    break;
                case GAME_PAGE_26_2:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_27);
                    break;
                case GAME_PAGE_26_3:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_27);
                    break; 
                case GAME_PAGE_27:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_28);
                    break;
                case GAME_PAGE_28: //Choice Page
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case GAME_PAGE_29_1:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_30);
                    break;
                case GAME_PAGE_29_2:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_30);
                    break;
                case GAME_PAGE_29_3:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_30);
                    break;
                case GAME_PAGE_30:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_31);
                    break;
                case GAME_PAGE_31:
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case GAME_PAGE_32_1:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_33);
                    break;
                case GAME_PAGE_32_2:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_33);
                    break;
                case GAME_PAGE_32_3:
                    taskBarEvents();
                    postChoicePageEvents(GAME_PAGE_33);
                    break;
                case GAME_PAGE_33:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_34);
                    break;
                case GAME_PAGE_34:
                    versePageEvents();
                    taskBarEvents();
                    break;
                case GAME_PAGE_35:
                    taskBarEvents();
                    newPage = choicePage.choicePageEvents(currentPage, color, e, renderer);
                    break;
                case GAME_PAGE_36:
                    taskBarEvents();
                    quotationPageEvents(GAME_PAGE_37);
                    break;
                case GAME_PAGE_37:
                    taskBarEvents();
                    if (player->getRep() > 20)
                        textPageEvents(GAME_PAGE_38_HERO);
                    else if (player->getRep() > 10)
                        textPageEvents(GAME_PAGE_38_AVERAGE);
                    else 
                        textPageEvents(GAME_PAGE_38_COWARD);
                    break;
                case GAME_PAGE_38_HERO:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_39);
                    break;
                case GAME_PAGE_38_AVERAGE:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_38_4_AVERAGE);
                    break;
                case GAME_PAGE_38_COWARD:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_39);
                    break;
                case GAME_PAGE_38_4_AVERAGE:
                    taskBarEvents();
                    textPageEvents(GAME_PAGE_39);
                    break;
                case GAME_PAGE_39:
                    textPageEvents(GAME_PAGE_40);
                    break;
                case GAME_PAGE_40:
                    postChoicePageEvents(GAME_PAGE_41);
                    break;
                case GAME_PAGE_41:
                    textPageEvents(MAIN_MENU_PAGE);
                    break;
                default:
                    taskBarEvents();
                    break;
            /*END EVENTS BASED ON PAGE SWITCH STATEMENT*/
            }
        } /*END EVENTS LOOP*/

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

        /*RENDER SWITCH*/
        switch (currentPage)
            {
            case START_PAGE:
                render.startPageRenderer(renderer);
                break;
            case MAIN_MENU_PAGE:
                render.mainMenuRenderer(renderer);
                break;
            case TUTORIAL_PAGE:
                render.taskBarRenderer(renderer, TASKBAR);
                render.tutorialRenderer(renderer);
                break;
            case SURVEY_PAGE:
                break;
            case GAME_PAGE_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.quotationPageRenderer(renderer);
                break;
            case GAME_PAGE_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case OUTCOME_PAGE:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.outcomePageRenderer(renderer);
                break;
            case GAME_PAGE_3_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_3_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_3_3:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_6:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case GAME_PAGE_7_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_7_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_7_3:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_10:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case GAME_PAGE_11_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_11_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_11_3:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_13:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case GAME_PAGE_14_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_14_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_14_3:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_16:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.versePageRenderer(renderer);
                break;
            case GAME_PAGE_17:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case GAME_PAGE_18:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.quotationPageRenderer(renderer);
                break;
            case GAME_PAGE_22:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case GAME_PAGE_23_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_23_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_23_3:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_25:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                timer.timerEvents(); //Timer events outside of event loop
                newPage = choicePage.choicePageEvents(currentPage, color, e, renderer, timer.isOut());
                render.timerRenderer(renderer, timer.getTimerSprites(), timer.getTimerTexture(), timer.getSeconds());
                break;
            case GAME_PAGE_26_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_26_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_26_3:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_28:
                timer.setSeconds(10); //Reset the timer
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case GAME_PAGE_29_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_29_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_29_3:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_31:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case GAME_PAGE_32_1:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_32_2:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_32_3:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.postChoicePageRenderer(renderer);
                break;
            case GAME_PAGE_34: //Verse Page
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.versePageRenderer(renderer);
                break;
            case GAME_PAGE_35:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.choicePageRenderer(renderer, player, timer.isOut());
                break;
            case GAME_PAGE_36:
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.quotationPageRenderer(renderer);
                break;
            case GAME_PAGE_39:
                render.startPageRenderer(renderer);
                break;
            case GAME_PAGE_40:
                render.postChoicePageRenderer(renderer);
                break;
            default: //Default is for regular text pages
                render.taskBarRenderer(renderer, TASKBAR);
                render.playerBarRenderer(renderer, PLAYER_STATS);
                render.textPageRenderer(renderer);
                break;

        }
        /*End switch for rendering frames*/

        //Render the mute button on top of every frame
        render.muteButtonRenderer(playMusic, renderer, MUTE_BUTTON_SPRITES, &MUTE_BUTTON);

        //Update screen
        SDL_RenderPresent(renderer);
    }
	/*END GAME LOOP*/
	close();
	return 0;
}

bool init(){
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

bool loadMedia(){
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

    timer.loadTimer(renderer);

    //This is for loading the different page textures
    switch (newPage)
    {
        case START_PAGE:
            if(!textures[0].loadFromFile("resources/title_page.png", renderer, dms.w(), dms.h())){
                cout << "Failed to load title_page.png" << endl;
                return false;
            }
            textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[1].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[1].loadFromRenderedText(renderer, START_PAGE_WORDS, WHITE))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }  
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
                if (!textures[i].loadFromRenderedText(renderer, MAIN_MENU_WORDS[i], WHITE))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }  
            }
            break;
        case TUTORIAL_PAGE:
            if(!textures[0].loadFromFile("resources/tutorial.png", renderer, dms.w(), dms.h())) {
                cout << "Failed to load title_page.png" << endl;
                return false;
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
            //Check for death and insanity.
            if (gamer.checkDeath())
                OUTCOME_PAGE_WORDS.append("You have died a hero, but you are dead nonetheless.\n");
            else if (gamer.checkInsanity())
                OUTCOME_PAGE_WORDS.append("You have gone insane. \nYou will choose self-preservation at any cost. \nYour choices will impact your reputation.\n");
                
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
            //If the player is not dead
            if (!gamer.checkDeath())
            {
                if (!textures[1].loadFromRenderedText(renderer, "Continue", TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            else 
                if (!textures[1].loadFromRenderedText(renderer, "Restart Chapter", TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            break;
        case GAME_PAGE_3_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
                cout << "Cannot load choice page 13" << currentPage << endl;
            break;
        case GAME_PAGE_14_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
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
        case GAME_PAGE_17:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load END CHAPTER 1, pg " << currentPage << endl;
            break;
        case GAME_PAGE_18:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_18_WORDS[0], TAN, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_18_WORDS[i], TAN, dms.w() / 3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_19:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_19_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_20:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_20_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_21:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_21_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_22:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load choice page 22" << currentPage << endl;
            break;
        case GAME_PAGE_23_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_23_1_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_23_1_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_23_2:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_23_2_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_23_2_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_23_3:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_23_3_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_23_3_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_24:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_24_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_25:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load choice page 25" << currentPage << endl;
            break;
        case GAME_PAGE_26_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_26_1_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_26_1_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_26_2:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_26_2_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_26_2_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_26_3:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_26_3_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_26_3_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_27:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_27_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_28:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load choice page 28" << currentPage << endl;
            break;
        case GAME_PAGE_29_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_29_1_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_29_1_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_29_2:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_29_2_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_29_2_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_29_3:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_29_3_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_29_3_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_30:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_30_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_31:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load choice page 31" << currentPage << endl;
            break;
        case GAME_PAGE_32_1:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_32_1_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_32_1_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_32_2:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_32_2_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_32_2_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_32_3:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_32_3_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_32_3_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_33:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_33_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_34:
            for (int i = 0; i < VERSE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", QUOTATION);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_34_WORDS[i], TAN, dms.w() / 3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_35:
            if(!choicePage.loadMedia(renderer, newPage))
                cout << "Cannot load end chptr page " << currentPage << endl;
            break;
        case GAME_PAGE_36:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_36_WORDS[0], TAN, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_36_WORDS[i], TAN, dms.w() / 3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;

        case GAME_PAGE_37:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_37_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_38_HERO:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_38_HERO_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_38_AVERAGE:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_38_AVERAGE_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_38_COWARD:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_38_COWARD_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_38_4_AVERAGE:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_38_4_AVERAGE_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_39:
            if(!textures[0].loadFromFile("resources/end.png", renderer, dms.w(), dms.h())){
                cout << "Failed to load end.png" << endl;
                return false;
            }
            textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[1].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            //Load in the textures for rendering
            if (!textures[1].loadFromRenderedText(renderer, NEXT_PAGE, TAN, dms.w() / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
            break;
        case GAME_PAGE_40:
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                cout << "texture 0" << endl;
                return false;
            }
            if (!textures[0].loadFromRenderedText(renderer, GAME_PAGE_40_WORDS[0], GREY, dms.w() / 2.5))
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
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_40_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    cout << "word " << i  << endl;
                    return false;
                }
            }
            break;
        case GAME_PAGE_41:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, GAME_PAGE_41_WORDS[i], TAN, dms.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        default:
            for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
            {
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, NEXT_PAGE, TAN, dms.w() / 1.3))
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

void close(){
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

void startPageEvents(){
    if (textures[1].isMouseOver(textures[1].getRect())){
        textColor = RED;
        if(e.type == SDL_MOUSEBUTTONDOWN){
            newPage = MAIN_MENU_PAGE;
        }
    }
    else
        textColor = WHITE;
    textures[1].loadFromRenderedText(renderer, START_PAGE_WORDS, textColor);
}

void taskBarEvents(){
    for (int i = 0; i < TASKBAR_TEXTURES; i++)
    {
        if (TASKBAR[i].isMouseOver(TASKBAR[i].getRect())) {   
            textColor = RED;
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                switch (i){
                    case 0: 
                        newPage = MAIN_MENU_PAGE;
                        gamer.resetStats();
                        break;
                    case 1:
                        gaming = false;
                        break;
                    default:
                        break;
                }
            }
        }
        else
            textColor = GREY;
        TASKBAR[i].loadFromRenderedText(renderer, TASKBAR_WORDS[i], textColor);
    }
}

void mainMenuEvents(){
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
                            if(SDL_OpenURL("https://forms.gle/RVpN55ZaerSB3iWW8") == -1)
                                cout << "ERROR ON URL" << endl;
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
            chapterHolder = GAME_PAGE_1;
            break;
        case GAME_PAGE_18:
            chapterHolder = GAME_PAGE_18;
            break;
        case GAME_PAGE_35:
            chapterHolder = GAME_PAGE_36;
            break;
        default:
            break;
    }
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
            textures[2].loadFromRenderedText(renderer, textures[2].getWord(), textColor, dms.w()/3);
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
            if (gamer.checkDeath())
                gamer.resetStats();
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
    if (!gamer.checkDeath())
        textures[OUTCOME_PAGE_TEXTURES - 1].loadFromRenderedText(renderer, "Continue", textColor, dms.w()/1.3);  
    else
        textures[OUTCOME_PAGE_TEXTURES - 1].loadFromRenderedText(renderer, "Restart Chapter", textColor, dms.w()/1.3);  
}

void versePageEvents(){
    if (textures[VERSE_PAGE_TEXTURES - 1].isMouseOver(textures[VERSE_PAGE_TEXTURES - 1].getRect())){
        textColor = GREY;
        textures[VERSE_PAGE_TEXTURES - 1].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
        if(e.type == SDL_MOUSEBUTTONDOWN)
            newPage+=10;
    }
    else{
        textColor = WHITE;
        textures[VERSE_PAGE_TEXTURES - 1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
    }
    textures[VERSE_PAGE_TEXTURES - 1].loadFromRenderedText(renderer, textures[VERSE_PAGE_TEXTURES - 1].getWord(), textColor, dms.w()/1.3);
}



