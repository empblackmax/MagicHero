//用于字符串宏定义

//文件名+_NAME
//控件名不加后缀
//键值名+_KEY

//存储键值字符串
#define NEW_PLAYER_KEY							"new_player"
#define MUSIC_ENABLE_KEY						"music_enable"
#define EFFECT_ENABLE_KEY						"effect_enable"
#define UNLOCK_LEVEL_KEY						"level"
#define JEWEL_KEY								"jewel_count"
#define	GOLD_KEY								"gold_count"
#define MAX_HP_KEY								"player_hp"
#define MAX_MP_KEY								"player_mp"
#define SELECTEDBOW_KEY							"select_bow"

//MenuScene
#define MENUSCENE_CSB_NAME						"MenuScene/MenuScene.csb"
#define MENUSCENE_BGM_NAME						"raw/cover_bgm.mp3"
#define CLICKEFFECT_NAME						"raw/button_click.wav"

#define STARTBUTTON								"start"
#define ACCOUNTBUTTON							"account"
#define RANKINGBUTTON							"ranking"
#define MOREGAMEBUTTON							"more_game"
#define MUSICBUTTON								"music"
#define EFFECTBUTTON							"effect"

//GameScene
#define ARROWANDBOWFILE_CSV_NAME				"data/ArrowAndBow.csv"
#define GAMESCENE_CSB_NAME						"GameScene/GameScene.csb"
#define GAMEOVERLAYER_CSB_NAME					"GameScene/GameOverLayer/GameOverLayer.csb"
#define WARNINGLAYER_CSB_NAME					"GameScene/WarningLayer/WarningLayer.csb"
#define GAMESCENELOADLIST_NAME					"json/GameSceneLoadingFile.json"
#define BOWANDARROW_PLIST_NAME					"BowAndArrow/game2.plist"
#define ARROWTYPE_PLIST_NAME					"data/arrow.plist"
#define BOWTYPE_PLIST_NAME						"data/bow.plist"
#define MONSTERTYPE_PLIST_NAME					"data/monster.plist"
#define TEXTFONT_NAME							"ants.TTF"

#define GAMESCENE_BGM_NAME						"raw/game_bgm.mp3"
#define GAMEOVER_BGM_NAME						"raw/gameover_bgm.mp3"
#define ARROWSHOOT_EFFECT_NAME					"raw/arrow_shot.wav"
#define WALLBEHIT_EFFECT_NAME					"raw/wall_behit.wav"
#define MONSTERDEAD_EFFECT_NAME					"raw/monster_dead.wav"
#define UNLOCKBOW_EFFECT_NAME					"raw/button_upgrade.wav"
#define GOLDOVER_EFFECT_NAME					"raw/gold_over.wav"
#define STATEUPGRADE_EFFECT_NAME				"raw/gold_count.wav"

#define FIREARROWPARTICLE_NAME					"fireArrow.plist"
#define FINGERPARTICLE_NAME						"finger.plist"

#define ARROWFILENAME_KEY						"arrowframe_filename"
#define ARROWSPEED_KEY							"arrow_speed"
#define ARROWKNOCKBACK_KEY						"arrow_knockback"
#define ARROWRANGE_KEY							"arrow_range"
#define BOWFILENAME_KEY							"bowframe_filename"
#define BOWPOWER_KEY							"power"
#define BOWSPEED_KEY							"speed"
#define BOWMULTARROW_KEY						"multarrow"

#define BGLAYER									"backgoundLayer"
#define BG_2									"background2"
#define BG_3									"background3"
#define WALLNODE								"wallNode"
#define BOWPOSNODE								"BowPositionNode"
#define PANELLAYER								"panelLayer"
#define LEVELLABEL								"levelLabel"
#define JEWELLABEL								"jewelLabel"
#define GOLDLABEL								"goldLabel"
#define PROGRESS								"progress"
#define PAUSEBUTTON								"pauseButton"

