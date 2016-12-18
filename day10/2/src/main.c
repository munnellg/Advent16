#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOT    "bot"
#define OUTPUT "output"

#define TYPE_BOT    0
#define TYPE_OUTPUT 1

#define NBOTS       256
#define LABEL_SIZE    8
#define BUFFER_SIZE  64

struct bot {
	int lo, hi;
	int dest_lo, dest_hi;
	int type_lo, type_hi;
};

static struct bot g_bots[NBOTS]; 
static int g_output[NBOTS];

void
load_bot( int bot_id, int value ) {
	struct bot *bot;
	bot = &g_bots[bot_id];
	
	if( value > bot->hi ) {
		bot->lo = bot->hi;
		bot->hi = value;
	} else {
		bot->lo = value;
	}
}

void
init_edge( char *instruction ) {
	char lo_label[LABEL_SIZE];
	char hi_label[LABEL_SIZE];
	int  src_id, lo_id, hi_id;
	
  sscanf(instruction, "bot %d gives low to %s %d and high to %s %d",
				 &src_id, lo_label, &lo_id, hi_label, &hi_id
	);

	g_bots[src_id].dest_lo = lo_id;
	g_bots[src_id].dest_hi = hi_id;
	g_bots[src_id].type_lo = (strcmp(lo_label, BOT))? TYPE_OUTPUT : TYPE_BOT;
	g_bots[src_id].type_hi = (strcmp(hi_label, BOT))? TYPE_OUTPUT : TYPE_BOT;
}

void
init_bot( char *instruction ) {
	int value, bot_id;
	sscanf(instruction, "value %d goes to bot %d", &value, &bot_id);
	load_bot(bot_id, value);
}

int
update( int bot_id ) {
	struct bot *bot = &g_bots[bot_id];
	
	if( bot->lo && bot->hi ) {
		
		if( bot->type_lo == TYPE_BOT ) {
			update(bot->dest_lo);
			load_bot(bot->dest_lo, bot->lo);
		} else {
			g_output[bot->dest_lo] = bot->lo;
		}

		if( bot->type_hi == TYPE_BOT ) {
			update(bot->dest_hi);
			load_bot(bot->dest_hi, bot->hi);
		} else {
			g_output[bot->dest_hi] = bot->hi;
		}

		bot->lo = bot->hi = 0;
		return 0;
	}
	return 1;
}

int
step() {
	int i, stable;
	stable = 1;
	
	for( i=0; i<NBOTS; i++) {
		stable = stable && update(i);
	}

	return stable;
}

int
main( int argc, char *argv[] ) {
	FILE *f;
	int i;
	char buf[BUFFER_SIZE];
	
	if( argc < 2 ) {
		printf("Usage: ./d10p1 FILE\n");
		return EXIT_FAILURE;
	}

	f = fopen(argv[1],"r");

	if(!f) {
		printf("Unable to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	while( fgets(buf, BUFFER_SIZE, f) != NULL ) {
		switch(buf[0]) {
		case 'b':
			init_edge(buf);
			break;
		case 'v':
			init_bot(buf);
			break;
		}
	}

	fclose(f);

	while(!step());

	printf("%d\n", g_output[0]*g_output[1]*g_output[2]);
	
	return EXIT_SUCCESS;
}

