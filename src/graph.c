
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

FILE *gfp;

void graph_init() {

	gfp = fopen(GRAPH_FILE, "w");

	if (!gfp) {
		printf("Failed to open graph file '%s'.\n", GRAPH_FILE);
		exit(-1);
	}

	fprintf(gfp, "var dot = \"dinetwork {node[shape=circle]; ");

}

void graph_fini() {

	fprintf(gfp, "}\";");

	fclose(gfp);

}

void graph_add(const char *parent, const char *child) {

	fprintf(gfp, "%s -> %s; ", parent, child);

}