#define BLOODPANEL								"bloodPanel"
#define BLOODBAR								"bloodBar"
#define BLOODLABEL								"bloodLabel"
#define MAGICBAR								"magicBar"
#define MAGICLABEL								"magicLabel"
#define FIREARROWBUTTON							"fire_arrow_button"
#define FREEZEBUTTON							"freeze_button"
#define LIGHTINGBUTTON							"lighting_button"
#define FREEZEEFFECT							"raw/ice_2.wav"
#define LIGHTINGEFFECT							"raw/lightning_1.wav"

#define PAUSELAYER								"pauseLayer"
#define RESUMEBUTTON							"resumeButton"
#define RETRYBUTTON								"retryButton"
#define HOMEBUTTON								"homeButton"

#define HPBAR									"HP_Bar"
#define MPBAR									"MP_Bar"
#define ATTACKBAR								"attack_Bar"
#define SHOOTSPEEDBAR							"shoot_speed_Bar"
#define MULTARROWBAR							"multarrow_Bar"
#define AIRSPEEDBAR								"airspeed_Bar"
#define KNOCKBACKBAR							"knock_back_Bar"
#define RANGEBAR								"range_Bar"

#define HPBUTTON								"HP_Button"
#define MPBUTTON								"MP_Button"
#define ATTACKBUTTON							"attack_Button"
#define SHOOTSPEEDBUTTON						"shoot_speed_Button"
#define MULTARROWBUTTON							"multarrow_Button"
#define AIRSPEEDBUTTON							"airspeed_Button"
#define KNOCKBACKBUTTON							"knock_back_Button"
#define RANGEBUTTON								"range_Button"

#define RETURNBUTTON							"go_back_menu"

#define GOLDICON_NAME							"GameScene/gold.png"
#define JEWELICON_NAME							"GameScene/jewel.png"
#define GETITEM_EFFECT_NAME						"raw/gold_over.wav"
#define GOLDCOUNT								20
#define JEWELCOUNT								1

//GameWinLayer
#define GAMEWIN_BGM_NAME						"raw/stagecomplete_bgm.mp3"
#define GAMEWINLAYER_CSB_NAME					"GameScene/GameWinLayer.csb"
#define WIN_TEXT								"win_text"
#define WIN_HOMEBUTTON							"win_home_button"
#define WIN_RETRYBUTTON							"win_retry_button"
#define WIN_NEXTBUTTON							"win_next_button"

//SelectScene
#define BOWBUTTON_PLIST_NAME					"SelectScene/bow_button.plist"
#define SELECTSCENE_CSB_NAME					"SelectScene/SelectScene.csb"
#define LOCKEDICON_NAME							"locked_icon.png"
#define UNSELECTICON_NAME						"unselect_icon.png"
#define GOLDTEXT								"goldText"
#define JEWELTEXT								"jewelText"
#define LEVELSELECTBUTTON						"level_select_button"
#define CONTINUE								"continue"
#define CLOSE									"close"

#define DEFAULT_BOW								"default"
#define SPEED_1_BOW								"speed_1"
#define SPEED_2_BOW								"speed_2"
#define SPEED_3_BOW								"speed_3"
#define MULTPLE_1_BOW							"multple_1"
#define MULTPLE_2_BOW							"multple_2"
#define MULTPLE_3_BOW							"multple_3"
#define POWER_1_BOW								"power_1"
#define POWER_2_BOW								"power_2"
#define POWER_3_BOW								"power_3"
#define DEMON_BOW								"demon"

#define BOW_LIST								{					\
													DEFAULT_BOW,	\
													MULTPLE_1_BOW,	\
													MULTPLE_2_BOW,	\
													MULTPLE_3_BOW,	\
													POWER_1_BOW,	\
													POWER_2_BOW,	\
													POWER_3_BOW,	\
													SPEED_1_BOW,	\
													SPEED_2_BOW,	\
													SPEED_3_BOW,	\
													DEMON_BOW		\
												}
#define PRESKILLS_LIST							{																\
													__Array::create(),											\
													__Array::createWithObject(__String::create(DEFAULT_BOW)),	\
													__Array::createWithObject(__String::create(MULTPLE_1_BOW)), \
													__Array::createWithObject(__String::create(MULTPLE_2_BOW)), \
													__Array::createWithObject(__String::create(DEFAULT_BOW)),	\
													__Array::createWithObject(__String::create(POWER_1_BOW)),	\
													__Array::createWithObject(__String::create(POWER_2_BOW)),	\
													__Array::createWithObject(__String::create(DEFAULT_BOW)),	\
													__Array::createWithObject(__String::create(SPEED_1_BOW)),	\
													__Array::createWithObject(__String::create(SPEED_2_BOW)),	\
													__Array::create()											\
												}
#define ICON_POSLIST							{\
													Vec2(100, 250), \
													Vec2(250, 150), \
													Vec2(400, 150), \
													Vec2(550, 150), \
													Vec2(250, 350), \
													Vec2(400, 350), \
													Vec2(550, 350), \
													Vec2(250, 250), \
													Vec2(400, 250), \
													Vec2(550, 250), \
													Vec2(700, 250)	\
												}

#define LEVELSELECTLAYER						"levelLayer"
#define BowSELECTLAYER							"bowLayer"
#define BOWSELECTBUTTON							"bow_select_button"

#define LEVELLOCKED_NAME						"SelectScene/locked_enable.png"
#define LEVELBUTTON_BG_NAME						"SelectScene/levelbutton_bg.png"
#define LEVELSTAR_NAME							"SelectScene/levelstar.png"
#define TOUCHEDEFFECT_NAME						"SelectScene/selected_icon.png"

//LoadingScene
#define LOADINGSCENE_CSB_NAME					"LoadingScene/LoadingScene.csb"
#define UNSELECTED_NAME							"SelectScene/unselect_icon.png"
#define LOADINGBAR								"LoadingBar"

//Enemy
#define ENEMY_BLOOD_NAME						"Game/enemy_blood.png"

#define DUYANGUAI_KEY							"duyanguai"
#define QUANJIGUAI_KEY							"quanjilao"
#define MANZUTU_KEY								"manzutu"
#define XIAOEMO_KEY								"xiaoemo"
#define YEMANSHOUREN_KEY						"yemanshouren"
#define JIELINGQISHI_KEY						"jielingqishi"

#define MONSTER_ATTACK_KEY						"monster_attacka"
#define MONSTER_HP_KEY							"monster_hp"
#define MONSTER_SPEED_KEY						"monster_speed"
#define MONSTER_KNOCKBACK_KEY					"knockback_resistance"
#define MONSTER_GIVENGOLD_KEY					"given_gold"
#define MONSTER_GIVENJEWEL_KEY					"given_jewel"

#define ATTACK_ANIMATE_KEY						"attack_animation"
#define DEATH_ANIMATE_KEY						"death_animation"
#define RUN_ANIMATE_KEY							"run_animation"
#define FREEZE_ANIMATE_KEY						"dong_animation"

#define ANIMATE_FRAME_NAME_KEY					"framename"
#define ANIMATE_FRAME_COUNT_KEY					"framecount"
#define PLISTFILENAME_KEY						"plistfilename"
#define TEXTUREFILENAME_KEY						"texturenfilename"

//Card
#define CARD_CSB_NAME							"GameScene/Card/CardNode.csb"
#define CARD_CSV_NAME							"data/Card.csv"
#define CARD_PLIST_NAME							"Plist/Card.plist"
#define CARD_PARTICLE_NAME						"particle_boom.plist"
#define CARDTOUCH_BUTTON						"button"
#define CARDIMAGE								"card"

//属性系数
#define POWER_COEFFICIENT(x)					(4 * x)
#define SHOOTSPEED_COEFFICIENT(x)				(10.0 / (4 * x + 5))
#define MULTARROW_COEFFICIENT(x)				(x)
#define AIRSPEED_COEFFICIENT(x)					(20 + 2 * x)
#define KNOCKBACK_COEFFICIENT(x)				(5 + x * 0.5)
#define RANGE_COEFFICIENT(x)					(0.15 * x)

